#include "archivo.h"
#include "librocabeceras.h"

#include <cctype>
#include <iostream>
#include <string>
#include <tuple>
#include <cstdlib>
#include <stdlib.h>
#include <windows.h>
#include <iomanip>
#include <ctime>
#include <conio.h>

using namespace std;

void Pantalla_De_Bienvenida();
bool Verificacion_Cotrasenia(char contrasenia[],string idUsuario);
void Pantalla_De_Login(bool &cierreDelPrograma);
void Menu_De_Abecedarios(bool &back);
bool Letras_repetidas (string , char );
void Ahorcado(bool &back,string vector_palabras[]);
void Palabra_Cifrada(bool &back,string vector_palabras[]);
void Numeros_En_Otro_Idioma(bool &back);
void Memoria(bool &back,string vector_palabras[]);
void Menu_De_Juegos(bool &back,string vector_palabras[]);
void Menu_Principal(bool &cierreDelPrograma,string vector_palabras[]);
void Procesador_de_texto(bool &back);
void Repeticiones_de_letras(string palabra,int repletras[]);
void Vocales_totales(string palabra,int vocalestotales[]);
float Puntuacion(int rta_esperada,int rta_ingresada);
void Cambio_de_numero_a_caracter (char contrasenia[]);
void CargarBIN (user u[],int TL);
void CaragarTXT (user u[],int TL);
void StrinAentero (int &Id,string idUsuario);
void CadAentero (int &Contra, char c[]);
void cambiarFechaHoraActual(user& usuario);
void Buscar_en_binario_CONTRA (int password, bool &esta);
void Buscar_en_binario_ID (int id, bool &esta);
/*
Explicacion funcionamiento de puntuacion en juego memoria:
La obtencion de los puntajes en el item 1 y 3 son dos promedios simples, ya que la letra que mas se repite
y la palabra de mayor longitud son conocidas. El problema se da en el item dos ya que el usuario puede ingresar
una cantidad de vocales mayor a la que realmente son, en ese caso el promedio no funcionara correctamente, por
lo que desarrollamos una funcion puntuacion para el caso en el que la respuesta del usuario sea un numero mayor al real. 
y asi calculamos el puntaje para ese caso en particular. luego simplemente promediamos los 3 puntajes en e final.
*/

int main(int argc, char *argv[]) {
	system("mode con: cols=50 lines=25");
	
	//cargando vector con las palabras del arcivo de texto
	archivo Entrada;
	string vector_palabras[100];
	string nombre="Listado de palabras";
	Entrada = setup(nombre,"palabras-1.txt");
	
	if (apertura(Entrada)==false){
		cout << "Error en apertura de archivo" << endl;
	}
	else {
		bool final=false;
		int i=0;
		do {
			vector_palabras[i]=leerLinea(Entrada, final);
			i++;
		} while (not final);
	}
	
	Pantalla_De_Bienvenida();
	
	bool cierreDelPrograma=0;
	
	Pantalla_De_Login(cierreDelPrograma);
	
	if(cierreDelPrograma){
		cout<<"Usuario no valido o demasiados intentos "<< endl;
		cout<<"se cierra..."<<endl;
		return 0;
	}

	Menu_Principal(cierreDelPrograma,vector_palabras);
	
	if(cierreDelPrograma){
		cout<<"Apreto X, se cierra el programa..."<<endl;
		return 0;
	}
	
	cierre(Entrada);

	return 0;
}

void Pantalla_De_Bienvenida(){
	system("color 31");
	int Imagen_Bienvenida[25][49]={
	//	 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,1 ,1 ,0 ,0 ,1 ,0 ,1 ,1 , 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0},
		{0 ,0 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 , 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,1 ,1 ,0 ,0 ,1 ,0 ,1 ,1 , 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0},
		{0 ,0 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 , 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
		{0 ,0 ,0 ,1 ,1 ,0 ,0 ,1 ,0 ,1 ,1 , 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
	for (int i=0; i<25; i++){
		for (int j=0; j<49;j++){
			if(Imagen_Bienvenida[i][j]==2 || Imagen_Bienvenida[i][j]==1){
				SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),144);
				cout<< char(219);
			}
			else if(Imagen_Bienvenida[i][j]==3){
				SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),151);
				cout<< char(219);
			}
			else if(Imagen_Bienvenida[i][j]==4){
				SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),150);
				cout<< char(219);
			}
			else if(Imagen_Bienvenida[i][j]==0){
				
				cout<< " ";
			}
			
		}
		cout<<endl;
	}
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),144);
	cout<< "Presione Enter para continuar...";
	cin.get(); 
	system("cls");
}
	
bool Verificacion_Cotrasenia(char contrasenia[],string idUsuario){
	char contraseniaCorrecta[6];
	
	for(int i=0;i<4;i++){
		contraseniaCorrecta[i]=idUsuario[4-i];
	}
	contraseniaCorrecta[4]=((idUsuario[4]-48+idUsuario[0]-48)%10)+48;
	contraseniaCorrecta[5]= '\0';
	bool flag = true;
	int i=0;
	while(i<5 and flag){
		if(contraseniaCorrecta[i]!=contrasenia[i])
			flag=false;
		    i++;
	}

	return flag;
}

