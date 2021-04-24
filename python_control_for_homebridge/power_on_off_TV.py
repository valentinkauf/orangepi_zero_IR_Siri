import time
import OPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

chan_list = [3,5,7]

# 3 connected to D11 Arduino's pin for TV
# 5 connected to D12 Arduino's pin for RADIO
# 7 to power up Arduino nano

GPIO.setup(chan_list, GPIO.OUT)

#GPIO.output(chan_list, (GPIO.HIGH,GPIO.HIGH,GPIO.LOW))

GPIO.output(3, GPIO.HIGH)
GPIO.output(5, GPIO.LOW)
GPIO.output(7, GPIO.HIGH)

time.sleep(10)

GPIO.output(chan_list, GPIO.LOW)

GPIO.cleanup()