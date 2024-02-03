#include <string>
#include <iostream>
using namespace std;

void gotoxy(short, short);
void f_cons();        			// establece un tamanio fijo para la consola
void color_letra(int);     		// poner un color de fuente, fondo
void centrar(string, int);      // centra un texto; tiene en cuenta caracteres especiales
void cabecera(string);          // crea un recuadro de cabecera
void error(string);             // muestra una cabecera especial de error
void fondo();
void logo(string);              // "tp 2 aedd ..."
void logo_UTN();
void recuadro();
void linea (short, short, int);
int flecha(short, short, int, int);         // cursor de navegacion entre menues
