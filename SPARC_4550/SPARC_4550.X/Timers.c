#include <xc.h>
#include <pic18f4550.h>
#include "Timers.h"
#include "Comunicacion.h"
#include "UART.h"

void tmr1Init() {
    //Declaracion de pines para TM1 para motor X (CCP1)
    T1CONbits.TMR1ON = 0; //Se apaga el TMR1 para poder configurarlo
    T1CONbits.RD16 = 1; //Se habilita escritura lectura en una ins 16 bits
    T1CONbits.T1OSCEN = 0; //Se apaga el oscilador TMR1
    T1CONbits.T1RUN = 1; //Device clock from another source
    T1CONbits.TMR1CS = 1; //Se usa el pin RC0 flanco ascendente como contador
    T1CONbits.T1SYNC = 1; //Se sincorniza el reloj externo
    TRISCbits.RC0 = 1; //Se declara RC0 como input, cuenta pulsos PWM CCP1
    TMR1 = 0; //Se inicia el TMR1 en 0
    T1CONbits.TMR1ON = 1; //Se enciende el TMR1 
}

void tmr0Init(void) {
    //Declaracion de pines para TMR0 para motor Y(CCP2)
    T0CONbits.TMR0ON = 0; //TMR0 esta apagado mientras se configura
    T0CONbits.T08BIT = 0; //Se configura el TMR0 de 16 bits
    T0CONbits.T0CS = 1; //Se usa el pin T0CKI como contador de eventos
    T0CONbits.T0SE = 0; //Incremento en transicion ascendente del T0CKI 
    TRISAbits.RA4 = 1; //Se declara A4 como input (PIN DE T0CKI), cuenta pulsos CCP2
    TMR0 = 0; //El valor del timer se inicia en 0
    T0CONbits.TMR0ON = 1; //Se enciende el TMR0 despues de haberlo configurado
}

void setNumPasosX(uint16_t numPasosX) {
    //Funcion encargada de poner el timer a contar los pulsos necesarios para avanzar
    //la distancia requerida 
    if (numPasosX > 0) {
          //Si es mayor a 0 la distancia a recorrer se hace un calculo
        uint16_t resultado = (65537 - numPasosX);
        TMR1H = (resultado >> 8);
        TMR1L = resultado;
    } else {
          //Si es mayor a 0 la distancia a recorrer se hace un calculo
        TMR1H = (65535 >> 8);
        TMR1L = 65535;
    }
}

void setNumPasosY(uint16_t numPasosY) {
    //Funcion encargada de poner el timer a contar los pulsos necesarios para avanzar
    //la distancia requerida 
    if (numPasosY > 0) {
        //Si es mayor a 0 la distancia a recorrer se hace un calculo
        uint16_t resultado = (65536 - numPasosY);
        TMR0H = (resultado >> 8);
        TMR0L = resultado;
    } else {
        //Si no, se deja el timer a un evento de generar interrupcion
        TMR0H = (65535 >> 8);
        TMR0L = 65535;
    }
}
