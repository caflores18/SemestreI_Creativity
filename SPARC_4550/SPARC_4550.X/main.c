//Seccion de liberias 
#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#include "Comunicacion.h"
#include "FuncionesMenu.h"
#include "Gpio.h"
#include "Interrupciones.h"
#include "Leds.h"
#include "MotoresXY.h"
#include "PWMCCP1.h"
#include "PWMCCP2.h"
#include "Timers.h"
#include "UART.h"
#define _XTAL_FREQ 8000000 //Se trabaja el programa a 8 Mhz
//ISR de alta prioridad 

__interrupt(high_priority) void high_isr(void) {
    if (overFlowTMR0 == 1) {
        if (destinoHomeY == 0) {
            PWM_DutyCycleCCP2(0);
        }
        CurrentPosY = coordinates.yWanted; //Se actualiza el valor actual de la Y*/
        printf("Interrupcion TMR0, llegaste a coordenada deseada Y\n");
        sparcEnMovimiento = 0;
        overFlowTMR0 = 0;
    }
    if (overFlowTMR1 == 1) { //Si el TMR1 registro OverFlow 
        if (destinoHomeX == 0) {
            PWM_DutyCycleCCP1(0);
        }
        CurrentPosX = coordinates.xWanted; //Se actualiza el valor actual de la Y
        printf("Interrupcion TMR1, llegaste a coordenada deseada X\n");
        sparcEnMovimiento = 0;
        overFlowTMR1 = 0; //Se apaga la interrupcion del TMR1
    }
    if (intLimitSwitch3Esquinas) {
        __delay_ms(10);
        if (pinLimitSwitch3Esquinas == 1) {
            printf("Ocurrio la interrupcion limitSwitch3Esquinas\n");
        }
        moverHomeX();
        moverHomeY();
        intLimitSwitch3Esquinas = 0; //Se apaga la bandera INT0 de interrupcion
    }
    if (intLimitSwitchHomeX == 1) {
        __delay_ms(10);
        if (pinlimitSwitchHomeX == 1) {
            printf("Ocurrio la interrupcion limitSwitchHomeX\n");
        }
        PWM_DutyCycleCCP1(0);
        CurrentPosX = 0;
        destinoHomeX = 0;
        //llegoHomeX = 1;
        sparcEnMovimiento = 0;
        intLimitSwitchHomeX = 0; //Se apaga la bandera INT1 de interrupcion
    }
    if (intLimitSwitchHomeY == 1) {
        __delay_ms(10);
        if (pinlimitSwitchHomeY == 1) {
            printf("Ocurrio la interrupcion limitSwitchHomeY\n");
        }
        PWM_DutyCycleCCP2(0);
        CurrentPosY = 0;
        destinoHomeY = 0;
        //llegoHomeY = 1;
        sparcEnMovimiento = 0;
        intLimitSwitchHomeY = 0; //Se apaga la bandera INT2 de interrupcion
    }
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
    //    ledsInit(); //Inicializa los LEDS para que se puedan encender
    PWM_CCP2_init(); //Se va a usar CCP2 para mover el motor X
    PWM_CCP1_init(); //Se va a usar CCP1 para mover el motor Y
    PWM_DutyCycleCCP2(0); //Se inicia el PWM del motor X en 0
    PWM_DutyCycleCCP1(0); //Se inicia el PWM del motor Y en 0
    motorXinit(); //Se inicializa lo necesario para el motor X
    motorYinit(); //Se inicializa lo necesario para el motor Y
    tmr0Init(); //Se inicializa TMR0 usado para contar los pulsos que mueven a X
    tmr1Init(); //Se inicializa TMR1 usado para contar los pulsos que mueven a Y
    interruptsEnable(); //Se enciende el sistema de interrupciones
    habilitarIntTMR0(); //Habilita interrupcion TMRO
    habilitarIntTMR1(); //Habilita interrupcion TMR1
    habilitarIntExternas();
    pistonInit(); //Habilita piston/actuador
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
        if (llegoHomeX == 1) {
            printf("Si  llegue a home X");
            moverHaciaX(0, 0, 5);
            llegoHomeX = 0;
        }
        scanf(pActMenu, tamanoarray = (sizeof (activarmenu) - 1)); //Se escanean 4 caracteres
        if ((activarmenu[0] == 'M' || activarmenu[0] == 'm') && activarmenu[1] == 'e' && activarmenu[2] == 'n' && activarmenu[3] == 'u') {
            //Si los 4 caracteres previamente escaneados son Menu o menu se entra al menu del SPARC
            printf("\n(0)Como funciona  (1)Agregar coordenada   (2)Imprimir coordenadas\n"
                    "(3)Editar coordenada   (4)Iniciar Programa     (5)Reiniciar todas las coordenadas\n"
                    "(6)Coordenada actual   (7)MovimientoLibre (8)Home/Inf\n");
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
                modificarCoordenada();
            }
            if (opcionsel == '4') {
                printf("Estas por inicar el programa, estas seguro? (1) Si (X) No");
                uint8_t decision5 = receiveNum();
                if (decision5 == '1') {
                    iniciarPrograma();
                } else printf("Regresando al menu");
            }
            if (opcionsel == '5') {
                printf("Vas a borrar todas las coordenadas, seguro? (1) Si (X)No");
                uint8_t decision6 = receiveNum();
                if (decision6 == '1') {
                    borrarTodasCoordenadas();
                } else printf("Regresando al menu");
            }
            if (opcionsel == '6') {
                impCoordActual();
            }
            if (opcionsel == '7') {
                printf("Has elegido movimiento libre\n");
                movimientoLibre();
            }
            if (opcionsel == '8') {
                printf("Entrase al 8");
                printf("Elige (1) infinito o 0 (home)");
                unsigned char loco = receiveNum();
                if (loco == '1') {
                    moverXInfinito();
                    moverYInfinito();
                } else if (loco == '0') {
                    moverHomeX();
                    moverHomeY();
                }
            }
            if (opcionsel == '9') {
                printf("Entrase al 9");
            }
        } else printf("Tuviste un error, escribe la palabra 'Menu' o 'menu' para acceder al menu\n");
    }
}
//Corregir motores XY el mensaje que envia si la coordenada es la misma no deberia pasar
//Parte de control
//Deslizar pantalla
