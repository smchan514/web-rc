# web-rc: TV Remote Control via a Web Server

This PlatformIO prototype creates a TV Remote Control via a Web Server hosted on an ESP32:

 1. Connect to local Wi-Fi network using SSID and password stored in a data partition
 2. Provide visual feedback on Wi-Fi connection status via RGD LED built-in on the ESP32
 3. Once Wi-Fi connection established, expose a Web server accessible on the local network
 4. Implement IR transmission signaling via external IR LED
 5. Respond to HTTP API calls to trigger IR commands
