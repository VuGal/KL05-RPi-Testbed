#include "MKL05Z4.h"
#include "uart.h"
#include "extra.h"


void uartInitialize() {
	
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(2);
	
		PORTB->PCR[1] = PORT_PCR_MUX(0x2);
    PORTB->PCR[2] = PORT_PCR_MUX(0x2);
	
    UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK );
	
		UART0->C4 |= UART0_C4_OSR(0x3);
	
    UART0->BDH = UART0_BDH_SBR(0x0);
    UART0->BDL = UART0_BDL_SBR(0x1);
		UART0->BDH &= ~UART0_BDH_SBNS_MASK;
	
		UART0->C1 &= ~UART0_C1_M_MASK;
		UART0->C1 &= ~UART0_C1_PE_MASK;
	
    UART0->C5 |= UART0_C5_BOTHEDGE_MASK;
	
    UART0->C2 |= UART0_C2_RIE_MASK;
    UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);
		
}


char uartCaptureChar(void) {
	
	while (!(UART0->S1 & UART0_S1_RDRF_MASK));
	return UART0->D;
	
}


char* uartCaptureRequest(void) {
	
	char capturedChar[2] = "";
	char request[100] = "";
	
	while (1) {
	
		capturedChar[0] = uartCaptureChar();
		strcat(request, &capturedChar);
		if (capturedChar[0] == '\n') {
			return request;
		}
		
	}
	
}


void uartSendChar(uint8_t data) {
	
	while(!(UART0->S1 & UART0_S1_TDRE_MASK) && !(UART0->S1&UART0_S1_TC_MASK));
	UART0->D = data;
	
}


void uartSendResponse(char* str) {
	
	uint16_t i=0;
	
	while(1) {
		
		while( !(UART0->S1&UART0_S1_TDRE_MASK) && !(UART0->S1&UART0_S1_TC_MASK));
		UART0->D = (uint8_t)(str[i]);
		if (str[i] == '\n') break;
		else ++i;
		
	}
	
}


