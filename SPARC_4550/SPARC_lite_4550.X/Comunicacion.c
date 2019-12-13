#include <xc.h>
#include <pic18f4550.h>
#include "Comunicacion.h"
#include "UART.h"

void printf(uint8_t *PointString) {
    errorUART(); //Comprueba si no hubo errores en la comunicacion
    for (unsigned char i = 0; i < 255; i++) {
        //Ciclo encargada de imprmir caracteres hasta que se encuentra uno nulo o se llega a los 255
        if (PointString[i] == NULL) {
            break;
        } else
            send(PointString[i]); //Se envia el caracter i de la cadena de caracteres PointString
    }
}

void scanf(uint8_t *guardarscan, uint8_t numcaracteres) {
    errorUART(); //Comprueba si no hubo errores en la comunicacion
    for (uint8_t i = 0; i < numcaracteres; i++) {
        //Ciclo encargado de recibir cierto numero de caracteteres, los cuales van a ser guardados en el arreglo de guardarscan
        guardarscan[i] = receive();
    }
}
