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
void PWM_DutyCycleCCP1(unsigned char WantedDutyCycle);
#endif	/* PWMCCP1_H */
