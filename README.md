# ESP32_2D_Sun_Tracker
An ESP32 calculates sun position using LAT, LON, Date-Time then sets Azimuth and Elevation servos in a gimbal

1. Change the WiFi SSID and PASSWORD
2. Set your LAT and LON
3. Set your time zone
4. Adjust your gimbal so that the elevation servo's minimum throw results in a horizontal platform.
5. Adjust your gimbal so that the azimuth servo's half-way throw results in a vertical direction (half the total travel).
6. Ensure time is not in DST or the alignment will be out.
