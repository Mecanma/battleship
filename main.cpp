    #include "pixeldrawtxt.h"
    #include "battlefunc.h"
    #include "battleclass.h"
    #include <ctime>
    #include <cstdlib>

    int main() {
        srand(time(NULL));

        pixeldraw::iniciar(500, 500, "hola");

        bool tu_turno(true);

        player jugador, computadora;

        pixeldraw::DImage fondo;
        pixeldraw::readbmp("fondo.bmp", &fondo);

                battle::generar_cuadricula(jugador.grilla, 20, 20);
                battle::generar_cuadricula(computadora.grilla, 250, 250);
                battle::colocar_barcos(jugador);
                battle::colocar_barcos(computadora, true);


        while(true){
            pixeldraw::borrar();

            //battle::pintar_fondo(fondo);


            battle::dibujar_cuadricula(jugador.grilla, RGB(255, 255, 255));
            battle::dibujar_cuadricula(computadora.grilla, RGB(255, 255, 255));

            if(tu_turno)
                battle::cuadricula_mouse_check(computadora, tu_turno);
            else{
            battle::IA(jugador);//ataca a el jugador
            tu_turno = true;
            Sleep(270);
            }

            battle::mostrar_barcos_colocados(jugador.grilla);
            battle::cuadricula_status_check(jugador.grilla);
            battle::cuadricula_status_check(computadora.grilla);

            pixeldraw::pintar();
            if(jugador.getVidas() == 0){
                pixeldraw::texto(0,0,2, "PIERDE JUGADOR", RGB(255, 255, 255), RGB(255,255,255), false);
                pixeldraw::pintar();
                system("pause");
            }
            else if(computadora.getVidas() == 0){
                pixeldraw::texto(0,0,2, "PIERDE COMPUTADORA", RGB(255, 255, 255), RGB(255,255,255), false);
                pixeldraw::pintar();
                system("pause");
            }
        }

        pixeldraw::salir();

    return 0;
    }
