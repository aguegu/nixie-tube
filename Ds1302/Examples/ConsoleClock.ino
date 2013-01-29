// Do not remove the include below
#include "Ds1302Test.h"
#include "Ds1302.h"
#include "DigitalTubeDisplay.h"

#define SET_TIME 1
#define SET_DATE 2

const String COMMAND_HI = "hi\n";
const String COMMAND_TIME = "time\n";
const String COMMAND_DATE = "date\n";
const String COMMAND_NOW = "now\n";
const String NOTE_HI =
		"Hi, this is ArduClock1302, \n"
				"designed by Weihong Guan (aguegu). \n"
				"You may try commands \"time\" and \"Date\" to get/set the time/date. \n"
				"Command \"Now\" to show current time, Date.\n"
				"Enjoy.\n";

Ds1302 ds(A3, A2, A1, A0, A4);
//Ds1302(uint8_t pin_sclk, uint8_t pin_io, uint8_t pin_rst, uint8_t pin_vcc = 255, uint8_t pin_gnd = 255);
DigitalTubeDisplay dtd(2, 11, 12, 9, 3, 13, 10, 6, 5, 4, 8, 7);

extern HardwareSerial Serial;
bool cmd_eof = false;
String str_tmp = "";
char s[64];
byte setting = 0;

void setTimeByString();
void setDateByString();

void setup()
{
	ds.setWritable(true);
	ds.setCharger();
	ds.halt(false);
	ds.setWritable(false);

	ds.refresh(false);

	Serial.begin(9600);
}

void loop()
{
	ds.refresh(true);
	if (ds.getSecond() & 0x01)
		dtd.setPointAt(2);
	else
		dtd.setPointAt(-1);

	dtd.printUIntInHex((ds.getHour() << 8) + ds.getMinute(), 0x10, 3);

	if (cmd_eof)
	{
		//Serial.print(str_tmp);
		if (str_tmp.equalsIgnoreCase(COMMAND_HI))
			Serial.print(NOTE_HI);
		else
		{
			if (str_tmp.equalsIgnoreCase(COMMAND_TIME))
			{
				snprintf(s, 64,
						"\nCurrent Time: %02x:%02x:%02x\nSet Time (HH:MM:SS)>",
						ds.getHour(), ds.getMinute(), ds.getSecond());
				setting = SET_TIME;
				Serial.print(s);
			}
			else if (str_tmp.equalsIgnoreCase(COMMAND_DATE))
			{
				snprintf(
						s,
						64,
						"\nCurrent Date:  %02x/%02x/%02x, %d\nSet Date (MM/DD/YY, W):",
						ds.getMonth(), ds.getDate(), ds.getYear(),
						ds.getWeekday());
				setting = SET_DATE;
				Serial.print(s);
			}
			else if (str_tmp.equalsIgnoreCase(COMMAND_NOW))
			{
				snprintf(s,	64,
						"\nNow: %02x:%02x:%02x, %02x/%02x/%02x, %d.\n",
						ds.getHour(), ds.getMinute(), ds.getSecond(),
						ds.getMonth(), ds.getDate(), ds.getYear(),
						ds.getWeekday());
				Serial.print(s);
			}
			else
			{
				switch (setting)
				{
				case SET_TIME:
					setTimeByString();
					break;
				case SET_DATE:
					setDateByString();
					break;
				}
				setting = 0;
			}
		}
		str_tmp = "";
		cmd_eof = false;
	}
}

void serialEvent()
{
	while (Serial.available() > 0)
	{
		char cData = Serial.read();
		str_tmp.concat(cData);

		if (cData == 0x0a)
			cmd_eof = true;
	}
}

byte string2byte(String s)
{
	byte value;
	if (s.length() == 2)
		value = ((byte) s.charAt(0) - 0x30) * 10 + ((byte) s.charAt(1) - 0x30);
	else
		value = (byte) s.charAt(s.length() - 1) - 0x30;
	return value;
}

void setTimeByString()
{
	if (setting == 0)
		return;

	byte hour, minute, second;

	if (str_tmp.length() == 9)
	{
		hour = string2byte(str_tmp.substring(0, 2));
		minute = string2byte(str_tmp.substring(3, 5));
		second = string2byte(str_tmp.substring(6, 8));
		snprintf(s, 64, "\n%02d:%02d:%02d saved.\n", hour, minute, second);
		ds.setTime(hour, minute, second);
		Serial.print(s);
	}

	else if (str_tmp.length() == 1)
		Serial.print("\nIgnore. No change made.");
	else
		Serial.print("\nIncorrect pattern. should be HH:MM:SS.");

	setting = 0;
}

void setDateByString()
{
	if (setting == 0)
		return;

	byte month, day, year, weekday;
	if (str_tmp.length() == 12)
	{
		month = string2byte(str_tmp.substring(0, 2));
		day = string2byte(str_tmp.substring(3, 5));
		year = string2byte(str_tmp.substring(6, 8));
		weekday = string2byte(str_tmp.substring(10, 11));
		snprintf(s, 64, "\n%02d/%02d/%02d, %d saved.\n", month, day, year,
				weekday);
		ds.setDate(year, month, day, weekday);
		Serial.print(s);
	}
	else if (str_tmp.length() == 1)
		Serial.print("\nIgnore. No change made.");
	else
		Serial.print("\nIncorrect pattern. should be MM/DD/YY, W");

	setting = 0;
}

