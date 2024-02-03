#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones_auxiliares.h"
#include "graficos_consola.h"
#include "lista_enlazada.h"
#include "usuarios_y_problemas.h"

void aux1()
{
	static string opciones[] = {"Actualizar ficha", "Informes de rendimiento", "Limpiar datos", "Configuración", "Cerrar sesión", "Cerrar aplicación"};
	static int i, j;
	
	f_cons(); fondo(); color_letra(8);
	cabecera("Menú principal");		
	for (i = 0, j = 5; i < 6; i++, j += 3)
		centrar (opciones[i], j);
}

void aux2()
{
	static string opciones[] = {"Registrar problema resuelto", "Registrar calificación de parcial", "Volver"};
	static int i, j;
	
	f_cons(); fondo(); color_letra(8);
	cabecera("Menú de actualización de ficha");
	for (i = 0, j = 5; i < 3; i++, j += 3)
		centrar (opciones[i], j);
}

void aux3()
{
	static string opciones[] = {"Desempeño individual", "Desempeño del equipo", "Volver"};
	static int i, j;
	
	f_cons(); fondo(); color_letra(8);
	cabecera("Menú de informes");
	for (i = 0, j = 5; i < 3; i++, j += 3)
		centrar (opciones[i], j);
}

void aux4(Usuario u[])
{
	static int i;
	static string fases1[] = {"Tema", to_string(u[0].nro_legajo), to_string(u[1].nro_legajo), to_string(u[2].nro_legajo)};
	
	f_cons(); fondo(); color_letra(8);
	cabecera("Informe de equipo: " + u[0].nombre_equipo);
	
	gotoxy(0, 3);
	cout << char(201);
	for (i = 0; i < 118; i++)
		cout << char(205);
	cout << char(187);
	
	gotoxy(0,4);
	cout << char(186) << "      ID       ";
	for (i = 0; i < 4; i++)
		cout << char(186) << "          " << fases1[i] << "          ";  
	cout << char(186);
	
	gotoxy(0, 5);
	cout << char(200);
	for (i = 0; i < 118; i++)
		cout << char(205);
	cout << char(188);
}

void aux5 (nodo_tarea_resuelta* l, Usuario u[])   // pasandose por copia, no importa que l se modifique
{
	int j;
	ofstream informe_grupo_rendimiento;
	
	informe_grupo_rendimiento.open("informe-grupo-rendimiento.txt");
	
	f_cons(); fondo(); color_letra(8);
	cabecera("Informe de equipo: " + u[0].nombre_equipo);
	informe_grupo_rendimiento << "Informe de equipo: " << u[0].nombre_equipo << "\n\n";
	
	j = 5;
	while (l != NULL)
	{
		if ((l -> tema_parcial >= 1) && (l -> tema_parcial <= obtener_cantidad_de_temas()))    // se supone que no se va a llegar al tema 999
		{
			if (l -> porcentaje != 666)   // numero clave ya definido para 0 / 0
			{
				centrar("Tema " + to_string(l -> tema_parcial) + ": " + (to_string(l -> porcentaje)).substr(0, 5) + "%", j);
				informe_grupo_rendimiento << "Tema " << l -> tema_parcial << ": " << fixed << setprecision(2) << l -> porcentaje << "%\n\n";
			}
			else
			{
				centrar("Tema " + to_string(l -> tema_parcial) + ": - (no existen problemas en esta categoría)", j);
				informe_grupo_rendimiento << "Tema " << l -> tema_parcial << ": - (no existen problemas en esta categoría) \n\n";
			}
		}
		else
		{
			centrar("Parcial " + to_string((l -> tema_parcial) - 998) + ": " + (to_string(l -> porcentaje)).substr(0, 5) + "%", j);
			informe_grupo_rendimiento << "Parcial " << l -> tema_parcial - 998 << ": " << fixed << setprecision(2) << l -> porcentaje << "%\n\n";
		}
		
		j+= 2;
		l = l -> ptr_siguiente;
	}
	
	gotoxy(40, j + 1); system("pause");
	
	informe_grupo_rendimiento.close();
}

