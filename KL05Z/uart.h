  
#ifndef __uart_H__
#define __uart_H__

#include "MKL05Z4.h"

void uartInitialize(void);

char uartCaptureChar(void);
char* uartCaptureRequest(void);

void uartSendChar(uint8_t data);
void uartSendResponse(char* str);

#endif /* __uart_H__ */
