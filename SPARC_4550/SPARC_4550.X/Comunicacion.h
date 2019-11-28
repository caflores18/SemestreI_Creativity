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
void printf (unsigned char *PointString);
    /*Se declara la funcion para imprimir una string, toma el dato del apuntador
    Imprime todo hasta un maximo de 255 caracteres o hasta que encuentra un 
    Caracter nulo */
void scanf (unsigned char *guardarscan, unsigned char numcaracteres);
    //Se escanea un numcaracteres y se guarda en el arreglo guardarscan
uint8_t receiveNum(void); 
#endif	/* COMUNICACION_H */

