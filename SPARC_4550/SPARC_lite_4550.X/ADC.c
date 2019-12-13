#include <xc.h>
#include <pic18f4550.h>
#include "ADC.h"

void ADCinit(void) {
    ADCON0bits.CHS = 0b0000; //Se selecciona el canal analogo A0
    ADCON1bits.VCFG = 0; //ADC tendra como referencia 5V y GND
    ADCON1bits.PCFG = 0b1110; // Se habilita A0 como analogo
    ADCON2bits.ADFM = 1; //Valor de los registros ADRESL Y ADRESH justificado a la derecha 
    ADCON2bits.ACQT = 0b100; //Tiempo de adquisicion 8 TAD
    ADCON2bits.ADCS = 0b100; // A/D Conversion clock select es de FOSC/4 (8Mhz/4)
    ADRESH = 0; //Se limpian los registros Low y High
    ADRESL = 0;
    TRISAbits.TRISA0 = 1; //A0 declarado como input
    ADCON0bits.ADON = 1; //ADC module habilitado (1)
}

uint16_t ADCvalue() {
    ADCON0bits.GO_DONE = 1; //Comenzar conversion 
    while (ADCON0bits.GO_DONE == 1) {
        //Mientras esta realizandose la conversion se espera
    }
    uint16_t valorADC = ADRESL + (ADRESH << 8); //El valor del ADC es guardado en la variable valorADC
    return valorADC; //Se regresa el valor de la variable ValorADC
}