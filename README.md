
<h1 align="center">STM32-NUCLEO-H745ZI-Q</h1>
<p align="center"><strong>
</strong>
<br></p>
<br/>
<div align="center"><img src="https://user-images.githubusercontent.com/48364159/148620702-67aa7b54-be73-44d6-a2d8-1c29fc87c319.png"></img></div>
<h2>About</h2>

This repository contains various projects on the STM32H745ZI-Q NUCLEO dual-core development board which will form the foundation of my automated indoor farm project. The main goal is to present the various projects, the steps taken, along with any challenges that were overcome. 

<h2>Hardware</h2>
<!---
<p align="center" width="100%">
    <img width="32%" src="https://user-images.githubusercontent.com/48364159/148620986-f79dfd09-b9be-40c4-be96-15f0608f4593.png">
    <img width="32%" src="https://user-images.githubusercontent.com/48364159/148620925-a93bb7fc-19a9-4e30-b7e5-c543aa33bd5e.png">
    <img width="32%" src="https://user-images.githubusercontent.com/48364159/148621034-3c0db89c-8327-4b01-8de3-d26966f653da.png">
</p>
-->

<h2>Key Topics</h2>



- [x] Parallel 4-bit LCD
- [x] Serial Temperature and Humidity Sensor 
- [ ] DMA Soil Moisture Sensor 
- [ ] Water Pump I/O 120V Relay
- [ ] Bluetooth Low Energy (BLE) RF 
- [ ] PWM OP-AMP LED Growlight 
- [ ] CMSIS - RTOS task and scheduling
- [ ] Altium Custom PCB

<h2>The Workflow</h2>

#### NUCLEO_H745_NHD_20x4_PARALLEL_LCD
The first project consisted of implementing a parallel 20x4 LCD display. The LCD communicates with the micro-controller using 8-bit data and command instructions sent through the bi-directional data bus. Using the timing diagram and online resources, I created an initilization function that uses the nessarasary 8-bit commands along with an enable pin, and a register select pin to interpret the type of data (data/command). I was able to split the data into two 4-bit nibbles which allowed me to initilization the LCD in 4-bit mode saving 4 pins on the micro-controller. I found challenges with writing to the correct location on the display, the critical timing of the initilization sequence and the order to send the two 4-bit data nibbles when in 4-bit mode. I'm considering switching to an I2C LCD for the final implementation of this project in order to simplify the schematic by minimizing the hardware requirements.  

#### NUCLEO_H745_DHT11_SERIAL_TEMP_SENSOR
Then the implementing the DHT11 sensor using single-wire serial communication. This was done using a 10KOhm pull-up resistor between the signal line and Vdd(+3.3V). Had issues with: implementing the timer to have an accurate delay, used ossciloscope to debug the signal line and determined timer delays were not correct. The used PWM and the osscilloscope to measure the actual period and corrected it in the code. Also had issues with displaying the decimal values of the temp and humidity readings. Had to convert the 8-bit decimal value to float by dividing by 10 then I added with the tens and ones value to get full value. 

#### NUCLEO_H745_CAPACTIVE_SOIL_MOISTURE_SENSOR
Next will be setting up the analog capacitive soil moisture sensors, I want to have multiple sensor read using only one ADC, this will be implemented using the DMA to pipe multiple inputs to memory. 

Tried to set up the DMA1 to transfer adc values to memory but ran into issue with implementation. No data gets passed through dma. Tried using different dma streams, with ADC1 request multiplexed on DMAMUX1 using address 9U. Everything found online points to system level driver issues. Going to implement the adc individually for each soil sensor.

Researched possible issues relating to the DMA. Found that the STM32H7 has dCache coherrency issues. Have to run cache cleaning and invaildation routines for the MPU to accept new data values in RAM.  


<h2>Copyright</h2>
This project is licensed under the terms of the MIT license and protected by Udacity Honor Code and Community Code of Conduct. See <a href="LICENSE.md">license</a> and <a href="LICENSE.DISCLAIMER.md">disclaimer</a>.
