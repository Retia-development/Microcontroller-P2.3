/*
 * LCD.h
 *
 * Created: 2/18/2019 1:53:02 PM
 *  Author: svber
 */ 

void init_lcd();
void lcd_command(unsigned char);
void lcd_writeChar( unsigned char);
void lcd_setCursorPosition(int position);
void lcd_writeLine ( char text[], int line);