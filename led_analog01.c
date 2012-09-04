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
    ANSELA = 0b00000000;        // Analog
    TRISA  = 0b00011000;        // I/O (RA3 is input only)

    ADCON1 = 0b10010000;
    ADCON0 = 0b00001101;
    __delay_us(5);

    CCP1SEL = 0;
    CCP1CON = 0b00001100;
    T2CON = 0b00000010;
    CCPR1L = 0;
    CCPR1H = 0;
    TMR2 = 0;
    PR2 = 124;
    TMR2ON = 1;

    PORTA = 0b00000000;

    while(1) {
        num = adconv();
        CCPR1L = num / 4;
    }
}