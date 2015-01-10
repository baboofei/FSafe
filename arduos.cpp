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
calcrawv (int read, int voltmax) {
	return read * voltmax / 1024;
}

int
calctemp (int rawv) {
	return 100 * rawv - 50;
}

const hwconf_t conf = {A0, 3, 4};

const int conf_temp = 30;

void
setup (void) {
	hwinit(conf);
	Serial.begin(9600);
}

void
loop (void) {
	delay(1000);

	hwreset(conf);

	int rawv = calcrawv(analogRead(A0), 5);
	int temp = calctemp(rawv);

	if(temp >= conf_temp)
	{
		digitalWrite(conf.pin_led_r, HIGH);
	}
	else
	{
		digitalWrite(conf.pin_led_g, HIGH);
	}
}
