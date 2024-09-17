#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

const int TAM = 50;

struct archivo{
	string nombre;
	string nombrefisico;
	int cantidad;
}; 

struct user {
	char nombre[TAM];
	char apellido[TAM];
	char sexo;
	int ID;
	int contra;
	char rol[TAM];
	char fecha[11];
	char hora[6];
};


archivo setup(string nombre, string nombreF);
bool apertura(archivo X);
string leerLinea(archivo & X, bool & final);
int leidas(archivo X);
bool cierre(archivo X);
