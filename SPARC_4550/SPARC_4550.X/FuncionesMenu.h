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
uint8_t coordXCentenas [10]; //Guarda el valor de las centenas de 10 coordenadas de X
uint8_t coordXDecenas [10]; //Guarda el valor de las decenas de 10 coordenadas de X
uint8_t coordXUnidades[10]; //Guarda el valor de las unidades de 10 coordenadas de X
//Para coordenadas Y
uint8_t coordYCentenas [10]; //Guarda el valor de las centenas de 10 coordenadas de Y
uint8_t coordYDecenas [10]; //Guarda el valor de las decenas de 10 coordenadas de Y
uint8_t coordYUnidades[10]; //Guarda el valor de las decenas de 10 coordenadas de Y
//Para el numero de veces a presionar la pantalla
uint8_t presionarZCentenas [10]; //Guarda el valor de las centenas a presionar el eje Z de una coordenada
uint8_t presionarZDecenas [10]; //Guarda el valor de las decenas a presionar el eje Z de una coordenada
uint8_t presionarZUnidades[10]; //Guarda el valor de las unidades a presionar el eje Z de una coordenada
//Para control interno del programa
uint8_t coordenadaNueva = 0;
uint8_t habilitarModCoord = 0;
//uint8_t coordenadaEscrita[10]; //Bandera para saber cuando se ha escrito en cierta coordenada */
void introducirCoordNueva(void);
void imprimirCoordenadas(void);
void modificarCoordenada(void);
void borrarTodasCoordenadas(void);
#endif	/* FUNCIONESMENU_H */

