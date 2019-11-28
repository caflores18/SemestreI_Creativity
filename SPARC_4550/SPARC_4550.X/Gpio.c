#include <xc.h>
#include <pic18f4550.h>
#include "Gpio.h"
#pragma config FOSC = INTOSC_EC       //CONFIG1H (0-3) = 0010: INTIO2 oscillator, Internal oscillator block, port function on RA6 and RA7.
#pragma config MCLRE    = OFF        //Master Clear Reset activado
#pragma config WDT = OFF
//#pragma config PBADEN   = OFF       //Hace que los puertos A y B sean digitales
#pragma config LVP      = OFF       //Low-voltage Programming desactivado */
//Seccion de directivos y defines
#define _XTAL_FREQ 8000000
void portInit ( void ) { //Se desarolla el contenido de la funcion portInit
    ADCON1bits.PCFG = 0xFF; //Se declaran todos los pines como digitales
    OSCCON = 0x70;          //Parte de declarar el clk 8Mhz
    //TRISBbits.TRISB0= 0; // Se declara el puerto B0 como salida
}
void motorXinit( void ) {
    //Motor X
    TRISDbits.RD2 = 0; //RD2 es el Enable del motor X  Output los 3
    TRISDbits.RD3 = 0; //RD3 es la DIR del motor X
    TRISCbits.RC2 = 0; //RC2 es el Step en X
    LATDbits.LATD2 = 0; //Enciende enable del motor X Negado
    LATDbits.LATD3 = 0; //DIR X empieza en sentido horario
    LATCbits.LATC2 = 0; //Step X inicia en 0

}
void motorYinit( void ) {
    //Para practicar
    //TRISAbits.RA2 = 0; //RA2 se declara como output (LED motor Y)
    //TRISAbits.RA3 = 0; //RA3 se declara como output (LED motor X)
    //LATAbits.LATA2 = 0; //LED motor Y inicia apagado
    //LATAbits.LATA3 = 0; //LED motor X inicia apagado
    //Motor Y
    TRISDbits.RD0 = 0; //RD0 es el Enable del motor Y  Output los 3
    TRISDbits.RD1 = 0; //RD1 es la DIR del motor Y
    TRISCbits.RC1 = 0; //RC1 es el Step en Y
    LATDbits.LATD0 = 0; //Enciende enable del motor Y Negado
    LATDbits.LATD1 = 0; //DIR Y empieza en sentido horario
    LATCbits.LC1 = 0; //Step en Y inicia en 0
}
