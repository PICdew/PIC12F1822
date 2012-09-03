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


void Wait(unsigned int num) {
    int i;

    for (i=0; i<num; i++) {
       __delay_ms(10);
    }
}


main()	{
    unsigned int num;

    OSCCON = 0b01101010;    // Internal clock: 4MHz
    ANSELA = 0b00000000;    // Analog
    TRISA  = 0b00001000;    // I/O (RA3 is input only)
    PORTA = 0b00000000;     // Output

    while(1) {
        PORTAbits.RA1 = 0;
        PORTAbits.RA2 = 1;
        Wait(5);
        PORTAbits.RA2 = 0;
        Wait(5);
        PORTAbits.RA2 = 1;
        Wait(5);
        PORTAbits.RA2 = 0;
        Wait(5);
        PORTAbits.RA2 = 1;
        Wait(5);
        PORTAbits.RA2 = 0;
        Wait(5);
        PORTAbits.RA2 = 1;
        Wait(5);
        PORTAbits.RA2 = 0;
        Wait(20);

        PORTAbits.RA1 = 1;
        Wait(5);
        PORTAbits.RA1 = 0;
        Wait(5);
        PORTAbits.RA1 = 1;
        Wait(5);
        PORTAbits.RA1 = 0;
        Wait(5);
        PORTAbits.RA1 = 1;
        Wait(5);
        PORTAbits.RA1 = 0;
        Wait(5);
        PORTAbits.RA1 = 1;
        Wait(5);
        PORTAbits.RA1 = 0;
        Wait(20);
    }
}