// -------------------Seccion de liberias------------------------   
#include <xc.h>
#include "Gpio.h"
#include "UART.h"
#include "PWMCCP2.h"
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
    //Escribir el duty cycle, con la formula calculada cuando el registro CCPR vale 62.5 se tiene duty cycle de 100%
    while (1) {
        unsigned char loco = receive();
        unsigned char PWMCycle = receive();
        PWM_DutyCycleCCP2(PWMCycle);
        if (loco == '0') {
            printf("El valor del PWMDutyValue es de:");
            send();
            loco = 0;
        }
    }
}

