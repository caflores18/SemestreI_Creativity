#include <stdint.h>
#include "Comunicacion.h"
#include "Gpio.h"
#include "PWMCCP1.h"
#include "PWMCCP2.h"
#include "Timers.h"
#include "UART.h"
#include "MotoresXYZ.h"
#define _XTAL_FREQ 8000000

// -------------------Declaracion de variables globales------------------------

void moverHaciaY(uint8_t coordYCentenas, uint8_t coordYDecenas, uint8_t coordYUnidades) {
    while (sparcEnMovimientoY == 1) {
        //No se hace nada hasta que termine de moverse la coordenada anterior de Y
    }
    //Procedimiento Y
    coordinates.yWanted = ((coordYCentenas - 48)*100)+((coordYDecenas - 48)*10)+(coordYUnidades - 48);
    yToAdvance = (abs(coordinates.yWanted - CurrentPosY))*5; //Y por avanzar es yWanted menos CurrentPosY
    if (coordinates.yWanted > CurrentPosY) { //Si el valor por recorrer es positivo
        dirMotorY = 0; //El motor se mueve hacia un lado
    } else if (coordinates.yWanted < CurrentPosY) {//Si el valor por recorrer es negativo
        dirMotorY = 1; //El motor se mueve al otro lado
    }
    if (coordinates.yWanted != CurrentPosY) {
        printf("yToAdvance is:");
        send(yToAdvance);
        send('\n');
        sparcEnMovimientoY = 1;
        //Se activa la bandera de que se estara moviendo el eje Y
        setNumPasosY(yToAdvance);
        //Se utiliza el timer 0 como contador de eventos para contar los pulsos requeridos
        //por el PWM para avanzar la distancia necesaria
        //PWM_DutyCycleCCP1(0);
        //Se deja el ciclo de trabajo de X en 0
        PWM_DutyCycleCCP2(50);
        //Se deja el ciclo de trabajo de Y EN 50 %
    } else printf("E,coorAcY\n");
}

void moverHaciaX(uint8_t coordXCentenas, uint8_t coordXDecenas, uint8_t coordXUnidades) {
    while (sparcEnMovimientoX == 1) {
        //No se hace nada hasta que termine de moverse a la coordenada anterior de X
    }
    //Procedimiento X
    coordinates.xWanted = ((coordXCentenas - 48)*100)+((coordXDecenas - 48)*10)+(coordXUnidades - 48);
    xToAdvance = (abs(coordinates.xWanted - CurrentPosX))*5; //X por avanzar es xWanted menos CurrentPosX

    if (coordinates.xWanted > CurrentPosX) { //Si el valor por recorrer es positivo
        dirMotorX = 0; //El motor se mueve hacia un lado
    } else if (coordinates.xWanted < CurrentPosX) {//Si el valor por recorrer es negativo
        dirMotorX = 1; //El motor se mueve al otro lado
    }
    if (coordinates.xWanted != CurrentPosX) {
        printf("xToAdvance is:");
        send(xToAdvance);
        send('\n');
        sparcEnMovimientoX = 1;
        //Se activa la bandera de que se estara moviendo el eje X
        setNumPasosX(xToAdvance);
        //Se utiliza el timer 0 como contador de eventos para contar los pulsos requeridos
        //por el PWM para avanzar la distancia necesaria
        //PWM_DutyCycleCCP2(0);
        //Se deja el ciclo de trabajo de Y en 0%
        PWM_DutyCycleCCP1(50);
        //Se deja el ciclo de trabajo de X en 50%
    } else printf("E,coorAcX\n");
}

void presionarPantalla(uint8_t presionarZCentenas, uint8_t presionarZDecenas, uint8_t presionarZUnidades) {
    coordinates.timesToPress = ((presionarZCentenas - 48)*100)+((presionarZDecenas - 48)*10)+(presionarZUnidades - 48);
    //Se calcula el numero de veces a presionar la pantalla
    if (coordinates.timesToPress != 0) {
        //ciclo para activar y desactivar el piston
        for (uint8_t toques = 0; toques < coordinates.timesToPress; toques++) {
            piston = 1;
            __delay_ms(100);
            piston = 0;
            __delay_ms(100);
        }
    }
}

void moverHomeX(void) {
    destinoHomeX = 1;
    //se activa la bandera de que X se dirigira al origen
    dirMotorX = 0; //Se da la direccion necesaria 
    sparcEnMovimientoX = 1;
    //Se activa la bandera de que se estara moviendo el eje X
    PWM_DutyCycleCCP1(50);
    //Se deja el ciclo de trabajo de X en 50%
}

void moverHomeY(void) {
    destinoHomeY = 1;
    //se activa la bandera de que X se dirigira al origen
    dirMotorY = 0;
    sparcEnMovimientoY = 1;
    //Se activa la bandera de que se estara moviendo el eje Y
    //PWM_DutyCycleCCP1(0);
    PWM_DutyCycleCCP2(50);
    //Se deja el ciclo de trabajo de Y en 50%
}

void moverXInfinito() {
    //Se activa el movimiento de X hacia alguno de los lim swithc de las esquinas ajenos al home
    dirMotorX = 1;
    //se da la direccion necesaria para ir en sentido contrario a home
    sparcEnMovimientoX = 1;
    //Se activa la bandera de que se estara moviendo el eje X
    //PWM_DutyCycleCCP2(0);
    PWM_DutyCycleCCP1(50);
}

void moverYInfinito() {
    //Se activa el movimiento de X hacia alguno de los lim swithc de las esquinas ajenos al home
    dirMotorY = 1;
    //se da la direccion necesaria para ir en sentido contrario a home
    sparcEnMovimientoY = 1;
    //Se activa la bandera de que se estara moviendo el eje Y
    //PWM_DutyCycleCCP1(0);
    PWM_DutyCycleCCP2(50);
}

void moverZArriba(void) {
    LATDbits.LATD5 = 1; //Se enciende la salida RD5
    LATDbits.LATD6 = 0; //Se enciende la salida RD6
}

void moverZAbajo(void) {
    LATDbits.LATD5 = 0; //Se apaga la salida RD5
    LATDbits.LATD6 = 1; //Se apaga la salida RD6
}

void apagarZ(void) {
    LATDbits.LATD5 = 0; //Se apaga la salida RD5
    LATDbits.LATD6 = 0; //Se apaga la salida RD6
}