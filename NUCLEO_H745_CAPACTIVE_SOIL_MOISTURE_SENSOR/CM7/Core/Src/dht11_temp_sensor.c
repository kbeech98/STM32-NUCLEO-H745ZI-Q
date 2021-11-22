//-KB,-5-11-202-
//dht11_temp_sensor.c

#include "dht11_temp_sensor.h"

//Define DHT11 global variables
uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
float SUM, RH, TEMP;
uint8_t Presence = 0;


//define the timer handler below
#define timer2 htim2

extern TIM_HandleTypeDef timer2;
void two_half_us_delay (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&timer2, 0);		//clear timer
	HAL_TIM_Base_Start_IT(&timer2);			//start timer
	while (__HAL_TIM_GET_COUNTER(&timer2) < us);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DHT11_Start (void)
{
	Set_Pin_Output (DHT11_PORT, DHT11_PIN);  		// set the pin as output
	HAL_GPIO_WritePin (DHT11_PORT, DHT11_PIN, 0);   // pull the pin low
	two_half_us_delay(6667);   								// wait for 18ms
	//HAL_Delay(2000);
    //HAL_GPIO_WritePin (DHT11_PORT, DHT11_PIN, 1);   // pull the pin high
	//two_half_us_delay(13);   								// wait for 30us
	Set_Pin_Input(DHT11_PORT, DHT11_PIN);    		// set as input
	two_half_us_delay(11);   								// wait for 30us
}

uint8_t DHT11_Read (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));   	// wait for the pin to go high
		two_half_us_delay(14);   										// wait for 40 us
		if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))   		// if the pin is low
		{
			i&= ~(1<<(7-j));   									// write 0
		}
		else i|= (1<<(7-j));  									// if the pin is high, write 1
		while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));  	// wait for the pin to go low
	}
	return i;
}

uint8_t DHT11_Check_Response (void)
{
	uint8_t Response = 0;
	two_half_us_delay(14);
	if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))
	{
		//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); //Debugging LED
		two_half_us_delay(30);
		if ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN))) Response = 1;
		else Response = -1; // 255
	}
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); //debugging LED
	while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));   // wait for the pin to go low

	return Response;
}

void poll_DHT11(void)
{
	DHT11_Start();
	Presence = DHT11_Check_Response();
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); //debugging LED
	Rh_byte1 = DHT11_Read ();
	Rh_byte2 = DHT11_Read ();
	Temp_byte1 = DHT11_Read ();
	Temp_byte2 = DHT11_Read ();
	SUM = DHT11_Read();

	TEMP = (float) (Temp_byte2);
	TEMP /= 10.0;
	TEMP += Temp_byte1;

	RH = (float) (Rh_byte2);
	RH /= 10.0;
	RH += Rh_byte1;

	Temperature = (float) (TEMP);
	Humidity = (float) (RH);
}

void delay_TEST (void) {
	__HAL_TIM_SET_COUNTER(&timer2, 0);		//clear timer
	HAL_TIM_Base_Start_IT(&timer2);			//start timer
}


