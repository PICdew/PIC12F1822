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

main()	{
    unsigned int num;

    OSCCON = 0b01110010;        // Internal clock: 4MHz
    OPTION_REG = 0b00000000;    // Digital I/O use the internal pullup registor
    ANSELA = 0b00000000;        // Analog
    TRISA  = 0b00011000;        // I/O (RA3 is input only)
    WPUA = 0b00010000;          // RA4 is internal pullup registor
    PORTA = 0b00000000;         // Output

    while(1) {
        if (PORTAbits.RA4 == 0) {
            PORTAbits.RA2 = 1;
        } else {
            PORTAbits.RA2 = 0;
        }
    }
}