//#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
//using namespace std;
#include "graficos_consola.h"
#include "manejo_de_txts.h"
#include "usuarios_y_problemas.h"

int obtener_cantidad_de_problemas()
{
	ifstream problemas_temas;
	ofstream cant_problemas;
	int cont = 0, basura1, basura2;
	
	problemas_temas.open("problemas-temas.txt");
	
	while(!problemas_temas.eof())
	{
		problemas_temas >> basura1 >> basura2;
		cont++;
	}
	
	problemas_temas.close();
	
	return cont;
}

int obtener_cantidad_de_temas()
{
	int cont = 0, basura1;
	string basura2;
	ifstream temas;
	
	temas.open("temas.txt");
	
	while (!temas.eof())
	{
		temas >> basura1;
		getline(temas, basura2);
		cont++;
	}
	
	temas.close();
	
	return cont;
}

void registrar_cant_problemas(int cant_problemas)
{
	ofstream cant_problemas_txt;
	
	cant_problemas_txt.open("cant-problemas-ultima-sesion.txt");
	
	cant_problemas_txt << cant_problemas;
	
	cant_problemas_txt.close();
}

bool comprobar_estado_txts()
{
	bool aux;
	ifstream usuarios, temas, problemas, problemas_temas;
	
	usuarios.open("usuarios.txt");
	temas.open("temas.txt");
	problemas_temas.open("problemas-temas.txt");
	problemas.open("problemas.txt");
	
	if (usuarios.fail() || temas.fail() || problemas_temas.fail() || problemas.fail())
	{
		f_cons(); fondo(); color_letra(1);
		error("Error al iniciar el programa");
		
		if (usuarios.fail())
			centrar("Falta: usuarios.txt", 4);
		if (temas.fail())
			centrar("Falta: temas.txt", 6);
		if (problemas_temas.fail())
			centrar("Falta: problemas-temas.txt", 8);
		if (problemas.fail())
			centrar("Falta: problemas.txt", 10);
		
		aux = false;
	}
	else
		aux = true;
	
	usuarios.close();
	temas.close();
	problemas_temas.close();
	problemas.close();
	
	return aux;
}

void problemas_parciales_txt(Usuario u[], int cant_problemas)
{
	int i, j;
	ofstream problemas_evaluaciones;
	
	problemas_evaluaciones.open("problemasyevaluaciones.txt");
	
	problemas_evaluaciones << u[0].nombre_equipo << "\n\n";
	
	for (i = 0; i < 3; i++)
	{
		problemas_evaluaciones << u[i].nombre_y_apellido << '\n';
		
		for (j = 0; j < cant_problemas; j++)
			problemas_evaluaciones << u[i].problemas_resueltos[j] << ' ';
		problemas_evaluaciones << '\n';
		
		for (j = 0; j < 2; j++)
			problemas_evaluaciones << u[i].nota_parcial[j] << ' ';
		problemas_evaluaciones << "\n\n";
	}
	
	problemas_evaluaciones.close();
}

