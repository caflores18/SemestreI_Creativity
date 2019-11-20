#include <xc.h>
#include <pic18f4550.h>
#include "Gpio.h"
#pragma config FOSC = INTOSC_EC       //CONFIG1H (0-3) = 0010: INTIO2 oscillator, Internal oscillator block, port function on RA6 and RA7.
#pragma config MCLRE    = OFF        //Master Clear Reset activado
//#pragma config PBADEN   = OFF       //Hace que los puertos A y B sean digitales
#pragma config LVP      = OFF       //Low-voltage Programming desactivado */

//Seccion de directivos
#define _XTAL_FREQ 8000000
void portInit ( void ) { //Se desarolla el contenido de la funcion portInit
    ADCON1bits.PCFG = 0xFF; //Se declaran todos los pines como digitales
    OSCCON = 0x70;          //Parte de declarar el clk 8Mhz
    TRISBbits.TRISB0= 0; // Se declara el puerto B0 como salida
}
