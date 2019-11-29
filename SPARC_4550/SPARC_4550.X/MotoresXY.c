#include <stdint.h>
#include "Comunicacion.h"
#include "Gpio.h"
#include "PWMCCP1.h"
#include "PWMCCP2.h"
#include "Timers.h"
#include "UART.h"
#include "MotoresXY.h"
#define _XTAL_FREQ 8000000

// -------------------Declaracion de variables globales------------------------
void moverHaciaY(uint8_t coordYCentenas, uint8_t coordYDecenas , uint8_t coordYUnidades) {
    while (sparcEnMovimiento == 1) {
        //No se hace nada hasta que termine
    }
    //Procedimiento Y
    coordinates.yWanted = ((coordYCentenas - 48)*100)+((coordYDecenas - 48)*10)+(coordYUnidades - 48);
    yToAdvance = (abs(coordinates.yWanted - CurrentPosY))*5; //Y por avanzar es yWanted menos CurrentPosY
    printf("yToAdvance is:");
    send(yToAdvance);
    send('\n');
    if (coordinates.yWanted > CurrentPosY) { //Si el valor por recorrer es positivo
        dirMotorY = 1; //El motor se mueve hacia un lado
    } else if (coordinates.yWanted < CurrentPosY) {//Si el valor por recorrer es negativo
        dirMotorY = 0; //El motor se mueve al otro lado
    }
    if (coordinates.yWanted != CurrentPosY) {
        sparcEnMovimiento = 1;
        LATAbits.LATA2 = 1; //Se enciende el foco que indica Y
        setNumPasosY(yToAdvance);
        PWM_DutyCycleCCP2(50);
    }
}
