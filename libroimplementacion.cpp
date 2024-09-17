#include "librocabeceras.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include <iomanip>
using namespace std;

void eliminar(string v[],int &tl,int pos,int cantpos){
	for(int i=pos;i<tl;i++){
		v[i]=v[i + cantpos];
	}
	tl-=cantpos;
}
	
void eliminarRepetidas(libro &l){
	//busqueda secuencial de todas las ocurrencias de una palabra
	int rep;
	l.tlr=0;
	for(int i=0;i<l.tlp-1;i++){
		rep=1;
		for(int j=i+1;j<l.tlp;j++){
			if(l.palabras[i]==l.palabras[j]){
				rep++;
				eliminar(l.palabras, l.tlp, j, 1);
			}
			l.repeticiones[i]=rep;
			l.tlr++;
		}
	}
}
	
bool esDelimitador(char c) {
	// Puedes ajustar la lista de delimitadores según tus necesidades
	return 
		(  c == ' '  || c == '-'  || c == '_' ||  c == '«'|| c == '»' || c == '‘' || c == '’' || c == '“' || c == '”' 
		|| c == '\t' || c == '\n' || c == ',' || c == ';' || c == '.' || c == ':' || c == '!' 
		|| c == '?'  || c == '•' );
}

bool Repetida(const string linea, libro &l,int& pos){
	bool seRepite=false;
	int i=0;
	while(!seRepite and i<l.tlp){
		if(linea==l.palabras[i]){
			seRepite=true;
			pos=i;
		}else{
			i++;
		}
	}
	if(!seRepite)
		pos=-1;
	return seRepite;
}
	
void leerPalabra(const string &linea, libro &l) {
	string palabra="";
	char c;
	unsigned int i=0;
	while(i<linea.length()) {
		c=linea.at(i);
		c=tolower(c);
		if(isalpha(c)){
			palabra+=c;
		}
		else if(esDelimitador(c)){
			if(palabra.length()>0 and l.tlp < TF){
				int pos;
				if(!Repetida(palabra, l, pos)) {
					l.palabras[l.tlp] = palabra;
					l.repeticiones[l.tlp]++;
					l.tlp++;
				}
				else{
				// La palabra ya existe, incrementa el número de repeticiones
				l.repeticiones[pos]++;
				}
			palabra.clear();
			}
		}
		i++;
	}
}

void mergeRepeticiones(libro& l,int inicio1,int final1,int inicio2,int final2){
	string c[l.tlp];
	int d[l.tlp];
	int i,j,k;
	i=inicio1; j=inicio2; k=0;
	
	while(i<=final1 and j<=final2){
		if(l.repeticiones[i]>l.repeticiones[j]){
			c[k] = l.palabras[i];
			d[k] = l.repeticiones[i];
			i++;
			k++;
		}
		else{
			c[k] = l.palabras[j];
			d[k] = l.repeticiones[j];
			j++;
			k++;
		}
	}
	
	while(i<=final1){
		c[k] = l.palabras[i];
		d[k] = l.repeticiones[i];
		i++;
		k++;
	}
	while(j<=final2){
		c[k] = l.palabras[j];
		d[k] = l.repeticiones[j];
		j++;
		k++;
	}
	for(int k=0;k<final2 - inicio1 + 1; k++){
		l.palabras[inicio1 + k] = c[k];
		l.repeticiones[inicio1 + k] = d[k];
	}
}

void mergesortRepeticiones(libro& l, int inicio, int fin){
	if (fin <= inicio) return ;
	
	int medio = (fin + inicio)/2;
	mergesortRepeticiones(l,inicio,medio);
	mergesortRepeticiones(l,medio+1,fin);
		
	mergeRepeticiones(l,inicio,medio,medio+1,fin);
}