void aux6(Usuario u[], int cant_problemas)
{
	int i, j;
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < cant_problemas; j++)
			u[i].problemas_resueltos[j] = 0;
		
		for (j = 0; j < 2; j++)
			u[i].nota_parcial[j] = 0;
	}
}

void aux7(Usuario u[], int cant_problemas)
{
	int i, j;
	string basura;
	ifstream problemas_evaluaciones;
	
	problemas_evaluaciones.open("problemasyevaluaciones.txt");
	
	getline (problemas_evaluaciones, basura);   	 //"sortear" nombre equipo
	problemas_evaluaciones.ignore();				//ignorar enter (no romper getline)
	
	for (i = 0; i < 3; i++)
	{
		getline (problemas_evaluaciones, basura);		//"sortear" nombre usuario
		
		for (j = 0; j < cant_problemas; j++)
			problemas_evaluaciones >> u[i].problemas_resueltos[j];
		
		for (j = 0; j < 2; j++)
			problemas_evaluaciones >> u[i].nota_parcial[j];
		
		problemas_evaluaciones.ignore(3);             // ignorar espacio al final del sdo parcial, enters
	}
	
	problemas_evaluaciones.close();
}

void aux8 (string mensaje, int& cont, bool aux)
{
	cont--;
	
	color_letra(9);
	centrar(mensaje, 21);
	Beep(100, 350);
	Sleep (1500);
	
	color_letra(3);
	centrar("Intentos restantes: " + to_string(cont), 23);
	Sleep (1500);
	
	color_letra(10);      // tapar partes del recuadro
	linea (45, 21, 30);
	color_letra(10);
	linea (45, 23, 30);
	color_letra(11);
	
	if (aux)   // si se envia 1, se imprime una linea en y = 14; sino en y = 18 (reciclar funcion)
		linea(45, 14, 30);
	else
		linea (45, 18, 30);
	
	color_letra(4);
	
}

bool es_numero_es_no_vacia(string str)
{
	static int i;
	static bool num_no_vac;
	
	if (str == "\0")
		num_no_vac = false;
	else
	{
		i = 0; num_no_vac = true; 
		while (i < (int) str.length() && num_no_vac) // verificar que no se ingresen letras / signos de puntuacion 
		{
			if (isalpha(str.at(i)) || ispunct(str.at(i)) || isspace(str.at(i)))
				num_no_vac = false;
			else 
				i++;
		}
	}
	
	return num_no_vac;
}

void merge_sort(Problema* p, int i, int f, int cant_problemas)  // i, f: inicio, final
{
	if (i == f)
		return;
	else
	{
		merge_sort(p, i, (i + f) / 2, cant_problemas);
		merge_sort(p, (i + f) / 2 + 1, f, cant_problemas);
		merge(p, i, (i + f) / 2, (i + f) / 2 + 1, f, cant_problemas);
	}
}

void merge(Problema* p, int i_1, int f_1, int i_2, int f_2, int cant_problemas)  // inicio 1, final 1, inicio 2, final 2
{
	static int i, j, k;
	static Problema *aux;
	
	aux = new Problema [cant_problemas];
	i = i_1;
	j = i_2;
	k = 0;
	
	while (i <= f_1 && j <= f_2)
	{
		if (p[i].nro < p[j].nro)
		{
			aux[k] = p[i];
			i++;
		}
		else
		{
			aux[k] = p[j];
			j++;
		}
		
		k++;
	}
	
	while (i <= f_1)
	{
		aux[k] = p[i];
		i++;
		k++;
	}
	
	while (j <= f_2)
	{
		aux[k] = p[j];
		j++;
		k++;
	}

	for (k = 0; k < (f_2 - i_1 + 1); k++)
		p[i_1 + k] = aux[k];
	
	delete [] aux;
	aux = NULL;
}
