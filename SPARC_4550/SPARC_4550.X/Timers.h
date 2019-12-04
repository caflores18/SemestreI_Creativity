/* 
 * File:   Timers.h
 * Author: Alejandro
 *
 * Created on November 25, 2019, 3:22 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H
#include <xc.h>
#include <stdint.h>
void tmr0Init(void); //Se inicializan los registros para que el TMR0 sea contador de eventos
void tmr1Init(void); //Se inicializan los registros para que el TMR1 sea contador de eventos
void setNumPasosX(uint16_t numPasosX); //Funcion para poner a contar al TMR0 los pasos requeridos
void setNumPasosY(uint16_t numPasosY); //Fucnion para poner a contar al TMR1los pasos requeridos

#endif	/* TIMERS_H */

