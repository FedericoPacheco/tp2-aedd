#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <fstream>
using namespace std;
//LIBRERIAS PROPIAS
#include "graficos_consola.h"
#include "funciones_auxiliares.h"
#include "lista_enlazada.h"
#include "manejo_de_txts.h"
#include "usuarios_y_problemas.h"

bool color_solido;

//FUNCIONES
bool menu_login(Usuario u[], int& u_actual);
bool menu_principal(Usuario u[], Problema *p, int, int);
void menu_actualizar_ficha(Usuario u[], Problema *p, int, int);
void registrar_problema(Usuario u[], Problema *p, int, int);
void registrar_parcial(Usuario u[], int);
void menu_borrado_datos(Usuario u[], int, int);
void menu_desempenio(Usuario u[], Problema *p, int, int);
void menu_performance_individual(Usuario u[], Problema *p, int, int);
void menu_performarce_equipo(Usuario u[], Problema *p, int);

int main() 
{
	Usuario u[3];
	Problema *p = NULL;
	int u_actual, cant_problemas;
	bool sesion;
	
	srand(time(NULL)); // fondo
	
	if (comprobar_estado_txts())
	{
		cant_problemas = obtener_cantidad_de_problemas();
		p = new Problema [cant_problemas];
		
		recuperar_datos_usuarios(u, cant_problemas);
		recuperar_problemas(p, cant_problemas);
		merge_sort(p, 0, cant_problemas - 1, cant_problemas);
		
		color_solido = false;
		logo(u[0].nombre_equipo);     // <------ pss, pss, Gaston, comentar!
		
		do
		{
			color_solido = false;
			
			if (menu_login(u, u_actual))
				sesion = menu_principal(u, p, u_actual, cant_problemas);
			else
				sesion = false;
		} while(sesion);
		
		registrar_cant_problemas(cant_problemas);
		
		delete [] p;
		delete [] u[0].problemas_resueltos;
		delete [] u[1].problemas_resueltos;
		delete [] u[2].problemas_resueltos;
	}
	else
		Sleep(4000);
	
	logo_UTN();
	
	return 0;
}

bool menu_login(Usuario u[], int& u_actual)
{
	string contrasenia, legajo_str;
	int i, cont, x;
	char ch;
	bool legajo_correcto, contrasenia_correcta;
	
	f_cons(); fondo();
	recuadro();
	color_letra(11);
	linea (40, 10, 40);
	color_letra(4); centrar ("LOG IN", 10);
	
	color_letra(3);
	centrar ("Ingrese su número de legajo:", 12);
	color_letra(11);
	linea (45, 14, 30); color_letra(4);
	
	legajo_correcto = contrasenia_correcta = false;
	cont = 3; 
	while (cont > 0 && !legajo_correcto)
	{
		gotoxy(58, 14); 
		getline(cin, legajo_str);
		
		if (es_numero_es_no_vacia(legajo_str))
		{
			i = 0;
			while (i < 3 && !legajo_correcto)
			{
				if (stoi(legajo_str) == u[i].nro_legajo)
					legajo_correcto = true;
				else
					i++;
			}
			
			if (legajo_correcto)
				u_actual = i;
			else
				aux8("¡Error! Legajo no registrado", cont, 1);
		}
		else
			aux8("¡Error! No es un número", cont, 1);
	}
	
	if (cont != 0)
	{
		color_letra(3);
		centrar ("Ingrese su clave:", 16);
		color_letra(11); //10
		linea (45, 18, 30); 
		color_letra(4);
		
		cont = 3;
		while (cont > 0 && !contrasenia_correcta)
		{
			gotoxy(54, 18); 
			x = 54;          // coordenada inicial en x de la contrasenia
			
			//ingreso de contrasenia
			//--------------------
			contrasenia = "";
			do                 
			{
				ch = getch();
				
				if (isprint(ch)) 
				{
					contrasenia.push_back(ch);  // inserta el caracter ingresado
					cout << '*';
					x++;               // se mueve la coordenada
				}
				else if (ch == 8 && contrasenia != "")  // delete y cadena no vacia
				{
					x--;
					
					gotoxy(x, 18);   // coordenadas del ultimo caracter valido ingresado
					
					color_letra(11);     // imprimir espacio para tapar asterisco
					cout << ' ';
					color_letra(4); 
					
					contrasenia.pop_back();   // extrae el ultimo caracter
					
					gotoxy(x, 18); //se re coloca el puntero luego de tapar el asterisco
				}
			}
			while (ch != 13); // ingresar mientras no se de enter
			//----------------------
			
			if (u[u_actual].contrasenia == contrasenia)
			{
				contrasenia_correcta = true;
				
				f_cons(); fondo(); color_letra(1);
				centrar("¡Bienvenido, " + u[i].nombre_y_apellido + "!", 15);
				gotoxy(40, 18); system("pause");
			}
			else
				aux8("¡Error! Clave incorrecta", cont, 0);
		}
	}

	return (legajo_correcto && contrasenia_correcta);
}

