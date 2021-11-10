//-KB,-5-11-202-
//dht11_temp_sensor.c

#include "dht11_temp_sensor.h"

//Define DHT11 variables
uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t SUM, RH, TEMP;
uint8_t Presence = 0;
float Temperature = 0;
float Humidity = 0;

//Define the DHT11 pin below
#define DHT11_PORT GPIOD
#define DHT11_PIN GPIO_PIN_0

//define the timer handler below
#define timer2 htim2

extern TIM_HandleTypeDef timer2;
void us_delay (int us)
{
	__HAL_TIM_SET_COUNTER(&timer2, 0);	//clear timer
	HAL_TIM_Base_Start_IT(&timer2);	//start timer
	while (__HAL_TIM_GET_COUNTER(&timer2) < us);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
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
	us_delay(18000);   								// wait for 18ms
    HAL_GPIO_WritePin (DHT11_PORT, DHT11_PIN, 1);   // pull the pin high
	us_delay(20);   								// wait for 20us
	Set_Pin_Input(DHT11_PORT, DHT11_PIN);    		// set as input
}

uint8_t DHT11_Read (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));   	// wait for the pin to go high
		us_delay (40);   										// wait for 40 us
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
	us_delay (40);
	if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)))
	{
		us_delay (80);
		if ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN))) Response = 1;
		else Response = -1; // 255
	}
	while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));   // wait for the pin to go low

	return Response;
}

void Display_Temp (float Temp)
{
	char str[20] = {0};
	lcd_clear();
	lcd_put_cur(0, 0);

	sprintf (str, "TEMP:- %.2f ", Temp);
	lcd_send_string(str);
	lcd_send_data('C');
}

void Display_Rh (float Rh)
{
	char str[20] = {0};
	lcd_clear();
	lcd_put_cur(1, 0);

	sprintf (str, "RH:- %.2f ", Rh);
	lcd_send_string(str);
	lcd_send_data('%');
}

void poll_DHT11(void)
{
	DHT11_Start();
	Presence = DHT11_Check_Response();
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
	Rh_byte1 = DHT11_Read ();
	Rh_byte2 = DHT11_Read ();
	Temp_byte1 = DHT11_Read ();
	Temp_byte2 = DHT11_Read ();
	SUM = DHT11_Read();

	TEMP = Temp_byte1;
	RH = Rh_byte1;

	Temperature = (float) TEMP;
	Humidity = (float) RH;

	Display_Temp(Temperature);
	Display_Rh(Humidity);
}


