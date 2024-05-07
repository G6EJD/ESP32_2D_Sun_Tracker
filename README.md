# ESP32_2D_Sun_Tracker
An ESP32 calculates sun position using LAT, LON, Date-Time then sets Azimuth and Elevation servos in a gimbal

1. Change the WiFi SSID and PASSWORD
2. Set your LAT and LON
3. Set your time zone
4. Adjust your gimbal so that the elevation servo's minimum throw results in a horizontal platform.
5. Adjust your gimbal so that the azimuth servo's half-way throw results in a vertical direction (half the total travel).
6. Ensure time is not in DST or the alignment will be out.

7. Typical serial port output:
8. 
Connecting to: SSID
...
WiFi connected at: 192.168.0.57
Tue May 07 2024  20:10:06
Az: 305.06  El: -3.54
Tue May 07 2024  20:11:13
Az: 305.24  El: -3.65

Setup:
1. Download the source code
2. Enter your WiFI SSID and PAASSWORD
3. Enter your location:
4. double Lon = -2.14,
          Lat = 53.0,
5. Enter your TimeZone
   Find your location in the central database, nearest will do: https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
   Modify the time zone setenv("TZ", "GMT0BST,M3.5.0/1,M10.5.0", 1);  // Change for your location
6. Compile and upload, check select Tools, Serial Monitor then speed is 115200, then monitor for whe WiFi is connected, that time is correct, then values are being displayed.  
