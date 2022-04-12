#include <WiFi.h>

// TODO: Match SSID and password with server
const char *ssid = "team0008";
const char *password = "Team_Gr8";

// TODO: update last number of clinetIP with team number
IPAddress clientIP(192, 168, 10, 8);
IPAddress serverIP(192, 168, 10, 0);
IPAddress subnet(255, 255, 0, 0);

void setup() {
  Serial.begin(115200);

  // WiFi connection procedure
  WiFi.mode(WIFI_STA);
  WiFi.config(clientIP, serverIP, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect...\n");
    delay(500);
  }
  Serial.print("WiFi connection successful with IP ");
  Serial.println(WiFi.localIP());
}

unsigned long previous_time = 0;
unsigned long timeout = 2000;  // 2 seconds delay

void loop() {
  double send_time = 0;
  for (int i = 0; i < 100; ++i){
    unsigned long start_time = millis();
    WiFiClient client;
    while (!client.connect(serverIP, 80)) 
    {
      Serial.println("Connection to server failed");
      if(WiFi.status() != WL_CONNECTED)
      {
        Serial.println("Wifi Disconnected; attempting to reconnect.");
        WiFi.disconnect();
        WiFi.begin(ssid, password);
      }
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to reconnect...\n");
        delay(500);
      }
      Serial.print("WiFi reconnection successful with IP ");
      delay(1000);
    }
//    client.print("+");
    client.print("s");
    client.print(i);
    client.print('\n');  // Manually send newline because println sends "\r\n"
//    Serial.print("Sending: ");
//    Serial.println(i);
    
    //wait and see if we get a line from the server
//    unsigned long timeout = millis();
//    while (client.available() == 0) {
//      if (millis() - timeout > 500) {
//        client.stop();
//        break;
//      }
//    }
//    while (client.available() > 0)
//    {
//      String stringFromServer = client.readStringUntil('\n');
//      //TODO: implement: reset count if the line equals "r"   
//    }
//    delay(1000);
    client.stop();  
    unsigned long end_time = millis();
    send_time += end_time - start_time;
    delay(10);
  }
  send_time /= 100.0;
  Serial.print("Average Time to Send Packet: ");
  Serial.println(send_time);
}
