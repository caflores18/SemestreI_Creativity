// -------------------Seccion de liberias------------------------   
#include <xc.h>
#include "Gpio.h"
#include "UART.h"
#include "PWMCCP2.h"
#include "PWMCCP1.h"
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
    //TRISCbits.RC2 = 0; //Se declara el PIN RC2 como output (Para el CCP1)
    //Escribir el duty cycle, con la formula calculada cuando el registro CCPR vale 62.5 se tiene duty cycle de 100%
    while (1) {
        unsigned char loco = receive();
        unsigned char PWMCycle = receive();
        PWM_DutyCycleCCP1(PWMCycle);
        if (loco == '0') {
            printf("El valor del PWMDutyValue es de:");
            send(loco);
            loco = 0;
        }
    }
}



