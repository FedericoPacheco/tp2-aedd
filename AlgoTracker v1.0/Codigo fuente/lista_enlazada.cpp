#include <stdlib.h>
#include "lista_enlazada.h"

void insertar_nodo_al_final(nodo_tarea_resuelta*& informe_equipo, int tema_parcial, double porcentaje)
{
	nodo_tarea_resuelta *i, *nuevo_nodo;
	
	nuevo_nodo = new nodo_tarea_resuelta;
	nuevo_nodo -> tema_parcial = tema_parcial;
	nuevo_nodo -> porcentaje = porcentaje;
	nuevo_nodo -> ptr_siguiente = NULL;
	
	if (informe_equipo == NULL)
		informe_equipo = nuevo_nodo;
	else
	{
		for (i = informe_equipo; i -> ptr_siguiente != NULL; i = i -> ptr_siguiente);
		
		i -> ptr_siguiente = nuevo_nodo;
	}
}

void borrar_lista(nodo_tarea_resuelta*& informe_equipo)
{
	nodo_tarea_resuelta *aux;
	
	while (informe_equipo != NULL)
	{
		aux = informe_equipo;
		informe_equipo = informe_equipo -> ptr_siguiente;
		delete aux;
	}
}
