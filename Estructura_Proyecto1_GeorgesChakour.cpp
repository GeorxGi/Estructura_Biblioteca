#include <conio.h>
#include <iostream>
#include <vector>
#include <string>

#include "Libro.h"
#include "Tesis.h"
#include "Estudiante.h"
#include "Funciones.h"

using namespace std;
//Se utilizara la convension de cpp. Basado en: https://www.geeksforgeeks.org/naming-convention-in-c/
//m_ = prefijo para variables privadas  |  p_ = prefijo para variables protegidas

vector <Tesis> tesis;
vector <Libro> libros;
vector<Estudiante> estudiant;

#pragma region OpcionesMenu
static void RegistrarLibroTesis() {
	ColorMsg("REGISTRAR\n\n", LightAqua);
	Libro lib = Libro(true);
	Tesis tes = Tesis(true);
	char opt;
	do {
		system("cls");
		ColorMsg("Desea registrar un libro o una tesis?\n", LightYellow);
		cout << "(Libro = 1 | Tesis = 2 | Salir = 0)\nOpcion = ";
		opt = _getch(); cout << opt << endl;
		switch (opt) {
		case '1':
			lib = Libro(false);
			libros.push_back(lib);
			opt = '0';
			break;
		case '2':
			tes = Tesis(false);
			tesis.push_back(tes);
			opt = '0';
			break;
		}
	} while (opt != '0' && opt != 27);
	system("pause");
}

static void ListaLibroTesis(){
	char opt;
	do {
		system("cls");
		ColorMsg("Desea mostrar una lista de libros o tesis?\n", LightYellow);
		cout << "(Libro = 1 | Tesis = 2 | Salir = 0)\nOpcion = ";
		opt = _getch();
		switch (opt) {
		case '1':
			MostrarVector(libros);
			opt = '0';
			break;
		case '2':
			MostrarVector(tesis);
			opt = '0';
			break;
		}
	} while (opt != '0' && opt != 27);
	system("pause");
}

static void BuscarLibroTesisPorAutor() {
	string aut;
	char opt;
	vector<Libro> lib; vector <Tesis> tes;
	Libro auxLib = Libro(true);
	Tesis auxTes = Tesis(true);

	ColorMsg("BUSCAR EN REGISTROS\n\n", LightAqua);
	do {
		system("cls");
		ColorMsg("Desea buscar un libro o una tesis?\n", LightYellow);
		cout << "(Libro = 1 | Tesis = 2 | Salir = 0)\nOpcion = ";
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
	} while (opt != '0' && opt != 27);
	cout << endl; system("pause");
}

static void ModificarLibroTesis() {
	Libro lib = Libro(true);
	Tesis tes = Tesis(true);
	int index = 0;
	char opt;
	ColorMsg("MODIFICAR\n\n", LightAqua);
	do {
		system("cls");
		ColorMsg("Desea modificar un libro o una tesis?\n", LightYellow);
		cout << "(Libro = 1 | Tesis = 2 | Salir = 0)\nOpcion = ";
		opt = _getch(); cout << opt << endl;
		ColorMsg("Utilice las flechas del teclado para seleccionar ", LightPurple);
		ColorMsg("(Presione ESC para volver al menu)\n", LightAqua);
		switch (opt) {
		case '1':
			index = Seleccion(libros, tesis, true);
			if (index != -1) {
				lib = libros.at(index);
				libros.erase(libros.begin() + index);
				lib.ModificarDatos(true);
				libros.insert(libros.begin() + index, lib);
			}
			opt = '0';
			break;
		case '2':
			index = Seleccion(libros, tesis, false);
			if (index != -1) {
				tes = tesis.at(index);
				tesis.erase(tesis.begin() + index);
				tes.ModificarDatos(true);
				tesis.insert(tesis.begin() + index, tes);
			}
			opt = '0';
			break;
		}
	} while (opt != '0');
	cout << endl;  system("pause");
}

