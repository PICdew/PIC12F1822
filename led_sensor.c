#include <xc.h>
#include <htc.h>
#include <pic12f1822.h>
#include <delays.h>

#define _XTAL_FREQ 4000000
//__CONFIG(CLKOUTEN_OFF & FCMEN_OFF & IESO_OFF &
//         MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & WDTE_OFF & PWRTE_OFF & FOSC_INTOSC) ;

__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
         PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF) ;
__CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF & LVP_OFF);


void Wait(unsigned int num)
{
    int i;

    for (i=0; i<num; i++) {
        __delay_ms(10);
    }
}

unsigned int adconv() {
    unsigned int temp;

    GO_nDONE = 1;
    while (GO_nDONE);
    temp = ADRESH;
    temp = (temp << 8) | ADRESL;
    
    return temp;
}

main()	{
    unsigned int num;

    OSCCON = 0b01110010;        // Internal clock: 4MHz
    ANSELA = 0b00010000;        // Analog
    TRISA  = 0b00011000;        // I/O (RA3 is input only)
    PORTA = 0b00000000;

    ADCON1 = 0b10010000;
    ADCON0 = 0b00001101;
    __delay_us(5);
/*
    CCP1SEL = 0;
    CCP1CON = 0b00001100;
    T2CON = 0b00000010;
    CCPR1L = 0;
    CCPR1H = 0;
    TMR2 = 0;
    PR2 = 124;
    TMR2ON = 1;
*/

    unsigned int limit = 800;
    while(1) {
        num = adconv();
        //CCPR1L = num / 4;
        if (num > limit) {
            PORTAbits.RA1 = 1;
            PORTAbits.RA2 = 1;
            limit = 1000;
        } else {
            PORTAbits.RA1 = 0;
            PORTAbits.RA2 = 0;
            limit = 600;
        }
//        __delay_us(10);
    }
}