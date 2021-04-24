# Orange Pi Zero IR remote control through Siri

This repo is about to create an infrared remote control that can be controlled with Siri.

I face an issue with directly sending IR commands with the OPiZ. This may be due to the speed of the OPiZ gpio library. 

I am working to create a solution to this problem. However, I have made a temporary solution which is to send IR commands with an Arduino Nano connected to the OPiZ.

I used an Arduino Uno to receive IR codes from my remotes. 

I drive with this solution a Beelink GT1 and a Logitech Z906.

I also power a 5V bluetooth adaptator with a NPN-PNP driver with a gpio. 

## Orange PI Zero configuration

### Os installation 

Based on : http://toglut.net/installation-dune-armbian-sur-orange-pi-zero/

The OS installed is Armbian Buster : https://www.armbian.com/orange-pi-zero/

Uncompress a img.xz file :

```
sudo apt-get install xz-utils
unxz Armbian_21.02.3_Orangepizero_buster_current_5.10.21.img.xz
sudo dd if=Armbian_5.91_Orangepizero_Debian_buster_next_4.19.59.img of=/dev/sdc bs=1M
sudo sync
sudo umount /media/user/*device
```

To access Orange PI Zero on serial : 

```
/media/user/uuid-of-the-µSD/boot/armbianEnv.txt 
```

To verify there is :

```
console=serial
```

Serial connection 

```
gtkterm -p /dev/ttyACM0 
```

Armbian getting started documentation : https://docs.armbian.com/User-Guide_Getting-Started/#how-to-prepare-a-sd-card

### Scan network to find OPIZero IP

```
sudo apt-get install arp-scan
ifconfig
sudo arp-scan --interface=enp3s0 --localnet
ssh user@192.168.X.X
```

### Armbian config 

```
armbian-config
```

https://docs.armbian.com/User-Guide_Armbian-Config/

### Install Homebridge

#### Install Node.js

```
sudo apt update
sudo apt upgrade

# install deps
sudo apt install -y gcc g++ make python git

# setup repo
curl -sL https://deb.nodesource.com/setup_14.x | sudo bash -

# install Node.js
sudo apt install -y nodejs gcc g++ make python net-tools

# test node is working
node -v
```

Version installed v15.12.0

#### Install Homebridge and Homebridge UI

Install Homebridge and the Homebridge UI using the following command:

```
sudo npm install -g --unsafe-perm homebridge homebridge-config-ui-x
```

To setup Homebridge as a service that will start on boot, you can use the provided hb-service command.

```
sudo hb-service install --user homebridge
```

This command will do everything that is required to setup Homebridge  and the Homebridge UI as a service on your system, it will create the user if it does not already exist, and create the default Homebridge `config.json` under `/var/lib/homebridge` if it does not already exist.

When setting up Homebridge as a service using this command, the UI  will stay online even if Homebridge is crashing due to a bad plugin or  configuration error.

#### How To Uninstall Homebridge

To remove the Homebridge service run:

```
sudo hb-service uninstall
```

To remove Homebridge and Homebridge Config UI X run:

```
sudo npm uninstall -g homebridge homebridge-config-ui-x
```

#### Using Homebridge

http://192.168.X.X:8581

### Plugin Homebridge

Install homebridge plugin Script2 : https://github.com/pponce/homebridge-script2#readme

Homebridge config is :

```
{
    "bridge": {
        "name": "Homebridge",
        "username": "yours",
        "port": yours,
        "pin": "yours"
    },
    "accessories": [
        {
            "accessory": "Script2",
            "name": "TV",
            "on": "python3 /home/valentin/OPiGPIO/power_on_off_TV.py",
            "off": "python3 /home/valentin/OPiGPIO/power_on_off_TV.py"
        },
        {
            "accessory": "Script2",
            "name": "Radio",
            "on": "python3 /home/valentin/OPiGPIO/power_on_off_RADIO_on.py",
            "off": "python3 /home/valentin/OPiGPIO/power_on_off_RADIO_off.py"
        }
    ],
    "platforms": [
        {
            "name": "Config",
            "port": 8581,
            "platform": "config"
        }
    ]
}
```

### Allow gpio access for homebridge

To run this python code 

https://opi-gpio.readthedocs.io/en/latest/install.html#

https://opi-gpio.readthedocs.io/en/latest/_modules/OPi/GPIO.html

```
apt install python3-pip	
sudo pip3 install --upgrade OPi.GPIO
```



```
sudo nano /etc/udev/rules.d/99-gpio.rules
```



```
SUBSYSTEM=="gpio", ACTION=="add", RUN="/bin/sh -c '\
  chown -R root:gpio /sys/class/gpio && chmod -R 770 /sys/class/gpio;\
  chown -R root:gpio /sys$DEVPATH && chmod -R 770 /sys$DEVPATH"
```



to home switch python : https://github.com/joepool/homebridge-cmdswitch2-no-logs#readme  



restard Homebridge after config.json modification

## ARDUINO NANO receive IR code

This code is for catch your remotes codes on a serial monitor. 

You will find this code in the arduino_code folder. 

Library used : https://github.com/Arduino-IRremote/Arduino-IRremote

Arduino Uno led receiver connection : G = GND, R = Vcc 5V, Y = data PIN2

## Sending IR code

I face an issue with sending code directly with OPiZ so i made this temporary solution until i reach a solution.

### Sending IR with Arduino Nano

I send code through a simple IR led.

You will find this code in the arduino_code folder. 

Codes for logitech Z906 : https://gist.github.com/pladaria/f8a1ce754f1ed3022b78f8a302d463b5

### GPIO on OPiZ



https://github.com/zhaolei/WiringOP

### Power up the arduino 

BC337

Ic = 150 mA => NANO

Vce = 1V

B = 220



Ib = 0.15/220 ~= 0.7mA
$$
R1 = Rb = (4.3-0.7) / 7.10-4 = 6.15kohms
$$


BC327

Ic = 150mA

B  = 200

Ib = 0.15/200 = 0.75mA
$$
R2 = Rb = (Vcc + 0.7)/Ib = 760 ohms
$$





![arduino_nano_power_up_through_OPiZ_gpio](/media/valentin/DEAE146CAE144007/arduino_nano_power_up_through_OPiZ_gpio.png)

### Pins connection 

For OPi.GPIO use physical numbers !

![image-20210329074725940](file:///home/valentin/.config/Typora/typora-user-images/image-20210329074725940.png?lastModify=1616998055)

|                       Orange Pi Zero                        | Arduino NANO | Transistor switch & IR LED |
| :---------------------------------------------------------: | :----------: | :------------------------: |
|                             5V                              |     Vin      |                            |
|                             GND                             |              |        Transistor E        |
| Physical 7 for Nano<br />Physical 8 for bluetooth adaptator |              |     Rb - Transistor E      |
|                                                             |     GND      |        Transistor C        |
|                         Physical 3                          |     D11      |                            |
|                         Physical 5                          |     D12      |                            |
|                                                             |      D3      |         IR LEDs +          |
|                                                             |     GND      |         IR LEDs -          |

