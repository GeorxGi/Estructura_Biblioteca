#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#include "Libro.h"
#include "Tesis.h"

constexpr unsigned short ARREMAX = 5;
constexpr auto ENDLINE = '\r';
constexpr auto fileName = "DataFile.txt";
//Segun documentacion, constexpr es una variable que se calcula en tiempo de compilacion y no ejecucion
//dando como resultado un mejor rendimiento, seguramente no afecte mucho, pero bueno, ahi esta

using namespace std;
//Se utilizara la convension de cpp (basado en: https://www.geeksforgeeks.org/naming-convention-in-c/)
//m_ = prefijo para variables privadas
//p_ = prefijo para variables protegidas

vector<Tesis> tesis;
vector <Libro> libros;

#pragma region ManejadoresConsola
//Retorna una estructura COORD en donde se almacena la coordenada XY actual del cursor de la consola
static COORD ObtenerPosicionCursor() {
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi)) {
		return cbsi.dwCursorPosition;
	}
	else{
		return COORD{0, 0};
	}
}
//Ir a la posicion XY de la consola
static void Gotoxy(short x, short y) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos = { x, y };
	SetConsoleCursorPosition(hcon, dwPos);
}

//Limpia la linea e imprime una cadena en la posicion XY de la consola
static void printf_xy(string cad, int x, int y) {
	Gotoxy(x, y); printf("\x1b[2K");
	Gotoxy(x, y); cout << cad;
}


//Ir a la posicion XY de la consola en relacion a la posicion actual
static void GotoxyRelative(short x, short y) {
	COORD extra = ObtenerPosicionCursor();
	Gotoxy(x + extra.X, y + extra.Y);
}

#pragma endregion

#pragma region Operadores

static void CargarDatosGenericos() {
	system("cls");
	if (tesis.size() == 0 && libros.size() == 0) {
		//Carga de libros genericos
		string autor[ARREMAX] = { "Marta Rodriguez", "Luis Fernandez", "Elena Garcia", "Ricardo Perez", "Julia Torres"};
		Libro lib = Libro("La aventura del saber", autor, "Ediciones Sabiduria", "978-123-456-7890", 2015);
		libros.push_back(lib);

		autor[0] = "Andres Silva"; autor[1] = "Carolina Herrera"; autor[2] = ""; autor[3] = ""; autor[4] = "";
		lib.ModificarDatos("Cocinando con amor", autor, "Cocina para Todos", "978-0-987-65432-1", 2018);
		libros.push_back(lib);

		autor[0] = "Andrea Ramirez"; autor[1] = "Gabriel Ortiz"; autor[2] = "Valeria mena"; autor[3] = ""; autor[4] = "";
		lib.ModificarDatos("Historias del mas alla", autor, "Editorial Misterio", "978-1-098-76543-2", 2021);
		libros.push_back(lib);

		//Carga de tesis genericas
		autor[0] = "Lorena Sanchez"; autor[1] = "Gustavo Diaz"; autor[2] = "Natalia Reyez"; autor[3] = "Enrique Gomez"; autor[4] = "Sofia Blanco";
		Tesis tes = Tesis("Desarrollo Sostenible en Zonas Rurales", autor, "Dr. Fernando Castillo", "Ingenieria Ambiental", 2022);
		tesis.push_back(tes);

		autor[0] = "Maria Lopez"; autor[1] = "Jose Fernandez"; autor[2] = "Clara Gomez"; autor[3] = ""; autor[4] = "";
		tes.ModificarDatos("Implementacion de IA en Medicina", autor, "Dra. Laura Vega", "Ingenieria Biomedica", 2023);
		tesis.push_back(tes);


		autor[0] = "Diego Perez"; autor[1] = "Lucia Gonzales"; autor[2] = "Miguel Castro"; autor[3] = "Sandra Torres"; autor[4] = "";
		tes.ModificarDatos("Analisis de Energias Renovables", autor, "Dr. Luis Hernandez", "Ingenieria Electrica", 2021);
		tesis.push_back(tes);
	}
	else {
		printf("Ya existen datos cargados en memoria. Solo se pueden generar genericamente si no hay datos cargados");
	}
}