void Cambio_de_numero_a_caracter (char contrasenia[]){
	int contador = 0;
	while (contador < 5) {
		char entrada = _getch();
		
		if (entrada == 13)  // 13 es el código ASCII para la tecla Enter
			break;
		
		if (entrada == 8 && contador > 0) {
			// Si se presiona la tecla de retroceso, borramos un carácter
			cout << "\b \b";  // Retrocede, borra y retrocede de nuevo
			contador--;
		} else if (isprint(entrada) && contador < 5) {//la funcion isprint(entrada) pregunrta si el caracter es o no es imprimible
			// Si es un carácter imprimible y no excede la longitud, lo almacenamos
			contrasenia[contador++] = entrada;
			cout << '*';  // Muestra '*' en lugar del caracter ingresado
		}
	}
	
	contrasenia[contador] = '\0';  // Agrega el carácter nulo al final
}
void Pantalla_De_Login(bool &cierreDelPrograma){
	//user u[1000];
	//int TL=100;
	bool UsuarioEncontrado=false;
	int Id, Contra;
	
	//CaragarTXT(u,TL);
	//CargarBIN(u,TL);
	
	string idUsuario;
	
	cout<<"=================================================="<<endl;
	cout<<"               Ingrese su usuario: "<<endl;
	cout<<"                      ";getline(cin,idUsuario);
	Id = stoi(idUsuario);
    Buscar_en_binario_ID(Id,UsuarioEncontrado);
	int contador=1;
	while((contador<3 and !(idUsuario.length()==5 and idUsuario>="10000" and idUsuario<="89999")) || (!UsuarioEncontrado and contador<3)){
		cout<<"Error de id"<<endl;
		cout<<"                      ";getline(cin,idUsuario);
		Id = stoi(idUsuario);
		if(!(idUsuario.length()==5 and idUsuario>="10000" and idUsuario<="89999"))
			contador++;
		cout<< endl;
		Buscar_en_binario_ID(Id,UsuarioEncontrado);
		if(!UsuarioEncontrado){
			contador++;
		}
	}	
	
	if(contador==3 and !UsuarioEncontrado)
		cierreDelPrograma=true;
	
	else{
		UsuarioEncontrado=false;
		contador=1;
		char contrasenia[6];
		bool verificacionCompletada=false;
		cout<<"              Ingrese su contraseña: "<<endl;
		cout<<"                      ";Cambio_de_numero_a_caracter (contrasenia);
		Contra=stoi(contrasenia);
		cout<< endl;
		Buscar_en_binario_CONTRA(Contra,UsuarioEncontrado);
		verificacionCompletada=Verificacion_Cotrasenia(contrasenia,idUsuario);
		while((contador<3 and !verificacionCompletada ) || (!UsuarioEncontrado and contador<3)){
			cout<<"Error de contraseña "<<endl;
			cout<<"                      ";Cambio_de_numero_a_caracter (contrasenia);
			cout<< endl;
			Contra=stoi(contrasenia);
			Buscar_en_binario_CONTRA(Contra,UsuarioEncontrado);
			verificacionCompletada=Verificacion_Cotrasenia(contrasenia,idUsuario);
			if(!verificacionCompletada)
				contador++;
			else if(!UsuarioEncontrado)
				contador++;
		}
		
		if(contador==3 and !UsuarioEncontrado){
			cierreDelPrograma=true;
		}
	}
	cout<<"=================================================="<<endl;
	
	Sleep(5000);

	system("cls");
}
void Buscar_en_binario_ID (int id, bool &esta){
	ifstream archivo("Usuarios.bin", ios::in | ios::out | ios::binary);
	if (archivo.fail()) {
		cout << "Error al abrir el archivo para lectura y escritura." << endl;
		return;
	}
	user usuarioActual;
	while (archivo.read((char *)(&usuarioActual), sizeof(user)) and !esta) {
		if (usuarioActual.ID == id){
			esta =true ;
		}
	}
}
void Buscar_en_binario_CONTRA (int password, bool &esta){
	fstream archivo("Usuarios.bin", ios::in | ios::out | ios::binary);
	
	if (archivo.fail()) {
		cout << "Error al abrir el archivo para lectura y escritura." << endl;
		return;
	}
	user usuarioActual;
	while (archivo.read((char *)(&usuarioActual), sizeof(user)) and !esta) {
		if (usuarioActual.contra == password) {
			cout << "Bienvenido/a   " << usuarioActual.nombre << "!!"<< endl;
			cout << "Ultimo acceso: "<< endl;
			cout<< "Fecha: " << usuarioActual.fecha << " Hora: " << usuarioActual.hora << std::endl;
			
			// Llamamos a la función para cambiar fecha y hora
			cambiarFechaHoraActual(usuarioActual);
			
			// Mueve el puntero de escritura (seekp) hacia atrás desde la posición actual.
			// static_cast<streamoff>(sizeof(user)): Calcula el tamaño de la estructura user
			// y lo convierte a un tipo streamoff, que es un tipo específico de entero utilizado
			// para representar desplazamientos en flujos de entrada/salida.
			// ios::cur: Indica que el desplazamiento se realiza desde la posición actual del puntero.
			
			archivo.seekp(-static_cast<streamoff>(sizeof(user)), ios::cur);
			
			// Escribe la estructura modificada en el archivo
			archivo.write((char *)(&usuarioActual), sizeof(user));
			
		    esta= true;
		}
	}
	archivo.close();
}
void cambiarFechaHoraActual(user& usuario) {
	time_t tiempoActual = time(nullptr);
	tm* tiempoLocal = localtime(&tiempoActual);
	
	// Formatear la fecha y hora
	strftime(usuario.fecha, sizeof(usuario.fecha), "%d/%m/%Y", tiempoLocal);
	strftime(usuario.hora, sizeof(usuario.hora), "%H:%M", tiempoLocal);
}

/*
Estas funciones quedan comentadas ya que solo hace falta cargar el
archivo una sola vez pq si lo cargo cada vez que se ejecuta el programa 
nunca se me van a actualizar los datos de ultimo acceso. si desea cargar
el archivo saque el cometario en las funciones y el las llamadas en 
Pantalla_De_Login*/
/*
void CaragarTXT (user u[],int TL){		
	// Abre un archivo para lectura
	ifstream archivo("usuarios.txt");
	//Verifica si ocurrió algún error durante la lectura
	if (archivo.fail()) {
		cout << "Error al leer del archivo." << endl;
	} else {
		// almacena los datos del archivo en el vector u[]
		int contador = 0;
		while (contador < TL &&
			archivo >> u[contador].nombre >> u[contador].apellido >> u[contador].sexo
			>> u[contador].ID >> u[contador].contra >> u[contador].rol
			>> u[contador].fecha >> u[contador].hora) {
			++contador;
		}
	}
	// Cierra el archivo
	archivo.close();
}
void CargarBIN (user u[],int TL){
	ofstream archivo;
	archivo.open("Usuarios.bin", ios::out);
	if(archivo.fail()){
	    cout<< "Error al abrir el archivo "<<endl;
	}
	else{
		for(int i=0;i<TL;i++){
			archivo.write((char *)&u[i],sizeof(user));
		}
	}
	archivo.close();
}*/

