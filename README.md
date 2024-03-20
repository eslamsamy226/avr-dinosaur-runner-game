# AVR Dinosaur Runne Game
This project is an implementation of Google Chorme's [Dinosaur Game](#https://en.wikipedia.org/wiki/Dinosaur_Game) using the AVR archticture, one of the key features of this project is the
random generation of obstacles, I managed to implement this feature by using a strurct where I kept track of the obstacle location relative to the playable character and whether it's
active or not, I can this change the active status based on a randomly generated number from C's rand() function.

## ⚡Components
 The following components have been used:
 * ATMEGA32 MCU
 * Buzzer
 * Push buttons
 * 2*16 LCD

## 🛠️Drivers
In order to achive the project funtionality I wrote the following drivers:
* DIO
* Buzzer
* Led
* LCD
* Bush buttons
these drivers can be found in /src forlder

## 👨‍💻Simulation
The proteus simulation design can be found in (design.pdsprj) file, here is the simulation in action:

https://github.com/eslamsamy226/avr-dinosaur-runner-game/assets/128985943/6f3f91cf-6337-4725-946f-0c8ea48bd6ce



## 🔳Hardware
I have also implemented this project in hardware:


https://github.com/eslamsamy226/avr-dinosaur-runner-game/assets/128985943/6d649531-3179-4691-a163-6187dcd1c89f

