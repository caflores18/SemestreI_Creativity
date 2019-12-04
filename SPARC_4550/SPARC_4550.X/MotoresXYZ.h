/* 
 * File:   MotoresXY.h
 * Author: Alejandro
 *
 * Created on November 28, 2019, 4:53 PM
 */

#ifndef MOTORESXY_H
#define	MOTORESXY_H
#include <xc.h>
#include <stdint.h>
struct SystemaSPARC {
    uint16_t xWanted; //coordenada X objetivo
    uint16_t yWanted; //coordenada Y objetivo
    uint16_t timesToPress; //Numero de veces a presionar la pantalla
} coordinates;
//Procedimiento Motor X
uint16_t xToAdvance; // X por avanzar en pasos (Xa)
uint16_t CurrentPosX = 0; // X current posicion actual X (Xc)
//unsigned char leercoordx[3]; //Guarda el valor coord X
//Procedimiennto Motor Y
uint16_t yToAdvance; // Y por avanzar en pasos (Ya)
uint16_t CurrentPosY = 0; // Y current posicion actual (Yc)
//unsigned char leerCoordy[3]; //Guarda el valor coord Y
//Procedimiento compartido (X) y (Y)
uint8_t sparcEnMovimiento = 0; //Esta variable se prende cuando alguno de los motores se va a mover
//extraaa sparcMovY
uint8_t destinoHomeX = 0;   //Variable que indica que el destino de coord sera HomeX 
uint8_t destinoHomeY = 0;   //Variable que indica que el destino de coord sera HomeY
uint8_t llegoHomeX = 0;   //Variable que indica que el destino de coord sera HomeX 
uint8_t llegoHomeY = 0;   //Variable que indica que el destino de coord sera HomeY
//----------------------------  ESTAS VARIABLES SE COMPARTEN TANTO PARA X como para Y  ------------------------------
void moverHaciaY(uint8_t coordYCentenas, uint8_t coordYDecenas, uint8_t coordYUnidades);
//Mueve los motores en direccion de Y cierta distancia
void moverHaciaX(uint8_t coordXCentenas, uint8_t coordXDecenas, uint8_t coordXUnidades); 
//Mueve los motores en direccion de X cierta distancia
void moverHomeX(void);  
//Se mueven los motores de X al origen
void moverHomeY(void); 
//Se mueven los motores de Y al origen
void moverXInfinito(void); 
//Se mueven los motores X indefinidamente (para probar funcionamiento limit switches)
void moverYInfinito(void); 
//Se mueven los motores Y indefinidamente (para probar funcionamiento limit switches)
void presionarPantalla(uint8_t presionarZCentenas, uint8_t presionarZDecenas, uint8_t presionarZUnidades); 
//Se activa el piston cierto numero de veces
void moverZArriba(void);
//Se mueven los motores de la base hacia arriba
void moverZAbajo(void);
//Se mueven los motores de la base hacia abajo
void apagarZ(void);
//Se apagan los motores de la base
#endif	/* MOTORESXY_H */
