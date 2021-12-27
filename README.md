
<h1 align="center">STM32-NUCLEO-H745ZI-Q</h1>
<p align="center"><strong>This repository contains various projects related to the STM32H745ZI-Q NUCLEO dual-core development board.
</strong>
<br></p>
<br/>
<div align="center"><img src="demo.gif"></img></div>
<h2>About</h2>
This project series will develop into my GROWBOT automated gardener project.
The main goal of this repository is to present the various projects and steps taken to acheieve this. 

<h2>The Workflow</h2>

First I implented the 20x4 LCD using a 4-bit addressing mode, had issues with: choosing write locations on display, timing in the initilization sequence, sending 8-bit data/commands in 4-bit nibbles//order of MSB/LSB.
Then the implementing the DHT11 sensor using single-wire serial communication. This was done using a 10KOhm pull-up resistor between the signal line and Vdd(+3.3V). Had issues with: implementing the timer to have an accurate delay, used ossciloscope to debug the signal line and determined timer delays were not correct. The used PWM and the osscilloscope to measure the actual period and corrected it in the code. Also had issues with displaying the decimal values of the temp and humidity readings. Had to convert the 8-bit decimal value to float by dividing by 10 then I added with the tens and ones value to get full value. 

Next will be setting up the analog capacitive soil moisture sensors, I want to have multiple sensor read using only one ADC, this will be implemented using the DMA to pipe multiple inputs to memory. 

Tried to set up the DMA1 to transfer adc values to memory but ran into issue with implementation. No data gets passed through dma. Tried using different dma streams, with ADC1 request multiplexed on DMAMUX1 using address 9U. Everything found online points to system level driver issues. Going to implement the adc individually for each soil sensor. 



<h2>Key learnings</h2>

- Implement LCD
- Temperature and Humidity Sensor 
- DMA controlled Soil Moisture Sensor 
- Water Pump I/O Relay 
- OP-amp PWM controlled LED Growlight 


<h2>Installation</h2>

1. Download this project as zip and extract it
2. Import it in Android Studio
3. Sync Gradle and run on your device/emulator

<h2>Contributing</h2>
Mention pull requests. Link to an example and/or put it down here

<h2>Project status</h2>
Insert here

<h2>Credits</h2>

- Author: Kristian Beech</a>
- Illustrations
- Colors
- Any material

<h2>Copyright</h2>
This project is licensed under the terms of the MIT license and protected by Udacity Honor Code and Community Code of Conduct. See <a href="LICENSE.md">license</a> and <a href="LICENSE.DISCLAIMER.md">disclaimer</a>.