bool menu_principal(Usuario u[], Problema *p, int u_actual, int cant_problemas)
{
	bool cerrar, sesion;
	int _volver;

	aux1();
	do
	{
		switch (flecha(44, 5, 3, 6))
		{
			case 1:
			{
				Beep(1000, 200);
				menu_actualizar_ficha(u, p, u_actual, cant_problemas);
				aux1();
				problemas_parciales_txt(u, cant_problemas);
				cerrar = false;
				sesion = true;
				break;
			}
			case 2:
			{
				Beep(1000, 200);
				menu_desempenio(u, p, u_actual, cant_problemas);
				aux1();
				cerrar = false;
				sesion = true;
				break;
			}
			case 3:
			{
				Beep(1000, 200);
				menu_borrado_datos(u, u_actual, cant_problemas);
				aux1();
				cerrar = false;
				sesion = true;
				break;
			}
			case 4: 
			{
				Beep(1000, 200);
				
				f_cons(); fondo(); color_letra(1);
				centrar("Fondo sólido / fondo decorado", 16);
				centrar("Volver", 19);
				
				_volver = flecha(42, 16, 3, 2);
				while(_volver != 2)
				{
					Beep(1000, 200);
					
					if (!color_solido)
						color_solido = true;
					else
						color_solido = false;
					
					f_cons(); fondo(); color_letra(1);
					centrar("Fondo sólido / fondo decorado", 16);
					centrar("Volver", 19);
					
					_volver = flecha(42, 16, 3, 2);
				}
				
				if (_volver == 2)
					Beep(1000, 200);
				
				aux1();
				
				break;
			}
			case 5:
			{
				Beep(1000, 200);
				
				f_cons(); fondo(); color_letra(1);
				centrar("Confirmar cierre de sesión", 16);
				centrar("Volver", 19);
				
				if (flecha(42, 16, 3, 2) == 1)
				{
					sesion = true;
					cerrar = true;
				}
				else
					aux1();
				
				Beep(1000, 200);
				
				break;
			}
			case 6: 
			{
				Beep(1000, 200);
				
				f_cons(); fondo(); color_letra(1);
				centrar("Confirmar cierre de la aplicación", 16);
				centrar("Volver", 19);
				
				if (flecha(40, 16, 3, 2) == 1)
				{
					cerrar = true;
					sesion = false;
				}
				else
					aux1();
				
				Beep(1000, 200);
				
				break;
			}
		}
	} while(!cerrar);
	
	return sesion;
}

void menu_borrado_datos(Usuario u[], int u_actual, int cant_problemas)
{
	int j;
	
	f_cons(); fondo(); color_letra(1);
	centrar("Confirmar el borrado de datos", 16);
	centrar("Volver", 19);
	
	if (flecha(41, 16, 3, 2) == 1)
	{
		Beep(1000, 200);
		
		for (j = 0; j < cant_problemas; j++)
			u[u_actual].problemas_resueltos[j] = 0;
		
		for (j = 0; j < 2; j++)
			u[u_actual].nota_parcial[j] = 0;
		
		problemas_parciales_txt(u, cant_problemas);
		
		f_cons(); fondo(); color_letra(1);
		
		centrar("Datos borrados exitosamente", 16);
		Sleep(2500);
	}
	else
		Beep(1000, 200);
}

void menu_actualizar_ficha(Usuario u[], Problema *p, int u_actual, int cant_problemas)
{
	bool volver;
	
	aux2();
	do
	{
		switch (flecha(40, 5, 3, 3))
		{
			case 1:
				Beep(1000, 200);
				registrar_problema(u, p, u_actual, cant_problemas);
				aux2();
				volver = false;
				break;	
			case 2:
				Beep(1000, 200);
				registrar_parcial(u, u_actual);
				aux2();
				volver = false;
				break;
			case 3:
				Beep(1000, 200);
				volver = true;
				break;
		}
	} while(!volver); 
}

