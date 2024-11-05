

#ifndef LCD_H_
#define LCD_H_

void lcd_init (void);
void lcd_send_string (char *str);
void setCursor(int a, int b);
void lcd_clear (void);

#endif /* LCD_H_ */
