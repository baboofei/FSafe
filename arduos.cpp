#include "./arduino/Arduino.h"
#include "./arduino/HardwareSerial.h"

#define   CONF_TEMP_THREASHOLD_STATIC     25
#define   CONF_TEMP_THREASHOLD_USEDYNC    0
#define   HWCHCK_ERR_TEMPPINNOTANALOG    -98
#define   HWCHCK_ERR_REPEATPIN           -99

typedef struct {
	int pin_temp;
	int pin_led_r;
	int pin_led_g;
} hwconf_t;

void
hwinit (hwconf_t hw) {
	Serial.begin(9600);

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

	if(hw.pin_temp == hw.pin_led_r || hw.pin_temp == hw.pin_led_g || hw.pin_led_r == hw.pin_led_g)
		return HWCHCK_ERR_REPEATPIN;

	int apins[6] = {A0, A1, A2, A3, A4, A5};
	int i;
	int isok = 0;

	for(i = 0; i < 5; ++i)
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

const int conf_temp = CONF_TEMP_THREASHOLD_STATIC;

void
setup (void) {
	if(hwchck(conf))
		for(;;){digitalWrite(13, !digitalRead(13));}

	hwinit(conf);
}

void
loop (void) {
	static int is_rotten = 0;

	delay(1000);

	hwreset(conf);

	float rawv = calcrawv(analogRead(A0), 5);
	float temp = calctemp(rawv);

	Serial.println(temp);

	if(temp >= conf_temp || is_rotten)
	{
		digitalWrite(conf.pin_led_r, HIGH);

		is_rotten = 1;
	}
	else
	{
		digitalWrite(conf.pin_led_g, HIGH);
	}
}
