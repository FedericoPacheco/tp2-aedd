#include <stdlib.h>
#include <fstream>
#include "funciones_auxiliares.h"
#include "manejo_de_txts.h"
#include "usuarios_y_problemas.h"

void recuperar_datos_usuarios(Usuario u[], int cant_problemas)
{
	int i, aux;
	string basura;
	ifstream usuarios, problemas_evaluaciones, cant_problemas_txt;
	
	usuarios.open("usuarios.txt");
	
	getline(usuarios, u[0].nombre_equipo); 			//recuperar nombre equipo
	for (i = 0; i < 3; i++)
	{
		usuarios >> u[i].nro_legajo >> u[i].contrasenia;
		usuarios.ignore();
		getline (usuarios, u[i].nombre_y_apellido);
	}
	
	usuarios.close();
	
	//-------------------------------------
	
	problemas_evaluaciones.open("problemasyevaluaciones.txt");
	cant_problemas_txt.open("cant-problemas-ultima-sesion.txt");
	
	u[0].problemas_resueltos = new int [cant_problemas];
	u[1].problemas_resueltos = new int [cant_problemas];
	u[2].problemas_resueltos = new int [cant_problemas];
	
	/*
	Se verifica que los "anchos" (cantidad de problemas registrados) sean complatibles y que el archivo de registro exista;
	y se carga la informacion guardada o no.
	*/
	cant_problemas_txt >> aux;
	
	if (!cant_problemas_txt.fail())
	{
		if (!problemas_evaluaciones.fail())
		{
			if (aux != cant_problemas)
				aux6(u, cant_problemas);
			else
				aux7(u, cant_problemas); // cargar
		}
		else
			aux6(u, cant_problemas);
	}
	else
		aux6(u, cant_problemas);  // poner a 0
	
	cant_problemas_txt.close();
	problemas_evaluaciones.close();
}

void recuperar_problemas(Problema *p, int cant_problemas)
{
	int i, j, problema_aux, tema_aux;
	ifstream problemas_temas, problemas;
	
	problemas.open("problemas.txt");
	problemas_temas.open("problemas-temas.txt");
	
	for (i = 0; i < cant_problemas; i++)
	{
		problemas >> p[i].nro;
		problemas.ignore();
		getline(problemas, p[i].nombre_problema);
		
		j = 0; problemas_temas.seekg(0, ios:: beg);
		while (j < cant_problemas && problema_aux != p[i].nro)
		{
			problemas_temas >> problema_aux;              
			problemas_temas >> tema_aux;
			
			j++;
		}
		p[i].tema = tema_aux;
	}
	
	problemas.close();
	problemas_temas.close();
}
