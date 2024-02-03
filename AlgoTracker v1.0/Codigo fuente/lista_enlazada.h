#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

struct nodo_tarea_resuelta
{
	int tema_parcial;   // 1, 2, 3, 4, 5, ... : temas ; 999, 1000: parciales
	double porcentaje;
	nodo_tarea_resuelta* ptr_siguiente;
};

void insertar_nodo_al_final(nodo_tarea_resuelta*&, int, double);
void borrar_lista(nodo_tarea_resuelta*&);

#endif

