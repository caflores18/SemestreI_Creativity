#include <xc.h>
#include <stdint.h>
#include <pic18f4550.h>
#include "Comunicacion.h"
#include "UART.h"
#include "FuncionesMenu.h"

void introducirCoordNueva() {
    uint16_t validarCoordX = 0;
    uint16_t validarCoordY = 0;
leerCoordValida:
    printf("Introduce en el siguiente orden las variables a usar (no uses las comas): coordX,coordY,# de veces a presionar Z");
    coordXCentenas[coordenadaNueva] = receive();
    coordXDecenas[coordenadaNueva] = receive();
    coordXUnidades[coordenadaNueva] = receive();
    printf("Recibi coordX");
    coordYCentenas[coordenadaNueva] = receive();
    coordYDecenas[coordenadaNueva] = receive();
    coordYUnidades[coordenadaNueva] = receive();
    printf("Recibi coordY");
    presionarZCentenas[coordenadaNueva] = receive();
    presionarZDecenas[coordenadaNueva] = receive();
    presionarZUnidades[coordenadaNueva] = receive();
    printf("Recibi # de veces a presionar Z\n");
    validarCoordX = ((coordXCentenas[coordenadaNueva] - 48)*100)+((coordXDecenas[coordenadaNueva] - 48)*10)+(coordXUnidades[coordenadaNueva] - 48);
    validarCoordY = ((coordYCentenas[coordenadaNueva] - 48)*100)+((coordYDecenas[coordenadaNueva] - 48)*10)+(coordYUnidades[coordenadaNueva] - 48);
    if ((validarCoordX > 300) || (validarCoordY > 300)) {
        printf("Metiste una coordenada invalida\n");
        goto leerCoordValida;
    }
    printf("Coordenada recibida, lo que recibimos fue:");
    send(coordXCentenas[coordenadaNueva]);
    send(coordXDecenas[coordenadaNueva]);
    send(coordXUnidades[coordenadaNueva]);
    send(',');
    send(coordYCentenas[coordenadaNueva]);
    send(coordYDecenas[coordenadaNueva]);
    send(coordYUnidades[coordenadaNueva]);
    send(',');
    send(presionarZCentenas[coordenadaNueva]);
    send(presionarZDecenas[coordenadaNueva]);
    send(presionarZUnidades[coordenadaNueva]);
    send('.');
    coordenadaNueva++;
}
void imprimirCoordenadas(void) {
    uint8_t numCoordenadas = coordenadaNueva + 48;
    printf("Elegiste la opcion de imprimir coordenadas\n");
    printf("Agregaste:");
    if (coordenadaNueva > 9) {
        send('1');
        send('0');
    } else {
        send('numCoordenadas');
    }
    printf("coordenadas, las cuales son: \n");
    for (uint8_t impresionCoordenada = 0; impresionCoordenada < coordenadaNueva; impresionCoordenada++) {
        printf("La coordenada ");
        send(impresionCoordenada + 48);
        printf(" contiene los valores de: ");
        send(coordXCentenas[impresionCoordenada]);
        send(coordXDecenas[impresionCoordenada]);
        send(coordXUnidades[impresionCoordenada]);
        send(',');
        send(coordYCentenas[impresionCoordenada]);
        send(coordYDecenas[impresionCoordenada]);
        send(coordYUnidades[impresionCoordenada]);
        send(',');
        send(presionarZCentenas[impresionCoordenada]);
        send(presionarZDecenas[impresionCoordenada]);
        send(presionarZUnidades[impresionCoordenada]);
        send('.');
        send ('\n');
    }
}
