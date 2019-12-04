#include <xc.h>
#include <pic18f4550.h>
#include "Interrupciones.h"

void interruptsEnable(void) {
    //Habilitar sistema de interrupciones
    RCONbits.IPEN = 0; //Solo un nivel de interrupciones
    INTCONbits.PEIE = 1; //Enciende peripheral interrupts
    INTCONbits.GIE = 1; //Prende el sistema de interrrupciones
}

void interruptsDisable(void) {
    //Habilitar sistema de interrupciones
    RCONbits.IPEN = 0; //Solo un nivel de interrupciones
    INTCONbits.PEIE = 0; //Apaga peripheral interrupts
    INTCONbits.GIE = 0; //Apaga el sistema de interrrupciones
}

void habilitarIntExternas(void) {
    //--------------Habilitar e inicializar pines de interrupcion externos------
    //INT0
    INTCONbits.INT0IF = 0; //Se garantiza un valor de cero para la INT0
    INTCONbits.INT0IE = 1; //Se habilita la interrupcion INT0
    INTCON2bits.INTEDG0 = 1; //La interrupcion de INT0 genera en flanco ascendente
    TRISBbits.RB0 = 1; //Se declara RB0 como input
    //INT1
    INTCON3bits.INT1F = 0; //Se garantiza un valor de cero para la INT1
    INTCON3bits.INT1IE = 1; //Se habilita la interrupcion INT1
    INTCON2bits.INTEDG1 = 1; //La interrupcion de INT1 se genera en flanco ascendente
    TRISBbits.RB1 = 1; //Se declara RB1 como input
    //INT2
    INTCON3bits.INT2IF = 0; //Se garantiza un valor de cero para la INT2
    INTCON3bits.INT2IE = 1; //Se habilita la interrupcion INT2
    INTCON2bits.INTEDG2 = 1; //La interrupcion de INT2 se genera en flanco ascendente
    TRISBbits.RB2 = 1; //Se declara RB2 como input
}

void habilitarIntTMR0(void) {
    INTCONbits.TMR0IE = 1; //Enciende interrupcion del TMR0  
}

void habilitarIntTMR1(void) {
    PIE1bits.TMR1IE = 1; //Enciende interrupcion del TMR1
}
