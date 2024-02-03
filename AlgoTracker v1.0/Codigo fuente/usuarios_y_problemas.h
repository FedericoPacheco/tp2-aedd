#ifndef USUARIOS_Y_PROBLEMAS_H
#define USUARIOS_Y_PROBLEMAS_H

struct Usuario      // (por defecto se tiene el "usuario vacio")
{
	string nombre_equipo = "";
	int nro_legajo = 0;
	string contrasenia = "";
	string nombre_y_apellido = "";
	int *problemas_resueltos = NULL;   // arreglo dinamico
	int nota_parcial[2] = {0};
};

struct Problema
{
	int nro;
	string nombre_problema;
	int tema;
};

void recuperar_datos_usuarios(Usuario u[], int);   // recupera de txts los datos de los usuarios
void recuperar_problemas(Problema *p, int);

#endif

