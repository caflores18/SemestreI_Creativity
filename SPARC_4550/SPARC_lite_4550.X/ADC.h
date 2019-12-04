/* 
 * File:   ADC.h
 * Author: Alejandro
 *
 * Created on November 21, 2019, 4:02 PM
 */

#ifndef ADC_H
#define	ADC_H
#include <xc.h>
#include <stdint.h>
void ADCinit(void); //Funcion utilizada para inicializar los registros y valores necesarios para activar el funcionamiento del ADC
uint16_t ADCvalue(); //Funcion encargada de regresar el valor digital del ADC (del pin A0)
#endif	/* ADC_H */

