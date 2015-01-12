#include "./arduino/Arduino.h"
#include "./arduino/HardwareSerial.h"

typedef struct {
	int pin_temp;
	int pin_led_r;
	int pin_led_g;
} hwconf_t;

void
hwinit (hwconf_t hw) {
	pinMode(hw.pin_temp, INPUT);
	pinMode(hw.pin_led_r, OUTPUT);
	pinMode(hw.pin_led_g, OUTPUT);
}

void
hwreset (hwconf_t hw) {
	digitalWrite(hw.pin_led_r, LOW);
	digitalWrite(hw.pin_led_g, LOW);
}

int
hwchck (hwconf_t hw) {
	/*
	 *	TODO: Implement: validate hardware configuration for potential problems
	 */

	#define HWCHCK_ERR_TEMPPINNOTANALOG -98
	#define HWCHCK_ERR_REPEATPIN -99

	if(hw.pin_temp == hw.pin_led_r || hw.pin_temp == hw.pin_led_g || hw.pin_led_r == hw.pin_led_g)
		return HWCHCK_ERR_REPEATPIN;

	int apins[6] = {A0, A1, A2, A3, A4, A5};
	int i;
	int isok = 0;

	for(i; i < 5; ++i)
		if(hw.pin_temp == apins[i])
			isok = 1;

	if(!isok)
		return HWCHCK_ERR_TEMPPINNOTANALOG;

	return 0;
}

float
calcrawv (float read, float voltmax) {
	return read * voltmax / 1023;
}

float
calctemp (float rawv) {
	return 100 * rawv - 50;
}

const hwconf_t conf = {A0, 3, 4};

const int conf_temp = 20;

void
setup (void) {
	if(hwchck(conf))
		for(;;){}

	hwinit(conf);
	Serial.begin(9600);
}

void
loop (void) {
	delay(1000);

	hwreset(conf);

	float rawv = calcrawv(analogRead(A0), 5);
	float temp = calctemp(rawv);

	if(temp >= conf_temp)
	{
		digitalWrite(conf.pin_led_r, HIGH);
	}
	else
	{
		digitalWrite(conf.pin_led_g, HIGH);
	}
}
