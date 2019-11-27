
__interrupt(high_priority) void high_isr(void) {
    if (PIR1bits.TMR1IF = 1) { //Si el TMR1 registro OverFlow 
        PWM_DutyCycleCCP1(0);
        LATAbits.LATA2 = 0; //Se apaga el foco que indica Y
        CurrentPosY = coordinates.yWanted; //Se actualiza el valor actual de la Y
        printf("Interrupcion TMR1, llegaste a coordenada deseada\n");
        working = 0;
        PIR1bits.TMR1IF = 0; //Se apaga la interrupcion del TMR1
    }
}
//ISR de baja prioridad
void main(void) {
    //Inicio del ciclo infinito 
    while (1) {
        if (working == 0) {
            unsigned char inutil = receive();
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
            send(0xD); //Envia salto de linea

            //Procedimiento Y
            coordinates.yWanted = ((leerCoordy[0] - 48)*100)+((leerCoordy[1] - 48)*10)+(leerCoordy[2] - 48);
            yToAdvance = (abs(coordinates.yWanted - CurrentPosY))*5; //Y por avanzar es yWanted menos CurrentPosY
            //yToAdvance = yToAdvance * 5;
            printf("yToAdvance is:");
            send(yToAdvance);
            send('\n');
            if (coordinates.yWanted > CurrentPosY) { //Si el valor por recorrer es positivo
                dirMotorY = 1; //El motor se mueve hacia un lado
            } else if (coordinates.yWanted < CurrentPosY) {//Si el valor por recorrer es negativo
                dirMotorY = 0; //El motor se mueve al otro lado
            }
            if (coordinates.yWanted != CurrentPosY) {
                working = 1;
                LATAbits.LATA2 = 1; //Se enciende el foco que indica Y
                setNumPasosY(yToAdvance);
                PWM_DutyCycleCCP1(50);
            } else if ((coordinates.yWanted == CurrentPosY)) {
                printf("\nYa estas en la coordenada deseada, prueba con otra coordenada\n");
            }
        }
    }
}