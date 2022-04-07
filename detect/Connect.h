#ifndef Connect_H
#define Connect_H

#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include <SparkFun GridEYE Arduino Library.h>
#include <Wifi.h>

class Connect{
public:
	void init();

	void send(char ctsn);

	void receive();

	void reset();

	//WiFiClient getClient();

	void setct(unsigned int ct);

private:
	IPAddress clientIP(192, 168, 10, 8);
	IPAddress serverIP(192, 168, 10, 0);
	IPAddress subnet(255, 255, 0, 0);
	const char *ssid = "team0008";
	const char *password = "Team_Gr8";
	WiFiClient client;
};


#endif