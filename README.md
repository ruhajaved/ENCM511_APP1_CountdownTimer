# ENCM511_APP1_CountdownTimer

## Introduction

### Problem Statement

Using the PIC24F16KA101 MCU and its peripherals, design a countdown timer app, capable of being set to a maximum of 59m : 59s, with the ability to start, pause, and reset the countdown. The countdown should be displayed on the terminal.

### Project Objective

The project objectives included:

1.	To gain experience with embedded programming in C on the application level, with a focus on becoming familiar with timers and UART serial communication. 
2.	To solidify general embedded programming concepts, such as power, software, and hardware optimization methods.

## Technologies

The technologies used include:

1. MPLAB IDE v5.40 (XC16 compiler)
2. PIC24F16KA101 MCU
3. ANSI C

## Launch

In order to successfully execute this project in terms of hardware, ensure that your hardware is set up according to the diagram in the "HWSetup.png" document. Furthermore, for the UART device, ensure that the connections to pin RxD and GND are NOT on the same node (top row and bottom row).

In terms of running the program, build the project, download it to the PIC, and ensure that the program is currently "playing". In settings, ensure you power the PIC with atleast 3.25 V. To actually power they system, you can use either a power sypply or your laptop. When programming the PIC, for newer laptops, you can also use the "low-voltage programming mode" option.

## Possible Improvements

Possible improvements for this project include:

1.	Operate at a higher base clock (at the expense of power consumption), in order to create more accurate delays used in the design. Current delays in the design were experimentally determined due to low clock speeds, which is not scalable. 
2.	As mechanical pushbuttons are used, implement functionality that filters out debounce effects.
3.	To improve the design, interface the MCU with a speaker, which when the countdown is complete, is used to create an audible alert.
