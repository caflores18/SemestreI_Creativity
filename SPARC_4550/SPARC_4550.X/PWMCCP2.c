#include <xc.h>
#include <pic18f4550.h>
#include "PWMCCP2.h"
void PWM_CCP2_init(void) {
    TRISCbits.RC1 = 0; //Se declara el PIN RC1 como output (Para el CCP2)
    CCP2CONbits.CCP2M = 0b1111; //Se declara el modulo CCP2 como PWM 
    //PR2 = 124; //Para una frecuencia de 1Khz con un preescalador de 16 PR2 debe ser 15
    PR2 = 249; //Para una frecuencia de 1Khz con un preescalador de 16 PR2 debe ser 15
    T2CONbits.T2CKPS = 0b11; //Preescalador de TMR2 de 16 bits
    //Se inicializa con un Duty Cycle de 0
    CCP2CONbits.DC2B = 0;
    CCPR2L = 0;
    TMR2 = 0; //Resetea el valor del TMR2 para asegurar que va de 0
    T2CONbits.TMR2ON = 1; //Enciende TMR2   
}
void PWM_DutyCycleCCP2(uint8_t WantedDutyCycle) {
    //unsigned char loco = WantedDutyCycle;
    uint16_t PWMDutyValue;
    PWMDutyValue = (WantedDutyCycle * 0.01)*1000; /*Se calcula el valor a poner en
         los registros CCPXL y CCPXCON para obtener el dutycycle querido*/
    CCP2CONbits.DC2B = (PWMDutyValue & 0x03); //Se asigna valor a los 2 LSB del duty cycle
    CCPR2L = ((PWMDutyValue >> 2)&0xFF); //
    //CCP2CONbits.DC2B contiene los dos bits menos significativos del PWM duty cycle
}