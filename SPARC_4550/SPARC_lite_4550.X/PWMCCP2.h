/* 
 * File:   PWMCCP2.h
 * Author: Alejandro
 *
 * Created on November 20, 2019, 5:57 PM
 */

#ifndef PWMCCP2_H
#define	PWMCCP2_H
#include <xc.h>
#include <stdint.h>
void PWM_CCP2_init(void);
//Inicializa los registros y valores necesarios para encender el CCP2
void PWM_DutyCycleCCP2(uint8_t WantedDutyCycle);
//Se obtiene el valor de porcentaje a poner el dutycycle del CCP2
// y con base un calculo matematico se modifica el dutycycle
#endif	/* PWMCCP2_H */

