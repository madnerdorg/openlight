[Version française](https://github.com/madnerdorg/openlight/blob/master/readme.fr.md)

OpenLight
--------
![openlight_photo](https://github.com/madnerdorg/openlight/raw/master/doc/milightONOFF.jpg)     
Openlight is an open source alternative for milight gateway based on an arduino nano (clone).     
Based on Henryk Plötz researchs : https://hackaday.io/project/5888-reverse-engineering-the-milight-on-air-protocol     

Milight bulbs are not controlled using WIFI, it uses its own protocol on **2.4Ghz**.     

![openlight Routing](https://github.com/madnerdorg/openlight/raw/master/doc/milightRouting.png)      
Our arduino will directly control the milight bulbs using **nrf24l01+** radio modules without **using the WIFI gateway**.

# Usage
* Copy **libraries/openlight** into your arduino sketchbooks
* Upload **openlight/openlight.ino**
* Go to http://madnerd.org/interface/homeautomation
* Use your milight gateway to turn on/off lamp to retrieve the code into the interface.

Tactile switchs are not mandatory, but it makes it enable to turn on/off a lamp.      
You need to add the code of your lamp in the code, last hexadecimal values will be ignored as it is updated incrementally:     
```
int on [7] = { 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x01};
int off [7] = { 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x01};
```
# Commands
* /info : display name:port (openlight:42002)
* If a code is received from another source it will be displayed as 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x01

# Components
* 1 Arduino nano (ch340g): 2.50€	   
* 1 nrf24l01+ (radio module) : 1€	   
* 2 Tactiles switchs : 2€   
Total : 5.50€    

# Wiring
**nrf modules use 3.3V not 5V**

![nrf_pinout](https://github.com/madnerdorg/openlight/raw/master/doc/nrf_pinout.png)

![touchsensor](https://github.com/madnerdorg/openlight/raw/master/doc/touchsensor.png)

```
NRF
D9	: orange
D10	: yellow
D11	: blue
D12	: purple
D13	: green
3.3V: red

SWITCHS
D4	OFF SIG
D5	ON SIG
5V: VCC
```

# Licences

# openlight.ino
* Author : Rémi Sarrailh (madnerd.org)
* Licence : MIT 

# openmili
* Author : Henryk Plötz
* Licence : GPLv3
* Link: https://github.com/henryk/openmili