static void MostrarVector(vector<Libro> libro) {
	Libro lib = Libro(true);
	for (unsigned short i = 0; i < libro.size(); i++) {
		lib = libro.at(i);
		cout << "TITULO:\n" << lib.ObtenerTitulo() << endl << "AUTORES:" << endl;
		for (unsigned short j = 0; j < ARREMAX; j++) {
			if(lib.ObtenerAutores(j).size() != 0) cout << lib.ObtenerAutores(j) << endl;
		}
		cout << "EDITORIAL:\n" << lib.ObtenerEditorial() << endl << "ANO DE PUBLICACION:\n" << lib.ObtenerYear() << endl;
		cout << endl;
	}
}

static void MostrarVector(vector<Tesis> tesis) {
	Tesis tes = Tesis(true);
	for (unsigned short i = 0; i < tesis.size(); i++) {
		tes = tesis.at(i);
		cout << "TITULO:\n" << tes.ObtenerTitulo() << endl << "AUTORES:\n" << endl;
		for (unsigned short j = 0; j < ARREMAX; j++) {
			if(tes.ObtenerAutores(j).size() != 0) cout << tes.ObtenerAutores(j) << endl;
		}
		cout << "ASESOR:\n" << tes.ObtenerAsesor() << endl << "ANO DE PUBLICACION:\n" << tes.ObtenerYear() << endl;
		cout << endl;
	}
}
#pragma endregion

#pragma region OpcionesMenu

//Registra una tesis y la almacena en el vector global
static void RegistrarTesis(){
	system("cls");
	Tesis tes = Tesis(false);
	tesis.push_back(tes);
}
//Registra un libro y lo almacena en el vector global
static void RegistrarLibro() {
	system("cls");
	Libro lib = Libro(false);
	libros.push_back(lib);
}

//Busca un libro o tesis a partir del vector global
static void BuscarLibroTesisPorAutor() {
	string aut;
	char opt;
	vector<Libro> lib; vector <Tesis> tes;
	Libro auxLib = Libro(true);
	Tesis auxTes = Tesis(true);

	system("cls");
	cout << "Desea buscar un libro o una tesis?\n(Libro = 1 | Tesis = 2 | Salir = 0)\nOpcion = ";
	do {
		opt = _getch(); cout << opt << endl;
		switch (opt) {
		case '1':
			cout << "Ingrese el autor del libro que desea buscar: ";
			cin >> aut;
			lib = auxLib.FiltrarPorAutor(aut, libros);
			MostrarVector(lib);
			opt = '0';
			break;

		case '2':
			cout << "Ingrese el autor de la tesis que desea buscar: ";
			cin >> aut;
			tes = auxTes.FiltrarPorAutor(aut, tesis);
			MostrarVector(tes);
			opt = '0';
			break;
		}
	} while (opt != '0');
	cout << endl; system("pause");
}
#pragma endregion


#pragma region MainMenu

static void Menu() {
	char opt;
	do {
		system("cls");
		cout << "Bienvenido a la biblioteca de Georges chakour, que desea realizar?:\n\n1.Registrar un Libro\n2.Registrar una Tesis\n3.Buscar Libro/Tesis\n9.Cargar libros y tesis genericas (DEBUG)\n0.Salir\n\n";
		cout << "Libros registrados = " << libros.size() << endl << "Tesis registradas = " << tesis.size() << "\n\nOpcion = ";
		opt = _getch();
		switch (opt) {
		case '1':
			RegistrarLibro();
			break;
		case '2':
			RegistrarTesis();
			break;
		case '3':
			BuscarLibroTesisPorAutor();
			break;
		case '9':
			CargarDatosGenericos();
			break;
		default:

			break;
		}
	} while (opt != '0');
	cout << endl; system("pause");
}
#pragma endregion





int main() {
	Menu();
}