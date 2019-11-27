/* 
 * File:   Interrupciones.h
 * Author: Alejandro
 *
 * Created on November 22, 2019, 3:07 PM
 */

#ifndef INTERRUPCIONES_H
#define	INTERRUPCIONES_H
#include <xc.h>
void interruptsEnable(void);
void interruptsDisable(void);
void habilitarIntExternas(void);
void habilitarIntTMR0(void);
void habilitarIntTMR1(void);
#endif	/* INTERRUPCIONES_H */

