#include <xc.h> 
#include <stdint.h> 
#include <pic18f4550.h> 
#include "Gpio.h"
#include "Comunicacion.h" 
#include "UART.h" 
#include "FuncionesMenu.h" 
#include "MotoresXYZ.h"
#define _XTAL_FREQ 8000000 //Se trabaja el programa a 8 Mhz

void moverHaciaXY(void) {
    uint16_t validarCoordX = 0;
    uint16_t validarCoordY = 0;
    //corregirCoord:
    printf("X:\n");
    coordXCentenas = receiveNum();
    coordXDecenas = receiveNum();
    coordXUnidades = receiveNum();
    printf("Y:\n");
    coordYCentenas = receiveNum();
    coordYDecenas = receiveNum();
    coordYUnidades = receiveNum();
    validarCoordX = ((coordXCentenas - 48)*100)+((coordXDecenas - 48)*10)+(coordXUnidades - 48);
    validarCoordY = ((coordYCentenas - 48)*100)+((coordYDecenas - 48)*10)+(coordYUnidades - 48);
    if ((validarCoordX > 300) || (validarCoordY > 300)) {
        printf("Metiste una coordenada invalida, vuelve a intentar\n");
        printf("E,cNoV\n");
        //goto corregirCoord;
    } else {
        printf("Coordenada recibida, lo que recibimos fue:");
        send(coordXCentenas);
        send(coordXDecenas);
        send(coordXUnidades);
        send(',');
        send(coordYCentenas);
        send(coordYDecenas);
        send(coordYUnidades);
        send('\n');
        //Parte de arriba se puede borrar
        moverHaciaY(coordYCentenas, coordYDecenas, coordYUnidades);
        moverHaciaX(coordXCentenas, coordXDecenas, coordXUnidades);
    }
}

void funcionToques(void) {
    printf("TocarPantalla:\n");
    presionarZCentenas = receiveNum(); //Guarda el valor de las centenas a presionar el eje Z de una coordenada
    presionarZDecenas = receiveNum(); //Guarda el valor de las decenas a presionar el eje Z de una coordenada
    presionarZUnidades = receiveNum(); //Guarda el valor de las unidades a presionar el eje Z de una coordenada
    presionarPantalla(presionarZCentenas, presionarZDecenas, presionarZUnidades);
}
void slidePiston(void){
    uint8_t selection;
    selection = receiveNum();
    if(selection == '1'){
        piston = 1;
    }else if (selection == '0'){
        piston = 0;
    }else{
        //Por seguridad se va a retraer el piston
        piston = 0; 
    }
}
void impCoordActual(void) {
    printf("X: ");
    send((CurrentPosX * 0.01) + 48);
    send(((CurrentPosX % 100)*0.1) + 48);
    send(((CurrentPosX % 100) % 10) + 48);
      printf(" ,Y: ");
    send((CurrentPosY * 0.01) + 48);
    send(((CurrentPosY % 100)*0.1) + 48);
    send(((CurrentPosY % 100) % 10) + 48);
    send('\n');
}

void modificarZ(void) {
    uint8_t OkEncendido = 0;
    while (OkEncendido == 0) {
        if (PORTAbits.RA5 == 1) {
            __delay_ms(10);
            if (PORTAbits.RA5 == 1) {
                printf("\nSaliendo\n");
                apagarZ();
                OkEncendido = 1;
            }
        }
        if (PORTCbits.RC4 == 1) {
            __delay_ms(10);
            if (PORTCbits.RC4 == 1) {
                printf("MovArriba\n");
                do {
                    moverZArriba();
                } while (PORTCbits.RC4 == 1);
            }
        }
        if (PORTCbits.RC5 == 1) {
            __delay_ms(10);
            if (PORTCbits.RC5 == 1) {
                printf("MovABajo\n");
                do {
                    moverZAbajo();
                } while (PORTCbits.RC5 == 1);
            }
        }
    }
}