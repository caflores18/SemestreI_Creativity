/* 
 * File:   Leds.h
 * Author: Alejandro
 *
 * Created on November 29, 2019, 10:23 AM
 */

#ifndef LEDS_H
#define	LEDS_H
#include <xc.h>
#define ledRojo         LATBbits.LATB5      //Se define el ledRojo como pin RB5
#define ledVerde        LATBbits.LATB6      //Se define el ledVerde como pin RB6
#define ledAzul         LATBbits.LATB7      //Se define el ledAzul como pin RB7
//ISR de alta prioridad
#define _XTAL_FREQ 8000000
void ledsInit(void); //Inicializa los pines de los leds y los deja apagados
void alertaRojo(void); //Enciende el led Rojo por 250 ms
void alertaVerde(void); //Enciende el led verde por 250 ms
void alertaAzul(void); //Enciende el led azul por 250 ms
#endif	/* LEDS_H */

