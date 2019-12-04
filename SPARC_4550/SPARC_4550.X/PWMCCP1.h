/* 
 * File:   PWMCCP1.h
 * Author: Alejandro
 *
 * Created on November 20, 2019, 6:08 PM
 */

#ifndef PWMCCP1_H
#define	PWMCCP1_H
#include <xc.h>
void PWM_CCP1_init(void); 
//Inicializa los registros y valores necesarios para encender el CCP1
void PWM_DutyCycleCCP1(unsigned char WantedDutyCycle);
//Se obtiene el valor de porcentaje a poner el dutycycle del CCP1
// y con base un calculo matematico se modifica el dutycycle
#endif	/* PWMCCP1_H */
