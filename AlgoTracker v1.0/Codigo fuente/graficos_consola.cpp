#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <ctime>
#include <conio.h>
#define C(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (x))
using namespace std;
#include "graficos_consola.h"

extern bool color_solido;

void gotoxy(short x, short y)
{
	COORD cp = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}

void f_cons() // "formatear" la consola
{
	if (!color_solido) 
		system("cls");
	system("mode con: cols=120 lines=40");
}

void color_letra (int aux) 
{
	switch (aux)
	{
		case 1:
			C(159); // letra blanca, fondo azul claro
			break;
		case 2: 
			C(7); // letra blanca, fondo negro
			break;
		case 3: 
			C(112); // letra negra, fondo gris
			break;
		case 4: 
			C(240); // letra negra, fondo blanco brillante
			break;
		case 5: 
			C(28); // letra roja, fondo azul
			break;
		case 6: 
			C(79); // letra blanca, fondo rojo
			break;
		case 7: 
			C(47); // letra blanca brillante, fondo verde
			break;
		case 8:
			C(249); // letra azul claro, fondo blanco brillante
			break;
		case 9:
			C(124); // letra roja, fondo gris
			break;
		case 10:
			C(119); // letra gris, fondo gris
			break;
		case 11:
			C(255); // letra blanca brillante, fondo blanca brillante
			break;
		case 12:
			C(153); // letra azul claro, fondo azul claro
			break;
		case 13:
			C(156); // letra rojo claro, fondo azul claro
			break;
	}
}

void centrar(string texto, int h)
{
	static unsigned int i;
	static char ch;
	
	gotoxy((60 - (texto.length() / 2)), h);

	for (i = 0; i < texto.length(); i++)
	{
		ch = texto.at(i); // birlar problemas al imprimir strings con caracteres especiales (aunque es caro computacionalmente)
		
		 	 if (ch == 'á')
			cout << char(160);  
		else if (ch == 'é')
			cout << char(130);
		else if (ch == 'í')
			cout << char(161);
		else if (ch == 'ó')
			cout << char(162);
		else if (ch == 'ú')
			cout << char(163);
		else if (ch == '¡')
			cout << char(173);
		else if (ch == 'ñ')
			cout << char(164);
		else if (ch == 'Á')
			cout << char(181);
		else if (ch == 'É')
			cout << char(144);
		else if (ch == 'Í')
			cout << char(214);
		else if (ch == 'Ó')
			cout << char(224);
		else if (ch == 'Ú')
			cout << char(233);
		else 
			cout << ch;
	}
	cout << '\n';
}

void cabecera(string texto)
{
	static int i;
	
	gotoxy(0, 0);
	cout << char(201);
	for (i = 0; i < 118; i++)
		cout << char(205);
	cout << char(187);

	gotoxy(0, 1);
	cout << char(186);
	for (i = 1; i < 199; i++) cout << ' '; // "limpiar" fondo 
	centrar(texto, 1);
	gotoxy(119, 1);
	cout << char(186);

	gotoxy(0, 2);
	cout << char(200);
	for (i = 0; i < 118; i++)
		cout << char(205);
	cout << char(188);
	
	color_letra(1);
}

void error(string texto)
{
	color_letra(6);
	cabecera(texto);
	Beep(100, 350);
	Sleep(1200);
}

void fondo()
{
	static int i, j;
	static int colores[] = {145, 149, 147}; // 155, 157
	static char ch[] = {' ', ' ', '#', ' ', ' ', '@', ' ', ' ', '$', ' ', ' ', '&', ' ', ' '};
	
	if (color_solido == true)
	{
		color_letra(12);
		//system("color 99");
		system("cls");
	}
	else
	{
		gotoxy(0, 0);
		for (i = 0; i < 40; i++)
		{
			for (j = 0; j < 120; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colores[rand() % 3]);
				cout << ch[rand() % 14];
			}
			
			if (i < 39)
				cout << '\n';
		}
	}
}

