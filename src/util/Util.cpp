#include <ArduinoJson.h>
#include "Util.h"
#include "module/BMP180.h"
#include "module/DHT11.h"
#include "module/GP2Y10.h"

void Util::encodeAndSendJsonData(String name, String ver)
{
	DynamicJsonBuffer jsonBuffer;
	JsonObject &root = jsonBuffer.createObject();
	root["fw_name"] = name;
	root["fw_ver"] = ver;
	root["uptime"] = millis();

	JsonArray &sensorData = root.createNestedArray("sensors");
	BMP180::addJsonData(sensorData);
	DHT11::addJsonData(sensorData);
	GP2Y10::addJsonData(sensorData);

	root.printTo(Serial);
	Serial.println();
}

String Util::getUptime()
{
	long time = millis() / 1000;
	int seconds = floor(time % 60);
	int minutes = 0;
	int hours = 0;
	int days = 0;
	long aDay = 86400L;
	if (time >= 60)
	{
		minutes = floor((time % 3600) / 60);
		if (time >= 3600)
		{
			hours = floor((time % aDay) / 3600);
			if (time >= aDay)
			{
				days = floor(time / aDay);
			}
		}
	}
	String uptime = (minutes != 0 ? (hours != 0 ? (days != 0 ? (String(days) + " d ")
															 : "") +
													  (String(hours) + " h ")
												: "") +
										(String(minutes) + " m ")
								  : "") +
					(String(seconds) + " s");
	return uptime;
}