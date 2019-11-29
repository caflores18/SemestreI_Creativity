/* 
 * File:   Leds.h
 * Author: Alejandro
 *
 * Created on November 29, 2019, 10:23 AM
 */

#ifndef LEDS_H
#define	LEDS_H
#include <xc.h>
#define ledRojo         LATBbits.LATB5
#define ledVerde        LATBbits.LATB6
#define ledAzul         LATBbits.LATB7
//ISR de alta prioridad
#define _XTAL_FREQ 8000000
void ledsInit(void);
void alertaRojo(void);
void alertaVerde(void);
void alertaAzul(void);
#endif	/* LEDS_H */

