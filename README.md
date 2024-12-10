# 260-5
This lab took our understanding of STM Cube and implemented the concept of interrupts. Interrupts are used in this lab to check data signals that are there to notify our microcontroller of any buttons being pushed. Interrupts are used in this lab instead of polling which is a method we used in the previous few labs. In this lab we took the HAL drivers used last lab and set up the ports to the names and pins we wanted. The overarching objective was to use interrupts to create a security pin system for the alarm system.

Specifications
The system is designed to take in a passcode when button A is pressed and then is stored into the system when button B is pressed. At this point a blue LED will light up to signify that the passcode has been stored. To check the new passcode against the correct one, button C is pressed and then the new passcode is put in. Once this is done button D is pressed to see if the passcodes are the same. If it is correct a green LED will light up, otherwise a yellow LED will light up and if the new passcode is wrong 3 times then a flashing red LED will light up. This can be turned off by the reset button. Every button press is also marked by a small LED on the microcontroller lighting up each time. Each major input is set to a Data Available pin that notifies the system that a button has been pressed. The system cannot perform anything outside of the described task.
