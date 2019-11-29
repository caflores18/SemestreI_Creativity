//ISR de alta prioridad

void moverHaciaX(uint8_t coordXCentenas, uint8_t coordXDecenas, uint8_t coordXUnidades) {
    while (sparcEnMovimiento == 1) {
        //No se hace nada hasta que termine
    }
    //Procedimiento X
    coordinates.xWanted = ((coordXCentenas - 48)*100)+((coordXDecenas - 48)*10)+(coordXUnidades - 48);
    xToAdvance = (abs(coordinates.xWanted - CurrentPosX))*5; //X por avanzar es xWanted menos CurrentPosX
    printf("xToAdvance is:");
    send(xToAdvance);
    send('\n');
    if (coordinates.xWanted > CurrentPosX) { //Si el valor por recorrer es positivo
        dirMotorX = 1; //El motor se mueve hacia un lado
    } else if (coordinates.xWanted < CurrentPosX) {//Si el valor por recorrer es negativo
        dirMotorX = 0; //El motor se mueve al otro lado
    }
    if (coordinates.xWanted != CurrentPosX) {
        working = 1;
        setNumPasosX(xToAdvance);
        PWM_DutyCycleCCP1(50);
    }
}

