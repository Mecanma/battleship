    #include "pixeldrawtxt.h"
    #include "battlefunc.h"
    #include "battleclass.h"
    #include <ctime>
    #include <cstdlib>

    int main() {
        srand(time(NULL));

        pixeldraw::iniciar(500, 500, "hola");


        bool generados(false);
        bool tu_turno(true);

        cuadricula cuadricula_jugador;
        cuadricula cuadricula_enemigo;

        pixeldraw::DImage fondo;
        pixeldraw::readbmp("fondo.bmp", &fondo);


        while(true){
            pixeldraw::borrar();

            //battle::pintar_fondo(fondo);

            if(pixeldraw::keydown(VK_ESCAPE)){break;}

            if(!generados){
                battle::generar_cuadricula(cuadricula_jugador, 20, 20);
                battle::generar_cuadricula(cuadricula_enemigo, 250, 250);
                battle::colocar_barcos(cuadricula_jugador);
                battle::colocar_barcos(cuadricula_enemigo, true);
                generados = true;
            }

            battle::dibujar_cuadricula(cuadricula_jugador, RGB(255, 255, 255));
            battle::dibujar_cuadricula(cuadricula_enemigo, RGB(255, 255, 255));


            if(tu_turno)
                battle::cuadricula_mouse_check(cuadricula_enemigo, tu_turno);
            else{
            battle::IA(cuadricula_jugador);
            tu_turno = true;
            }

            battle::cuadricula_status_check(cuadricula_jugador);
            battle::cuadricula_status_check(cuadricula_enemigo);

            pixeldraw::pintar();
        }

        pixeldraw::salir();

    return 0;
    }