void registrar_problema(Usuario u[], Problema *p, int u_actual, int cant_problemas) 
{
	string problema_str;
	int problema, i;
	bool verificar;
	
	f_cons(); fondo(); color_letra(8);
	cabecera("Menú de registro de problemas");
	
	do
	{
		recuadro();
		color_letra(11);linea (40, 10, 40);
		color_letra(4); centrar ("Problemas resueltos", 10);
		
		color_letra(3);
		centrar("Para volver al menú anterior", 22);
		centrar("ingrese '0'", 23);
		
		centrar ("Ingrese ID del problema resuelto:", 12);
		color_letra(11); linea (45, 14, 30); 
		color_letra(4); gotoxy(58, 14); 
		
		getline(cin, problema_str);
		
		if (es_numero_es_no_vacia(problema_str))
		{
			problema = stoi(problema_str);
			
			if (problema != 0)
			{
				i = 0; verificar = true;
				while (i < cant_problemas && verificar)
				{
					if (problema == p[i].nro)
						verificar = false;
					else 
						i++;
				}
				
				if (!verificar)
				{
					if (u[u_actual].problemas_resueltos[i] == 0)
					{
						u[u_actual].problemas_resueltos[i] = problema;
						color_letra(3);
						Beep(1000, 200);
						centrar ("Problema Registrado: " + to_string(p[i].nro), 16);
						centrar ("(" + p[i].nombre_problema + ")", 17);
						Sleep(1500);
					}
					else
					{
						error("¡Error! Problema ya registrado");
						color_letra(8);
						cabecera("Menú de registro de problemas");
					}
					
				}
				else if (verificar && problema)
				{
					error("¡Error! Problema inválido");
					color_letra(8);
					cabecera("Menú de registro de problemas");
				}
			}	
		}
		else
		{
			error("¡Error! No es un número");
			color_letra(8);
			cabecera("Menú de registro de problemas");
		}
	}
	while (problema);
}

void registrar_parcial(Usuario u[], int u_actual)
{
	string numero_parcial_str, nota_parcial_str;
	int numero_parcial, nota_parcial;
	
	f_cons(); fondo(); color_letra(8);
	cabecera("Menú de registro de calificaciones de parciales");
	
	do
	{
		recuadro();
		color_letra(11); linea (40, 10, 40);
		color_letra(4); centrar ("Parciales rendidos", 10);
		
		color_letra(3);
		centrar("Para volver al menú anterior", 22);
		centrar("ingrese '0'", 23);
		
		centrar ("Ingrese el parcial a registrar (1 o 2):", 12);
		color_letra(11); linea (45, 14, 30); color_letra(4);
		gotoxy(60, 14); 
		
		getline(cin, numero_parcial_str);
		
		if (es_numero_es_no_vacia(numero_parcial_str))
		{
			numero_parcial = stoi(numero_parcial_str);
			
			if (numero_parcial == 1 || numero_parcial == 2)
			{
				color_letra(3);
				centrar("Ingrese la nota: ", 16); 
				color_letra(11); linea (45, 18, 30); 
				color_letra(4); gotoxy(59, 18); 
				
				getline(cin, nota_parcial_str);
				
				if (es_numero_es_no_vacia(nota_parcial_str))
				{
					nota_parcial = stoi(nota_parcial_str);
					
					if (nota_parcial > 0 && nota_parcial <= 100)
					{
						if (u[u_actual].nota_parcial[numero_parcial - 1] == 0)
						{
							u[u_actual].nota_parcial[numero_parcial - 1] = stoi(nota_parcial_str);
							color_letra(3);
							Beep(1000, 200);
							centrar ("Calificación registrada", 20);
							Sleep(1500);
						}
						else
						{
							error("¡Error! Una calificación ya fue registrada");
							color_letra(8);
							cabecera("Menú de registro de calificaciones de parciales");
						}
					}
					else
					{
						error("¡Error! La calificación debe ser un número entre 1 y 100");
						color_letra(8);
						cabecera("Menú de registro de calificaciones de parciales");
					}
				}
				else
				{
					error("¡Error! No es un número");
					color_letra(8);
					cabecera("Menú de registro de calificaciones de parciales");
				}
			}
			else if (numero_parcial != 0 && numero_parcial != 1 && numero_parcial != 2)
			{
				error("¡Error! No existe parcial " + to_string(numero_parcial));
				color_letra(8);
				cabecera("Menú de registro de calificaciones de parciales");
			}
		}
		else
		{
			error("¡Error! No es un número");
			color_letra(8);
			cabecera("Menú de registro de calificaciones de parciales");
		}
	}
	while (numero_parcial);
}


