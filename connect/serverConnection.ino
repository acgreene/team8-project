#include <WiFi.h>
#include <esp_task_wdt.h>
const int BUTTON_PIN = 0;

const char *ssid = "team0008";  // TODO: Fill in with team number
const char *password = "Team_Gr8";  // At least 8 chars


IPAddress local_IP(192, 168, 10, 0);
IPAddress gateway(192, 168, 11, 0);
IPAddress subnet(255, 255, 0, 0);

WiFiServer server(80);
int32_t count = 0;

void setup() {
  Serial.begin(115200);

  // Built-in button, active low
  pinMode(BUTTON_PIN, INPUT);

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
}

void loop()
{
  WiFiClient client = server.available();
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        // Prints the received line to the serial terminal
        if(line[0] == '-') --count;
        else if(line[0] == '+') ++count;
        else if(line[0] == 's') count = line.substring(1).toInt();
        Serial.print("Updated count: ");
        Serial.println(count);
      }
      if (!digitalRead(BUTTON_PIN))
      {
        //software debouncing (if button is still pressed 100ms later, we conisder it valid)
        delay(100);
        if (!digitalRead(BUTTON_PIN))
        {
          client.print("r\n");
          Serial.println("Client reset!");
          delay(400);
        }      
      }
    }
    client.stop();
  }
  delay(10);
  esp_task_wdt_reset();
}
