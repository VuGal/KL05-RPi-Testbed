#ifndef gpio_h
#define gpio_h

#include "stdbool.h"
#include "inttypes.h"

typedef enum {
	Port_A, Port_B
} GPIOPort;

typedef struct gpioPin {
	const GPIOPort port;
	const uint8_t pinNumber;
} GPIOPin;	

void gpioInitialize(void);
void gpioSwitchAllPinsToInputs(void);
void gpioSwitchAllPinsToOutputs(void);
char* gpioGetInputStates (void);
char* gpioGetOutputStates (void);
void gpioSetOutputStates (bool states[22]);

#endif
