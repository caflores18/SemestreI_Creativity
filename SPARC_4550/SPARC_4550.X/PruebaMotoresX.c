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
unsigned char leerCoordx[3]; //Guarda el valor coord X
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
        CurrentPosX = coordinates.xWanted; //Se actualiza el valor actual de la Y*/
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
    PWM_CCP2_init(); //Se usara CCP2 para mover el motor X    motorXinit();
    PWM_DutyCycleCCP2(0);
    PWM_DutyCycleCCP1(0);
    interruptsEnable();
    motorYinit();
    motorXinit();
    tmr0Init();
    INTCONbits.TMR0IE = 1; //Se enciende del TMR0    
    PWM_CCP1_init();
    //habilitarIntExternas();
    //ADCinit(); 
    //Inicio del ciclo infinito 
    while (1) {
        if (working == 0) {
            unsigned char inutil = receive();
            inutil = 0;
            //Pregunta coordenadas X
            printf("Empieza nueva instruccion dame tu coordenada X\n"); //Envia salto de linea
            leerCoordx[0] = receive();
            leerCoordx[1] = receive();
            leerCoordx[2] = receive();
            printf("La coordenada que he recibido es: ");
            send(leerCoordx[0]);
            send(leerCoordx[1]);
            send(leerCoordx[2]);
            send(0xD); //Envia salto de linea
            //Procedimiento X
            coordinates.xWanted = ((leerCoordx[0] - 48)*100)+((leerCoordx[1] - 48)*10)+(leerCoordx[2] - 48);
            xToAdvance = (abs(coordinates.xWanted - CurrentPosX))*5; //X por avanzar es xWanted menos CurrentPosX
            printf("xToAdvance is:");
            send(xToAdvance);
              send('\n');
            if (coordinates.xWanted > CurrentPosX) { //Si el valor por recorrer es positivo
                dirMotorX = 1; //El motor se mueve hacia un lado
            } else if (coordinates.xWanted < CurrentPosX) {//Si el valor por recorrer es negativo
                dirMotorX = 0; //El motor se mueve al otro lado
            }
            if (coordinates.xWanted != CurrentPosX) {
                working = 1; 
                LATAbits.LATA2 = 1; //Se enciende el foco que indica Y
                setNumPasosX(xToAdvance);
                PWM_DutyCycleCCP2(50);
            } else if ((coordinates.xWanted == CurrentPosX)) {
                printf("\nYa estas en la coordenada deseada, prueba con otra coordenada\n");
            }
        }
    }
}