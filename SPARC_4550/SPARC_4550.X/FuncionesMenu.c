#include <xc.h> 
#include <stdint.h> 
#include <pic18f4550.h> 
#include "Comunicacion.h" 
#include "UART.h" 
#include "FuncionesMenu.h" 

void introducirCoordNueva() {
    uint16_t validarCoordX = 0;
    uint16_t validarCoordY = 0;
    if ((coordenadaNueva < 10) || (habilitarModCoord == 1)) {
corregirCoord:
        printf("Introduce en el siguiente orden las variables a usar (no uses las comas): coordX,coordY,# de veces a presionar Z");
        coordXCentenas[coordenadaNueva] = receiveNum();
        coordXDecenas[coordenadaNueva] = receiveNum();
        coordXUnidades[coordenadaNueva] = receiveNum();
        printf("Recibi coordX");
        coordYCentenas[coordenadaNueva] = receiveNum();
        coordYDecenas[coordenadaNueva] = receiveNum();
        coordYUnidades[coordenadaNueva] = receiveNum();
        printf("Recibi coordY");
        presionarZCentenas[coordenadaNueva] = receiveNum();
        presionarZDecenas[coordenadaNueva] = receiveNum();
        presionarZUnidades[coordenadaNueva] = receiveNum();
        printf("Recibi # de veces a presionar Z\n");
        validarCoordX = ((coordXCentenas[coordenadaNueva] - 48)*100)+((coordXDecenas[coordenadaNueva] - 48)*10)+(coordXUnidades[coordenadaNueva] - 48);
        validarCoordY = ((coordYCentenas[coordenadaNueva] - 48)*100)+((coordYDecenas[coordenadaNueva] - 48)*10)+(coordYUnidades[coordenadaNueva] - 48);
        if ((validarCoordX > 300) || (validarCoordY > 300)) {
            printf("Metiste una coordenada invalida\n");
            goto corregirCoord;
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
        if (habilitarModCoord == 0) {
            printf("Has agregado este numero de coordenadas:");
            coordenadaNueva++;
            send(coordenadaNueva + 48);
        }
    } else {
        printf("Ya estan las 10 coordenadas llenas, no puedes agregar mas");
    }
}

void imprimirCoordenadas(void) {
    uint8_t numCoordenadas = 0;
    numCoordenadas = coordenadaNueva + 48;
    printf("Agregaste: ");
    send(numCoordenadas);
    printf(" coordenadas, las cuales son: \n");
    for (uint8_t impresionCoordenada = 0; impresionCoordenada < coordenadaNueva; impresionCoordenada++) {
        printf("Coordenada ");
        send(impresionCoordenada + 48);
        printf(": ");
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
        send('\n');
    }
}

void modificarCoordenada(void) {
    habilitarModCoord = 1; //Habilita que se puede ejecutar la funcion de agregar coordenada
    uint8_t modCoord, coordenadaNuevaCopia; //Variable que almacena coordenada a modificar
    habilitarModCoord = 1; //Habilita que se puede ejecutar la funcion de agregar coordenada, pues en esta funcion se usa para modificar un valor
    imprimirCoordenadas();
    printf("Cual de estas coordenadas quieres modificar?\n");
    modCoord = receiveNum();
    while ((modCoord - 48) >= coordenadaNueva) { //Si se intenta modificar alguna coordenada que aun no se ha recibido
        printf("Error, estas queriendo modificar una coordenada que aun no agregas\n");
        printf("Cual coordenada quieres modificar, elige valores validos?\n");
        modCoord = receiveNum();
    }
    printf("Vas a modificar la coordenada ");
    send(modCoord);
    send('\n');
    modCoord = modCoord - 48;
    coordenadaNuevaCopia = coordenadaNueva; //Se guarda una copia de la variable coordenadaNueva
    coordenadaNueva = modCoord; //Se modifica el valor de coordenadaNueva para modificar es  numero de coordenada en la funcion introducirCoordNueva
    introducirCoordNueva(); //Se usa la funcion introducirCoordNueva para modificar una coordenada
    coordenadaNueva = coordenadaNuevaCopia; //Se regresa el valor de coordenadaNueva al original
    habilitarModCoord = 0; //Deshabilita que se puede ejecutar la funcion de agregar coordenada, para no generar OVF
}

void borrarTodasCoordenadas(void) {
    for (uint8_t impresionCoordenada = 0; impresionCoordenada < 10; impresionCoordenada++) {
        coordXCentenas[impresionCoordenada] = 0;
        coordXDecenas[impresionCoordenada] = 0;
        coordXUnidades[impresionCoordenada] = 0;
        coordYCentenas[impresionCoordenada] = 0;
        coordYDecenas[impresionCoordenada] = 0;
        coordYUnidades[impresionCoordenada] = 0;
        presionarZCentenas[impresionCoordenada] = 0;
        presionarZDecenas[impresionCoordenada] = 0;
        presionarZUnidades[impresionCoordenada] = 0;
    }
    coordenadaNueva = 0;
    printf("Listo, todas las coordenadas han sido borradas\n");
}