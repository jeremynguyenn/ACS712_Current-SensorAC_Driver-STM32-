#include "stdio.h"
#include "delay.h"
#include "lcd.h"
#include "i2c.h"

#include "acs712.h"

float current_value;

char curr_data[15];
int main(void)
{
	i2c_init();
	systick_init_ms(16000000);
	lcd_init();
	acs712_init();

	while(1)
	{

		current_value=get_acs712_current();
		if(millis()%400==0){
		setCursor(0,0);
		lcd_send_string("AC Current=");
		sprintf(curr_data,"%0.3f   ",current_value);
		setCursor(0,1);
		lcd_send_string(curr_data);}

	}
}
