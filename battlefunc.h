#ifndef BATTLEFUNC_H_INCLUDED
#define BATTLEFUNC_H_INCLUDED

    #include "battleclass.h"
    #include <windef.h>
    #include "pixeldrawtxt.h"

    namespace battle{

        void IA(cuadricula&);//pseudo inteligencia artificial
        void disparar(espacio&);//solo para uso de la IA

        void colocar_barcos(cuadricula&, bool = false);//coloca los barcos, segundo parametro manual/automatico
        void mostrar_barcos_colocados(cuadricula&);//solo para la funcion de arriba en modo manual y muestra los
                                                    //barcos a medida que se van colocando

        void cuadricula_mouse_check(cuadricula&, bool&);//revisa si el mouse está encima de un espacio de la cuadricula
        void cuadricula_status_check(cuadricula&);//revisa el estado impacto/fallado de los espacios y pinta el
                                                //simbolo correspondiente


        void generar_cuadricula(cuadricula&, int, int);//genera una cuadricula desde las cordenadas proporcionadas
        void dibujar_cuadricula(cuadricula&, COLORREF);//dibuja las lineas que separan los espacios

        void _lineax(const int &X, const int &W, const int &Y, COLORREF color);//dibuja una linea desde XY hacia la derecha el numero W
        void _lineay(const int &X, const int &H, const int &Y, COLORREF color);//dibuja una linea desde XY hacia abajo el numero H

        bool mouse_colision(boton&, int, int);//Ligera derivación de pixeldraw::colisiones(...)

        void rectangulofill(boton&, COLORREF);//Ligera derivación de pixeldraw::rectangulofill(...)
        void pintar_fondo(const pixeldraw::DImage&);//pinta la imagen fondo

    }///battle





#endif // BATTLEFUNC_H_INCLUDED