void menu_desempenio(Usuario u[], Problema *p, int u_actual, int cant_problemas)
{
	bool volver;
	
	aux3();
	do
	{
		switch (flecha(44, 5, 3, 3))
		{
			case 1:
				Beep(1000, 200);
				menu_performance_individual(u, p, u_actual, cant_problemas);
				aux3();
				volver = false;
				break;
			case 2:
				Beep(1000, 200);
				menu_performarce_equipo(u, p, cant_problemas);
				aux3();
				volver = false;
				break;
			case 3:
				Beep(1000, 200);
				volver = true;
				break;
		}
	} while(!volver); 
}

void menu_performance_individual(Usuario u[], Problema *p, int u_actual, int cant_problemas)
{
	int i, j, k, cont_resueltos, cont_total, tema_nro;
	string tema_str, aux;
	ifstream temas;
	ofstream informe_legajo_rendimiento;
	
	informe_legajo_rendimiento.open("informe-legajo-rendimiento.txt");
	temas.open("temas.txt");
	
	informe_legajo_rendimiento 
		<< "______________________________\n"
		<< "Informe de problemas resueltos: " << u[u_actual].nombre_y_apellido << "\n\n";
	
	for (i = 0; i < obtener_cantidad_de_temas(); i++)
	{
		f_cons(); fondo(); color_letra(8);
		cabecera("Informe de problemas resueltos: " + u[u_actual].nombre_y_apellido);
		
		temas >> tema_nro;      
		getline(temas, tema_str);
		
		centrar("Tema " + to_string(tema_nro) + " - " + tema_str, 5);
		informe_legajo_rendimiento 
			<< "------\n"
			<< "Tema " << tema_nro << " - " << tema_str << "\n\n";
		
		
		for (cont_total = cont_resueltos = j = 0, k = 8; j < cant_problemas; j++)
		{
			if (p[j].tema == tema_nro)
			{
				cont_total++;
				
				if (u[u_actual].problemas_resueltos[j] != 0)
				{
					centrar((to_string(p[j].nro) + " - " + p[j].nombre_problema), k);
					informe_legajo_rendimiento << p[j].nro << " - " << p[j].nombre_problema << '\n';
					cont_resueltos++;
					k++;
				}
				
			}
		}
		
		if (cont_total != 0)   // si hay problemas de ese tema
		{
			aux = to_string((((double) cont_resueltos) / cont_total)* 100).substr(0, 5);   // saca el porcentaje y luego lo trunca (emular fixed setprecision)
			centrar("Total: " + to_string(cont_resueltos), k + 2);
			centrar(("Porcentaje problemas resueltos tema " + to_string(tema_nro) + ": " + aux + "%"), k + 3);
			informe_legajo_rendimiento 
				<< "\nTotal : " << cont_resueltos << '\n'
				<< "Porcentaje problemas resueltos tema " << tema_nro << ": " << fixed << setprecision(2) << (((double) cont_resueltos) / cont_total) * 100 << "%\n\n"; 
		}
		else
		{
			centrar("(no existen problemas en esta categoría)", k + 2);
			informe_legajo_rendimiento << "(no existen problemas en esta categoría)\n\n";
		}
		
		gotoxy(40, k + 6); system("pause");
	}
	
	//-------------
	f_cons(); fondo(); color_letra(8);
	cabecera("Informe de calificaciones de parciales: " + u[u_actual].nombre_y_apellido);
	informe_legajo_rendimiento 
		<< "______________________________________\n"
		<< "Informe de calificaciones de parciales: " << u[u_actual].nombre_y_apellido << "\n\n";
	
	for (i = 0, j = 6; i < 2; i++, j+= 2)
	{
		if (u[u_actual].nota_parcial[i] != 0)
		{
			if (u[u_actual].nota_parcial[i] >= 60 && (u[u_actual].nota_parcial[i] < 70))
				aux = " (aprobado)";
			else if ((u[u_actual].nota_parcial[i] > 70))
				aux = " (promocionado)";
			else if (u[u_actual].nota_parcial[i] < 60)
				aux = " (reprobado)";
			
			centrar("Parcial " + to_string(i + 1) + ": " + to_string(u[u_actual].nota_parcial[i]) + aux, j);
			informe_legajo_rendimiento << "Parcial " << i + 1 << ": " << u[u_actual].nota_parcial[i] << aux << '\n';
		}
		else
		{
			centrar("Parcial " + to_string(i + 1) + ": - (no fue registrado)", j);
			informe_legajo_rendimiento << "Parcial " << i + 1 << ": - (no fue registrado)\n";
		}
	}
	
	gotoxy(40, 11); system("pause");	
	
	temas.close();	
	informe_legajo_rendimiento.close();
}

