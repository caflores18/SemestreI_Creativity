// Seccion de liberias 
#include <xc.h>
#include "Gpio.h"
#include "UART.h"
#include "PWMCCP2.h"
#include "PWMCCP1.h"
#include "ADC.h"
#include "Interrupciones.h"
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

struct SystemaSPARC {
    int xWanted; //coordenada X objetivo
    int yWanted; //coordenada Y objetivo
    unsigned long timesToPress; //Numero de veces a presionar la pantalla
} coordinates;
//Procedimiento Motor X
int xToAdvance; // X por avanzar en pasos (Xa)
int CurrentPosX = 0; // X current posicion actual X (Xc)
unsigned char leercoordx[3]; //Guarda el valor coord X
//Procedimiennto Motor Y
int yToAdvance; // Y por avanzar en pasos (Ya)
int CurrentPosY = 0; // Y current posicion actual (Yc)
unsigned char leerCoordy[3]; //Guarda el valor coord Y
//void movMotorX(unsigned char)

void main(void) {
    portInit();
    UARTinit();
    //PWM_CCP2_init();
    //PWM_CCP1_init();
    //habilitarIntExternas();
    //interruptsEnable();
    //ADCinit(); 
    motorXinit();
    motorYinit();
    //Inicio del ciclo infinito 
    while (1) {
        unsigned char inutil = receive();
        //  Pregunta coordenadas X
        printf("Empieza nueva instruccion dame tu coordenada x\n"); //Envia salto de linea
        /*leercoordx[0] = receive();
        leercoordx[1] = receive();
        leercoordx[2] = receive();*/
        send(0xD); //Envia salto de linea
        //Pregunta coordenadas Y
        printf("Empieza nueva instruccion dame tu coordenada Y\n"); //Envia salto de linea
        leerCoordy[0] = receive();
        leerCoordy[1] = receive();
        leerCoordy[2] = receive();
        send(0xD); //Envia salto de linea
        //Procedimiento X
        /*coordinates.xWanted = ((leercoordx[0] - 48)*100)+((leercoordx[1] - 48)*10)+(leercoordx[2] - 48);
        xToAdvance = coordinates.xWanted - CurrentPosX; //X por avanzar es xWanted menos CurrentPosX
        xToAdvance = xToAdvance *5;
        printf("xToAdvance is:");
        send(xToAdvance);
        if (xToAdvance > 0) { //Si el valor por recorrer es positivo
            dirMotorX = 1; //El motor se mueve hacia un lado
        } else if (xToAdvance < 0) {//Si el valor por recorrer es negativo
            dirMotorX = 0; //El motor se mueve al otro lado
        }
        send(abs(xToAdvance));
        for (unsigned int i = 0; i < abs(xToAdvance); i++) {
            LATAbits.LATA3 = 1; //Se enciende el foco que indica X
            stepX = 1; //Se da un pulso positivo Motor X
            __delay_ms(5);
            stepX = 0; //Se da un pulso positivo Motor X
            __delay_ms(5);
        }
        LATAbits.LATA3 = 0; //Se apaga el foco que indica X
        CurrentPosX = coordinates.xWanted; //Se actualiza el valor actual de la X*/
        //Procedimiento Y
        coordinates.yWanted = ((leerCoordy[0] - 48)*100)+((leerCoordy[1] - 48)*10)+(leerCoordy[2] - 48);
        yToAdvance = coordinates.yWanted - CurrentPosY; //Y por avanzar es yWanted menos CurrentPosY
        yToAdvance = yToAdvance * 5;
        printf("yToAdvance is:");
        send(yToAdvance);
        if (yToAdvance > 0) { //Si el valor por recorrer es positivo
            dirMotorY = 1; //El motor se mueve hacia un lado
        } else if (yToAdvance < 0) {//Si el valor por recorrer es negativo
            dirMotorY = 0; //El motor se mueve al otro lado
        }
        send(abs(yToAdvance));
        for (unsigned int i = 0; i < abs(yToAdvance); i++) {
            LATAbits.LATA2 = 1; //Se enciende el foco que indica Y
            stepY = 1; //Se da un pulso positivo Motor Y
            __delay_ms(5);
            stepY = 0; //Se da un pulso positivo Motor Y
            __delay_ms(5);
        }
        LATAbits.LATA2 = 0; //Se apaga el foco que indica Y
        CurrentPosY = coordinates.yWanted; //Se actualiza el valor actual de la Y*/
    }
}
//--------------Contenido de las funciones -------------
