#include "leds.h"
#include "extra.h"


const uint32_t MaskLED[] = {1UL << 8, 1UL << 9, 1UL << 10};

void initLed(void){

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[8] = PORT_PCR_MUX(1UL);
	PORTB->PCR[9] = PORT_PCR_MUX(1UL);
	PORTB->PCR[10] = PORT_PCR_MUX(1UL);
	PTB->PDDR |= MaskLED[0];
  PTB->PDDR |= MaskLED[1];
  PTB->PDDR |= MaskLED[2];
	
	PTB->PSOR = MaskLED[0];
	PTB->PSOR = MaskLED[1];
	PTB->PSOR = MaskLED[2];
}

void blinkLeds(void){
	for (int i = 0; i < 3; i++){
		PTB->PCOR = MaskLED[i];
		delay_mc(300);
		PTB->PSOR = MaskLED[i];
		delay_mc(600);
	}
}

void ledOn(uint8_t color){
	for(int i = 0; i < 3; i++)
		PTB->PSOR = MaskLED[i];
	
	PTB->PCOR = MaskLED[color];
}

void ledBlink(uint8_t color, uint8_t count){
	for(int i = 0; i < 3; i++)
		PTB->PSOR = MaskLED[i];
	
	for(int i = 0; i < count; i++){
		PTB->PCOR = MaskLED[color];
		delay_mc(300);
		PTB->PSOR = MaskLED[color];
		delay_mc(600);

		}
}

void ledOff(void){
	for(int i = 0; i < 3; i++)
		PTB->PSOR = MaskLED[i];
}