void logo(string nombre_equipo)
{
	int i, j, k;
	string fases1[] =
	{
		" |1010101010|   |101010|    |10101010|        |10101|   |1010101|   |101010|     |101010|   ",
		"     |10|       |10   10|        |101|       |10  01|   |10         |10    10|   |10    10| ",
		"     |10|       |101010|    |01010101|      |1010101|   |10101|     |10    10|   |10    10| ",
		"     |10|       |10|        |101|          01|   |10|   |10         |10    10|   |10    10| ",
		"     |10|       |10|        |10101010|    |10     01|   |1010101|   |101010|     |101010|   "
	};
	string fases2[] =
	{
		"Chort, Julio Alberto",
		"Pacheco Pilan, Federico Ignacio",
		"Reynoso, Valentín",
		" - Comisión A / 2019 - ",
		" - Versión 1.0 - "
	};

	f_cons(); fondo(); 
	gotoxy(0, 0);
	color_letra(5);

	gotoxy(10, 3); for (i = 0; i < 100; i++) cout << char(205);

	for (i = 0, j = 4, k = 1400; i < 5; i++, j++, k -= 200)
	{
		gotoxy(13, j); cout << char(186);
		centrar(fases1[i], j);
		gotoxy(106, j); cout << char(186);

		Sleep(100);
		Beep(k, 350);
	}

	gotoxy(10, 9); for (i = 0; i < 100; i++) cout << char(205);

	Sleep(250);
	Beep(400, 350);
	
	color_letra(13);
	centrar("- " + nombre_equipo + " -", 13);
	color_letra(1);
	for (i = 0, j = 14; i < 5; i++, j++)
	{
		centrar(fases2[i], j);

		if (i == 2) //evitar dejar de usar un bucle
		{
			j += 2;
			color_letra(13);
		}
	}

	color_letra(1);
	gotoxy(40, 23); system("pause");
}

void logo_UTN()
{
	string fases[] =
	{
		"UTN   UTN   UTN",
		"UTN   UTN   UTN",
		 "UTN  UTN  UTN",
		   "UTNUTNUTN",
		"UTNUTNUTNUTNUTN",
		   "UTNUTNUTN",
		 "UTN  UTN  UTN",
		"UTN   UTN   UTN",
		"UTN   UTN   UTN"
	};
	int i, j, k;

	f_cons();
	fondo();
	color_letra(5);

	for (i = 0, j = 3, k = 1200; i < 9; i++, j++, k -= 100)
	{
		centrar(fases[i], j);
		Sleep(150);
		Beep(k, 150);
	}

	cout << "\n\n";
}

void recuadro()
{
	int i, j;
	
	color_letra(2);
	
	for (i = 10; i < 25; i++)
	{
		gotoxy(40, i);
		
		for (j = 40; j < 80; j++)
		{
			cout << char(219);
		}
	}
}

void linea(short x, short y, int largo)
{
	int i;
	
	gotoxy(x,y);
	
	for (i = 0; i < largo; i++)
		cout << char(219);
}

int flecha(short x0, short y0, int incremento, int opciones_posibles)
{
	int opcion_seleccionada, y1;
	char ch;

	color_letra(1);
	gotoxy(x0, y0); cout << "->";
	gotoxy(119 - x0,y0); cout << "<-";
	
	y1 = y0;
	opcion_seleccionada = 1;
	do
	{
		ch = getch();
		
		if (ch == 's' && opcion_seleccionada != opciones_posibles) // flecha hacia abajo
		{
			// borrar flecha anterior
			color_letra(12);
			gotoxy(x0, y1); cout << "  ";
			gotoxy(119 - x0, y1); cout << "  ";
			//-------
			
			y1 += incremento;
			
			color_letra(1);
			gotoxy(x0, y1); cout << "->";
			gotoxy(119 - x0,y1); cout << "<-";
			
			opcion_seleccionada++;
			
			Sleep(100);
		}
		else if (ch == 'w' && y1 != y0) // flecha hacia arriba
		{
			// borrar flecha anterior
			color_letra(12);
			gotoxy(x0, y1); cout << "  ";
			gotoxy(119 - x0, y1); cout << "  ";
			//-------
			
			y1 -= incremento;
			
			color_letra(1);
			gotoxy(x0, y1); cout << "->";
			gotoxy(119 - x0,y1); cout << "<-";
			
			opcion_seleccionada--;
			
			Sleep(100);
		}
	} while(ch != 13);
	
	return opcion_seleccionada;
}