void mergeFrecuencia(libro& l,int inicio1,int final1,int inicio2,int final2){
	char v[cantcaracteres];
	int c[cantcaracteres];
	int i,j,k;
	i=inicio1; j=inicio2; k=0;
		
	while(i<=final1 and j<=final2){
		if(l.frecCar[i]>l.frecCar[j]){
			c[k] = l.frecCar[i];
			v[k]= l.caracteres[i];
			i++;
			k++;
		}
		else{
			c[k] = l.frecCar[j];
			v[k]= l.caracteres[j];
			j++;
			k++;
		}
	}
		
	while(i<=final1){
		c[k] = l.frecCar[i];
		v[k]= l.caracteres[i];
		i++;
		k++;
	}
	while(j<=final2){
		c[k] = l.frecCar[j];
		v[k]= l.caracteres[j];
		j++;
		k++;
	}
	for(int k=0;k<final2 - inicio1 + 1; k++){
		l.frecCar[inicio1 + k] = c[k];
		l.caracteres[inicio1 + k] = v[k];
	}
}
void mergesortFrecuencia(libro& l, int inicio, int fin){
	if (fin <= inicio) return ;
	
	int medio = (fin + inicio)/2;
	mergesortFrecuencia(l,inicio,medio);
	mergesortFrecuencia(l,medio+1,fin);
	
	mergeFrecuencia(l,inicio,medio,medio+1,fin);
}
/*Aclaracion:
	en nuestro texto encontramos al caracter especial 'ä'
	pero ninguno de los acentos tipicos del idioma que nos toco
	lo consultamos con agustin, el profe de practica y nos dijo que
	modifiquemos el texto de la divina comedia y cambiaramos 'ä' por 'a'
*/
void contarCaracteres(const string linea, libro &l){
	unsigned int i=0;
	char c;
	for(int j=0; j< cantcaracteres; j++){
		l.caracteres[j]=j+97;
	}
	while(i<linea.length()){
		c=linea.at(i);
		if(isalpha(c)){
			c=tolower(c);
			l.frecCar[c-'a']++;
		}
		i++;
	}
}
//caracteres especiales que si aparecen ä
//caracteres especiales que no aparecen é à è ì ò ù 
void llenarLibro(libro &l) {
	//abro el archivo
	ifstream archivo(l.nombre);
	if (!archivo.is_open()) {
		cout<<"Error al abrir el archivo para lectura de texto."<<endl;
		return;
	}
	//lleno el vector con todas las palabras del archivo
	l.tlp=0;
	l.frecCar[cantcaracteres]={0};
	string linea;
	while(!archivo.eof() and l.tlp<TF){
		getline(archivo, linea);
		contarCaracteres(linea,l);
		//cuento la frecuencia de los caracteres (opcion 1 a)
		leerPalabra(linea,l);
		//guardo una repeticion de cada palabra del texto (util para la opcion 2)
	}
	archivo.close();
	//cierro el archivo
	
	mergesortFrecuencia(l,0,cantcaracteres-1);
	//ordeno la frecuencia de caracteres (opcion 1 b)
	int fin=l.tlp-1;
	mergesortRepeticiones(l,0,fin);
	//la ordeno en orden alfabetico para visualizarlo mejor
}
	
	
void mostrarContenido(libro l){
	system("mode con: cols=50 lines=35");
	cout<<"Nombre libro:"<<l.nombre<<endl;
	
	cout<<"Tabla de frecuencia de caracteres:"<<endl;
	int suma=0;
	
	for(int i=0;i<cantcaracteres;i++){
		
		cout<<" "<<l.caracteres[i]<<"		"<<l.frecCar[i]<<endl;
		suma+=l.frecCar[i];
	}
}

void llenarArchivoFrecuencias(libro l){
	
	ofstream f;
	f.open("frecuencia.txt");
	cout<<"escribiendo el archivo..."<<endl;
	
	for(int i=0;i<cantcaracteres-1;i++){
		f<<char(i+97)<<"		"<<l.frecCar[i]<<endl;
	}
	
	f.close();
}

string palabraMasLarga(libro l){
	//asigno la mas larga a la primera
	string maxlong=l.palabras[0];
	for(int i=0;i<l.tlp-1;i++){
		for(int j=i+1;j<l.tlp;j++){
			if(l.palabras[i].length()<l.palabras[j].length()){
				maxlong=l.palabras[j];
			}
		}
	}
	return maxlong;
}
void MostrarmatrizPalabra(int mPalabras[30][cantcaracteres],int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<cantcaracteres;j++){
			cout<<mPalabras[i][j]<<" 	";
		}
		cout<<endl;
	}
}
void matrizPalabra(int mPalabras[30][cantcaracteres],libro l){
	int n=palabraMasLarga(l).length();
	int m=cantcaracteres;
	int tampal;
	char primeral;
	//inicializo en 0 las posiciones de memoria que me interesa
	mPalabras[n][m]={0};
	for(int i=0;i<l.tlp;i++){
		//primera letra de la palabra
		primeral=l.palabras[i].at(0);
		//longitud de la palabra
		tampal=l.palabras[i].length();
		//me ubico en el subindice correspondiente y sumo la frecuencia
		mPalabras[tampal-1][primeral-97]+=l.repeticiones[i];
	}
	MostrarmatrizPalabra(mPalabras,n);
}
	
