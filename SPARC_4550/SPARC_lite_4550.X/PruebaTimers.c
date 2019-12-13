// Seccion de liberias 
#include <xc.h>
#include <pic18f4550.h>
#include "Gpio.h"
#include "UART.h"
#include "PWMCCP2.h"
#include "PWMCCP1.h"
#include "ADC.h"
#include "Interrupciones.h"
#include "Comunicacion.h"
#include "Timers.h"
#define _XTAL_FREQ 8000000

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
    //PWM_CCP2_init();
    //PWM_CCP1_init();
    //habilitarIntExternas();
    //ADCinit(); 
    //motorXinit();
    //motorYinit();

    //PruebasExtras TMR0
    TRISDbits.RD1 = 0; //Se declara como output RD1
    LATDbits.LATD1 = 0; //Se inicializa en 0 el RD1
    TRISCbits.RC1 = 0; //Se declara como output RD1
    LATCbits.LATC1 = 1; //Se inicializa en 0 el RD1
    //interruptsEnable();
    tmr1Init();
    tmr0Init();
    //Inicio del ciclo infinito 
    while (1) {
        unsigned char leer = receive();
        if (leer == '0') {
            printf("El valor del TMR0 es de:");
            for (unsigned char i = 0; i < 10; i++) {
                LATDbits.LATD1 = 1; //Se inicializa en 0 el RD1
                __delay_ms(1);
                LATDbits.LATD1 = 0; //Se inicializa en 0 el RD1
                 __delay_ms(1);
                //Nop(); //Funcion para consumir un ciclo de instruccion
            }
            send(TMR0);
            send('\n');
            leer = 0;
        }
        if (leer == '1') {
            TMR0 = 0;
            printf("Resetee este pedo salu2");
            leer = 0;
        }
    }
}
//--------------Contenido de las funciones -------------
