#include <xc.h>
#include <pic18f4550.h>
#include "Leds.h"

void ledsInit(void) {
    TRISBbits.RB5 = 0; //Se declara el pin para LED ROJO como output
    TRISBbits.RB6 = 0; //Se declara el pin para LED VERDE como output
    TRISBbits.RB7 = 0; //Se declara el pin para LED AZUL como output
    ledRojo = 0; //Se dejan los tres leds apagados en un inicio
    ledVerde = 0;
    ledAzul = 0;
}

void alertaRojo(void) {
    ledRojo = 1;           //Se enciende el led rojo por 250ms
    __delay_ms(250);
    ledRojo = 0;
}
void alertaVerde(void) {
    ledVerde = 1;          //Se enciende el led verde por 250ms
    __delay_ms(250);
    ledVerde = 0;
}
void alertaAzul(void) {
    ledAzul = 1;           //Se enciende el led azul por 250ms
    __delay_ms(250);
    ledAzul = 0;
}