void Menu_De_Abecedarios(bool &back){
	cout<<"=================================================="<<endl;
	cout<<"            Presione 1 para Espaniol"<<endl;
	cout<<"            Presione 2 para Ingles"<<endl;
	cout<<"            Presione 3 para Italiano"<<endl;
	cout<<"            Presione 4 para Portugues"<<endl;
	cout<<"            Presione 5 para Frances"<<endl;
	cout<<"Presione X para Volver al menu principal"<<endl;
	cout<<"=================================================="<<endl;
	
	char c;
	while(!back){
		
		cin>>c;
		system("cls");
	    cin.ignore();
	    switch(c){
		case '1':{
			int cantletras=0;
			
			cout<<"Letras minusculas: ";
			for (char i='a';i<='z';i++){
				if(cantletras%10==0){
					cout<<endl;
				}
				if(i=='o'){
					cout<< "ñ o ";
					cantletras+=2;
				}
				else{
				    cantletras++;
				    cout<<i<<" ";
				}
			}
			cout<<endl;
			cantletras=0;
			cout<<endl;
			cout<<"Letras mayusculas: ";
			for (char i='A';i<='Z';i++){
				if(cantletras%10==0){
					cout<<endl;
				}
				if(i=='O'){
					cout<< "Ñ O ";
					cantletras+=2;
				}
				else{
					cantletras++;
					cout<<i<<" ";
				}
				
			}
			cout<<endl<<endl;
			cout<<"Letras acentuadas: "<<endl;
			cout<<"á é í ó ú ü"<<endl;
			cout<< endl;
			cout<<"Presione x para volver atras o X si quiere volver al menu principal: ";
			break;
		}
		case '2':{
			int cantletras=0;
			
			cout<<"Letras minusculas: ";
			for (char i='a';i<='z';i++){
				if(cantletras%10==0){
					cout<<endl;
				}
				cantletras++;
				cout<<i<<" ";
			}
			cout<<endl;
			cantletras=0;
			cout<<endl;
			cout<<"Letras mayusculas: ";
			for (char i='A';i<='Z';i++){
				if(cantletras%10==0){
					cout<<endl;
				}
				cantletras++;
				cout<<i<<" ";
			}
			cout<< endl;
			cout<<"Presione x para volver atras o X si quiere volver al menu principal: ";
			break;
		}
		case '3':{
			int cantletras=0;
			cout<<endl;
			cout<<"Letras minusculas: "<<endl;
			for (char i='a';i<='z';i++){
				if(i!='j' && i!='k' && i!='w' && i!='x' && i!='y'){
					if(cantletras%10==0){
						cout<<endl;
					}
					cout<<i<<" ";
					cantletras++;
				}
			}
			cout<<endl;
			cantletras=0;
			cout<<"Letras mayusculas: "<<endl;
			for (char i='A';i<='Z';i++){
				if(i!='J' && i!='K' && i!='W' && i!='X' && i!='Y'){
					if(cantletras%10==0){
						cout<<endl;
					}
					cout<<i<<" ";
					cantletras++;
				}
			}
			cout<<endl<<endl;
			cout<< "Letras acentuadas: "<<endl;
			cout<<"é"<<endl;
			cout<<"à è ì ò ù"<<endl;
			cout<< endl;
			cout<<"Presione x para volver atras o X si quiere volver al menu principal: ";
			break;
		}
		case '4':{
			int cantletras=0;
			cout<<"Letras minusculas: ";
			for (char i='a';i<='z';i++){
				if(cantletras%10==0){
					cout<<endl;
				}
				cantletras++;
				cout<<i<<" ";
			}
			cout<<endl;
			cantletras=0;
			cout<<endl;
			cout<<"Letras mayusculas: ";
			for (char i='A';i<='Z';i++){
				if(cantletras%10==0){
					cout<<endl;
				}
				cantletras++;
				cout<<i<<" ";
			}
			cout<< endl<<endl;
		    cout<< "Letras Acentuadas: "<<endl;
			cout<<"á à é í ó ú"<<endl;
			//cout<<"ã õ ç"<<endl;
			cout<<"â ê ô"<<endl;
			cout<< endl;
			cout<<"Presione x para volver atras o X si quiere volver al menu principal: ";
			break;
		}
		case '5':{
			int cantletras=0;
			cout<<"Letras minusculas: ";
			for (char i='a';i<='z';i++){
				if(cantletras%10==0){
					cout<<endl;
				}
				cantletras++;
				cout<<i<<" ";
			}
			cout<<endl;
			cantletras=0;
			cout<<endl;
			cout<<"Letras mayusculas: ";
			for (char i='A';i<='Z';i++){
				if(cantletras%10==0){
					cout<<endl;
				}
				cantletras++;
				cout<<i<<" ";
			}
			cout<< endl<<endl;
			cout<< "Letras Acentuadas: "<<endl;
			cout<<"é"<<endl;
			cout<<"à è ù"<<endl;
			cout<<"â ê î ô û"<<endl;
			cout<<"ë ï ü ÿ"<<endl;
			cout<< endl;
			cout<<"Presione x para volver atras o X si quiere volver al menu principal: ";
			break;
		}
		case 'X':{
			back=true;
			break;
		}
		case 'x':{
			cout<<"=================================================="<<endl;
			cout<<"            Presione 1 para Español"<<endl;
			cout<<"            Presione 2 para Ingles"<<endl;
			cout<<"            Presione 3 para Italiano"<<endl;
			cout<<"            Presione 4 para Portugues"<<endl;
			cout<<"            Presione 5 para Frances"<<endl;
			cout<<"=================================================="<<endl;
			cout<<"Presione X para Volver al menu principal "<<endl;
			break;
		}
		default:{
			cout<< "Opcion no valida, ingrese nuevamente: "<<endl;
			break;
		}
	    }
	}
}
bool Letras_repetidas (string Letras_jugadas,char guess){
	bool encontrada=false;
	for(int i=0;i<(int)Letras_jugadas.length();i++){
		if(Letras_jugadas[i]==guess)
			encontrada=true;
	}
	return encontrada;
}
void Ahorcado(bool &back,string vector_palabras[]){
	int i=0, puntos=100;
	srand(time(NULL));
	string palabra_secreta=vector_palabras[rand()%100];
	char Letras_jugadas[100]={" "};
	char intento[100], guess;
	int tamPalabra = palabra_secreta.size();
	int intentos_restantes = 6;
	bool correcto, gano = false;
	
	for (int i=0;i<tamPalabra;i++) {
		intento[i] = '_';
	}
	intento[tamPalabra] ='\0';
	
	while (intentos_restantes>0 and !gano) {
		switch(intentos_restantes){// dependiendo de la cantidad de intentos restantes se muestra una parte u otra del monigote
		case 5:{// cabeza
			cout << "   ______" << endl;
			cout << "   |    |" << endl;
			cout << "   |    O" << endl;
			cout << "   |   " << endl;
			cout << "   |    " << endl;
			cout << "   |   " << endl;
			cout << "  _|_" << endl;
		}break;
		case 4:{// torzo
			cout << "   ______" << endl;
			cout << "   |    |" << endl;
			cout << "   |    O" << endl;
			cout << "   |    |" << endl;
			cout << "   |    |" << endl;
			cout << "   |   " << endl;
			cout << "  _|_" << endl;
		}break;
		case 3:{// mano 1
			cout << "   ______" << endl;
			cout << "   |    |" << endl;
			cout << "   |    O" << endl;
			cout << "   |   /|" << endl;
			cout << "   |    |" << endl;
			cout << "   |   " << endl;
			cout << "  _|_" << endl;
		}break;
		case 2:{// mano 2
			cout << "   ______" << endl;
			cout << "   |    |" << endl;
			cout << "   |    O" << endl;
			cout << "   |   /|\\" << endl;
			cout << "   |    |" << endl;
			cout << "   |   " << endl;
			cout << "  _|_" << endl;
		}break;
		case 1:{// pierna 1
			cout << "   ______" << endl;
			cout << "   |    |" << endl;
			cout << "   |    O" << endl;
			cout << "   |   /|\\" << endl;
			cout << "   |    |" << endl;
			cout << "   |   / " << endl;
			cout << "  _|_" << endl;
		}break;
		}
		cout<<"Palabra: ";
		for(int i=0;i<tamPalabra;i++){
			cout<<intento[i]<<" ";
		}
		cout<<endl<<"Intentos restantes: "<<intentos_restantes<<endl;
		cout<<"Ingresa una letra: ";
		cin>>guess;
		guess = tolower(guess);
		cin.ignore();
		if(Letras_repetidas(Letras_jugadas,guess)){
			cout<<"Usted ya uso esta letra"<<endl;
			Sleep(1000);
			system("cls");
		}
		else{
			Letras_jugadas[i]=guess;
			i++;
			
			correcto = false;
			for (int i=0;i<tamPalabra;i++) {
				if (palabra_secreta[i]==guess) {
					intento[i] = guess;
					correcto = true;
				}
			}
			if (!correcto){
				intentos_restantes--;
				cout <<"Incorrecto, Pierdes un intento"<<endl;
				Sleep(1000);
				puntos-=10;
			}
			system("cls");
		}
		if(palabra_secreta==intento)
			gano=true;
	}

	cout<<"Usted termina la partida con "<<puntos<<" puntos"<<endl;
	if(gano){
		cout<<"¡Ganaste! La palabra era: " <<palabra_secreta<<endl;
	}
	else{
	   //aca va dibulo de monigote entero
		cout << "   ______" << endl;
		cout << "   |    |" << endl;
		cout << "   |    O" << endl;
		cout << "   |   /|\\" << endl;
		cout << "   |    |" << endl;
		cout << "   |   / \\" << endl;
		cout << "  _|_" << endl;
	   cout<<"¡Perdiste! La palabra era: "<<palabra_secreta<<endl;
	}
}
void Palabra_Cifrada(bool &back,string vector_palabras[]){
	string palabra,palabra_secreta;
	srand(time(0));
	palabra=vector_palabras[rand()%100];
	palabra_secreta=palabra;
	
	for(int i=0;i<(int)palabra.length();i++){
		if(palabra[i] + 13 < 123)
			palabra[i]+=13;
		else 
			palabra[i]-=13;
	}
	cout<<"La palabra a decifrar es: "<<palabra<<endl;
	
	char intento[100], guess;
	int i=0;
	int tamPalabra = palabra_secreta.size();
	int intentos_restantes = tamPalabra*(2);
	bool correcto = false, gano = false;
	
	for (int i=0;i<tamPalabra;i++) {
		intento[i] = '_';
	}
	intento[tamPalabra] ='\0';
	
	while (intentos_restantes>0 and !gano) {
		cout<<"Palabra: "<<endl;
		for(int i=0;i<tamPalabra;i++){
			cout<<palabra[i]<<" ";
		}
		cout<<endl;
		for(int i=0;i<tamPalabra;i++){
			cout<<intento[i]<<" ";
		}
		cout<<endl<<"Intentos restantes: "<<intentos_restantes<<endl;
		cout<<"Ingresa una letra: ";
		
		cin>>guess;
		cin.ignore();
		guess = tolower(guess);
		
		correcto = false;
		if (palabra_secreta[i]==guess) {
			intento[i] = guess;
			correcto = true;
			i++;
		}
		
		if (!correcto){
			intentos_restantes--;
			cout <<"Incorrecto, Pierdes un intento"<<endl;
		}
		else
			cout <<"Correcto"<<endl;
		
		if(palabra_secreta==intento)
			gano=true;
	}
	if(gano){
		cout<<"¡Ganaste! La palabra era: " <<palabra_secreta<<endl;
	}
	else 
	   cout<<"¡Perdiste! La palabra era: "<<palabra_secreta<<endl;
}
void Numeros_En_Otro_Idioma(bool &back){
	cout<<"Elija un numero del 0 al 9..."<<endl;
	char num;
	cin>>num;
	cin.ignore();
	while(num>'9' or num<'0'){
		cout<<"Numero invalido, ingresar nuevamente...";
		cin>>num;
		cin.ignore();
	}
	cout<<"Ingrese el parametro de aumento para el grafico"<<endl;
	char parametro;
	cin>>parametro;
	cin.ignore();
	while(parametro>'4' or parametro<'1'){
		cout<<"Parametro fuera de rango, ingresar nuevamente...";
		cin>>parametro;
		cin.ignore();
	}
	string idioma;
	cout<<"Ingrese el idioma en el que quiere el numero..."<<endl;
	getline(cin,idioma);
	while(idioma!="espaniol" and idioma!="ingles" and idioma!="italiano" and idioma!="portugues" and idioma!="frances"){
		cout<<"idioma no valido, ingresar nuevamente...";
		getline(cin,idioma);
	}
	cout<<"Forma escrita en "<<idioma<<": ";
	if(idioma=="espaniol"){//lo escribimos asi porque la letra ñ no esta en la tabla ASCII
		switch(num){
		case '1':{cout<<"uno"<<endl;break;}
		case '2':{cout<<"dos"<<endl;break;}
		case '3':{cout<<"tres"<<endl;break;}
		case '4':{cout<<"cuatro"<<endl;break;}
		case '5':{cout<<"cinco"<<endl;break;}
		case '6':{cout<<"seis"<<endl;break;}
		case '7':{cout<<"siete"<<endl;break;}
		case '8':{cout<<"ocho"<<endl;break;}
		case '9':{cout<<"nueve"<<endl;break;}
		}
	}
	else if(idioma=="ingles"){
		switch(num){
		case '1':{cout<<"one"<<endl;break;}
		case '2':{cout<<"two"<<endl;break;}
		case '3':{cout<<"three"<<endl;break;}
		case '4':{cout<<"four"<<endl;break;}
		case '5':{cout<<"five"<<endl;break;}
		case '6':{cout<<"six"<<endl;break;}
		case '7':{cout<<"seven"<<endl;break;}
		case '8':{cout<<"eight"<<endl;break;}
		case '9':{cout<<"nine"<<endl;break;}
		}
	}
	else if(idioma=="portugues"){
		switch(num){
		case '1':{cout<<"um"<<endl;break;}
		case '2':{cout<<"dois"<<endl;break;}
		case '3':{cout<<"três"<<endl;break;}
		case '4':{cout<<"quatro"<<endl;break;}
		case '5':{cout<<"cinco"<<endl;break;}
		case '6':{cout<<"seis"<<endl;break;}
		case '7':{cout<<"sete"<<endl;break;}
		case '8':{cout<<"oito"<<endl;break;}
		case '9':{cout<<"nove"<<endl;break;}
		}
	}
	else if(idioma=="frances"){
		switch(num){
		case '1':{cout<<"un"<<endl;break;}
		case '2':{cout<<"deux"<<endl;break;}
		case '3':{cout<<"trois"<<endl;break;}
		case '4':{cout<<"quatre"<<endl;break;}
		case '5':{cout<<"cinq"<<endl;break;}
		case '6':{cout<<"six"<<endl;break;}
		case '7':{cout<<"sept"<<endl;break;}
		case '8':{cout<<"huit"<<endl;break;}
		case '9':{cout<<"neuf"<<endl;break;}
		}
	}
	else if(idioma=="italiano"){
		switch(num){
		case '1':{cout<<"uno"<<endl;break;}
		case '2':{cout<<"due"<<endl;break;}
		case '3':{cout<<"tre"<<endl;break;}
		case '4':{cout<<"quattro"<<endl;break;}
		case '5':{cout<<"cinque"<<endl;break;}
		case '6':{cout<<"sei"<<endl;break;}
		case '7':{cout<<"sette"<<endl;break;}
		case '8':{cout<<"otto"<<endl;break;}
		case '9':{cout<<"nove"<<endl;break;}
		}
	}
	cout<<"Grafico con un parametro de "<<parametro<<": "<<endl;
	switch(num){
	case '1':{
		switch(parametro){
		case '1':{
			cout<<"/|"<<endl;
			cout<<" |"<<endl;
			cout<<" |"<<endl;
			break;}
		case '2':{
				cout<<" /|"<<endl;
				cout<<"/ |"<<endl;
				cout<<"  |"<<endl;
				cout<<"  |"<<endl;
				break;}
		case '3':{
					cout<<"  /|"<<endl;
					cout<<" / |"<<endl;
					cout<<"/  |"<<endl;
					cout<<"   |"<<endl;
					cout<<"   |"<<endl;
					cout<<"   |"<<endl;
					break;}
		case '4':{
						cout<<"   /|"<<endl;
						cout<<"  / |"<<endl;
						cout<<" /  |"<<endl;
						cout<<"/   |"<<endl;
						cout<<"    |"<<endl;
						cout<<"    |"<<endl;
						cout<<"    |"<<endl;
						cout<<"    |"<<endl;
						break;}
		}
		break;};
	case '2':{
		switch(parametro){
		case '1':{
			cout<<" __"<<endl;
			cout<<" __|"<<endl;
			cout<<"|__"<<endl;
			break;}
		case '2':{
				cout<<" __"<<endl;
				cout<<"   |"<<endl;
				cout<<" __|"<<endl;
				cout<<"|"<<endl;
				cout<<"|__"<<endl;
				break;}
		case '3':{
					cout<<"  ___"<<endl;
					cout<<"     |"<<endl;
					cout<<"     |"<<endl;
					cout<<"  ___|"<<endl;
					cout<<" |"<<endl;
					cout<<" |"<<endl;
					cout<<" |___"<<endl;	
					break;}
		case '4':{
						cout<<"  ____"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						cout<<"  ____|"<<endl;
						cout<<" |"<<endl;
						cout<<" |"<<endl;
						cout<<" |"<<endl;
						cout<<" |____"<<endl;	
						break;}
		}
		break;};
	case '3':{
		switch(parametro){
		case '1':{
			cout<<" __"<<endl;
			cout<<" __|"<<endl;
			cout<<" __|"<<endl;
			break;}
		case '2':{
				cout<<"___"<<endl;
				cout<<"   |"<<endl;
				cout<<"___|"<<endl;
				cout<<"   |"<<endl;
				cout<<"___|"<<endl;
				break;}
		case '3':{
					cout<<"____"<<endl;
					cout<<"    |"<<endl;
					cout<<"    |"<<endl;
					cout<<"____|"<<endl;
					cout<<"    |"<<endl;
					cout<<"    |"<<endl;
					cout<<"____|"<<endl;	
					break;}
		case '4':{
						cout<<"_____"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"_____|"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"_____|"<<endl;	
						break;
					}
		}
		break;};
	case '4':{
		switch(parametro){
		case '1':{
			cout<<"|__|"<<endl;
			cout<<"   |"<<endl;
			break;}
		case '2':{
				cout<<"|   |"<<endl;
				cout<<"|___|"<<endl;
				cout<<"    |"<<endl;
				cout<<"    |"<<endl;
				break;}
		case '3':{
					cout<<"|    |"<<endl;
					cout<<"|    |"<<endl;
					cout<<"|____|"<<endl;
					cout<<"     |"<<endl;
					cout<<"     |"<<endl;
					cout<<"     |"<<endl;
					break;}
		case '4':{
						cout<<"|     |"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|_____|"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						break;}
		}
		break;};
	case '5':{
		switch(parametro){
		case '1':{
			cout<<" __"<<endl;
			cout<<"|__"<<endl;
			cout<<" __|"<<endl;
			break;}
		case '2':{
				cout<<" ___"<<endl;
				cout<<"|"<<endl;
				cout<<"|___"<<endl;
				cout<<"    |"<<endl;
				cout<<" ___|"<<endl;
				break;}
		case '3':{
					cout<<" ____"<<endl;
					cout<<"|"<<endl;
					cout<<"|"<<endl;
					cout<<"|____"<<endl;
					cout<<"     |"<<endl;
					cout<<"     |"<<endl;
					cout<<" ____|"<<endl;
					break;}
		case '4':{
						cout<<" _____"<<endl;
						cout<<"|"<<endl;
						cout<<"|"<<endl;
						cout<<"|"<<endl;
						cout<<"|_____"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						cout<<" _____|"<<endl;
						break;}
		}
		break;}
	case '6':{
			switch(parametro){
			case '1':{
				cout<<" __"<<endl;
				cout<<"|__"<<endl;
				cout<<"|__|"<<endl;
				break;}
			case '2':{
					cout<<" ___"<<endl;
					cout<<"|"<<endl;
					cout<<"|___"<<endl;
					cout<<"|   |"<<endl;
					cout<<"|___|"<<endl;
					break;}
			case '3':{
						cout<<" ____"<<endl;
						cout<<"|"<<endl;
						cout<<"|"<<endl;
						cout<<"|____"<<endl;
						cout<<"|    |"<<endl;
						cout<<"|    |"<<endl;
						cout<<"|____|"<<endl;
						break;}
			case '4':{
							cout<<" _____"<<endl;
							cout<<"|"<<endl;
							cout<<"|"<<endl;
							cout<<"|"<<endl;
							cout<<"|_____"<<endl;
							cout<<"|     |"<<endl;
							cout<<"|     |"<<endl;
							cout<<"|     |"<<endl;
							cout<<"|_____|"<<endl;
							break;}
			}
			break;};
	case '7':{
		switch(parametro){
		case '1':{
			cout<<" __"<<endl;
			cout<<"   |"<<endl;
			cout<<"   |"<<endl;
			break;}
		case '2':{
				cout<<"___"<<endl;
				cout<<"   |"<<endl;
				cout<<"   |"<<endl;
				cout<<"   |"<<endl;
				cout<<"   |"<<endl;
				break;}
		case '3':{
					cout<<"____"<<endl;
					cout<<"    |"<<endl;
					cout<<"    |"<<endl;
					cout<<"    |"<<endl;
					cout<<"    |"<<endl;
					cout<<"    |"<<endl;
					cout<<"    |"<<endl;
					break;}
		case '4':{
						cout<<"_____"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						cout<<"     |"<<endl;
						break;}
		}
		break;};
	case '8':{
		switch(parametro){
		case '1':{
			cout<<" __"<<endl;
			cout<<"|__|"<<endl;
			cout<<"|__|"<<endl;
			break;}
		case '2':{
				cout<<" ___"<<endl;
				cout<<"|   |"<<endl;
				cout<<"|___|"<<endl;
				cout<<"|   |"<<endl;
				cout<<"|___|"<<endl;
				break;}
		case '3':{
					cout<<" ____"<<endl;
					cout<<"|    |"<<endl;
					cout<<"|    |"<<endl;
					cout<<"|____|"<<endl;
					cout<<"|    |"<<endl;
					cout<<"|    |"<<endl;
					cout<<"|____|"<<endl;
					break;}
		case '4':{
						cout<<" _____"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|_____|"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|_____|"<<endl;
						break;}
		}
		break;};
	case '9':{
		switch(parametro){
		case '1':{
			cout<<" __"<<endl;
			cout<<"|__|"<<endl;
			cout<<" __|"<<endl;
			break;}
		case '2':{
				cout<<" ___"<<endl;
				cout<<"|   |"<<endl;
				cout<<"|___|"<<endl;
				cout<<"    |"<<endl;
				cout<<" ___|"<<endl;
				break;}
		case '3':{
					cout<<" ____"<<endl;
					cout<<"|    |"<<endl;
					cout<<"|    |"<<endl;
					cout<<"|____|"<<endl;
					cout<<"     |"<<endl;
					cout<<"     |"<<endl;
					cout<<" ____|"<<endl;
					break;}
		case '4':{
						cout<<" _____"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|     |"<<endl;
						cout<<"|_____|"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						cout<<"      |"<<endl;
						cout<<" _____|"<<endl;	
						break;}
		}
		break;};
	}
}
void Memoria(bool &back,string vector_palabras[]){
	string palabra, vector[5];
	int repletras[26]={0},vocalestotales[5]={0},longitudespalabras[5]={0};
	srand(time(NULL));
	
	for(int i=0;i<5;i++){
		palabra=vector_palabras[rand()%101];
		cout<<palabra<<endl;
		Repeticiones_de_letras(palabra,repletras);
		Vocales_totales(palabra,vocalestotales);
		
		vector[i]=palabra;
		longitudespalabras[i]=palabra.length();
	}
	Sleep(2000);
	system("cls");
	//ENTRADA DE RESPUESTAS HECHAS POR EL USUARIO
	int rta_total_vocales;
	char rta_letra_mas_se_repite;
	string rta_palabra_mayor_longitud;
	
	cout<<"Ingresar la letra que mas se repite: "<<endl;
	cin>>rta_letra_mas_se_repite;
	rta_letra_mas_se_repite = tolower(rta_letra_mas_se_repite);
	cin.ignore();
	while(!isalpha(rta_letra_mas_se_repite)){
		cout<<"Entrada invalida, ingrese nuevamente: "<<endl;
		cin>>rta_letra_mas_se_repite;
		rta_letra_mas_se_repite = tolower(rta_letra_mas_se_repite);
		cin.ignore();
	}
	cout<<"Ingresar la cantidad de vocales que aparecen: "<<endl;
	cin>>rta_total_vocales;
	cin.ignore();
	while(rta_total_vocales<-1){
		cout<<"Entrada invalida, ingrese nuevamente: "<<endl;
		cin>>rta_total_vocales;
		cin.ignore();
	}
	
	cout<<"Ingresar la palabra de mayor longitud: "<<endl;
	getline(cin,rta_palabra_mayor_longitud);
	
	//COMPARACION DE SUS RESPUESTAS Y LAS CORRECTAS 
	cout<<endl<<"La letra que mas se repite es: ";
	int mayor=repletras[0];
	int letramasrep=0;
	for(int i=1;i<26;i++){
		if(repletras[i]>mayor){
			mayor=repletras[i];
			letramasrep=i;
		}
	}
	//RESPUESTA CORRECTA ITEM 1 
	cout<<(char)(letramasrep+97)<<" apareciendo "<<mayor<<" veces"<<endl;
	//PUNTOS ITEM 1
	cout<<"La letra que igreso se repite: ";
	int cant_rep_rta=repletras[rta_letra_mas_se_repite-97];
	cout<<cant_rep_rta<<endl;
	float puntos_item_1=(cant_rep_rta*10.0)/mayor;
	cout<<"Puntos obtenidos en el item 1: "<<fixed<<setprecision(2)<<puntos_item_1<<endl;
	
	//RESPUESTA CORRECTA ITEM 2
	cout<<"El total de vocales que aparecen es: ";
	int cantidad_Vocales=0;
	for(int i=0;i<5;i++){
		if(vocalestotales[i]>0){
			cantidad_Vocales+=vocalestotales[i];
		}
	}
	cout<<cantidad_Vocales<<endl;
	//PUNTOS ITEM 2
	float puntos_item_2;
	if(cantidad_Vocales>=rta_total_vocales)
		puntos_item_2=(rta_total_vocales*10.0)/cantidad_Vocales;
	else 
		puntos_item_2=Puntuacion(cantidad_Vocales,rta_total_vocales);		
	cout<<"Puntos obtenidos en el item 2: "<<fixed<<setprecision(2)<<puntos_item_2<<endl;
	
	//RESPUESTA CORRECTA ITEM 3
	cout<<"La palabra de mayor longitud es: ";
	int mayorlongitud=longitudespalabras[0];
	string palabrademayorlong;
	for(int i=1;i<5;i++){
		if(longitudespalabras[i]>mayorlongitud){
			palabrademayorlong=vector[i];
			mayorlongitud=longitudespalabras[i];
		}
	}
	cout<<palabrademayorlong<<" "<<mayorlongitud<<endl;
	//PUNTOS ITEM 3
	cout<<"la palabra que usted ingreso tiene una longitud de : "<<rta_palabra_mayor_longitud.length()<<endl;
	
	float puntos_item_3=(rta_palabra_mayor_longitud.length()*10.0)/mayorlongitud;	
	cout<<"puntos obtenidos en el item 3: "<<fixed<<setprecision(2)<<puntos_item_3<<endl;
	
	cout<<"el puntaje final es: "<<fixed<<setprecision(2)<<(puntos_item_1+puntos_item_2+puntos_item_3)/3.0<< endl;
}
float Puntuacion(int rta_esperada,int rta_ingresada){
	float error_relativo=(rta_ingresada-rta_esperada)/(float)rta_esperada;
	float puntuacion=10.0*(1.0-(error_relativo/2.0));
	return puntuacion;
}
void Repeticiones_de_letras(string palabra,int repletras[]){
	for(int i=0;i<(int)palabra.length();i++){
		palabra[i]=repletras[palabra[i]-97]++;
	}
}
	
void Vocales_totales(string palabra,int vocalestotales[]){
	for(int i=0;i<(int)palabra.length();i++){
		switch(palabra[i]){
		case 'a':{vocalestotales[0]++;break;}
		case 'e':{vocalestotales[1]++;break;}
		case 'i':{vocalestotales[2]++;break;}
		case 'o':{vocalestotales[3]++;break;}
		case 'u':{vocalestotales[4]++;break;}
		}
	}
}
void Menu_De_Juegos(bool &back,string vector_palabras[]){
	cout<<"=================================================="<<endl;
	cout<<"        Presione 1 para Ahorcado"<<endl;
	cout<<"        Presione 2 para Palabra cifrada"<<endl;
	cout<<"        Presione 3 para Numeros en otro idioma"<<endl;
	cout<<"        Presione 4 para Memoria"<<endl;
	cout<<"Presione X para volver al menu principal"<<endl;
	cout<<"=================================================="<<endl;
	
	char c;
	while(!back){
	    cin>>c;
		system("cls");
	    cin.ignore();
	    switch(c){
	    case '1':{
			cout<< "Estas jugando al ahorcado, BUENA SUERTE!! "<< endl;
			Ahorcado(back, vector_palabras);
			cout<<"Presione X para volver al menu principal o x si quiere volver al menu de juegos: ";
			cout<< endl;
		    break;
		}
		case '2':{
		    cout<< "Estas jugando al palabra cifrada, BUENA SUERTE!! "<< endl;
			Palabra_Cifrada(back,vector_palabras);
			cout<<"Presione X para volver al menu principal o x si quiere volver al menu de juegos: ";
			cout<< endl;
		    break;
		}
		case '3':{
			cout<< "Estas jugando al numeros en otro idioma, BUENA SUERTE!! "<< endl;
			Numeros_En_Otro_Idioma(back);
			cout<<"Presione X para volver al menu principal o x si quiere volver al menu de juegos: ";
			cout<< endl;
		    break;
		}
		case '4':{
			cout<< "Estas jugando al memoria, BUENA SUERTE!! "<< endl;
			Memoria(back, vector_palabras);
			cout<<"Presione X para volver al menu principal o x si quiere volver al menu de juegos: ";
			cout<< endl;
		    break;
		}
		case 'X':{
		    back=true;
			break;
		}
		case 'x':{
				cout<<"=================================================="<<endl;
				cout<<"        Presione 1 para Ahorcado"<<endl;
				cout<<"        Presione 2 para Palabra cifrada"<<endl;
				cout<<"        Presione 3 para Numeros en otro idioma"<<endl;
				cout<<"        Presione 4 para Memoria"<<endl;
				cout<<"=================================================="<<endl;
				cout<<"Presione X para volver al menu principal"<<endl;
		}
		default:{
			cout<< "Opcion no valida, ingrese nuevamente: "<<endl;
			cout<<"=================================================="<<endl;
			cout<<"        Presione 1 para Ahorcado"<<endl;
			cout<<"        Presione 2 para Palabra cifrada"<<endl;
			cout<<"        Presione 3 para Numeros en otro idioma"<<endl;
			cout<<"        Presione 4 para Memoria"<<endl;
			cout<<"=================================================="<<endl;
			cout<<"Presione X para volver al menu principal"<<endl;
			break;
		}
	    }
	}
}
void Menu_Principal(bool &cierreDelPrograma,string vector_palabras[]){
	char c;
	while(!cierreDelPrograma){
		cout<<"=================================================="<<endl;
		cout<<"      Presione 1 para el menu de abecedarios"<<endl;
		cout<<"      Presione 2 para el menu de juegos"<<endl;
		cout<<"      Presione 3 para el procesador de texto"<<endl;
		cout<<"      Presione X para salir de la aplicacion"<<endl;
		cout<<"=================================================="<<endl<<endl;
		cout<<"                  INTEGRANTES"<<endl<<endl;
		cout<<"           lucabortolottog@gmail.com"<<endl<<endl;
		cout<<"            matumaidana26@gmail.com"<<endl<<endl;
		cout<<"=================================================="<<endl;
		cout<<"Ingrese una opcion: ";cin>>c;
		
		system("cls");
		cin.ignore();
	    bool back=false;
	    switch(c){
		case '1':{
			Menu_De_Abecedarios(back); 
			break;
		}
		case '2':{
			Menu_De_Juegos(back,vector_palabras); 
			break;
		}
		case '3':{
			Procesador_de_texto(back);
			break;
		}
		case 'X':{
			cierreDelPrograma=true; 
			break;
		}
		default:{
				cout<< "Opcion no valida, ingrese nuevamente: "<<endl;
				cout<<"=================================================="<<endl;
				cout<<"      Presione 1 para el menu de abecedarios"<<endl;
				cout<<"      Presione 2 para el menu de juegos"<<endl;
				cout<<"      Presione 3 para el procesador de texto"<<endl;
				cout<<"      Presione X para salir de la aplicacion"<<endl;
				cout<<"=================================================="<<endl<<endl;
				break;
			}
		}
	}
}
void Procesador_de_texto(bool &back){
	cout<<"=================================================="<<endl;
	cout<<"  Presione 1 para Estadisticas a nivel caracteres"<<endl;
	cout<<"  Presione 2 para Estadisticas a nivel palabras"<<endl;
	cout<<"  Presione X para volver al menu principal"<<endl;
	cout<<"=================================================="<<endl;
	
	char c;
	cout<<"Ingrese una opcion: ";
	libro l;
	l.nombre="Divina commedia.txt";
	llenarLibro(l);
	
	while(!back){
		cin>>c;
		system("cls");
		cin.ignore();
		system("mode con: cols=50 lines=25");
		switch(c){
		case '1':{
			cout<<"Estas en Estadisticas a nivel caracteres"<<endl;
			
		    llenarArchivoFrecuencias(l);
			mostrarContenido(l);
			cout<<"Presione X para volver al menu principal o x si quiere volver atras: ";
			break;
		}
		case '2':{
			
			cout<<"Estas en Estadisticas a nivel palabras"<<endl;
			longitudPromedio(l);
			cout<< "Ingrese la letra inicial de las palabras"<<endl;
			cout<< "que desea ver: ";
			char x;
			cin>> x;
			cin.ignore();
			x=tolower(x);
			frecuenciaDeLetraInicial(l,x);
			cout<< endl;
			porcentajeDeInicio(l);
			cout<< endl;
			llenarListaEnlazada(l);
			cout<<"Presione X para volver al menu principal o x si "<<endl
				<< "quiere volver atras: ";
			break;
		}
		case 'X':{
			back=true; 
			break;
		}
		case 'x':{
			cout<<"=================================================="<<endl;
			cout<<"  Presione 1 para Estadisticas a nivel caracteres"<<endl;
			cout<<"  Presione 2 para Estadisticas a nivel palabras"<<endl;
			cout<<"  Presione X para volver al menu principal"<<endl;
			cout<<"=================================================="<<endl;
			break;
		}
		default:{
			cout<< "Opcion no valida, ingrese nuevamente: "<<endl;
			cout<<"=================================================="<<endl;
			cout<<"  Presione 1 para Estadisticas a nivel caracteres"<<endl;
			cout<<"  Presione 2 para Estadisticas a nivel palabras"<<endl;
			cout<<"  Presione X para volver al menu principal"<<endl;
			cout<<"=================================================="<<endl;
			break;
		}
		}
	}
}

