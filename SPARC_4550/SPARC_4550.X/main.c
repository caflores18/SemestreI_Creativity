// -------------------Seccion de liberias------------------------   
#include <xc.h>
#include "Gpio.h"
#include "UART.h"

//ISR de alta prioridad
__interrupt(high_priority) void high_isr(void) {
    Nop(); //Funcion para consumir un ciclo de instruccion
}
//ISR de baja prioridad 
__interrupt(low_priority) void low_isr(void) {
    Nop(); //Funcion para consumir un ciclo de instruccion
}
// -------------------Declaracion de variables globales------------------------   
void main(void) {
    // -------------------Inicio del programa---------------------------
    portInit(); //Se declaran los puertos a usar 
    UARTinit(); //Se inicializa puerto UART
    //Apuntadores a string para poder hacer uso de la funcion scanf
    unsigned char activarmenu[5];
    activarmenu[4] = NULL;
    unsigned char *pActMenu = (unsigned char *) &activarmenu;
    unsigned char tamanoarray; //Aqui se almacena tamano de array a sobreescribir

    //Inicio del ciclo infinito 
    unsigned char desechable = receive();
    printf("Escribe la palabra 'Menu' o 'menu' para acceder al menu\n");
    while (1) {
        scanf(pActMenu, tamanoarray = (sizeof (activarmenu) - 1));
        if ((activarmenu[0] == 'M' || activarmenu[0] == 'm') && activarmenu[1] == 'e' && activarmenu[2] == 'n' && activarmenu[3] == 'u') {
            printf("(1)_Introducir coordenadas (2)_Iniciar Programa (3)_Ir a home (4)_Nada\n");
            unsigned char opcionsel = receive();
            while (opcionsel > 57 || opcionsel < 48) {
                printf("Eleccion no valida vuelte a intentar");
                opcionsel = receive();
            }
            if (opcionsel == '1') {
                printf("Entrase al 1");
            }
            if (opcionsel == '2') {
                printf("Entrase al 2");
            }
            if (opcionsel == '3') {
                printf("Entrase al 3");
            }
            if (opcionsel == '4') {
                printf("Entrase al 4");
            }
        } else printf("Tuviste un error, escribe la palabra 'Menu' o 'menu' para acceder al menu\n");
    }
}