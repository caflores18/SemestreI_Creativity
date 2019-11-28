// -------------------Seccion de liberias------------------------   
#include <xc.h>
#include "Gpio.h"
#include "UART.h"
#include "PWMCCP2.h"
#include "PWMCCP1.h"
//ISR de alta prioridad
#define _XTAL_FREQ 8000000

__interrupt(high_priority) void high_isr(void) {
    Nop(); //Funcion para consumir un ciclo de instruccion
}
//ISR de baja prioridad 

__interrupt(low_priority) void low_isr(void) {
    Nop(); //Funcion para consumir un ciclo de instruccion
}
// -------------------Declaracion de variables globales------------------------   

void main(void) {
    portInit();
    UARTinit();
    TRISAbits.RA2 = 0;
    while (1) {
        LATAbits.LATA2 = 1;
        __delay_ms(100);
        LATAbits.LATA2 = 0;
        __delay_ms(100);
        send('0');
        printf("Que pedo");
        unsigned char inutil = receive();
        send(49);
        send(inutil + 2);
    }
}




