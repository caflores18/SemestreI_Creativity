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

uint8_t receiveNum(void) {
    errorUART(); //Comprueba si no hubo errores en la comunicacion
    uint8_t recibido = 0;
    while (recibido > 57 || recibido < 48) {
        //Ciclo que checa que los caracteres introducidos sean valor del 0 al 9 en ASCII, se rompe cuando un caracter valido es introducido
        while (PIR1bits.RCIF == 0) {
            // Mientras RCRGEG1 este vacio no se hace nada hasta
        } //Cuando se lleno
        recibido = RCREG1; // se guarda lo que llego de RCREG1 en viene
        RCREG1 = 0; //Se resetea el registro recibidor
        if (recibido > 57 || recibido < 48) {
            //Si el caracter recibido no es valido se imprime un error y se regresa a escanear un valor valido
            printf("Solo puedes introducir numeros, prueba de nuevo");
        }
    }
    return recibido; //Cuando el caracter leido es valido, se hace un regreso del valor 
}
