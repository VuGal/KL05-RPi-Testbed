#include "MKL05Z4.h"
#include "stdbool.h"
#include "operations.h"
#include "gpio.h"
#include "rtc.h"
#include "uart.h"
#include "extra.h"
#include "operations.h"


static char message[100] = "";
static char* response = "";


int main(void) {
	
	uartInitialize();
	rtcInitialize();
	gpioInitialize();
	
	gpioSwitchAllPinsToInputs();
	
	while (1) {
		strcpy(message, uartCaptureRequest());
		response = handleRequest(message);
		uartSendResponse(response);
		delay_mc(100000);
	}
	
}
