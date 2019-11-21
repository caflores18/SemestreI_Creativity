// -------------------Seccion de liberias------------------------   
#include <xc.h>
#include "Gpio.h"
#include "UART.h"
#include "PWMCCP2.h"
#include "PWMCCP1.h"
#include "ADC.h"
//ISR de alta prioridad

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
    PWM_CCP2_init();
    PWM_CCP1_init();
    ADCinit();
    while (1) {
        unsigned char entrada = receive();
        if (entrada == '1') {
            unsigned int valorADC = ADCvalue();
        send((valorADC >> 8));
            printf(",");
            send((unsigned char) valorADC);
            entrada = 0;
        }
    }
}




