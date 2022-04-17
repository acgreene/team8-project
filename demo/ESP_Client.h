#ifndef Connect_H
#define Connect_H

#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include "Detector.h"
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <WiFi.h>

class ESP_Client{
public:
	void init();

  void increment_count();

  void decrement_count();

	void reset();

	void set_count(unsigned int ct);

  void send_background(double background, double noise);
private:
  const char *ssid = "team0008";
  const char *password = "Team_Gr8";
	IPAddress clientIP = IPAddress(192, 168, 10, 8);
	IPAddress serverIP = IPAddress(192, 168, 10, 0);
	IPAddress subnet = IPAddress(255, 255, 0, 0);
};

#endif
