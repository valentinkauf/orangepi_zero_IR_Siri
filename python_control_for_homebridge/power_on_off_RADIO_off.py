import time
import OPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

chan_list = [3,5,7,8]

# 3 connected to D11 Arduino's pin for TV
# 5 connected to D12 Arduino's pin for RADIO
# 7 to power up Arduino nano
# 8 to power up bluetooth adaptator

GPIO.setup(chan_list, GPIO.OUT)

#GPIO.output(chan_list, (GPIO.HIGH,GPIO.HIGH,GPIO.LOW))

GPIO.output(8, GPIO.LOW)

time.sleep(0.2)

GPIO.output(3, GPIO.LOW)
GPIO.output(5, GPIO.HIGH)
GPIO.output(7, GPIO.HIGH)
GPIO.output(8, GPIO.LOW)

time.sleep(8)

GPIO.output(chan_list, GPIO.LOW)

GPIO.cleanup()