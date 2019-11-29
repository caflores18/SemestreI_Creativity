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
    unsigned int xWanted; //coordenada X objetivo
    unsigned int yWanted; //coordenada Y objetivo
    unsigned long timesToPress; //Numero de veces a presionar la pantalla
} coordinates;
//Procedimiento Motor X
unsigned int xToAdvance; // X por avanzar en pasos (Xa)
unsigned int CurrentPosX = 0; // X current posicion actual X (Xc)
//unsigned char leercoordx[3]; //Guarda el valor coord X
//Procedimiennto Motor Y
unsigned int yToAdvance; // Y por avanzar en pasos (Ya)
unsigned int CurrentPosY = 0; // Y current posicion actual (Yc)
//unsigned char leerCoordy[3]; //Guarda el valor coord Y
//Procedimiento compartido (X) y (Y)
unsigned char sparcEnMovimiento = 0; //Esta variable se prende cuando alguno de los motores se va a mover
//----------------------------  ESTAS VARIABLES SE COMPARTEN TANTO PARA X como para Y  ------------------------------
void moverHaciaY(uint8_t coordYCentenas, uint8_t coordYDecenas, uint8_t coordYUnidades);
#endif	/* MOTORESXY_H */





