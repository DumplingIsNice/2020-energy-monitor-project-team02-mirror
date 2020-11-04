![](https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png)

# Firmware for Smart Energy Monitor (FW)

## General Info

- Firmware program to work with ATmega328PB microcontroller.
- Program written in Atmel Studio 7.0 under Atmega328P simulator.

### Description of files:
- **main.c:** The main function, entry point of code.
- **common.c:** Functions, definitions and global variables that are common to all modules (i.e. debug printing etc.).
- **uart.c:** Functions to do with communicating over the UART protocol.
- **adc.c:** Functions to do with Analogue-to-Digital Conversion.
- **dsp.c:** Functions to do with Digital-Signal-Processing Conversion.
- **test.c:** Functions to test the various functions of the Firmware.
- **timer1.c:** Functions to do with timer1 peripherals.
- **timer2.c:** Functions to do with timer2 peripherals.
- **display.c:** Functions to do with 7-segment display. 

# TODO:

> See the Trello card [Embedded Program: Development & Simulation](https://trello.com/b/7f8trbUE/electeng-209-team-2) for current and past (completed) tasks etc.
