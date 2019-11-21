/* 
 * File:   PWMCCP2.h
 * Author: Alejandro
 *
 * Created on November 20, 2019, 5:57 PM
 */

#ifndef PWMCCP2_H
#define	PWMCCP2_H
#include <xc.h>
void PWM_CCP2_init(void);
void PWM_DutyCycleCCP2(unsigned char WantedDutyCycle);
#endif	/* PWMCCP2_H */

