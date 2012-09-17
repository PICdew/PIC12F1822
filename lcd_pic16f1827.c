/* 
 * File:   lcd.c
 * Author: root
 *
 * Created on September 16, 2012, 9:41 AM
 */

#include <stdlib.h>
#include <pic.h>
#include <pic16f1827.h>
#include <htc.h>
#include <delays.h>


#define _XTAL_FREQ 8000000

#define LCD_RS RB2
#define LCD_EN RB3
#define LCD_D4 RB4
#define LCD_D5 RB5
#define LCD_D6 RB6
#define LCD_D7 RB7

#define LCD_STROBE() ((LCD_EN=1),(LCD_EN=0))

__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
         PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF);

__CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF &  LVP_OFF);

void Wait(unsigned int num)
{
    int i;
    for (i=0 ; i<num ; i++) {
        __delay_ms(10);
    }
}

void lcd_write(unsigned char c)
{
    LCD_D4 = ((c>>4) & 0x01);
    LCD_D5 = ((c>>5) & 0x01);
    LCD_D6 = ((c>>6) & 0x01);
    LCD_D7 = ((c>>7) & 0x01);
    //LCD_STROBE();
    LCD_EN = 1;
    __delay_ms(1);
    LCD_EN = 0;
    __delay_ms(1);
    LCD_D4 = ((c) & 0x01);
    LCD_D5 = ((c>>1) & 0x01);
    LCD_D6 = ((c>>2) & 0x01);
    LCD_D7 = ((c>>3) & 0x01);
    //LCD_STROBE();
    LCD_EN = 1;
    __delay_ms(1);
    LCD_EN = 0;
    __delay_ms(1);

}

void command(unsigned char c)
{
    LCD_RS = 0;
    LCD_D4 = ((c) & 0x01);
    LCD_D5 = ((c>>1) & 0x01);
    LCD_D6 = ((c>>2) & 0x01);
    LCD_D7 = ((c>>3) & 0x01);
    LCD_EN = 1;
    __delay_ms(1);
    LCD_EN = 0;

//    LCD_STROBE();
}

void lcd_clear(void)
{
    LCD_RS = 0;
    lcd_write(0x01);
}

void lcd_setCursor(int col, int row)
{
    int row_offsets[] = { 0x00, 0x40 };
    LCD_RS = 0;
    lcd_write(0x80 | row_offsets[row]);
}

void lcd_putc(char c)
{
    LCD_RS = 1;
    lcd_write(c);
}

void lcd_puts(const char* s)
{
    LCD_RS = 1;
    while(*s) {
        lcd_write(*s++);
    }
}

void lcd_init()
{
    LCD_RS = 0;
    LCD_EN = 0;

    __delay_ms(15);
    command(0x03);
    __delay_ms(5);
    command(0x03);
    __delay_us(100);
    command(0x03);
    __delay_us(100);
    command(0x02);
    __delay_us(100);

    lcd_write(0x28);
    lcd_write(0x0c);
    lcd_clear();
    lcd_write(0x06);
}


int main(int argc, char** argv) {
    int i;
    char s[17];
//    char mes[6] = {0xbd, 0xc0, 0xb0, 0xc4, 0x00};
    char mes[6] = {0x48, 0x65, 0x6c, 0x6c, 0x6f};

    OSCCON = 0b01110010;
//    ADCON1 = 0b00000110;
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    TRISA = 0b00000000;
    TRISB = 0b00000000;
    PORTA = 0b00000000;
    PORTB = 0b00000000;


    lcd_init();
    lcd_puts(mes);

    i = 0;

    while(1) {
        lcd_setCursor(0,1);
        //lcd_puts("                ");
        lcd_setCursor(0,1);
        itoa(s,i,10);
        lcd_puts(s);
        i++;
        Wait(100);
    }
}