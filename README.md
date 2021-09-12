# FRDM-KL05Z Testbed device using Raspberry Pi 3B+
  
The project goal was to create a testbed device for FRDM-KL05Z boards. Raspberry Pi 3B+ was used to enable Python and Robot Framework usage.
The testbed board is connected to the RPi from one side and to the tested board from the other ("sandwich" connection). Also USB connection 
between RPi and KL05Z is needed to enable USB-CDC communication. Tests are launched from Linux environment on RPi.
  
## KL05Z
Keil uVision5 was used during KL05Z code development. .hex file generation must be enabled.

Source code files description:  
<b>main.c</b> - file containing the main loop and calls of necessary initializations (GPIO, RTC, UART)  
<b>operations.c / operations.h</b></b> - handlers for commands received via UART messages  
<b>gpio.c / gpio.h</b> - GPIO initialization and functions responsible for getting and setting pin state  
<b>rtc.c / rtc.h</b> - Real-time clock (RTC) configuration  
<b>uart.c / uart.h</b> - UART initialization and functions responsible for receiving and sending message  
<b>extra.c / extra.h</b> - helper functions  

## Raspberry Pi
Requirements:  
Python 3.7.3  
Python libraries: serial, RPi.GPIO  
Robot Framework 4.1  
  
Usage:  
Starting tests: ./start.sh  
Tests are visible in robot/main.robot  
Keywords are visible in python/Keywords.py  
Results will be visible in output.xml, log.html and report.html
