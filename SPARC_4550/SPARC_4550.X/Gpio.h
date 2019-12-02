/* 
 * File:   Gpio.h
 * Author: Alejandro
 *
 * Created on November 20, 2019, 11:55 AM
 */

#ifndef GPIO_H
#define	GPIO_H
#include <xc.h>
//PORTBbits.RB0
//PORTBbits.RB1
//PORTBbits.RB2
#define pinLimitSwitch3Esquinas     PORTBbits.RB0
#define pinlimitSwitchHomeX         PORTBbits.RB1
#define pinlimitSwitchHomeY         PORTBbits.RB2
#define enableMotorX                LATDbits.LATD2  //Enciende enable X(Negado)
#define dirMotorX                   LATDbits.LATD3  //DIR X
#define stepX                       LATCbits.LATC2  //Step X
#define enableMotorY                LATDbits.LATD0  //Enciende enable motor Y (Negado)
#define dirMotorY                   LATDbits.LATD1  //DIR Y 
#define stepY                       LATCbits.LC1    //Step motor Y
#define piston                      LATEbits.LATE0  //Accionamiento del piston Z
void portInit(void); // Se declara la funcion para inicializar los puertos
void motorXinit(void);
void motorYinit(void);
void pistonInit(void); 
#endif	/* GPIO_H */

