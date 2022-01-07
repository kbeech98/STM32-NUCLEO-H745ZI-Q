
<h1 align="center">STM32-NUCLEO-H745ZI-Q</h1>
<p align="center"><strong>
</strong>
<br></p>
<br/>
<div align="center"><img src="demo.gif"></img></div>
<h2>About</h2>
This repository will contain a series of small projects that will form the foundation of my automated indoor farm project.  
The main goal is to present the various projects, the steps taken, along with any challenges that were overcome. 

# <h2>The Workflow</h2>

#### NUCLEO_H745_NHD_20x4_PARALLEL_LCD
First I implented the 20x4 LCD using a 4-bit addressing mode, had issues with: choosing write locations on display, timing in the initilization sequence, sending 8-bit data/commands in 4-bit nibbles//order of MSB/LSB.

#### NUCLEO_H745_DHT11_SERIAL_TEMP_SENSOR
Then the implementing the DHT11 sensor using single-wire serial communication. This was done using a 10KOhm pull-up resistor between the signal line and Vdd(+3.3V). Had issues with: implementing the timer to have an accurate delay, used ossciloscope to debug the signal line and determined timer delays were not correct. The used PWM and the osscilloscope to measure the actual period and corrected it in the code. Also had issues with displaying the decimal values of the temp and humidity readings. Had to convert the 8-bit decimal value to float by dividing by 10 then I added with the tens and ones value to get full value. 

#### NUCLEO_H745_CAPACTIVE_SOIL_MOISTURE_SENSOR
Next will be setting up the analog capacitive soil moisture sensors, I want to have multiple sensor read using only one ADC, this will be implemented using the DMA to pipe multiple inputs to memory. 

Tried to set up the DMA1 to transfer adc values to memory but ran into issue with implementation. No data gets passed through dma. Tried using different dma streams, with ADC1 request multiplexed on DMAMUX1 using address 9U. Everything found online points to system level driver issues. Going to implement the adc individually for each soil sensor. 



# <h2>Key Topics</h2>


- [x] Parallel 4-bit LCD
- [x] Serial Temperature and Humidity Sensor 
- [ ] DMA Soil Moisture Sensor 
- [ ] Water Pump I/O 120V Relay
- [ ] Bluetooth Low Energy (BLE) RF 
- [ ] PWM OP-AMP LED Growlight 

<h2>Copyright</h2>
This project is licensed under the terms of the MIT license and protected by Udacity Honor Code and Community Code of Conduct. See <a href="LICENSE.md">license</a> and <a href="LICENSE.DISCLAIMER.md">disclaimer</a>.
