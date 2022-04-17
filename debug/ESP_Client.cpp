#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <WiFi.h>
#include "Connect.h"

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

//void Client::send(char ctsn) {
//	client.print(ctsn); //This should be a char but in clientConnection.ino ex is "s"
//	client.print('\n');
//	Serial.print("Sending: ");
//	if(ctsn == '+') {
//		Serial.println("count addition");
//	}
//	else if(ctsn == '-') {
//		Serial.println("count detraction");
//	}
//	else {
//		Serial.println("count reset");
//	}
//}

//void Client::receive() {
//	unsigned long timeout = millis();
//	while(client.available() == 0) {
//		if(millis() - timeout > 500) {
//			client.stop();
//			break;
//		}
//	}
//	while(client.available() > 0) {
//		String stringFromServer = client.readStringUntil('\n');
//		Serial.print(stringFromServer);
//		//TODO: implement count reset from Server
//	}
//}

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
