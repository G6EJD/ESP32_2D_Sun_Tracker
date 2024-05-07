
#include <WiFi.h>             // Built-in
#include <ESP32Servo.h>       // Sketch/Include Library/Manage Libraries/Search for ESP32Servo by Kevin Harrington - Install
#include <SolarCalculator.h>  // Sketch/Include Library/Manage Libraries/Search for SolarCalculator by jpb10 - Install
#include <TimeLib.h>

const char* ssid     = "yourSSID";
const char* password = "yourPASSWORD";

#define elevation_servo 5
#define azimuth_servo 2

double Lon = -2.14,
       Lat = 53.0,
       el,
       az,
       sun_elevation;

int    utc_offset;

String time_str;

Servo Azi_servo;
Servo Ele_servo;

void setup() {
  Serial.begin(115200);
  StartWiFi(ssid, password);
  StartTime();
  Azi_servo.attach(azimuth_servo);
  Ele_servo.attach(elevation_servo);
  test_azimuth();
  delay(1000);
  test_elevation();  // Stop at 145 which is vertical or 0 elevation
  delay(1000);
}

void loop() {
  time_t utc = now();
  calcHorizontalCoordinates(utc, Lat, Lon, az, el);
  sun_elevation = el;
  Serial.println("Az: " + String(az) + "  El: " + String(el));
  Azi_servo.write(map(az, 90, 270, 180, 0));  // Align to azimuth
  if (sun_elevation < 0) sun_elevation = 0;   // Point at horizon if less than horizon
  Ele_servo.write(145 - sun_elevation);       // map(value, fromLow, fromHigh, toLow, toHigh)
  delay(1 * 60 * 1000);                       // Wait 1-minute then check position again
  UpdateLocalTime();
}

////////////// WiFi, Time and Date Functions /////////////////
int StartWiFi(const char* ssid, const char* password) {
  int connAttempts = 0;
  Serial.print(F("\r\nConnecting to: "));
  Serial.println(String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (connAttempts > 20) {
      Serial.println("\nFailed to connect to a Wi-Fi network");
      return false;
    }
    connAttempts++;
  }
  Serial.print(F("\nWiFi connected at: "));
  Serial.println(WiFi.localIP());
  return true;
}

void StartTime() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
  setenv("TZ", "GMT0BST,M3.5.0/1,M10.5.0", 1);  // Change for your location
  //setenv("TZ", "<+06>-6>", 1);  // Change for your location //<+06>-6
  UpdateLocalTime();
}

void UpdateLocalTime() {
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo, 10000)) { // Wait for 10-sec for time to synchronise
    Serial.println("Failed to obtain time");
  }
  //See http://www.cplusplus.com/reference/ctime/strftime/
  char output[50];
  strftime(output, 50, "%a %b %d %Y  %H:%M:%S", &timeinfo);
  time_str = output;
  Serial.println(time_str);
  String H, M, S, Dy, Mn, Yr, TZ;
  strftime(output, 50, "%H", &timeinfo);
  H = output;
  strftime(output, 50, "%M", &timeinfo);
  M = output;
  strftime(output, 50, "%d", &timeinfo);
  Dy = output;
  strftime(output, 50, "%m", &timeinfo);
  Mn = output;
  strftime(output, 50, "%Y", &timeinfo);
  Yr = output;
  strftime(output, 50, "%z", &timeinfo);
  TZ = output;
  utc_offset = TZ.toInt();
  setTime(H.toInt(), M.toInt(), 0, Dy.toInt(), Mn.toInt(), Yr.toInt());
}

void test_azimuth() {
  Azi_servo.write(90);  // Centre position
  delay(500);
  Azi_servo.write(60);  // Centre position
  delay(500);
  Azi_servo.write(120);  // Centre position
  delay(500);
  Azi_servo.write(90);  // Centre position
  delay(500);
}

void test_elevation() {
  for (int a = 5; a < 145; a = a + 2) {
    Ele_servo.write(a);  // Centre position
    delay(30);
  }
  Ele_servo.write(145);  // Centre position
  delay(1000);
}