/* 
 * File:   Comunicacion.h
 * Author: Alejandro
 *
 * Created on November 25, 2019, 11:29 AM
 */
#ifndef COMUNICACION_H
#define	COMUNICACION_H
#include <xc.h>
#include <stdint.h>
void printf (uint8_t *PointString);
    /*Se declara la funcion para imprimir por UART una serie de caracteres (maximo 255)
     * hasta que se encuentra un caracter nulo */
void scanf (uint8_t *guardarscan, uint8_t numcaracteres);
    //Se escanea por UART un numero de caracteres y se guarda en el arreglo guardarscan
uint8_t receiveNum(void); //Funcion para recibir numeros (por UART)
#endif	/* COMUNICACION_H */

