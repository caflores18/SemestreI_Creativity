// -------------------Seccion de liberias------------------------   
#include <xc.h>
#include "Gpio.h"
#include "UART.h"
#include "Comunicacion.h"
#include "PWMCCP2.h"
#include "PWMCCP1.h"
#define ledRojo         LATBbits.LATB5
#define ledVerde        LATBbits.LATB6
#define ledAzul         LATBbits.LATB7
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
    TRISBbits.RB5 = 0; //Se declara el pin para LED ROJO como output
    TRISBbits.RB6 = 0; //Se declara el pin para LED VERDE como output
    TRISBbits.RB7 = 0; //Se declara el pin para LED AZUL como output
    ledRojo = 0;
    ledVerde = 0;
    ledAzul = 0;
    while (1) {
        ledRojo = 1;
        __delay_ms(250);
        ledRojo = 0;
        __delay_ms(250);
        ledVerde = 1;
        __delay_ms(250);
        ledVerde = 0;
        __delay_ms(250);
        ledAzul = 1;
        __delay_ms(250);
        ledAzul = 0;
        __delay_ms(250);
    }

}



