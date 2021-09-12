#include "MKL05Z4.h"
#include "stdbool.h"
#include "gpio.h"
#include "uart.h"


const static uint8_t GPIO_COUNT = 20;


const static GPIOPin gpioPinsArray[20] = {

	{Port_A, 11},  // D2 pin (PTA11)
	{Port_B, 5},   // D3 pin (PTB5)
	{Port_A, 10},  // D4 pin (PTA10)
	{Port_A, 12},  // D5 pin (PTA12)
	{Port_B, 6},   // D6 pin (PTB6)
	{Port_B, 7},   // D7 pin (PTB7)
	{Port_B, 10},  // D8 pin (PTB10)
	{Port_B, 11},  // D9 pin (PTB11)
	{Port_A, 5},   // D10 pin (PTA5)
	{Port_A, 7},   // D11 pin (PTA7)
	{Port_A, 6},   // D12 pin (PTA6)
	{Port_B, 0},   // D13 pin (PTB0)
	{Port_B, 4},   // D14 pin (PTB4)
	{Port_B, 3},   // D15 pin (PTB3)

	{Port_B, 8},   // A0 pin (PTB8)
	{Port_B, 9},   // A1 pin (PTB9)
	{Port_A, 8},   // A2 pin (PTA8)
	{Port_A, 0},   // A3 pin (PTA0)
	{Port_A, 9},   // A4 pin (PTA9)
	{Port_B, 13}   // A5 pin (PTB13)

};


void gpioInitialize(void) {
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	for (int i = 0; i < GPIO_COUNT; ++i) {

		if (gpioPinsArray[i].port == Port_A)
			PORTA->PCR[gpioPinsArray[i].pinNumber] = PORT_PCR_MUX(1);
		else
			PORTB->PCR[gpioPinsArray[i].pinNumber] = PORT_PCR_MUX(1);
		
	}
	
}


void gpioSwitchAllPinsToInputs(void) {
	
	for (int i = 0; i < GPIO_COUNT; ++i) {

		if (gpioPinsArray[i].port == Port_A)
			PTA->PDDR &= ~( 1UL << (gpioPinsArray[i].pinNumber) );
		else
			PTB->PDDR &= ~( 1UL << (gpioPinsArray[i].pinNumber) );
		
	}
	
}


void gpioSwitchAllPinsToOutputs(void) {
	
	for (int i = 0; i < GPIO_COUNT; ++i) {

		if (gpioPinsArray[i].port == Port_A)
			PTA->PDDR |= ( 1UL << (gpioPinsArray[i].pinNumber) );
		else
			PTB->PDDR |= ( 1UL << (gpioPinsArray[i].pinNumber) );
		
	}
	
}


char* gpioGetInputStates (void) {
	
	char gpioState[2] = "";
	char states[40] = "";
	
	for (int i = 0; i < GPIO_COUNT; ++i) {
			
		if (gpioPinsArray[i].port == Port_A)
			gpioState[0] = (char)((PTA->PDIR << (31-gpioPinsArray[i].pinNumber)) >> 31) + 48;
		else
			gpioState[0] = (char)((PTB->PDIR << (31-gpioPinsArray[i].pinNumber)) >> 31) + 48;
		
		strcat(states, &gpioState);
	
	}
	
	return states;
		
}


char* gpioGetOutputStates (void) {
	
	char gpioState[2] = "";
	char states[40] = "";
	
	for (int i = 0; i < GPIO_COUNT; ++i) {
			
		if (gpioPinsArray[i].port == Port_A)
			gpioState[0] = (char)((PTA->PDOR << (31-gpioPinsArray[i].pinNumber)) >> 31) + 48;
		else
			gpioState[0] = (char)((PTB->PDOR << (31-gpioPinsArray[i].pinNumber)) >> 31) + 48;
		
		strcat(states, &gpioState);
	
	}
	
	return states;
		
}


void gpioSetOutputStates (bool states[20]) {
	
	for (int i = 0; i < GPIO_COUNT; ++i) {

		if (states[i]) {	// high logic state
			
			if (gpioPinsArray[i].port == Port_A) {
				PTA->PSOR = ( 1UL << (gpioPinsArray[i].pinNumber) );
			}
			else {
				PTB->PSOR = ( 1UL << (gpioPinsArray[i].pinNumber) );
			}
		}
		else {	// low logic state
			
			if (gpioPinsArray[i].port == Port_A) {
				PTA->PCOR = ( 1UL << (gpioPinsArray[i].pinNumber) );
			}
			else {
				PTB->PCOR = ( 1UL << (gpioPinsArray[i].pinNumber) );
			}
		}
			
	}
	
}
