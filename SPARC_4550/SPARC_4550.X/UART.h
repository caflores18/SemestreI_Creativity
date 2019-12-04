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
//Funcion encargada de inicializar registros y pines encargados de la comunicacion UART
unsigned char receive(); 
    //Se declara la funcion para enviar un caracter
void send(unsigned char enviarpc); 
    //Se declara la funcion para recibir un caracter
void printf (unsigned char *PointString);
    /*Se declara la funcion para imprimir una string, toma el dato del apuntador
    Imprime todo hasta un maximo de 255 caracteres o hasta que encuentra un 
    Caracter nulo */
void scanf (unsigned char *guardarscan, unsigned char numcaracteres);
    //Se escanea un numcaracteres y se guarda en el arreglo guardarscan
void errorUART(void);
//Funcion que verifica si ha habido problemas de comunicacion UART y en caso
//de tenerlos reinicia la comunicacion
#endif	/* UART_H */

