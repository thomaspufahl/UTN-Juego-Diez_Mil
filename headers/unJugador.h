//
// Created by thoma on 14/10/2022.
//

#ifndef DIEZ_MIL_UNJUGADOR_H
#define DIEZ_MIL_UNJUGADOR_H

#endif //DIEZ_MIL_UNJUGADOR_H



int unJugador(int &condicionCls, char jugadores[][35], char apellidos[][35], int cantidadPJ, int puntuacion[], int &rondas) {
    rlutil::cls();
    condicionCls = 1;
    int puntosXRonda;
    int puntosAux=0;
    int dados[6];
    int mostrarCaso4;
    int jugada;
    int jugadaJugador[1]={0};
    int lanzamientos;
    int ganador;
    int TURNO = 0;
    do {
        lanzamientos=0;
        rondas++;
        pantallaTurno(rondas, jugadores, cantidadPJ, puntuacion, TURNO, jugadaJugador);
        rlutil::cls();

        ///ESTILOS
        //CABECERA
        recuadroJuego();
        //numero de ronda
        rlutil::locate(56, 4);
        std::cout << "RONDA N" << char(248) << " " << rondas;
        lineaHorizontal(6, 196);

        //CUERPO
        //jugador
        lineaVertical(46, 179);
        rlutil::locate(21, 7);
        std::cout << "JUEGA " << strupr(jugadores[0]);
        //puntaje
        rlutil::locate(10, 9);
        std::cout << char(4) << " " << "PUNTAJE TOTAL: " << puntuacion[0] << " PUNTOS";
        //puntaje x ronda
        rlutil::locate(10, 10);
        std::cout << char(4) << " " << "PUNTAJE DE LA RONDA: " << puntosAux << " PUNTOS";
        //lanzamientos
        rlutil::locate(10, 12);
        std::cout << char(4) << " " << "LANZAMIENTOS: " << lanzamientos;

        ///TIRADA || JUEGO
        bool band = true;

        int posX = 19;
        int posY = 22;

        do {
            label("TIRAR DADOS", 21, 22);
            label("GUARDAR PUNTOS", 21, 24);

            labelInt(175, posX, posY);

            int key = rlutil::getkey();
            //up    14
            //down  15
            //enter 1

            switch (key) {
                case 14:
                    punteroArriba(posX, posY, 175, 22, 2);
                    break;
                case 15:
                    punteroAbajo(posX, posY, 175, 24, 2);
                    break;
                case 1:
                    switch (posY) {
                        case 22:
                            limpiarJuego();
                            mezclar();
                            guardarDados(dados, 6);
                            mostrarDados(dados, 6);
                            lanzamientos++;
                            jugada = identificarJugada(dados, 6, puntosXRonda, mostrarCaso4);
                            mostrarJugada(jugada, mostrarCaso4);
                            puntosAux+=puntosXRonda;
                            mostrarSumaPuntaje(puntosXRonda);

                            rlutil::locate(10, 12);
                            std::cout << char(4) << " " << "LANZAMIENTOS N" << char(248) << " " << lanzamientos;

                            rlutil::locate(10, 9);
                            std::cout << char(4) << " " << "PUNTAJE TOTAL: " << puntuacion[0] << " PUNTOS";

                            jugadaJugador[0]=jugada;

                            if (jugada!=7) {
                                rlutil::msleep(750);
                                rlutil::locate(10, 10);
                                std::cout << char(4) << " " << "PUNTAJE DE LA RONDA: " << puntosAux << " PUNTOS";
                            }

                            if (jugada==0) {
                                //significa jugada perdedora
                                rlutil::locate(10, 10);
                                std::cout << char(4) << " " << "                     " << puntosAux << "       ";

                                puntosAux=0;

                                rlutil::locate(10, 10);
                                std::cout << char(4) << " " << "PUNTAJE DE LA RONDA: " << puntosAux << " PUNTOS";

                                label("             ", 19, 22);
                                label("                ", 19, 24);

                                rlutil::msleep(500);
                                label("-PULSA UNA TECLA PARA CONTINUAR", 12, 22);
                                rlutil::anykey();
                                band=false;
                            }
                            if (jugada==7){
                                //significa que saque un sexteto
                                puntuacion[0]=puntosXRonda;

                                label("-PULSA UNA TECLA PARA CONTINUAR", 12, 22);
                                rlutil::anykey();

                                band = false;
                            }
                            break;
                        case 24:
                            if (puntuacion[0]+puntosAux>10000){
                                limpiarJuego();
                                label("TE PASASTE DE LOS 10.000", 16, 22);
                            } else {
                                limpiarJuego();
                                puntuacion[0]+=puntosAux;
                            }
                            puntosAux=0;

                            rlutil::msleep(250);

                            rlutil::locate(10, 9);
                            std::cout << char(4) << " " << "PUNTAJE TOTAL: " << puntuacion[0] << " PUNTOS";

                            label("-PULSA UNA TECLA PARA CONTINUAR", 12, 24);
                            rlutil::anykey();

                            band=false;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        } while (band);

        ///PANTALLAS DE FIN DE JUEGO
        if (jugada==7) {
            //pantalla final de sexteto
            ganador = pantallaFinal("GANADOR POR COMBINACION GANADORA: SEXTETO", 40, 10, jugadores, apellidos, 1, puntuacion, rondas, true, jugadaJugador);
            rlutil::anykey();
            return ganador;
        }
        if (puntuacion[0]==10000) {
            //pantalla final de ganador basico
            ganador = pantallaFinal("FINALIZACION POR LLEGAR A 10.000 PUNTOS", 40, 10, jugadores, apellidos, 1, puntuacion, rondas, true, jugadaJugador);
            rlutil::anykey();
            return ganador;
        }
    } while (rondas!=10);
    //pantalla final de límite de rondas
    rondas++;
    ganador = pantallaFinal("FINALIZACION POR LIMITE DE RONDAS (10/10)", 40, 10, jugadores, apellidos, 1, puntuacion, rondas,true, jugadaJugador);
    rlutil::anykey();
    return ganador;
}