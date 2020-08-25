#ifndef BATTLEFUNC_CPP_INCLUDED
#define BATTLEFUNC_CPP_INCLUDED

    #include "battlefunc.h"
    #include "pixeldrawtxt.h"
    #include <winuser.h>
    #include <ctime>
    #include <cstdlib>

    void intercambio(int &a, int &b){
        if(a != b){
        int tmp = a;
        a = b;
        b = tmp;
        }
    }


namespace battle{

    void IA(player &P){
        srand(time(NULL));
            static bool nuevo = true, impactado = false;
            static int X, Y, direccion;
            if(nuevo){
                while(1){
                    X = (1 + rand() % (TAMANIO_CUADRICULA + 1 - 1)) - 1;
                    Y = (1 + rand() % (TAMANIO_CUADRICULA + 1 - 1)) - 1;
                    if(P.grilla[Y][X].getFallado() || P.grilla[Y][X].getImpactado())
                        continue;
                    disparar(P.grilla[Y][X]);
                    if(P.grilla[Y][X].getImpactado()){
                        nuevo = false;
                        P.disminuir_vidas();
                    }
                    break;
                }
            }
            else{
                if(!impactado){
                    direccion = manecillas(P, X, Y, impactado);
                }
                else{
                    seguir_direccion(P, X, Y, direccion, nuevo, impactado);
                }
            }

        }



    int manecillas(player& P, int &X, int &Y, bool &impactado){

         if(dentro_area_juego(X, Y, arriba) && !P.grilla[Y - 1][X].getFallado() && !P.grilla[Y - 1][X].getImpactado()){
            disparar(P.grilla[Y - 1][X]);
                if(P.grilla[Y - 1][X].getImpactado()){
                    impactado = true;
                    Y--;
                    P.disminuir_vidas();
                    return arriba;
                }

        }
        else if(dentro_area_juego(X, Y, derecha) && !P.grilla[Y][X + 1].getFallado() && !P.grilla[Y][X + 1].getImpactado()){
            disparar(P.grilla[Y][X + 1]);
                if(P.grilla[Y][X + 1].getImpactado()){
                    impactado = true;
                    X++;
                    P.disminuir_vidas();
                    return derecha;
                }

        }
        else if(dentro_area_juego(X, Y, abajo) && !P.grilla[Y + 1][X].getFallado() && !P.grilla[Y + 1][X].getImpactado()){
            disparar(P.grilla[Y + 1][X]);
                if(P.grilla[Y + 1][X].getImpactado()){
                    impactado = true;
                    Y++;
                    P.disminuir_vidas();
                    return abajo;
                }

        }
        else if(dentro_area_juego(X, Y, izquierda) && !P.grilla[Y][X - 1].getFallado() && !P.grilla[Y][X - 1].getImpactado()){
            disparar(P.grilla[Y][X - 1]);
                if(P.grilla[Y][X - 1].getImpactado()){
                    impactado = true;
                    X--;
                    P.disminuir_vidas();
                    return izquierda;
                }

        }

    }

    void seguir_direccion(player &P, int &X, int &Y, int direccion, bool &nuevo, bool &impactado){

        switch(direccion){
            case arriba:
                if(dentro_area_juego(X, Y, arriba) && !P.grilla[Y - 1][X].getFallado() && !P.grilla[Y - 1][X].getImpactado()){
                    disparar(P.grilla[Y - 1][X]);
                    if(P.grilla[Y - 1][X].getFallado()){
                        nuevo = true;
                        impactado = false;
                        break;
                    }
                    P.disminuir_vidas();
                    Y--;
                }
                else{
                     nuevo = true;
                    impactado = false;
                }
                break;
            case derecha:
                if(dentro_area_juego(X, Y, abajo) && !P.grilla[Y - 1][X].getFallado() && !P.grilla[Y - 1][X].getImpactado()){
                    disparar(P.grilla[Y][X + 1]);
                    if(P.grilla[Y][X + 1].getFallado()){
                        nuevo = true;
                        impactado = false;
                        break;
                    }
                    P.disminuir_vidas();
                    X++;
                }
                else{
                     nuevo = true;
                    impactado = false;
                }
                break;
            case abajo:
                if(dentro_area_juego(X, Y, abajo) && !P.grilla[Y + 1][X].getFallado() && !P.grilla[Y + 1][X].getImpactado()){
                    disparar(P.grilla[Y + 1][X]);
                    if(P.grilla[Y + 1][X].getFallado()){
                        nuevo = true;
                        impactado = false;
                        break;
                    }
                    P.disminuir_vidas();
                    Y++;
                }
                else{
                     nuevo = true;
                    impactado = false;
                }
                break;

            case izquierda:
                if(dentro_area_juego(X, Y, arriba) && !P.grilla[Y][X - 1].getFallado() && !P.grilla[Y][X - 1].getImpactado()){
                    disparar(P.grilla[Y][X - 1]);
                    if(P.grilla[Y][X - 1].getFallado()){
                        nuevo = true;
                        impactado = false;
                        break;
                    }
                    P.disminuir_vidas();
                    X--;
                }
                else{
                     nuevo = true;
                    impactado = false;
                }
                break;

        }


    }

    void disparar(espacio &B){
        B.getOcupado() ? B.setImpactado(true) : B.setFallado(true);
    }

    bool dentro_area_juego(int X, int Y, int direccion){

        int direccionX = 0, direccionY = 0;

            switch(direccion){
                case arriba:
                    direccionY = -1; break;
                case izquierda:
                    direccionX = -1; break;
                case abajo:
                    direccionY = 1; break;
                case derecha:
                    direccionX = 1; break;
            }

                      if(Y + direccionY > TAMANIO_CUADRICULA - 1 ||
                        Y + direccionY < 0 ||
                        X + direccionX < 0 ||
                        X + direccionX > TAMANIO_CUADRICULA - 1)
                            return false;

            return true;
    }


