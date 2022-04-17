#include <WiFi.h>
#include <esp_task_wdt.h>

const char *ssid = "team0008";  // TODO: Fill in with team number
const char *password = "Team_Gr8";  // At least 8 chars


IPAddress local_IP(192, 168, 10, 0);
IPAddress gateway(192, 168, 11, 0);
IPAddress subnet(255, 255, 0, 0);

WiFiServer server(80);
int count = 0;

void setup() {
  Serial.begin(9600);

  // WiFi connection procedure
  WiFi.mode(WIFI_AP);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());
  
  server.begin();

  //watchdog timer with 3s period
  esp_task_wdt_init(3, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch
  
  Serial.println("Server started\n");

  // wait for background info
  bool received_background = false;
  bool received_noise = false;
  unsigned int background;
  unsigned int noise;
  while(!received_background and !received_noise){
    WiFiClient client = server.available();
    if (client){
      while (client.connected()){
        if (client.available()){
          String line = client.readStringUntil('\n');
          // Prints the received line to the serial terminal
          if(line[0] == 'b'){
            background = line.substring(1).toInt();
            received_background = true;
          }
          else if(line[0] == 'n'){
            noise = line.substring(1).toInt();
            received_noise = true;
          }
        }
      }
      client.stop();
    }
    delay(1);
    esp_task_wdt_reset();
  }
  Serial.print("Background Temp: ");
  Serial.println(background);
  Serial.print("Noise: ");
  Serial.println(noise);
}

void loop()
{
  WiFiClient client = server.available();
  if (client){
    while (client.connected()){
      if (client.available()){
        String line = client.readStringUntil('\n');
        // Prints the received line to the serial terminal
        if(line[0] == '-') --count;
        else if(line[0] == '+') ++count;
        else if(line[0] == 's') count = line.substring(1).toInt();
        Serial.println(count);
      }
    }
    client.stop();
  }
  delay(1);
  esp_task_wdt_reset();
}
