//-KB,-5-11-202-
//nhd_20x4_LCD.h

#ifndef INC_NHD_20X4_LCD_H_
#define INC_NHD_20X4_LCD_H_


void nhd_LCD_Init(void);	//initialize lcd

void lcd_send_cmd(char cmd);  //send command to the lcd

void lcd_send_data(char data);  //send data to the lcd

void lcd_send_string(char *str);  //send string to the lcd

void lcd_put_cur(int row, int col);  //put cursor at the entered position row (0, 1, 2, or 3), col (0-19);

void lcd_clear(void);

void lcd_nibble(void);

void five_ns_delay (int ns);

#endif /* INC_NHD_20X4_LCD_H_ */
