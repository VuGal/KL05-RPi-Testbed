# FRDM-KL05Z Testbed device using Raspberry Pi 3B+
  
The project goal was to create a testbed device for FRDM-KL05Z boards. Raspberry Pi 3B+ was used to enable Python and Robot Framework usage.
The testbed board is connected to the RPi from one side and to the tested board from the other ("sandwich" connection). Also USB connection 
between RPi and KL05Z is needed to enable USB-CDC communication. Tests are launched from Linux environment on RPi. Tests included into this project
are focused on GPIO testing - all GPIO ports are tested with the exception of D0 and D1 because they are needed for correct UART communication
(it's needed anyway to test other ports so D0 and D1 behavior is fine if the UART communication works).
  
## KL05Z
Keil uVision5 was used during KL05Z code development. Output .hex file (.hex generation must be enabled in IDE settings) should be put into /home/pi/RobotWorkspace/files/ path on RPi.

Source code files description:  
<b>main.c</b> - file containing the main loop and calls of necessary initializations (GPIO, RTC, UART)  
<b>operations.c / operations.h</b></b> - handlers for commands received via UART messages  
<b>gpio.c / gpio.h</b> - GPIO initialization and functions responsible for getting and setting pin state  
<b>rtc.c / rtc.h</b> - Real-time clock (RTC) configuration  
<b>uart.c / uart.h</b> - UART initialization and functions responsible for receiving and sending message  
<b>extra.c / extra.h</b> - helper functions  

## Raspberry Pi
Requirements:  
Raspberry Pi OS - May 2021 version  
Python 3.7.3  
Python libraries: serial, RPi.GPIO  
Robot Framework 4.1  
  
Usage:  
Files should be put into /home/pi/RobotWorkspace/ path.
Starting tests: ./start.sh  
Tests are visible in robot/main.robot  
Keywords are visible in python/Keywords.py  
Results will be visible in output.xml, log.html and report.html  

## PCB

Pins of Raspberry Pi had to be connected with suitable pins of KL05Z.  
In order to implement this idea a PCB shield has been designed with usage of KiCad ver. 5.1.9.  
The 1 kΩ resistors were added in each connection to avoid current overdrive in case of different GPIO logic states on each side.