void menu_performarce_equipo(Usuario u[], Problema *p, int cant_problemas)
{
	int i, j, k, l, aux;              
	int filas_a_mostrar = 10; // (filas de datos efectivas a mostrar, no se cuentan lineas intermedias)

	///salida tabla
	///-------------------------------------------------------------------------
	
	if (cant_problemas % filas_a_mostrar == 0)   // evitar mostrar cabecera sin elementos
		aux = cant_problemas / filas_a_mostrar;
	else
		aux = cant_problemas / filas_a_mostrar + 1;
	
	for (l = i = 0; i < aux; i++)
	{		
		aux4(u);
		
		gotoxy(0, 6);
		
		j = l;
		while ((j < (filas_a_mostrar + l)) && j < cant_problemas)
		{
			color_letra(1);
			
			cout 
				<< char(186) << "     " << p[j].nro << "      " 
				<< char(186) << "            " << p[j].tema << "           ";
			
			for (k = 0; k < 3; k++)
			{
				color_letra(1);
				
				if (u[k].problemas_resueltos[j] != 0)
				{
					cout << char(186);
					color_letra(7);
					cout << "         Accepted        ";
				}
				else
				{
					cout << char(186);
					color_letra(6);
					cout << "            X            ";
				}
			}
			
			color_letra(1);
			cout << char(186) << '\n';
			for (k = 0; k < 120; k++)
				cout << char(205);
			
			j++;
		}
		
		l = j;
		
		gotoxy(40, 38); system("pause");	
	}
	///-------------------------------------------------------------------------
	
	///lista enlazada
	///-------------------------------------------------------------------------  
	/*se genera una pequenia lista enlazada de acuerdo al criterio establecido en el tp
	con los porcentajes calculados de cada tema. Si las notas del parcial i no estan cargadas
	en todos los integrantes, no se genera un nodo; para los problemas siempre se crean. Se
	borra la lista luego de mostrar los resultados (ciertamente se podría usar un simple
	arreglo de n posiciones, siendo un poco menos costoso en terminos de memoria ocupada
	y funciones). */
	
	nodo_tarea_resuelta *informe_equipo;
	int cont_resueltos, cont_total;
	
	informe_equipo = NULL;
	
	for (i = 1; i <= obtener_cantidad_de_temas(); i++)
	{
		for (cont_total = cont_resueltos = j = 0; j < cant_problemas; j++)
		{
			if (p[j].tema == i)
			{
				cont_total++;
				
				if 
				(
					u[0].problemas_resueltos[j] != 0 || 
					u[1].problemas_resueltos[j] != 0 || 
					u[2].problemas_resueltos[j] != 0
				)
					cont_resueltos++;
			}	
		}
		
		if (cont_total != 0)
			insertar_nodo_al_final(informe_equipo, i, ((((double) cont_resueltos) / cont_total) * 100));
		else
			insertar_nodo_al_final(informe_equipo, i, 666);    // se inserta 666 si se hace 0 / 0 (no hay problemas en la categoria)
 	}
	
	for (j = 0, i = 999; i <= 1000; i++, j++)     //se insertara un nodo en la medida en que los tres integrantes hayan registrado notas de parcial
	{
		if 
		(
			u[0].nota_parcial[j] != 0 &&
			u[1].nota_parcial[j] != 0 &&
			u[2].nota_parcial[j] != 0
		)
			insertar_nodo_al_final
			(
				informe_equipo,
				i,
				((u[0].nota_parcial[j] + u[1].nota_parcial[j] + u[2].nota_parcial[j]) / 3.0)
			);
	}
	
	aux5(informe_equipo, u);  // mostrar por pantalla, archivo
	borrar_lista(informe_equipo);
	///-------------------------------------------------------------------------  
}
