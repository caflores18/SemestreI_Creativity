#include <xc.h>
#include <pic18f4550.h>
#include "Comunicacion.h"
#include "UART.h"
void printf(unsigned char *PointString) {
    for (unsigned char i = 0; i < 255; i++) {
        if (PointString[i] == NULL) {
            break;
        } else
            send(PointString[i]);
    }
}
void scanf(unsigned char *guardarscan, unsigned char numcaracteres) {
    for (unsigned char i = 0; i < numcaracteres; i++) {
        guardarscan[i] = receive();
    }
}
