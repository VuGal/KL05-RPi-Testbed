from robot.api.deco import keyword
from robot.api import logger
import serial
import RPi.GPIO as GPIO
import time
from os import path
import shutil


class Keywords:
    def __init__(self):
        self.gpioDict = {18: '10000000000000000000', 23: '01000000000000000000', 24: '00100000000000000000',
                         6: '00010000000000000000', 7: '00001000000000000000', 8: '00000100000000000000',
                         14: '00000010000000000000', 15: '00000001000000000000', 25: '00000000100000000000',
                         12: '00000000010000000000', 16: '00000000001000000000', 20: '00000000000100000000',
                         21: '00000000000010000000', 26: '00000000000001000000', 19: '00000000000000100000',
                         13: '00000000000000010000', 17: '00000000000000001000', 27: '00000000000000000100',
                         22: '00000000000000000010', 10: '00000000000000000001'}

    def _mapBinToGPIO(self, argbin):
        list1 = []
        list2 = []
        for key, value in self.gpioDict.items():
            if (int(value, 2) & argbin) == int(value, 2):
                list1.append(key)
            else:
                list2.append(key)
        return list1, list2

    @keyword(name="Check Input GPIO Value")
    def check_input_gpio_value(self, argbin):
        gpioReadListHigh, gpioReadListlow  = self._mapBinToGPIO(argbin)
        GPIO.setmode(GPIO.BCM)
        failListLow = []
        failListHigh = []
        for i in range(30):
            failCheck = 0
            if i == 29:
                raise Exception(f"GPIO aren't low: {failListHigh}, GPIO aren't high: {failListLow}")
            for keys in self.gpioDict:
                if GPIO.input(keys) == GPIO.HIGH and keys in gpioReadListlow:
                    failCheck = 1
                    if keys not in failListHigh:
                        failListHigh.append(keys)
                if GPIO.input(keys) == GPIO.LOW and keys in gpioReadListHigh:
                    failCheck = 1
                    if keys not in failListLow:
                        failListLow.append(keys)
            if failCheck == 0:
                break
            time.sleep(1)
        return 1

    @keyword(name="Set Output GPIO")
    def set_output_gpio(self, argbin):
        gpioReadListHigh, gpioReadListlow = self._mapBinToGPIO(argbin)
        GPIO.setmode(GPIO.BCM)
        for i in self.gpioDict:
            GPIO.setup(i, GPIO.OUT)
        for x in gpioReadListHigh:
            GPIO.output(x, 1)
            time.sleep(0.01)
        for x in gpioReadListlow:
            GPIO.output(x, 0)
            time.sleep(0.01)
        time.sleep(3)
        return 1

    @keyword(name="Set Input GPIO All")
    def set_input_gpio_all(self):
        GPIO.setmode(GPIO.BCM)
        for i in self.gpioDict:
            GPIO.setup(i, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

        return 1

    @keyword(name="Cleanup GPIO")
    def cleanup_gpio(self):
        GPIO.cleanup()
        return 1

    @keyword(name="Check If Board Is Connected")
    def check_if_board_is_connected(self):
        for i in range(30):
            if(i == 29):
                raise Exception("Board not connected")
            if(path.exists('/media/pi/FRDM-KL05ZJ')):
                break
            time.sleep(1)
        return 1

    @keyword(name="Check If Software Is Available")
    def check_if_software_is_available(self):
        if not path.exists('/home/pi/RobotWorkspace/files/software.hex'):
            raise Exception("File software.hex not found in /home/pi/RobotWorkspace/files/")
        return 1

    @keyword(name="Upload Software")
    def upload_software(self):
        shutil.copyfile('/home/pi/RobotWorkspace/files/software.hex', '/media/pi/FRDM-KL05ZJ/software.hex')
        time.sleep(5)
        return 1

    @keyword(name="Check Pin State")
    def check_pin_state(self, mode):
        failList = []
        pin_list = []
        for key in self.gpioDict:
            pin_list.append(key)
        for pin in range(len(pin_list)):
            if mode == "in" and not GPIO.gpio_function(pin_list[pin]) == GPIO.IN:
                failList.append(pin_list[pin])
            elif mode == "out" and not GPIO.gpio_function(pin_list[pin]) == GPIO.OUT:
                failList.append(pin_list[pin])
        if mode == "in" and len(failList) > 0:
            raise Exception(f"Pin number {failList} is not set as INPUT")
        if mode == "out" and len(failList) > 0:
            raise Exception(f"Pin number {failList} is not set as OUTPUT")
        return 1

    def _readlineCR(self, port):
        rv = ""
        ts = time.time()
        while True:
            ch = port.read()
            try:
                rv += ch.decode()
            except:
                pass
            if ch == b'\n' or ch == b'':
                return rv
            if time.time() - ts > 30:
                raise Exception("Reached 30 s timeout waiting for response")

    @keyword(name="Send String Via UART And Wait For Response")
    def send_string_via_uart(self, string, response_string):
        port = serial.Serial("/dev/ttyACM0", baudrate=2048, timeout=3.0)
        for char in string:
            port.write(char.encode())
            time.sleep(0.1)
        time.sleep(1)
        rcv = self._readlineCR(port)
        if not rcv[:-1] == response_string:
            raise Exception(f"Strings doesn't match, expected {response_string}, got {rcv}")
        return 1

    @keyword(name="Map Bin to String To Send")
    def map_bin_to_string_to_send(sel, argbin):
        argbin1 = bin(argbin)
        return '0'*(20 - (len(argbin1) - 2))+argbin1[2:]



