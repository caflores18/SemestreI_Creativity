
// Seccion de liberias 
#include <xc.h>
#include "Gpio.h"
#include "UART.h"
#include "PWMCCP2.h"
#include "PWMCCP1.h"
#include "ADC.h"
#include "Interrupciones.h"
#include "Comunicacion.h"
#include "Timers.h"
#define _XTAL_FREQ 8000000
// -------------------Declaracion de variables globales------------------------

struct SystemaSPARC {
    unsigned int xWanted; //coordenada X objetivo
    unsigned int yWanted; //coordenada Y objetivo
    unsigned long timesToPress; //Numero de veces a presionar la pantalla
} coordinates;
//Procedimiento Motor X
unsigned int xToAdvance; // X por avanzar en pasos (Xa)
unsigned int CurrentPosX = 0; // X current posicion actual X (Xc)
unsigned char leercoordx[3]; //Guarda el valor coord X
//Procedimiennto Motor Y
unsigned int yToAdvance; // Y por avanzar en pasos (Ya)
unsigned int CurrentPosY = 0; // Y current posicion actual (Yc)
unsigned char leerCoordy[3]; //Guarda el valor coord Y
//Procedimiento compartido (X) y (Y)
unsigned char working = 0; //Esta variable se prende cuando alguno de los motores se va a mover

//ISR de alta prioridad

__interrupt(high_priority) void high_isr(void) {
    if (INTCONbits.TMR0IF = 1) {
        PWM_DutyCycleCCP2(0);
        LATAbits.LATA2 = 0; //Se apaga el foco que indica Y
        CurrentPosY = coordinates.yWanted; //Se actualiza el valor actual de la Y*/
        printf("Interrupcion TMR0, llegaste a coordenada deseada\n");
        working = 0;
        INTCONbits.TMR0IF = 0;
    }
}
//ISR de baja prioridad

__interrupt(low_priority) void low_isr(void) {
    Nop(); //Funcion para consumir un ciclo de instruccion
}

void main(void) {
    portInit();
    UARTinit();
    PWM_CCP1_init(); //Se va a usar CCP1 para mover el motor X
    PWM_CCP2_init(); //Se va a usar CCP1 para mover el motor Y
    PWM_DutyCycleCCP1(0);
    PWM_DutyCycleCCP2(0);
    interruptsEnable(); //Se enciende el sistema de interrupciones
    motorYinit(); //Se inicializa lo necesario para el motor Y
    motorXinit();
    //tmr1Init(); //Se inicializa TMR1
    tmr0Init(); //Se inicializa TMR1
    INTCONbits.TMR0IE = 1; //Se enciende del TMR0
    //habilitarIntExternas();
    //ADCinit(); 

    //Inicio del ciclo infinito 
    while (1) {
        if (working == 0) {
            unsigned char inutil = receive();
            inutil = 0;
            //Pregunta coordenadas Y
            printf("Empieza nueva instruccion, dame tu coordenada Y\n"); //Envia salto de linea
            leerCoordy[0] = receive();
            leerCoordy[1] = receive();
            leerCoordy[2] = receive();
            printf("La coordenada que he recibido es: ");
            send(leerCoordy[0]);
            send(leerCoordy[1]);
            send(leerCoordy[2]);
            send(0xD); //Envia salto de linea
            //Procedimiento Y
            coordinates.yWanted = ((leerCoordy[0] - 48)*100)+((leerCoordy[1] - 48)*10)+(leerCoordy[2] - 48);
            yToAdvance = (abs(coordinates.yWanted - CurrentPosY))*5; //Y por avanzar es yWanted menos CurrentPosY
            //yToAdvance = yToAdvance * 5;
            printf("yToAdvance is:");
            send(yToAdvance);
            send('\n');
            if (coordinates.yWanted > CurrentPosY) { //Si el valor por recorrer es positivo
                dirMotorY = 1; //El motor se mueve hacia un lado
            } else if (coordinates.yWanted < CurrentPosY) {//Si el valor por recorrer es negativo
                dirMotorY = 0; //El motor se mueve al otro lado
            }
            if (coordinates.yWanted != CurrentPosY) {
                working = 1;
                LATAbits.LATA2 = 1; //Se enciende el foco que indica Y
                setNumPasosY(yToAdvance);
                PWM_DutyCycleCCP2(50);
            } else if ((coordinates.yWanted == CurrentPosY)) {
                printf("\nYa estas en la coordenada deseada, prueba con otra coordenada\n");
            }
        }
    }
}