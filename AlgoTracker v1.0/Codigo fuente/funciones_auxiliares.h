#include "graficos_consola.h"
#include "lista_enlazada.h"
#include "manejo_de_txts.h"
#include "usuarios_y_problemas.h"

void aux1();									    // Opciones del menu principal
void aux2();   										// Opciones del menu de actualizacion de ficha
void aux3();										// Opciones del menu de desempenio
void aux4(Usuario u[]);     						// Cabecera de la tabla de desempenio de grupo
void aux5(nodo_tarea_resuelta*, Usuario u[]);		// Informe final equipo por temas a partir de lista
void aux6(Usuario [], int);    						// Puesta a 0 problemas resueltos usuarios
void aux7(Usuario [], int);    						// Recuperacion de problemas de usuarios del txt
void aux8 (string, int&, bool);   					// Ingresos incorrectos login
bool es_numero_es_no_vacia(string);
void merge_sort(Problema*, int, int, int);   		// Ordena por mezcla los problemas
void merge(Problema*, int, int, int, int, int);    // Funcion auxiliar a merge_sort()
 
