#include "MKL05Z4.h"
#include "gpio.h"
#include "stdbool.h"
#include "operations.h"
#include "uart.h"


char* handleRequest(char* request) {
	
	if ( !strncmp(request, "REQ_START\n", 10) ) {
		return "ACK_START\n";
	}
	
	else if ( !strncmp(request, "REQ_SWITCH_INPUT\n", 17) ) {
		gpioSwitchAllPinsToInputs();
		return "ACK_SWITCH_INPUT\n";
	}
	
	else if ( !strncmp(request, "REQ_SWITCH_OUTPUT\n", 18) ) {
		gpioSwitchAllPinsToOutputs();
		return "ACK_SWITCH_OUTPUT\n";
	}
	
	else if ( !strncmp(request, "REQ_SET_", 8) ) {
		
		bool testStates[20];
		
		for (int i = 0; i < 20; ++i) {
			if (request[8+i] == '1')
				testStates[i] = 1;
			else
				testStates[i] = 0;
		}
	
		gpioSetOutputStates(testStates);
		
		char response[30] = "";
		strcat(response, "ACK_SET_");
		strncat(response, &request[8], 20);
		strcat(response, "\n");
		
		return response;
		
	}
	
	else if ( !strncmp(request, "REQ_INPUT_STATE\n", 16) ) {
		
		char response[37] = "";
		
		strcat(response, "ACK_INPUT_STATE_");
		strcat(response, gpioGetInputStates());
		strcat(response, "\n");
		
		return response;
		
	}
	
	else if ( !strncmp(request, "REQ_OUTPUT_STATE\n", 16) ) {
		
		char response[37] = "";
		
		strcat(response, "ACK_OUTPUT_STATE_");
		strcat(response, gpioGetOutputStates());
		strcat(response, "\n");
		
		return response;
		
	}
	
}
