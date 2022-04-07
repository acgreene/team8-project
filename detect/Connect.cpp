#include "Particle.h"
#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include <SparkFun GridEYE Arduino Library.h>
#include <Wifi.h>
#include "Connect.h"

void Connect::init() {
	WiFi.mode(WIFI_STA);
	WiFi.config(clientIP, serverIP, subnet);
	WiFi.begin(ssid,password);
	while(WiFi.status() != WL_CONNECTED) {
		Serial.println("Attempting to connect to Server...\n");
		delay(500);
	}
	Serial.print("Wifi Connection Successful with IP: ");
	Serial.println(WiFi.localIP());
}

void Connect::send(char ctsn) {
	client.print(ctsn); //This should be a char but in clientConnection.ino ex is "s"
	client.print('\n');
	Serial.print("Sending: ");
	if(ctsn == '+') {
		Serial.println("count addition");
	}
	else if(ctsn == '-') {
		Serial.println("count detraction");
	}
	else {
		Serial.println("count reset");
	}
}

void Connect::receive() {
	unsigned long timeout = millis();
	while(client.available() == 0) {
		if(millis() - timeout > 500) {
			client.stop();
			break;
		}
	}
	while(client.available() > 0) {
		String stringFromServer = client.readStringUntil('\n');
		Serial.print(stringFromServer);
		//TODO: implement count reset from Server
	}
}

void Connect::reset() {
	client.print('r');
	client.print('\n');
	Serial.println("Resetting Count");
}

void Connect::setct(unsigned int ct) {
	char *intStr = itoa(ct);
	String ct = string(intStr);
	client.print('s');
	client.print(ct);
	client.print('\n');
	Serial.print("Setting count to: ");
	Serial.println(ct);
}