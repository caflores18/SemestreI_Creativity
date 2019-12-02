#include <xc.h>
#include <pic18f4550.h>
#include "Comunicacion.h"
#include "UART.h"

void printf(unsigned char *PointString) {
    errorUART();
    for (unsigned char i = 0; i < 255; i++) {
        if (PointString[i] == NULL) {
            break;
        } else
            send(PointString[i]);
    }
}

void scanf(unsigned char *guardarscan, unsigned char numcaracteres) {
    errorUART();
    for (unsigned char i = 0; i < numcaracteres; i++) {
        guardarscan[i] = receive();
    }
}

uint8_t receiveNum(void) {
    errorUART();
    unsigned char recibido = 0;
    while (recibido > 57 || recibido < 48) {
        while (PIR1bits.RCIF == 0) {
            // Mientras RCRGEG1 este vacio no se hace nada hasta
        } //Cuando se lleno
        recibido = RCREG1; // se guarda lo que llego de RCREG1 en viene
        RCREG1 = 0; //Se resetea el registro recibidor
        if (recibido > 57 || recibido < 48) {
            printf("Solo puedes introducir numeros, prueba de nuevo");
        }
    }
    return recibido;
}