    void colocar_barcos(player &P, bool automatico){
        srand(time(NULL));
        int flota[4] = {2, 3, 3, 4};
        barco *punt = NULL;
        bool colocado(false);
            if(automatico){
                    for(int i = 0; i < 4; i++){
                        P.setVidas(P.getVidas() + flota[i]);
                        colocado = false;
                        punt = new barco(P.grilla, flota[i]);
                        while(!colocado){
                            punt->setX0((1 + rand() % (TAMANIO_CUADRICULA + 1 - 1)) - 1);
                            punt->setY0((1 + rand() % (TAMANIO_CUADRICULA + 1 - 1)) - 1);
                            punt->setRotacion((1 + rand() % (2 + 1 - 1)) - 1);
                            if(punt->validar_rotacion()){
                                punt->efectuar_movimiento();
                                if(punt->invalidar() == true){
                                    punt->fijar_barco();
                                    colocado = true;
                                }
                            }
                        }
                        delete punt;
                    }
            }
            else{

                for(int i = 0; i < 4; i++){
                    colocado = false;
                    P.setVidas(P.getVidas() + flota[i]);
                    punt = new barco(P.grilla, flota[i]);
                        while(!colocado){
                            pixeldraw::borrar();
                            battle::dibujar_cuadricula(P.grilla, RGB(255, 255, 255));
                            mostrar_barcos_colocados(P.grilla);
                            punt->mover();

                            if(pixeldraw::keydown('X') && punt->getValido()){
                                punt->fijar_barco();
                                colocado = true;
                            }
                            pixeldraw::pintar();
                        }
                    delete punt;
                }
            }
        }

    void mostrar_barcos_colocados(cuadricula& B){
         for(int i = 0; i < TAMANIO_CUADRICULA; i++){
            for(int j = 0; j < TAMANIO_CUADRICULA; j++){
                int X1 = B[i][j].getX1() + 3, Y1 = B[i][j].getY1() + 3,
                 X2 = B[i][j].getX2() - 3, Y2 = B[i][j].getY2() - 3;

                 if(B[i][j].getOcupado()){
                    pixeldraw::rectangulofill(X1, Y1, X2, Y2, RGB(113, 226, 80));
                }
            }
        }
    }


    void cuadricula_mouse_check(player &P, bool &turno){
        bool encontrado = false;
        for(int i = 0; i < TAMANIO_CUADRICULA; i++){
            for(int j = 0; j < TAMANIO_CUADRICULA; j++){
                if(P.grilla[i][j].mouse_check()){
                    if(pixeldraw::izquierdo()){
                        P.grilla[i][j].getOcupado() ? P.grilla[i][j].setImpactado(true) : P.grilla[i][j].setFallado(true);
                        turno = false;
                        if(P.grilla[i][j].getImpactado())
                            P.disminuir_vidas();
                        Sleep(270);
                    }
                    encontrado = true;
                    break;
                }
            }
            if(encontrado)
                break;
        }

    }

    void cuadricula_status_check(cuadricula &B){
        for(int i = 0; i < TAMANIO_CUADRICULA; i++){
            for(int j = 0; j < TAMANIO_CUADRICULA; j++){
                if(B[i][j].getImpactado())
                    B[i][j].disparo_impacto(RGB(230, 0,0));
                else if(B[i][j].getFallado())
                    B[i][j].disparo_errado(RGB(255,255,255));
            }
        }
    }

    void generar_cuadricula(cuadricula &B, int inicioY, int inicioX){

        int beginY = inicioY, beginX = inicioY;

                    for(int i = 0; i < TAMANIO_CUADRICULA; i++){
                        for(int j = 0; j < TAMANIO_CUADRICULA; j++){
                            B[i][j].setX1(beginX); B[i][j].setY1(beginY);
                            B[i][j].setX2(beginX + EXTENSION); B[i][j].setY2(beginY + EXTENSION);
                            beginX += EXTENSION;
                        }
                        beginX = inicioX;
                        beginY += EXTENSION;
                    }
        }

    void dibujar_cuadricula(cuadricula &B, COLORREF color){
        int inicioX = B[0][0].getX1(), inicioY = B[0][0].getY1();
        int punto_final = EXTENSION * TAMANIO_CUADRICULA;
        int auxX = inicioX, auxY = inicioY;

        for(int i = 0; i <= TAMANIO_CUADRICULA; i++){
            _lineax(auxX, punto_final + 1, inicioY, color);
            _lineay(inicioX, punto_final + 1, auxY, color);

            inicioY += EXTENSION;
            inicioX += EXTENSION;
        }
    }

    bool mouse_colision(boton& B, int Mx, int My){
        bool Colisionan = false;
            if(Mx > B.getX1() && My > B.getY1() && Mx < B.getX2() && My < B.getY2())
                Colisionan = true;
        return Colisionan;
    }

    void rectangulofill(boton& B, COLORREF color){
        pixeldraw::rectangulofill(B.getX1(), B.getY1(), B.getX2(), B.getY2(), color);
    }


    void pintar_fondo(const pixeldraw::DImage &imagen){

        pixeldraw::drawbmp(0, 0, 0, imagen);

    }

    void _lineax(const int &X, const int &W, const int &Y, COLORREF color){
        int j = X, i = 0;
         while(i < W){
            pixeldraw::pixel(j, Y, color);
            j++;
            i++;
        }
    }

    void _lineay(const int &X, const int &H, const int &Y, COLORREF color){
        int j = Y, i = 0;
         while(i < H){
          pixeldraw::pixel(X, j, color);
            j++;
            i++;
        }
    }



}

#endif // BATTLEFUNC_CPP_INCLUDED