static void DesincorporarLibro() {
	Libro lib = Libro(true);
	char opt;
	int index, ejempIndex;
	system("cls");
	ColorMsg("DESINCORPORAR\n\n", LightAqua);
	ColorMsg("Seleccione el libro que desea manejar:\n", LightYellow);
	index = Seleccion(libros, tesis, true);
	if (index != -1) {
		do {
			lib = libros.at(index);
			cout << "(Libro = 1 | Ejemplar = 2 | Salir = 0)\nOpcion = ";
			opt = _getch(); cout << opt << endl;
			switch (opt) {
			case '1':
				ColorMsg("Esta seguro de eliminar el libro: " + lib.ObtenerTitulo() + "\nEsta accion no se puede revertir\n", Red);
				if (SeleccionTrueFalse()) {
					libros.erase(libros.begin() + index);
					ColorMsg("Libro eliminado correctamente", LightRed);
				}
				else ColorMsg("Libro no eliminado", LightGreen);
				opt = '0';
				break;
			case '2':
				ColorMsg("Utilice las flechas del teclado para seleccionar el ISBN del ejemplar\n", LightPurple);
				ejempIndex = SeleccionISBN(lib);
				if(ejempIndex != -1){
					ColorMsg("Esta seguro de eliminar este ejemplar?\nEsta accion no se puede revertir\n", Red);
					if (SeleccionTrueFalse()) {
						libros.erase(libros.begin() + index);
						lib.EliminarEjemplar(ejempIndex);
						libros.insert(libros.begin() + index, lib);
						ColorMsg("Ejemplar eliminado correctamente", LightRed);
					}
					else ColorMsg("Ejemplar no eliminado", LightGreen);
				}
				
				opt = '0';
				break;
				}
			} while (opt != '0' && opt != 27);
		} 
	cout << endl;  system("pause");
}

static void ProcesarPrestamo() {
	system("cls");
	ColorMsg("PROCESAR PRESTAMO\n\n", LightAqua);
	Estudiante est = Estudiante(false);
	if (!ValidarEstudianteRepetido(est, estudiant)) {
		ColorMsg("Datos de estudiante cargados correctamente\n", LightGreen);
		if (est.RealizarPrestamo(libros, estudiant)) {
			estudiant.push_back(est);
		}
	}
	else {
		ColorMsg("Estudiante ya registrado, debera devolver los libros si desea pedir nuevamente un prestamo\n", LightRed);
	}
	system("pause");
}

static void ProcesarReintegro() {
	int index;
	bool select;
	system("cls");
	ColorMsg("PROCESAR PRESTAMO\n\n", LightAqua);
	ColorMsg("(Utilice las flechas del teclado para seleccionar\n", LightPurple);
	index = SeleccionarEstudiante(estudiant);
	if (index != -1) {
		ColorMsg("Se reintegraran los libros prestados, eliminando la informacion del estudiante\n", LightYellow);
		ColorMsg("Esta accion no se puede revertir, esta seguro de ello?\n", Red);
		if (SeleccionTrueFalse()) {
			estudiant.erase(estudiant.begin() + index);
			ColorMsg("\nReintegro realizado correctamente", Green);
		}
		else {
			ColorMsg("\nOperacion cancelada", LightYellow);
		}
	}
	cout << endl;
	system("pause");
}

static void ListarPrestamos() {
	system("cls");
	ColorMsg("LISTA DE PRESTAMOS", LightAqua);
	MostrarPrestamos(estudiant, libros);
	system("pause");
}

static void DatosGenericos() {
	system("cls");
	libros = CargarLibrosGenericos(libros);
	tesis = CargarTesisGenerica(tesis);
	system("pause");
}
#pragma endregion

static void Menu() {
	char opt;
	do {
		system("cls");
		ColorMsg("Bienvenido a la biblioteca de Georges chakour, que desea realizar?\n", LightYellow);
		cout <<"\n1.Ingresar         [Libro | Tesis]"       <<
			   "\n2.Lista            [Libro | Tesis]"       <<
			   "\n3.Buscar por autor [Libro | Tesis]"       <<
			   "\n4.Modificar        [Libro | Tesis]"       <<
			   "\n5.Desincorporar un [Libro | Ejemplar]"    <<
			   "\n6.Procesar prestamo"                      <<
	           "\n7.Procesar un reintegro"                  <<
			   "\n8.Lista de prestamos"                     <<
			   "\n9.Cargar libros y tesis genericas(DEBUG)" <<
			   "\n0.Salir\n\n";
		
		ColorMsg("Libros Registrados = " + to_string(libros.size()) + "\nTesis registradas = " + to_string(tesis.size()) + "\nPrestamos realizados = " + to_string(estudiant.size()) + "\n\n", LightAqua);
		cout << "Opcion = ";
		opt = _getch();
		
		switch (opt) {
		case '1':
			RegistrarLibroTesis();
			break;
		case '2':
			ListaLibroTesis();
			break;
		case '3':
			BuscarLibroTesisPorAutor();
			break;
		case '4':
			ModificarLibroTesis();
			break;
		case '5':
			DesincorporarLibro();
			break;
		case '6':
			ProcesarPrestamo();
			break;
		case '7':
			ProcesarReintegro();
			break;
		case '8':
			ListarPrestamos();
			break;
		case '9':
			DatosGenericos();
			break;
		}
	} while (opt != '0' && opt != 27);
	cout << endl;
}
int main() { Menu();}