void longitudPromedio(libro l){
	float suma=0;
	for(int i=0;i<l.tlp;i++){
		//sumo la longitud de todas las palabras
		suma=suma + l.palabras[i].length();
	}
	//divido la suma por el total de palabras
	cout<<"La longitud de palabra promedio del archivo es: "<< endl;
	cout<<fixed<<setprecision(2)<<suma/l.tlp<<endl;
}
	
void intercambiar(string &a,string &b) {
	string aux = a;
	a = b;
	b = aux;
}

void frecuenciaDeLetraInicial(libro &l,char x){
	
	int i=0,j=1;
	while(i<l.tlp and j<6){
		//busco la primera ocurrencia de las palabras que empicen con x
		//como el vector l.palabras ya esta ordenado segun la cantidad de repeticiones
		if(l.palabras[i].at(0)==x){
			if(j==1)cout<<"las 5 palabras que empiezan con "<<x<<" mas repetidas:"<<endl;
			cout<<j<<") "<<l.palabras[i]<<" con "<<l.repeticiones[i]<<" repeticiones."<<endl;
			j++;
		}
		i++;
	}
}

void porcentajeDeInicio(libro &l){
	float svocales=0.0,scons=0.0;
	int suma=0;
	for(int i=0;i<l.tlp;i++){
		switch(l.palabras[i].at(0)){
		case 'a':{svocales+=l.repeticiones[i];break;}
		case 'e':{svocales+=l.repeticiones[i];break;}
		case 'i':{svocales+=l.repeticiones[i];break;}
		case 'o':{svocales+=l.repeticiones[i];break;}
		case 'u':{svocales+=l.repeticiones[i];break;}
		default:{scons+=l.repeticiones[i];break;}
		}
		suma+= l.repeticiones[i];
	}
	cout<<"Porcentaje de inicio con vocales es: "<<fixed<<setprecision(2)<<(svocales/suma)*100<<"%"<<endl;
	cout<<"Porcentaje de inicio con consonantes es: "<<fixed<<setprecision(2)<<(scons/suma)*100<<"%"<<endl;
}

void insertarElementoEnListaEnlazada(char palabra[], int repeticiones, nodo *&lista) {
	nodo *anterior, *actual, *nuevo;
	
	nuevo = new nodo;
	
	if (nuevo != NULL) {
		strcpy(nuevo->palabra.contenido, palabra);
		nuevo->palabra.repeticiones = repeticiones;
		nuevo->proximoPtr = NULL;
		
		anterior = NULL;
		actual = lista;
		
		while ((actual != NULL) and
			(repeticiones < actual->palabra.repeticiones or
			 (repeticiones == actual->palabra.repeticiones and strlen(palabra) < strlen(actual->palabra.contenido)) or
			 (repeticiones == actual->palabra.repeticiones and strlen(palabra) == strlen(actual->palabra.contenido) and strcmp(palabra, actual->palabra.contenido)>0))) {
			
			anterior = actual;
			actual = actual->proximoPtr;
		}
			if (anterior == NULL) {
				nuevo->proximoPtr = lista;
				lista = nuevo;
			} 
			else {
				anterior->proximoPtr = nuevo;
				nuevo->proximoPtr = actual;
			}
	}
	else {
		cout << "No insertado. No hay memoria disponible..." << endl;
	}
}


void llenarArchivoListaEnlazada(nodo * &lista, char x){
		
	ofstream f;
	f.open("palabrasX.txt");
	cout<<"escribiendo el archivo..."<<endl;
	
	nodo* actual=lista;
	while(actual != NULL){
		if(actual->palabra.contenido[0]==x){
			f<<actual->palabra.contenido<<"		"<<actual->palabra.repeticiones<<endl;
		}
		actual=actual->proximoPtr;
	}
	f.close();
}
	
void llenarListaEnlazada(libro &l){
	char palabra[30];
	int repeticiones;
	nodo * lista;
	
	lista = NULL;
	
	for(int i=0;i<l.tlp;i++){
		
		strcpy(palabra,l.palabras[i].c_str());
		repeticiones=l.repeticiones[i];
		
		insertarElementoEnListaEnlazada(palabra, repeticiones, lista);
	}
	
	
	cout<<"ingrese la la primera letra de las palabras que"<<endl
		<<"quieren que se guarden en el archivo..";
	char x;
	cin>>x;
	cin.ignore();
	cout<<endl;
	llenarArchivoListaEnlazada(lista,x);
}
	
