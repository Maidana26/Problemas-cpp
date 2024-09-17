#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define TF 14636
#define cantcaracteres 26

struct libro{
	
	string nombre;
	string idioma;
	int tlp;
	int tlr;
	//26 letras ascci a,b,c,d,....,y,z
	//1 letras especiales ä
	int frecCar[cantcaracteres];
	string palabras[TF];
	int repeticiones[TF];
	char caracteres[cantcaracteres];
};

struct pal{
	char contenido[30];
	int repeticiones;
};
struct nodo{
	pal palabra;
	nodo *proximoPtr;
};

//GENERALES
void eliminar(string v[],int &tl,int pos,int cantpos);
void eliminarRepetidas(libro &l);

void llenarLibro(libro &l);

void mostrarContenido(libro l);

//OPCION 1

//i)
void contarCaracteres(const string linea, libro &l);

//ii)
void mergeFrecuencia(libro& l,int inicio1,int final1,int inicio2,int final2);
void mergesortFrecuencia(libro& l, int inicio, int fin);

void llenarArchivoFrecuencias(libro l);

//OPCION 2
void leerPalabra(const string &linea, libro& l);

//i)
string palabraMasLarga(libro l);
void MostrarmatrizPalabra(int mPalabras[30][cantcaracteres],int n);
	
void matrizPalabra(int mPalabras[30][cantcaracteres],libro l);

//ii)
//1)
void longitudPromedio(libro l);

//2)
void mergeRepeticiones(libro& l,int inicio1,int final1,int inicio2,int final2);
void mergesortRepeticiones(libro& l, int inicio, int fin);

void frecuenciaDeLetraInicial(libro &l,char x);

//3)
void porcentajeDeInicio(libro &l);

//iii)

void insertarElementoEnListaEnlazada(char palabra[],int repeticiones, nodo * &lista);
	
void llenarListaEnlazada(libro &l);

//iiii)
void llenarArchivoListaEnlazada(nodo * &lista, char x);
	
	
