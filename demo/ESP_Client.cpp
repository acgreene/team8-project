#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include "Detector.h"
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <WiFi.h>
#include "ESP_Client.h"

void ESP_Client::init() {
	WiFi.mode(WIFI_STA);
	WiFi.config(clientIP, serverIP, subnet);
	WiFi.begin(ssid, password);
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
	}
}


void ESP_Client::increment_count(){
   WiFiClient client;
   while (!client.connect(serverIP, 80)) 
    {
      if(WiFi.status() != WL_CONNECTED)
      {
        WiFi.disconnect();
        WiFi.begin(ssid, password);
      }
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
      }
      delay(1000);
    }
    client.print("+");
    client.stop();
}

void ESP_Client::decrement_count(){
  WiFiClient client;
   while (!client.connect(serverIP, 80)) 
    {
      if(WiFi.status() != WL_CONNECTED)
      {
        WiFi.disconnect();
        WiFi.begin(ssid, password);
      }
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
      }
      delay(1000);
    }
    client.print("-");
    client.stop();
}

void ESP_Client::reset() {
  WiFiClient client;
   while (!client.connect(serverIP, 80)) 
    {
      if(WiFi.status() != WL_CONNECTED)
      {
        WiFi.disconnect();
        WiFi.begin(ssid, password);
      }
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
      }
      delay(1000);
    }
	client.print('r');
	client.print('\n');
  client.stop();
//	Serial.println("Resetting Count");
}

void ESP_Client::set_count(unsigned int count) {
 WiFiClient client;
 while (!client.connect(serverIP, 80)){ 
    if(WiFi.status() != WL_CONNECTED)
    {
      WiFi.disconnect();
      WiFi.begin(ssid, password);
    }
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    delay(1000);
  }
	client.print("s");
	client.print(count);
	client.print('\n');
  client.stop();
}
void ESP_Client::send_background(double background, double noise) {
 WiFiClient client;
 while (!client.connect(serverIP, 80)){ 
    if(WiFi.status() != WL_CONNECTED)
    {
      WiFi.disconnect();
      WiFi.begin(ssid, password);
    }
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    delay(1000);
  }
  client.print("b");
  client.print(background);
  client.print('\n');
  delay(2000);
  client.print("n");
  client.print(noise);
  client.print('\n');
  client.stop();
}
