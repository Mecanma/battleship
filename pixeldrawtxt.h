#ifndef _PIXELDRAW_H_
#define _PIXELDRAW_H_
#include <iostream>
#include <windows.h>
#include <math.h>
#include <chrono>
#include <fstream>
#ifndef PIXELDRAW_SOURCE
#define main _main_
#endif

#define PI acos(-1)
#define TWO_PI ( acos(-1)*acos(-1) )

int _main_();


/* ****************************************** */
/* ****************************************** */
/* **** STRUCTURA PARA LOS POLYGONOSFILL **** */
/* ****************************************** */
/* ****************************************** */
typedef struct point{
	int x,y;
} point, points, punto, puntos, PUNTO, PUNTOS;

namespace pixeldraw {

int  vx();
int  vy();
int  vX();
int  vY();


bool iniciar(unsigned int W, unsigned int H, std::string TITLE);
bool pintar(unsigned int Esp = 0);
void salir();

unsigned char *bufferarray();

void pixel(float x, float y, COLORREF COLOR);
COLORREF getpixel(float x, float y);

void fondo(COLORREF color);
void borrar();

void linea (float x0, float y0, float x1, float y1, COLORREF COLOR);
void lineax (float x, float w, float y, COLORREF COLOR);
void lineay (float y, float h, float x, COLORREF COLOR);

void rectangulo(float X, float Y, float X2, float Y2, COLORREF COLOR);
void rectangulofill(float x, float y, float w, float h, COLORREF COLOR);

void moveto(float x, float y);
void lineato(float x, float y, COLORREF COLOR);

void circulo(float xc, float yc, float r, COLORREF COLOR);
void circulofill(float xc, float yc, float r, COLORREF COLOR);

void ellipse(float xc, float yc, float rx, float ry, COLORREF COLOR);
void ellipsefill(float xc, float yc, float rx, float ry, COLORREF COLOR);

void polyrectangulo(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4, COLORREF COLOR);
void polyrectangulofill(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4, COLORREF COLOR);

void triangulo(float X1, float Y1, float X2, float Y2, float X3, float Y3, COLORREF COLOR);
void triangulofill(float X1, float Y1, float X2, float Y2, float X3, float Y3, COLORREF COLOR);

void polytriangulo(float X1, float Y1, float X2, float Y2, float X3, float Y3, COLORREF COLOR);
void polytriangulofill(float X1, float Y1, float X2, float Y2, float X3, float Y3, COLORREF COLOR);

void polygonfill(int cantidad, point *p, COLORREF COLOR);

void bezier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, COLORREF COLOR);
void bezier3(float x1, float y1, float x2, float y2, float x3, float y3, COLORREF COLOR);
void bezier4(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, COLORREF COLOR);

void pixeltxt(float X, float Y, unsigned char ascii, int fontIndex, COLORREF Fondo, COLORREF Texto, bool Tranparent);

void texto(float x, float y, int fontIndex, std::string TextoArray, COLORREF Fondo, COLORREF Texto, bool transparent);

bool tecla(int K);
bool keydown(int K);
bool onoff(int K);

bool  mouse(float& x, float& y);
bool  mousedentro();
float mousex();
float mousey();
bool  izquierdo();
bool  derecho();



/* ************************************* */
/* ********* DATOS PARA EL BMP ********* */
/* ************************************* */

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_ 18
#define HEIGHT_ 22
#define BITS_PER_PIXEL_ 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0



/* ***************************************** */
/* ****** STRUCTURA PARA LAS IMAGENES ****** */
/* ***************************************** */


