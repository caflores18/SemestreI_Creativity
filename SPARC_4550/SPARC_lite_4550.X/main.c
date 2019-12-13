//Seccion de liberias 
#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#include "Comunicacion.h"
#include "FuncionesMenu.h"
#include "Gpio.h"
#include "Interrupciones.h"
#include "Leds.h"
#include "MotoresXYZ.h"
#include "PWMCCP1.h"
#include "PWMCCP2.h"
#include "Timers.h"
#include "UART.h"
#define _XTAL_FREQ 8000000 //Se trabaja el programa a 8 Mhz
//ISR de alta prioridad 
uint8_t OcurrioIntEsq = 0; //Bandera usada para registrar que ocurrio la interrupcion 3Esquinas

__interrupt(high_priority) void high_isr(void) {
    if (overFlowTMR0 == 1) {
        if (destinoHomeY == 0) {
            PWM_DutyCycleCCP2(0);
        }
        CurrentPosY = coordinates.yWanted; //Se actualiza el valor actual de la Y*/
        printf("Interrupcion TMR0, llegaste a coordenada deseada Y\n");
        printf("Ok,coorY\n");
        sparcEnMovimientoY = 0;
        enableMotorY = 1;
        overFlowTMR0 = 0;
    }
    if (overFlowTMR1 == 1) { //Si el TMR1 registro OverFlow 
        if (destinoHomeX == 0) {
            PWM_DutyCycleCCP1(0);
        }
        CurrentPosX = coordinates.xWanted; //Se actualiza el valor actual de la Y
        printf("Interrupcion TMR1, llegaste a coordenada deseada X\n");
        printf("Ok,coorX\n");
        sparcEnMovimientoX = 0;
        enableMotorX = 1;
        overFlowTMR1 = 0; //Se apaga la interrupcion del TMR1
    }
    if (intLimitSwitch3Esquinas) {
        __delay_ms(10);
        if (pinLimitSwitch3Esquinas == 1) {
            printf("Ocurrio la interrupcion limitSwitch3Esquinas\n");
        }
        moverHomeX();
        moverHomeY();
        OcurrioIntEsq = 1;
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
        llegoHomeX = 1;
        sparcEnMovimientoX = 0;
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
        llegoHomeY = 1;
        sparcEnMovimientoY = 0;
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
    motoresZinit();
    pistonInit(); //Habilita piston/actuador
    //Apuntadores a string para poder hacer uso de la funcion scanf
    uint8_t activarmenu[5];
    activarmenu[4] = NULL;
    uint8_t *pActMenu = (unsigned char *) &activarmenu;
    uint8_t tamanoarray; //Aqui se almacena tamano de array a sobreescribir
    uint8_t calibrarSparc = 0;
    //Para acceder al SPARC
    uint8_t desechable = receive();
    while (calibrarSparc == 0) {
        printf("Escribe init para calibrar el SPARC y poder acceder al resto de las funciones\n");
        scanf(pActMenu, tamanoarray = (sizeof (activarmenu) - 1)); //Se escanean 4 caracteres
        if ((activarmenu[0] == 'i' || activarmenu[0] == 'I') && activarmenu[1] == 'n' && activarmenu[2] == 'i' && activarmenu[3] == 't') {
            calibrarSparc = 1;
            printf("Inicializando...\n");
        }
    }
    //Inicio del ciclo infinito 
    while (1) {
        if (calibrarSparc == 1) {
            moverHaciaX('0', '0', '5'); //Se mueve 5mm X para no estar tocando el limSwitch
            moverHaciaY('0', '0', '5'); //Se mueve 5mm Y para no estar tocando el limSwitch
            __delay_ms(100); //Se da un delay para esperar a que se mueva 
            moverHomeX(); //Se dirige X y Y a home
            moverHomeY();
            while (!(llegoHomeX && llegoHomeY)) {
                //Se espera a que llegue al origen X y Y
            }
            //Despues de que se ha llegado al origen
            printf("SACANDO\n");
            moverHaciaX('0', '1', '5'); //Se mueve 15mm X para no estar tocando el limSwitch
            moverHaciaY('0', '1', '5'); //Se mueve 15mm Y para no estar tocando el limSwitch
            llegoHomeX = 0; //Se apagan las banderas de que se llego a home en X y Y
            llegoHomeY = 0;
            CurrentPosX = 0; //Se actualiza la posicion actual de X y Y a 0
            CurrentPosY = 0;
            calibrarSparc = 0; //Se apaga la bandera de inicializacion del SPARC
            printf("Ya esta calibrado el SPARC\n");
        }
        if (OcurrioIntEsq == 1) {
            while (!(llegoHomeX && llegoHomeY)) {
                //Se espera a que llegue al origen X y Y
            }
            //Despues de que se ha llegado al origen
            printf("Int3 Esquinas, recalibrando SPARC\n");
            moverHaciaX('0', '1', '5'); //Se mueve 5mm X para no estar tocando el limSwitch
            moverHaciaY('0', '1', '5'); //Se mueve 5mm Y para no estar tocando el limSwitch
            llegoHomeX = 0; //Se apagan las banderas de que se llego a home en X y Y
            llegoHomeY = 0;
            CurrentPosX = 0; //Se actualiza la posicion actual de X y Y a 0
            CurrentPosY = 0;
            OcurrioIntEsq = 0;
        }
        printf("Ok,comN\n");
        uint8_t opcionsel = receive();
        if (opcionsel == 'm' || opcionsel == 'M') {
            printf("Vas a mover el Sparc en X y Y\n");
            printf("Ok,comV\n");
            moverHaciaXY();
        } else if (opcionsel == 'p' || opcionsel == 'P') {
            printf("Presionar Z cierto numero de veces recibidas\n");
            printf("Ok,comV\n");
            sistemaInt = 0;
            funcionToques();
            __delay_ms(250); //Delay de 100ms para volver a activar INT0
            limpiarIntExtF();
            sistemaInt = 1;
        } else if (opcionsel == 's' || opcionsel == 'S') {
            printf("Piston para deslizar o dejar retraido?\n");
            printf("Ok,comV\n");
            sistemaInt = 0;
            slidePiston();
            __delay_ms(250); //Delay de 100ms para volver a activar INT0
            limpiarIntExtF();
            sistemaInt = 1;

        } else if (opcionsel == 'h' || opcionsel == 'H') {
            printf("Vas a ir a homeX y home Y\n");
            printf("Ok,comV\n");
            moverHomeX(); //Se dirige X y Y a home
            moverHomeY();
            while (!(llegoHomeX && llegoHomeY)) {
                //Se espera a que llegue al origen X y Y
            }
            //Despues de que se ha llegado al origen
            moverHaciaX('0', '1', '5'); //Se mueve 5mm X para no estar tocando el limSwitch
            moverHaciaY('0', '1', '5'); //Se mueve 5mm Y para no estar tocando el limSwitch
            //Talvez se viene para arriba estas dos lineas
            llegoHomeX = 0; //Se apagan las banderas de que se llego a home en X y Y
            llegoHomeY = 0;
            CurrentPosX = 0; //Se actualiza la posicion actual de X y Y a 0
            CurrentPosY = 0;
            printf("Ok,comF\n");
        }/*else if (opcionsel == 'i' || opcionsel == 'I') {
            printf("Vas a ir infinito X e infinito Y\n");
            printf("Ok,comV\n");
            moverXInfinito();
            moverYInfinito();
            OcurrioIntEsq = 1;
            printf("Ok,comF\n");
        }*/ else if (opcionsel == 'c' || opcionsel == 'C') {
            printf("Imprmir coordenada actual \n");
            printf("Ok,comV\n");
            impCoordActual();
            printf("Ok,comF\n");
        } else if (opcionsel == 'b' || opcionsel == 'B') {
            printf("Entraste a mover la base\n");
            printf("Ok,comV\n");
            modificarZ();
            printf("Ok,comF\n");
        } else {
            printf("E,com\n");
        }
    }
}
//SPARC_Lite