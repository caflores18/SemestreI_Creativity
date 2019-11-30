/* 
 * File:   Interrupciones.h
 * Author: Alejandro
 *
 * Created on November 22, 2019, 3:07 PM
 */

#ifndef INTERRUPCIONES_H
#define	INTERRUPCIONES_H
#include <xc.h>
#define intLimitSwitch3Esquinas            INTCONbits.INT0IF       //Se define al bit de la int externa INT0
#define intLimitSwitchHomeX                INTCON3bits.INT1IF      //Se define al bit de la int externa INT1
#define intLimitSwitchHomeY                INTCON3bits.INT2IF      //Se define al bit de la int externa INT2
#define overFlowTMR0                       INTCONbits.TMR0IF       //Se define el bit de interrupcion (overFlow) del TMR0
#define overFlowTMR1                       PIR1bits.TMR1IF         //Se define el bit de interrupcion (overFlow) del TMR1
void interruptsEnable(void);
void interruptsDisable(void);
void habilitarIntExternas(void);
void habilitarIntTMR0(void);
void habilitarIntTMR1(void);
#endif	/* INTERRUPCIONES_H */

