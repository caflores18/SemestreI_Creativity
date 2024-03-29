#include <xc.h>
#include <pic18f4550.h>
#include "UART.h"
#define _XTAL_FREQ 8000000 //Se trabaja el programa a 8 Mhz

void UARTinit(void) {
    TRISCbits.RC6 = 1; //Se declara el TX como output
    TRISCbits.RC7 = 1; //Se declara el RX como input

    SPBRG = 16; //Baudrate de 8 para 115200 de baudrate
    TXSTA1bits.BRGH = 1; // Highrate value  (1)
    BAUDCONbits.BRG16 = 1; //Se usa baudrate de 16 bits cuando activo

    TXSTA1bits.TX9 = 0; // Transmision de 8 bits
    TXSTA1bits.TXEN = 1; //Se permite la transmision 
    TXSTA1bits.SYNC = 0; //Modo asincrono 
    RCSTA1bits.SPEN = 1; // Enciedne TX y RX
    RCSTA1bits.RX9 = 0; //Recepcion a 8 bits 
    RCSTA1bits.CREN = 1; //Habilita recibir
}

uint8_t receive() {
    errorUART(); //Comprueba si no hubo errores en la comunicacion
    uint8_t recibido;
    while (PIR1bits.RCIF == 0) {
        // Mientras RCRGEG1 este vacio nada hasta
    } //Cuando se lleno
    recibido = RCREG1; // se guarda lo que llego de RCREG1 en viene
    RCREG1 = 0; //Se resetea el registro recibidor
    //__delay_ms(10);
    return recibido;
}

void send(uint8_t enviarpc) {
    errorUART(); //Comprueba si no hubo errores en la comunicacion
    while (TXSTA1bits.TRMT == 0) {
        //Mientres TSR este lleno no hace nada 
    } // Cuando se vacio 
    TXREG1 = enviarpc; // Se envia el nuevo caracter al registro de transmision USART
}

void errorUART(void) {
    //Esta funcion no es de mi autoria, ha sido obtenida de:
    //https://investigatronica.wordpress.com/2016/03/10/uso-de-la-uart-en-microcontroladores-se-cuelga-el-micro-o-deja-de-recibir/
    uint8_t temp;
    if (OERR) {//�hubo desborde?
        do {
            temp = RCREG; //limpia pila
            temp = RCREG; //limpia pila
            temp = RCREG; //limpia pila
            temp = RCREG; //limpia pila
            CREN = 0; //deshabilita la recepcion
            CREN = 1; //habilita la recepcion

        } while (OERR);
    }

    if (FERR) {
        temp = RCREG;
        TXEN = 0;
        TXEN = 1;
    }
}