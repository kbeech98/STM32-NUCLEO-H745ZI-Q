/*
 * DFRobot_soil_moisture_sensor.h
 *
 *  Created on: Nov. 20, 2021
 *      Author: Kristian Beech
 */

#include "stm32h7xx_hal.h"

int SoilSensor1, SoilSensor2;

#define SOIL_SENS1_PORT GPIOA
#define SOIL_SENS1_PIN GPIO_PIN_6

#define SOIL_SENS2_PORT GPIOC
#define SOIL_SENS2_PIN GPIO_PIN_4



#ifndef INC_DFROBOT_SOIL_MOISTURE_SENSOR_H_
#define INC_DFROBOT_SOIL_MOISTURE_SENSOR_H_

ADC_HandleTypeDef hadc1;


//void poll_SOIL_SENSOR(void);
void poll_SOIL_SENSOR_1_2(void);
void ADC_Select_CH3 (void);
void ADC_Select_CH5 (void);

#endif /* INC_DFROBOT_SOIL_MOISTURE_SENSOR_H_ */
