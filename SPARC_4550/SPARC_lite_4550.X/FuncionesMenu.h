/* 
 * File:   FuncionesMenu.h
 * Author: Alejandro
 *
 * Created on November 27, 2019, 11:23 AM
 */
#ifndef FUNCIONESMENU_H
#define	FUNCIONESMENU_H
#include <xc.h>
#include <stdint.h>
//Para coordenadas X
uint8_t coordXCentenas ; //Guarda el valor de las centenas de 10 coordenadas de X
uint8_t coordXDecenas ; //Guarda el valor de las decenas de 10 coordenadas de X
uint8_t coordXUnidades; //Guarda el valor de las unidades de 10 coordenadas de X
//Para coordenadas Y
uint8_t coordYCentenas; //Guarda el valor de las centenas de 10 coordenadas de Y
uint8_t coordYDecenas; //Guarda el valor de las decenas de 10 coordenadas de Y
uint8_t coordYUnidades; //Guarda el valor de las decenas de 10 coordenadas de Y
//Para el numero de veces a presionar la pantalla
uint8_t presionarZCentenas; //Guarda el valor de las centenas a presionar el eje Z de una coordenada
uint8_t presionarZDecenas; //Guarda el valor de las decenas a presionar el eje Z de una coordenada
uint8_t presionarZUnidades; //Guarda el valor de las unidades a presionar el eje Z de una coordenada
//Para control interno del programa
uint8_t coordenadaNueva = 0; //Variable que guarda el valor de las coordenadas que se han puesto en la rutina
uint8_t habilitarModCoord = 0; //Bandera usada para habilitar la edicion de una coordenada
//uint8_t coordenadaEscrita[10]; //Bandera para saber cuando se ha escrito en cierta coordenada */
void moverHaciaXY(void); //Funcion encargada de anadir una coordenada al sistema
void funcionToques(void); //Funcion encargada de tocar la pantalla
void slidePiston(void); //Se decide si el piston se deja activado para hacer slide o no
void impCoordActual(void); //Funcion encargada de imprimir las coordenadas de posicion actuales del SPARC
void modificarZ(void); //Funcion encargada de modificar la altura de la base del sistema 
#endif	/* FUNCIONESMENU_H */

