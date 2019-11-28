//ISR de alta prioridad

__interrupt(high_priority) void high_isr(void) {
    if (INTCONbits.TMR0IF = 1) { //Rutina Y interrupcion TIMER 0
        PWM_DutyCycleCCP2(0);
        LATAbits.LATA2 = 0; //Se apaga el foco que indica Y
        CurrentPosY = coordinates.yWanted; //Se actualiza el valor actual de la Y*/
        printf("Interrupcion TMR0, llegaste a coordenada deseada\n");
        sparcEnMovimiento = 0;
        INTCONbits.TMR0IF = 0;
    }
}

/*unsigned char inutil = receive();
            inutil = 0;
            //Pregunta coordenadas Y
            printf("Empieza nueva instruccion, dame tu coordenada Y\n"); //Envia salto de linea
            leerCoordy[0] = receive();
            leerCoordy[1] = receive();
            leerCoordy[2] = receive();
            printf("La coordenada que he recibido es: ");
            send(leerCoordy[0]);
            send(leerCoordy[1]);
            send(leerCoordy[2]);
            send(0xD); //Envia salto de linea*/
void main(void) {
    //Inicio del ciclo infinito 

    