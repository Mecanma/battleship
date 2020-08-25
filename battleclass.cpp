#ifndef BATTLECLASS_CPP_INCLUDED
#define BATTLECLASS_CPP_INCLUDED

    #include "battleclass.h"
    #include "pixeldrawtxt.h"
    #include "battlefunc.h"

    ///FUNCIONES class boton++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        boton::boton(int X1, int Y1, int X2, int Y2,
                    COLORREF boton_init, COLORREF boton_hover,
                    std::string texto, COLORREF text_init, COLORREF text_hover,
                    bool rectangulo):
                        x1(X1), y1(Y1),//cordenadas de el punto uno (esquina superior izquierda)
                        x2(X2), y2(Y2),//cordenadas de el punto dos (esquina inferior derecha)
                        boton_init_color(boton_init), boton_hover_color(boton_hover),//colores de el fondo de el boton
                        text(texto),//texto de el boton
                        text_init_color(text_init), text_hover_color(text_hover),//color cuando el mouse se pose sobre el boton
                        press(false),//booleano, ¿el botón ha sido presionado?
                        dibujar_rectangulo(rectangulo){
                            pixeldraw::rectangulofill(x1, y1, x2, y2, boton_init_color);//hacer un rectangulo donde van los puntos
                    }

        bool boton::mouse_check(){

            if(this->press == false){
                    if(battle::mouse_colision(*this, pixeldraw::mousex(), pixeldraw::mousey())){
                        battle::rectangulofill(*this, this->boton_hover_color);
                        // SetCursor(cursor_manita);
                            if(pixeldraw::izquierdo())
                                this->press = true;
                        return true;
                    }
                    else{
                        battle::rectangulofill(*this, this->boton_init_color);
                        // SetCursor(cursor_flechita);
                    }
                }///this->press == false
                else{
                    battle::rectangulofill(*this, RGB(117, 145, 60));
                }
            return false;
        }

        int boton::getX1(){return this->x1;} int boton::getY1(){return this->y1;}
        int boton::getX2(){return this->x2;} int boton::getY2(){return this->y2;}

        void boton::setX1(int num){this->x1 = num;} void boton::setY1(int num){this->y1 = num;}
        void boton::setX2(int num){this->x2 = num;} void boton::setY2(int num){this->y2 = num;}

        bool boton::getPress(){return this->press;}

    ///FIN FUNCIONES CLASE BOTON********************************************************************


    ///FUNCIONES CLASE ESPACIO+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        espacio::espacio(COLORREF _boton_init, COLORREF _boton_hover,
                            int _X1, int _Y1, int _X2, int _Y2,
                            std::string _texto, COLORREF _text_init, COLORREF _text_hover):
                            boton(_X1, _Y1, _X2, _Y2,
                                _boton_init, _boton_hover,
                                _texto, _text_init, _text_hover,
                                false),
                                ocupado(false), impactado(false), fallado(false){}

        bool espacio::mouse_check(){

            if(!this->impactado && !this->fallado){//si no ha sido impactado o fallado
                if(battle::mouse_colision(*this, pixeldraw::mousex(), pixeldraw::mousey())){//si el mouse sobre un recuadro
                    mirilla(RGB(201, 57, 213));//pintar mirilla
                    return true;
                }
            }
            return false;
        }

        void espacio::mirilla(COLORREF color){
            int X = (this->getX1() + this->getX2() ) / 2;
            int Y = (this->getY1() + this->getY2() ) / 2;
            int radio = EXTENSION / 2.7f;
            int extension_linea = EXTENSION / 3;
                pixeldraw::circulo(X, Y, radio, color);
                battle::_lineay(X, extension_linea, this->getY1() + 2, color);
                battle::_lineax(X + 5, extension_linea, Y, color);
                battle::_lineay(X, extension_linea, Y + 3, color);
                battle::_lineax(this->getX1(), extension_linea, Y, color);
    }

    void espacio::disparo_impacto(COLORREF color){
        int X = (this->getX1() + this->getX2() ) / 2;
        int Y = (this->getY1() + this->getY2() ) / 2;
        int radio = EXTENSION / 2.7f;
            pixeldraw::circulo(X, Y, radio, color);
            pixeldraw::linea(this->getX1(), this->getY1(), this->getX2(), this->getY2(), color);
            pixeldraw::linea(this->getX1() + EXTENSION, this->getY1(), this->getX2() - EXTENSION, this->getY2(), color);
    }

    void espacio::disparo_errado(COLORREF color){
        int X = (this->getX1() + this->getX2() ) / 2;
        int Y = (this->getY1() + this->getY2() ) / 2;
        int radio = EXTENSION / 2.7f;
            pixeldraw::circulofill(X, Y, radio, color);
    }

        bool espacio::getOcupado(){return this->ocupado;}
        bool espacio::getFallado(){return this->fallado;}
        bool espacio::getImpactado(){return this->impactado;}

        void espacio::setOcupado(bool estado){this->ocupado = estado;}
        void espacio::setFallado(bool estado){this->fallado = estado;}
        void espacio::setImpactado(bool estado){this->impactado = estado;}

    ///FIN FUNCIONES CLASE BARCO*******************************************************************

    ///FUNCIONES CLASE BARCO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        barco::barco(cuadricula& punt, int extension):
            cuadricula_punt(punt), valido(false), orientacion(horizontal){
            extension > limite_espacio_barco ? extension_barco = limite_espacio_barco : extension_barco = extension;

                int cabezaY = TAMANIO_CUADRICULA / 2;
                int cabezaX = cabezaY;
                espacio_punt[0] = &cuadricula_punt[cabezaY][cabezaX];
                X[0] = Y[0] = cabezaY;
                    for(int i = 1; i < extension_barco; i++){
                        espacio_punt[i] = &cuadricula_punt[cabezaY][--cabezaX];
                        X[i] = cabezaX; Y[i] = cabezaY;
                    }
            }


        bool barco::movimiento_valido(const int &type){
            for(int i = 0; i < extension_barco;i++){
                if(!battle::dentro_area_juego(X[i], Y[i], type))
                    return false;
            }
            return true;
        }


        void barco::mover(){

            bool pulsado = false;

            if(pixeldraw::keydown('Z') && validar_rotacion()){
                orientacion == vertical ? orientacion = horizontal : orientacion = vertical;
                pulsado = true;
            }
            else if(pixeldraw::keydown(VK_LEFT) && movimiento_valido(izquierda)){
                X[0]--;
                pulsado = true;
            }

            else if(pixeldraw::keydown(VK_RIGHT) && movimiento_valido(derecha)){
                X[0]++;
                pulsado = true;
            }

            else if(pixeldraw::keydown(VK_DOWN) && movimiento_valido(abajo)){
                Y[0]++;
                pulsado = true;
            }

            else if(pixeldraw::keydown(VK_UP) && movimiento_valido(arriba)){
                Y[0]--;
                pulsado = true;
            }

            if(pulsado){
                efectuar_movimiento();
                valido = invalidar();
                Sleep(130);
            }
            mostrar_barco();
        }

        void barco::efectuar_movimiento(){
        int cabezaX, cabezaY;
            switch(orientacion){
                case vertical:
                     cabezaX= X[0], cabezaY = Y[0];
                    espacio_punt[0] = &cuadricula_punt[cabezaY][cabezaX];
                    for(int i = 1; i < extension_barco; i++){
                        espacio_punt[i] = &cuadricula_punt[--cabezaY][cabezaX];
                        X[i] = cabezaX; Y[i] = cabezaY;
                    }
                    break;
                case horizontal:
                    cabezaX = X[0]; cabezaY = Y[0];
                    espacio_punt[0] = &cuadricula_punt[cabezaY][cabezaX];
                    for(int i = 1; i < extension_barco; i++){
                        espacio_punt[i] = &cuadricula_punt[cabezaY][--cabezaX];
                        X[i] = cabezaX; Y[i] = cabezaY;
                    }
                    break;
            }
        }

        void barco::mostrar_barco(){
            for(int i = 0; i < extension_barco; i++){
                int X1 = espacio_punt[i]->getX1() + 3, Y1 = espacio_punt[i]->getY1() + 3,
                 X2 = espacio_punt[i]->getX2() - 3, Y2 = espacio_punt[i]->getY2() - 3;

                if(espacio_punt[i]->getOcupado()){
                    pixeldraw::rectangulofill(X1, Y1, X2, Y2, RGB(255, 255, 255));
                    espacio_punt[i]->disparo_impacto(RGB(255, 0,0));
                }
                else{
                    pixeldraw::rectangulofill(X1, Y1, X2, Y2, RGB(0, 0, 255));
                }
            }
        }

        bool barco::validar_rotacion(){
            int num;
            orientacion == vertical ? num = horizontal : num = vertical;

            switch(num){
                case vertical:
                    if(Y[0] - extension_barco < -1)
                        return false;
                case horizontal:
                    if(X[0] - extension_barco < -1)
                        return false;
            }

            return true;
        }

        bool barco::invalidar(){
            for(int i = 0; i < extension_barco; i++){
                if(espacio_punt[i]->getOcupado() == true)
                    return false;
            }
            return true;
        }

        void barco::fijar_barco(){
            for(int i = 0; i < extension_barco; i++){
                espacio_punt[i]->setOcupado(true);
            }
        }

        bool barco::getValido(){return this->valido;}
        void barco::setX0(int num){this->X[0] = num;}
        void barco::setY0(int num){this->Y[0] = num;}
        void barco::setRotacion(int num){this->orientacion = num;}


    ///FIN FUNCIONES CLASE BARCO********************************************************************


    ///FUNCIONES CLASE PLAYER++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        void player::disminuir_vidas(){this->vidas--;}

        int player::getVidas(){return this->vidas;}
        void player::setVidas(const int &num){this->vidas = num;}

    ///FIN FUNCIONES CLASE PLAYER********************************************************************

#endif // BATTLECLASS_CPP_INCLUDED
