#ifndef __LEDS_H__
#define __LEDS_H__

#include "MKL05Z4.h"

#define RED		0
#define GREEN	1
#define BLUE 	2 


void initLed(void);

void blinkLeds(void);

void ledOn(uint8_t color);

void ledBlink(uint8_t color, uint8_t count);

void ledOff(void);

#endif /* __LEDS_H__ */

