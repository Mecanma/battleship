#ifndef BATTLECLASS_H_INCLUDED
#define BATTLECLASS_H_INCLUDED

    #include <string>
    #include <windef.h>
    #include <wingdi.h>

    const int EXTENSION = 25, TAMANIO_CUADRICULA = 9;

    ///CLASE BOTON++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    class boton{
        int x1, y1;
        int x2, y2;
            COLORREF boton_init_color, boton_hover_color;
            std::string text;
            COLORREF text_init_color, text_hover_color;
            bool press;
            bool dibujar_rectangulo;
                public:
                   boton(int X1, int Y1, int X2, int Y2,
                        COLORREF boton_init, COLORREF boton_hover,
                        std::string texto = "", COLORREF text_init = 0, COLORREF text_hover = 0,
                        bool rectangulo = true);

                    int getX1(); int getY1();
                    int getX2(); int getY2();

                    void setX1(int); void setY1(int);
                    void setX2(int); void setY2(int);

                    bool getPress();

                    bool mouse_check();
        };

        ///FIN CLASE BOTON***************************************************************************




        ///CLASE ESPACIO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        class espacio: public boton{

            bool ocupado;
            bool impactado;
            bool fallado;
                public:

                    espacio(COLORREF _boton_init = RGB(0,0, 255), COLORREF _boton_hover = RGB(255, 0,0),
                            int _X1 = 0, int _Y1 = 0, int _X2 = 0, int _Y2 = 0,
                            std::string _texto = "", COLORREF _text_init = 0, COLORREF _text_hover = 0);

                    bool mouse_check();

                    void mirilla(COLORREF);//pinta un punto de mira si el mouse
                    void disparo_impacto(COLORREF);
                    void disparo_errado(COLORREF);

                    bool getOcupado();      void setOcupado(bool);
                    bool getImpactado();    void setImpactado(bool);
                    bool getFallado();      void setFallado(bool);

            };

        typedef espacio cuadricula[TAMANIO_CUADRICULA][TAMANIO_CUADRICULA];

        ///FIN CLASE ESPACIO*************************************************************************




        ///CLASE BARCO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        enum{vertical,
            horizontal,
            abajo,
            izquierda,
            derecha,
            arriba};

        const int limite_espacio_barco = 4;

        class barco{
            int X[4];
            int Y[4];
            espacio *espacio_punt[4];
            cuadricula &cuadricula_punt;
            bool valido;
            int extension_barco;
            int orientacion;

            ///MOVIMIENTO
            void mostrar_barco();
            ///VALIDACIONES
            bool movimiento_valido(const int&);
                public:

                    barco(cuadricula& punt, int extension);

                    void mover();

                    void fijar_barco();
                    bool validar_rotacion();
                    bool invalidar();
                    void efectuar_movimiento();
                    void setRotacion(int);

                    bool getValido();
                    void setX0(int); void setY0(int);
        };


        ///FIN CLASE BARCO**************************************************************************



#endif // BATTLECLASS_H_INCLUDED
