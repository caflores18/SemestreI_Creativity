/* 
 * File:   UART.h
 * Author: Alejandro
 *
 * Created on November 20, 2019, 12:02 PM
 */

#ifndef UART_H
#define	UART_H
#include <xc.h>
void UARTinit(void);
unsigned char receive(); 
    //Se declara la funcion para enviar un caracter
void send(unsigned char enviarpc); 
    //Se declara la funcion para recibir un caracter
void printf (unsigned char *PointString);
    /*Se declara la funcion para imprimir una string, toma el dato del apuntador
    Imprime todo hasta un maximo de 255 caracteres o hasta que encuentra un 
    Caracter nulo */
void scanf (unsigned char *guardarscan, unsigned char numcaracteres);

#endif	/* UART_H */

