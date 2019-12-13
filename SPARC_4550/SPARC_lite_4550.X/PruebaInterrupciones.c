// -------------------Seccion de liberias------------------------   
#include <xc.h>
#include "Gpio.h"
#include "UART.h"
#include "PWMCCP2.h"
#include "PWMCCP1.h"
#include "ADC.h"
#include "Interrupciones.h"
#define _XTAL_FREQ 8000000
//ISR de alta prioridad

unsigned char numPresionesBoton0 = 48;
unsigned char numPresionesBoton1 = 48;
unsigned char numPresionesBoton2 = 48;
__interrupt(high_priority) void high_isr(void) {
    if (INTCONbits.INT0IF == 1) {
        __delay_ms(10);
        if (PORTBbits.RB0 == 1) {
            printf("Ya entre una vez INT0\n");
            numPresionesBoton0 = numPresionesBoton0 + 1;
        }
        INTCONbits.INT0IF = 0; //Se apaga la bandera INT0 de interrupcion
    }
    if (INTCON3bits.INT1IF == 1) {
        __delay_ms(10);
        if (PORTBbits.RB1 == 1) {
            printf("Ya entre una vez INT1\n");
            numPresionesBoton1 = numPresionesBoton1 + 1;
        }
        INTCON3bits.INT1IF = 0; //Se apaga la bandera INT0 de interrupcion
    }
        if (INTCON3bits.INT2IF == 1) {
        __delay_ms(10);
        if (PORTBbits.RB2 == 1) {
            printf("Ya entre una vez INT2\n");
            numPresionesBoton2 = numPresionesBoton2 + 1;
        }
        INTCON3bits.INT2IF = 0; //Se apaga la bandera INT0 de interrupcion
    }
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
    habilitarIntExternas();
    interruptsEnable();
    //ADCinit(); 
    while (1) {
        send(numPresionesBoton0);
        send(',');
        send(numPresionesBoton1);
        send(',');
        send(numPresionesBoton2);
        printf("\n");
        __delay_ms(500);
    }
}