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
/media/$user/*uuid-of-the-µSD/boot/armbianEnv.txt 
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

## ARDUINO NANO receive IR code

This code is for catch your remotes codes on a serial monitor. 

You will find this code in the arduino_code folder. 

Library used : https://github.com/Arduino-IRremote/Arduino-IRremote

Arduino Uno led receiver connection : G = GND, R = Vcc 5V, Y = data PIN2

