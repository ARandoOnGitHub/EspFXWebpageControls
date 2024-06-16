
# ESP32 controled Arachnid v2 PCB mod

An idea to uses an ESP32 to create a webserver that can control the output of the [Arachnid v2 PCB by Pedel PCB](https://www.pedalpcb.com/product/octagon/)

The effects cuircuit is based on the [FV-1 chip](http://spinsemi.com/Products/datasheets/spn1001/FV-1.pdf) following fairly closly to the datasheet

Other useful resources: https://electric-canary.com/fv1start.html


If you somhow stumbled on this by accident, Welcome I guess... this isn't even close to being finished, just randomly started doing this, idk when i'll get to finishing. 

If you decide to improve opon this before i get to it. pls let me know 





## Features

- Control you multi fx pedel through wifi
    - Change FX program
    - Control FX parameters (working on it)
    - Control Volume and Mix (working on it)
    - 
- 
- Cross platform


## Components used(so far): 

- [Octigon (Arachnid v2) PCB by Pedel PCB](https://www.pedalpcb.com/product/octagon/)
- Esp32 wroom dev
- 74H595C (Shift Register)
- Assortment of passive electronic components (capacitors, resistors, etc)
- 9v and 3.3v power supply (or 3.3v linear regulator)

- DigiPots (eventualy)
-

## Documentation
Not sure how to easily put pics in here so heres the doc with some pics

[Documentation](https://docs.google.com/document/d/1YMJDztT-3IjzAF4EKWoZTLshfhHZI1bToYKVvrYV1EU/edit?usp=sharing)






The Octigon FX board follows the FV-1 example circuit with minor changes to some values here and there.



### FX Selection:

For fx selection the pins of interest are pins 16,17, and 18 (s0, s1, s2). As you would guess, these pins read a 3 bit binary number to choose a program 0-7.


The octagon FX board uses an interesting assortment of diodes and a selector switch connectng between the switches and and 3.3v supply (theoreticly the diodes arn't necessary and can be replaced with just wire, but i think the diodes are for transient protection).
This is cool and effective if you don't want to add extra digital components and you can use the current pinout with something like a Demux, or a shift register to switch but that would require 8 bits rather than just the 3 that we need. (also depending on the output current capabilities of your shift register, there may be too much of a voltage drop on some of the output leading to the effect not being read)

To break out these Switching pins, We can use 3 pads from the diodes that connect directly to the pins 16,17, and 18 (s0, s1, s2). The pins that can be use on the PCB are highlighted in the Image below.









Now that we have the switching pins broken out we use something like shift register connected to the esp32 to select wich output we want selected (In my case I used the 74HC595)


I put basic the code of operation in “Comms.cpp” and its header file for now



### Swiching between internal and external FX:

From the FV-1 datasheet, we can see that T0, (pin13) decided where to read the programs from. It appears that the resistor connecting the pin to 3.3v is just a pullup resistor for protection, and if we connect the T0 to ground or 3.3v we can switch between internal and external FX.


The PCB does not explicitly allow us to switch between the t0. To break out this pin we can use the connection to R5 and solder a wire from there to make connections the Pad is highlighted in the image below.






Since we have 5 unused outputs on our shift register, we can use one to trigger T0 of the fv-1. In my case I decided to use bit 5 of the shift register.
I basically decided to switch the bit on and off by XORing it with itself when ever i want it to change value. 

ex


(*note I was only able to confirm it using a push button shorting the pin to ground and I did not get to test this with sending a logic low from theshift register before i damaged my circuit)


### FX parameter control (not implemented yet):

The board uses potentimoters to acting as a voltage divider between 3.3v and GND. these Potentimters feed a variable voltage between Pins 20, 21, 22 (P0, P1, P2). 

To control these pins we can use either DigiPots, or a DAC, to feed an analoge voltage to these pins using the ESP32 built in DAC (only 2 built in)

To control the VOLUME and MIX pots, it would easiest to use DIgiPots since these resistance values affect the operation of the Opamps




| DAC  | | DigiPot||
|---|---|---------|----|
| Pros | Cons | Pros |Cons |
| 2 onboard Simplifies wiring for those pins | Need an external dat for more than 2 controls | Simplifies code ig| Complicates wiring a bit|
|| | (Can reuse/adapt digipot code for all controles) |
| Reduces Power draw (possibly idk) | Still need Digipots for the Opamps            |         | I dont have on hand, need to wait for shipment |


| First Header  | Second Header |
| ------------- | ------------- |
| Content Cell  | Content Cell  |
| Content Cell  | Content Cell  |


I don't have on hand, need to wait for shipment



















Ill probably attempt usingthe internal DAC because I don't have DigiPots on hand (and im not spending enough time on this to get them)












Ideas for Multiple EEPROMS and switching:

use a MUX on the SDA lines and connect it to the SDA pin on the fv-1 (I will elaborate on it later, idk but should theoreticly be possible)

other ideas are in the txt file
## Explaination of Code

its very bad :( , it was combined with different previous projects and written poorly so it takes up too much memory, also tried seperating the fuctions and making it more modular by writing my own header files (good idea but ended up being more convoluted)


I am planning on removing this and starting from scratch when I get the time

other than that:

what I have currently are Just testing of program select using an shift register (in ShiftReg.h and ShiftReg.cpp) 

currently using the serial Comunication to select program rather than the webpage for now



in the "Comms.h" and its cpp file are right now part of some old code to give a viual indicator of connection status

Also was planning to put website comuncation code in here 

there are 2 ways I was thinking of this:
using websockets or xml updates, i think now its using websockets but I kept switiching between the 2, so there might be some extra code here and there. its also incomplete


there are 3 html files i used for experimentation on the webpage. this code can be copy pasted as a RAW Literal in the "Supermon.h" file to upload to the esp32

or 

we can use SPIFFS and upload the html into the data to host directly on the esp32 'drive partiion' (I havent done that yet but it looks nicer) 



other than that, the way it currently stands, it very bad. if you want to know more/clarifications, just mesege me
