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
    uint8_t charNoNumerico = 0;
    uint16_t validarCoordX = 0;
    uint16_t validarCoordY = 0;
    printf("X:\n");
    coordXCentenas = receive();
    coordXDecenas = receive();
    coordXUnidades = receive();
    printf("Y:\n");
    coordYCentenas = receive();
    coordYDecenas = receive();
    coordYUnidades = receive();
    validarCoordX = ((coordXCentenas - 48)*100)+((coordXDecenas - 48)*10)+(coordXUnidades - 48);
    validarCoordY = ((coordYCentenas - 48)*100)+((coordYDecenas - 48)*10)+(coordYUnidades - 48);
    if (coordXCentenas > 57 || coordXCentenas < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (coordXDecenas > 57 || coordXDecenas < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (coordXUnidades > 57 || coordXUnidades < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (coordYCentenas > 57 || coordYCentenas < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (coordYDecenas > 57 || coordYDecenas < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (coordYUnidades > 57 || coordYUnidades < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (((validarCoordX > 300) || (validarCoordY > 300)) || (charNoNumerico == 1)) {
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
        moverHaciaX(coordXCentenas, coordXDecenas, coordXUnidades);
        moverHaciaY(coordYCentenas, coordYDecenas, coordYUnidades);
        printf("Ok,comF\n");
    }
}

void funcionToques(void) {
    uint8_t charNoNumerico = 0;
    printf("TocarPantalla:\n");
    presionarZCentenas = receive(); //Guarda el valor de las centenas a presionar el eje Z de una coordenada
    presionarZDecenas = receive(); //Guarda el valor de las decenas a presionar el eje Z de una coordenada
    presionarZUnidades = receive(); //Guarda el valor de las unidades a presionar el eje Z de una coordenada
    if (presionarZCentenas > 57 || presionarZCentenas < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (presionarZDecenas > 57 || presionarZDecenas < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (presionarZUnidades > 57 || presionarZUnidades < 48) {
        //Si el caracter recibido no es valido se activa la bandera charNoNumerico
        charNoNumerico = 1;
    }
    if (charNoNumerico == 1) {
        printf("E,cNoV\n");
    } else {
        presionarPantalla(presionarZCentenas, presionarZDecenas, presionarZUnidades);
        printf("Ok,comF\n");
    }
}

void slidePiston(void) {
    uint8_t selection;
    selection = receive();
    if (selection == '1') {
        piston = 1; //Trabaja con logica contraria
        printf("Ok,comF\n");
    } else if (selection == '0') {
        piston = 0;
        printf("Ok,comF\n");
    } else {
        printf("E,cNoV\n");
        //Por seguridad se va a retraer el piston
        piston = 1;
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
    enableMotoresZ = 1;
    while (OkEncendido == 0) {
        if (PORTAbits.RA5 == 1) {
            __delay_ms(10);
            if (PORTAbits.RA5 == 1) {
                printf("\nSaliendo\n");
                apagarZ();
                enableMotoresZ = 0;
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
                apagarZ();
            }
        }
        if (PORTCbits.RC5 == 1) {
            __delay_ms(10);
            if (PORTCbits.RC5 == 1) {
                printf("MovABajo\n");
                do {
                    moverZAbajo();
                } while (PORTCbits.RC5 == 1);
                apagarZ();
            }
        }
    }
}