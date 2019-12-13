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
#define pinLimitSwitch3Esquinas     PORTBbits.RB0   //Pin de lectura de los limitSwitch de proteecion
#define pinlimitSwitchHomeX         PORTBbits.RB2   //Pin de lectura limitSwitch HomeX
#define pinlimitSwitchHomeY         PORTBbits.RB1   //Pin de lectura limitSwitch HomeY
#define enableMotorX                LATDbits.LATD2  //Enciende enable motor X(Negado)
#define dirMotorX                   LATDbits.LATD3  //DIR X
#define stepX                       LATCbits.LATC2  //Step X
#define enableMotorY                LATDbits.LATD0  //Enciende enable motor Y (Negado)
#define dirMotorY                   LATDbits.LATD1  //DIR Y 
#define stepY                       LATCbits.LC1    //Step motor Y
#define piston                      LATEbits.LATE0  //Accionamiento del piston Z
#define enableMotoresZ              LATDbits.LATD4 //Enable puente H
void portInit(void); // Se declara la funcion para poder declarar los puertos como digitales
void motorXinit(void); //Se inicializa lo necesario para hacer funcionar el MotorX
void motorYinit(void); //Se inicializa lo necesario para hacer funcionar el MotorY
void pistonInit(void); //Se inicializa lo necesario para poder mover el Piston 
void motoresZinit(void); //Se inicializa lo necesario para hacer funcionar los motores que subenla base
#endif	/* GPIO_H */

