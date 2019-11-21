#include <xc.h>
#include <pic18f4550.h>
#include "PWMCCP1.h"
void PWM_CCP1_init(void) {
    TRISCbits.RC2 = 0; //Se declara el PIN RC2 como output (Para el CCP1)
    CCP1CONbits.CCP1M = 0b1111; //Se declara el modulo CCP2 como PWM 
    PR2 = 124; //Para una frecuencia de 1Khz con un preescalador de 16 PR2 debe ser 15
    T2CONbits.T2CKPS = 0b11; //Preescalador de TMR2 de 16 bits
    TMR2 = 0; //Resetea el valor del TMR2 para asegurar que va de 0
    T2CONbits.TMR2ON = 1; //Enciende TMR2   
}

void PWM_DutyCycleCCP1(unsigned char WantedDutyCycle) {
    //unsigned char loco = WantedDutyCycle;
    unsigned int PWMDutyValue;
    PWMDutyValue = (WantedDutyCycle * 0.01)*500; /*Se calcula el valor a poner en
         los registros CCPXL y CCPXCON para obtener el dutycycle querido*/
    CCP1CONbits.DC1B = (PWMDutyValue & 0x03); //Se asigna valor a los 2 LSB del duty cycle
    CCPR1L = ((PWMDutyValue >> 2)&0xFF); //
    //CCP2CONbits.DC2B contiene los dos bits menos significativos del PWM duty cycle
}