typedef struct DImage
{
    unsigned char *dataBMP;
    unsigned char *CdataBMP;
    int width = 0;
    int height = 0;
    int bytesPerPixel = 0;

    void buffer( int w, int h ){
      bytesPerPixel = 3;
      dataBMP = (unsigned char *) malloc(w * h * bytesPerPixel);
      width = w;
      height = h;
      for (int i = 0; i < (w*h*bytesPerPixel); ++i){ dataBMP[i] = 0; }
      copia();
    }

    COLORREF getpixel( float _x, float _y ){
        int R,G,B;
        int Index = ((int)_y * width + (int)_x) * 3;
        B = dataBMP[Index + 0];
        G = dataBMP[Index + 1];
        R = dataBMP[Index + 2];
        return (COLORREF)RGB(R,G,B);
    }

    void setpixel( float _X, float _Y, COLORREF color = 0xffffffff ){
        if(_X>=0 && _Y>=0 && _X<width && _Y<height){
            int index = ( _Y * width + _X ) * bytesPerPixel;
            dataBMP[index + 0] = GetBValue(color);
            dataBMP[index + 1] = GetGValue(color);
            dataBMP[index + 2] = GetRValue(color);
        }
    }

    void pixel( float _X, float _Y, COLORREF color = 0xffffffff ){
        if(_X>=0 && _Y>=0 && _X<width && _Y<height){
            int index = ( _Y * width + _X ) * bytesPerPixel;
            dataBMP[index + 0] = GetBValue(color);
            dataBMP[index + 1] = GetGValue(color);
            dataBMP[index + 2] = GetRValue(color);
        }
    }

    COLORREF samplepixel( float x, float y ){
        int sx = (int)(x * (float)width);
        int sy = (int)(y * (float)height-1.0f);
        if (sx <0 || sx >= width || sy < 0 || sy >= height){
            return 0;
        } else {
            return getpixel(sx,sy);
        }
    }

    void grayscale(){
        for (int y = 0; y <=(height-1); ++y){
            for (int x = 0; x <=(width-1); ++x){
                int rgb = getpixel(x, y);
                int r = (rgb & 0xFF);
                int g = (rgb >> 8) & 0xFF;
                int b = (rgb >> 16) & 0xFF;
                int grayLevel = (r + g + b) / 3;
                int gray = (grayLevel << 16) + (grayLevel << 8) + grayLevel;
                setpixel( x,y, gray );
            }
        }
    }

    void invertscale(){
        for (int y = 0; y <=(height-1); ++y){
            for (int x = 0; x <=(width-1); ++x){
                int rgb = getpixel(x, y);
                int r = (rgb & 0xFF);
                int g = (rgb >> 8) & 0xFF;
                int b = (rgb >> 16) & 0xFF;
                setpixel( x,y, RGB(255-r,255-g,255-b) );
            }
        }
    }

    void rscale(){
        for (int y = 0; y <=(height-1); ++y){
            for (int x = 0; x <=(width-1); ++x){
                int rgb = getpixel(x, y);
                int r = (rgb & 0xFF);
                setpixel( x,y, RGB(r,0,0) );
            }
        }
    }

    void gscale(){
        for (int y = 0; y <=(height-1); ++y){
            for (int x = 0; x <=(width-1); ++x){
                int rgb = getpixel(x, y);
                int g = (rgb >> 8) & 0xFF;
                setpixel( x,y, RGB(0,g,0) );
            }
        }
    }


    void bscale(){
        for (int y = 0; y <=(height-1); ++y){
            for (int x = 0; x <=(width-1); ++x){
                int rgb = getpixel(x, y);
                int b = (rgb >> 16) & 0xFF;
                setpixel( x,y, RGB(0,0,b) );
            }
        }
    }

    void copia(){
        CdataBMP = (unsigned char*)malloc(width*height*bytesPerPixel);
        for (int Y = 0; Y < (width*height*bytesPerPixel); ++Y)
        {
            CdataBMP[Y] = dataBMP[Y];
        }
    }

    void reset(){
        for (int Y = 0; Y < (width*height*bytesPerPixel); ++Y)
        {
            dataBMP[Y] = CdataBMP[Y];
        }
    }

    void salir(){
        delete[] CdataBMP;
        delete[] dataBMP;
    }

} DImage;

void readbmp(const char *fileName, DImage *img);
void writebmp(const char *fileName, DImage *img);
void drawbmp(float x, float y, float z, DImage img);

}



// #########################################################
// #########################################################
// ##################### OTRAS FUNCIONES ###################
// #########################################################
// #########################################################

#define ctrlenmemoria(array) ( sizeof(array) / sizeof( (array)[0] ) )

#define ctrlenmemory(array) ( sizeof(array) / sizeof( (array)[0] ) )

#define espera(espera) (Sleep(espera))

void coordxy(float x, float y, COLORREF COLORX, COLORREF COLORY);

int distancia(int x1, int y1, int x2, int y2);

bool colisiones(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh, bool MostrarRectangulo = false);

float angulo(float X, float Y);

float angle(float X, float Y);

float anguloxy(float posX, float posY, float mouseX, float mouseY);

float anglexy(float posX, float posY, float mouseX, float mouseY);

void rota(float& x, float& y, float cx, float cy, float da);




// ##################################################################
// ##################################################################
// ############################ SONIDOS #############################
// ##################################################################
// ##################################################################


float frequenciasonido(const float *FREQ, const float Tiempos[], unsigned int Repetir);

void sonido(LPCSTR SONIDO, int modo);

void sound(LPCSTR SONIDO, int modo = 0);






#endif

