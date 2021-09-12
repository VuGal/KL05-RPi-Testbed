#include "time.h"
#include "rtc.h"
#include "MKL05Z4.h"
#include "uart.h"


void rtcInitialize(void) {
	
	SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;

	SIM->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_MASK;
	SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0);
	
	RTC->TSR = 1;
	
	RTC->LR &= ~RTC_LR_LRL_MASK;
	RTC->TCR = RTC_TCR_CIR(0) | RTC_TCR_TCR(0);

	RTC->LR |= RTC_LR_TCL_MASK;
	RTC->LR |= RTC_LR_LRL_MASK;
	
	RTC->IER = RTC_IER_TAIE_MASK;

	RTC->SR |= RTC_SR_TCE_MASK;
	
}

