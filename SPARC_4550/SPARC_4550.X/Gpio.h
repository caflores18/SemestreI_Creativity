/* 
 * File:   Gpio.h
 * Author: Alejandro
 *
 * Created on November 20, 2019, 11:55 AM
 */

#ifndef GPIO_H
#define	GPIO_H
#include <xc.h>
#define enableMotorX            LATDbits.LATD0  //Enciende enable motor X (Negado)
#define dirMotorX               LATDbits.LATD1  //DIR X 
#define stepX                   LATCbits.LC1    //Step motor X
#define enableMotorY            LATDbits.LATD2  //Enciende enable Y (Negado)
#define dirMotorY               LATDbits.LATD3  //DIR Y
#define stepY                   LATCbits.LATC2  //Step Y
void portInit(void); // Se declara la funcion para inicializar los puertos
void motorXinit(void);
void motorYinit(void);
#endif	/* GPIO_H */

