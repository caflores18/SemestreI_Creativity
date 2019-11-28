//Seccion de liberias 
#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#include "Comunicacion.h"
#include "FuncionesMenu.h"
#include "Gpio.h"
#include "Interrupciones.h"
#include "MotoresXY.h"
#include "PWMCCP1.h"
#include "PWMCCP2.h"
#include "Timers.h"
#include "UART.h"
#define _XTAL_FREQ 8000000 //Se trabaja el programa a 8 Mhz
//---------------------Variables globales ----------------------------------

/*struct SystemaSPARC {
    unsigned int xWanted; //coordenada X objetivo
    unsigned int yWanted; //coordenada Y objetivo
    unsigned long timesToPress; //Numero de veces a presionar la pantalla
} coordinates;
//Procedimiento Motor X
unsigned int xToAdvance; // X por avanzar en pasos (Xa)
unsigned int CurrentPosX = 0; // X current posicion actual X (Xc)
//unsigned char leercoordx[3]; //Guarda el valor coord X
//Procedimiennto Motor Y
unsigned int yToAdvance; // Y por avanzar en pasos (Ya)
unsigned int CurrentPosY = 0; // Y current posicion actual (Yc)
//unsigned char leerCoordy[3]; //Guarda el valor coord Y
//Procedimiento compartido (X) y (Y)
unsigned char working = 0; //Esta variable se prende cuando alguno de los motores se va a mover*/
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
    // -------------------Inicializacion de funciones --------------------------
    portInit(); //Inicializa todos los pines como digitales hasta que entra el ADC
    UARTinit(); //Inicializa lo necesario para poder comunicarce por UART  
    PWM_CCP2_init(); //Se va a usar CCP2 para mover el motor X
    PWM_CCP1_init(); //Se va a usar CCP1 para mover el motor Y
    PWM_DutyCycleCCP2(0); //Se inicia el PWM del motor X en 0
    PWM_DutyCycleCCP1(0); //Se inicia el PWM del motor Y en 0
    motorXinit(); //Se inicializa lo necesario para el motor X
    motorYinit(); //Se inicializa lo necesario para el motor Y
    tmr0Init(); //Se inicializa TMR0 usado para contar los pulsos que mueven a X
    tmr1Init(); //Se inicializa TMR1 usado para contar los pulsos que mueven a Y
    //interruptsEnable(); //Se enciende el sistema de interrupciones
    habilitarIntTMR0(); //Habilita interrupcion TMRO
    habilitarIntTMR1(); //Habilita interrupcion TMR1
    //habilitarIntExternas();
    //ADCinit(); //Habilita el uso del ADC, se declara el RA0 como analogico

    //Apuntadores a string para poder hacer uso de la funcion scanf
    unsigned char activarmenu[5];
    activarmenu[4] = NULL;
    unsigned char *pActMenu = (unsigned char *) &activarmenu;
    unsigned char tamanoarray; //Aqui se almacena tamano de array a sobreescribir
    unsigned char desechable = receive();
    // Variables a usar    
    printf("Escribe la palabra 'Menu' o 'menu' para acceder al menu\n");
    //Inicio del ciclo infinito 
    while (1) {
        scanf(pActMenu, tamanoarray = (sizeof (activarmenu) - 1)); //Se escanean 4 caracteres
        if ((activarmenu[0] == 'M' || activarmenu[0] == 'm') && activarmenu[1] == 'e' && activarmenu[2] == 'n' && activarmenu[3] == 'u') {
            //Si los 4 caracteres previamente escaneados son Menu o menu se entra al menu del SPARC
            printf("(0)Ayuda sobre como funciona el programa (1)Introducir coordenada nueva (2)Imprimir las coordenadas recibidas (3)Ir a home\n"
                    "(4)Modificar coordenada (5)Iniciar Programa (6)Borrar el valor de todas las coordenadas\n");
            uint8_t opcionsel = receive();
            while (opcionsel > 57 || opcionsel < 48) {
                printf("Eleccion no valida vuelva a intentar");
                opcionsel = receive();
            }
            if (opcionsel == '0') {
                printf("Funcionamiento del SPARC:");
            }
            if (opcionsel == '1') {
                introducirCoordNueva();
            }
            if (opcionsel == '2') {
                printf("Elegiste la opcion de imprimir coordenadas\n");
                imprimirCoordenadas();
            }
            if (opcionsel == '3') {
                printf("Has elegido ir a home\n");
            }
            if (opcionsel == '4') {
                modificarCoordenada();
            }
            if (opcionsel == '5') {
                printf("Entrase al 5");
            }
            if (opcionsel == '6') {
                printf("Vas a borrar todas las coordenadas, seguro? (1) Si (0)No");
                uint8_t decision = receiveNum();
                if (decision == '1') {
                    borrarTodasCoordenadas();
                } else printf("Regresando al menu");
            }
            if (opcionsel == '7') {
                printf("Entrase al 7");
            }
            if (opcionsel == '8') {
                printf("Entrase al 8");
            }
            if (opcionsel == '9') {
                printf("Entrase al 9");
            }
        } else printf("Tuviste un error, escribe la palabra 'Menu' o 'menu' para acceder al menu\n");
    }
}