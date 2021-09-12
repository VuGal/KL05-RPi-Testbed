# FRDM-KL05Z Testbed device using Raspberry Pi 3B+

## KL05Z
Keil uVision5 was used during KL05Z code development. .hex file generation must be enabled.

Source code files description:
main.c - file containing the main loop and calls of necessary initializations (GPIO, RTC, UART)
operations.c / operations.h - handlers for commands received via UART messages
gpio.c / gpio.h - GPIO initialization and functions responsible for getting and setting pin state
rtc.c / rtc.h - Real-time clock (RTC) configuration
uart.c / uart.h - UART initialization and functions responsible for receiving and sending message
extra.c / extra.h - helper functions

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
