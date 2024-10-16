#include "Libro.h"
#include "Funciones.h"

#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

#pragma region Constructores
//Constructor independiente que se encarga de validaciones y entrada de datos
Libro::Libro(bool GenerarVacio) {
	if (!GenerarVacio) {
		ModificarDatos(false);
		cout << "Libro registrado exitosamente\n";
	}
}
Libro::Libro(string titulo, string autor[ARRMAX], string editorial, string modeloISBN, unsigned short year, unsigned short numEjemp) {
	ModificarDatos(titulo, autor, editorial, modeloISBN, year, numEjemp);
}
#pragma endregion

#pragma region RetornoDeDatos

//Retorna el ISBN del ejemplar indicado
string Libro::ObtenerISBN(short ejemplar) const { return m_ISBN[ejemplar]; }
//Retorna la editorial del libro
string Libro::ObtenerEditorial() const { return m_Editorial; }
#pragma endregion

#pragma region MetodosEspeciales

//Metodo encargado de recibir los datos necesarios para generar/modificar los datos de un libro
void Libro::ModificarDatos(string titulo, string autor[ARRMAX], string editorial, string modeloISBN, unsigned short year, unsigned short numEjemp) {
	EstablecerTitulo(titulo); EstablecerAutores(autor);
	RegistrarEjemplares(numEjemp);

	m_Editorial = editorial;
	p_Year = year;            p_EsLibro = true;

	for (unsigned short i = 0; i < numEjemp; i++) {
		m_ISBN[i] = GenerarISBN(modeloISBN);
	}
}

//Metodo encargado de manejar la consola para ingresar datos de un libro
void Libro::ModificarDatos(bool mostrarDatosAnteriores) {
	string titulo, autor[ARRMAX], isbn[MAXEJEMP], editorial, straux;
	unsigned short year = 0, numEjemp = 0, numAutor;
	char opt = ' ', aux;
	fflush(stdin);
	if (mostrarDatosAnteriores) ColorMsg("Titulo anterior: " + this->ObtenerTitulo() + "\n", Gray);
	do {
		cout << "Ingrese el titulo del libro: ";
		getline(cin, titulo);
	} while (titulo.empty());

	if (mostrarDatosAnteriores) {
		ColorMsg("Autores anteriores:\n", Gray);
		for (unsigned short i = 0; i < ARREMAX; i++) {
			if (!this->ObtenerAutor(i).empty()) ColorMsg(this->ObtenerAutor(i) + "\n", Gray);
			else break;
		}
	}
	do {
		cout << "Cuantos autores posee el libro? (1 - " << ARRMAX << "):";
		numAutor = RetornarNumero();
	} while (numAutor < 1 || numAutor > ARRMAX);

	for (unsigned short i = 0; i < numAutor; i++) {
		cout << "Autor #" << i + 1 << ": ";
		getline(cin, autor[i]);
		if (autor[i].empty()) {
			if (i > 0) {
				cout << "Entrada vacia, desea dejar de ingresar autores? [Y/N]";
				aux = _getch();
				if (aux == 'Y' || aux == 'y') {
					break;
				}
				else {
					i--;
				}
			}
			else {
				i--;
			}
		}
	}

	if (mostrarDatosAnteriores) ColorMsg("Editorial Anterior: " + this->ObtenerEditorial() + "\n", Gray);
	do {
		cout << "Ingrese la editorial del libro: ";
		getline(cin, editorial);
	} while (editorial.empty());

	if (mostrarDatosAnteriores) ColorMsg("Ejemplares registrados: " + to_string(this->ObtenerEjemplares()) + "\n", Gray);
	do {
		cout << "Cantidad de ejemplares a registrar (maximo " << MAXEJEMP << "): ";
		numEjemp = RetornarNumero();
	} while (numEjemp <= 0 || numEjemp > MAXEJEMP);

	if (mostrarDatosAnteriores) ColorMsg("Modelo ISBN existente: " + this->ObtenerISBN(0) + "\n", Gray);
	string model = GenerarModeloISBN();
	for (unsigned short i = 0; i < numEjemp; i++) {
		m_ISBN[i] = GenerarISBN(model);
	}
	cout << endl;

	if (mostrarDatosAnteriores) ColorMsg("Anio de publicacion anterior: " + to_string(this->ObtenerYear()) + "\n", Gray);
	do {
		cout << "Ingrese el anio de publicacion del libro (Entre 0 y 2024): ";
		year = RetornarNumero();
	} while (year < 0 || year > 2025);

	ModificarDatos(titulo, autor, editorial, model, year, numEjemp);
}

//Recibe una cadena y valida que posea un formato ISBN valido
bool Libro::ValidarISBN(string isbn) {
	unsigned short cont = 0, cont2 = 0;
	if (isbn.size() < 13) {
		return false;
	}
	else {
		for (unsigned short i = 0; i < isbn.size(); i++) {
			switch (isbn[i]) {
			case 'X':
				cont++;
				break;

			case '-':
				if (i > 0) {
					if (isbn[i - 1] == '-') {
						return false;
					}
					else cont2++;
				}
				break;

			default:
				if(EsNumero(isbn[i])) cont++;
				else {
					return false;
				}
				break;
			}
		}
		return cont == 13 && cont2 >= 3;
	}
}

//Recibe el nombre del autor y un vector con todos los libros almacenados y retorna un vector con
//todos los libros cuyos autores posean interseccion con el nombre ingresado
vector<Libro> Libro::FiltrarPorAutor(string autor, vector<Libro> libros) {
	vector<Libro> retorno;
	Libro auxlib = Libro(true);
	string auxAutor;
	bool EsValido;

	//Recorre todos los libros del vector
	for (unsigned short i = 0; i < libros.size(); i++) {
		auxlib = libros.at(i);
		//Recorre todos los autores del libro
		for (unsigned short j = 0; j < ARRMAX; j++) {
			EsValido = true;
			auxAutor = auxlib.ObtenerAutor(j);
			//Recorre todos los caracteres del nombre del autor ingresado
			for (unsigned short k = 0; k < autor.size(); k++) {
				if (autor[k] != auxAutor[k]) {
					EsValido = false;
					break;
				}
			}
			if (EsValido) retorno.push_back(auxlib);
		}
	}
	return retorno;
}

//Recibe la estructura del ISBN del tipo "XXX-XXX-XX-XXXX-X", retorna el ISBN generado aleatoriamente
//Retornara un string vacio en caso de recibir un modelo ISBN no valido
string Libro::GenerarISBN(string modelo) {
	char charRand = '0';
	if (ValidarISBN(modelo)) {
		string newModel = modelo;
		for (unsigned short i = 0; i < newModel.size(); i++) {
			if (newModel[i] == 'X') {
				charRand = 48 + (rand() % 10);
				newModel[i] = charRand;
			}
		}
		return newModel;
	}
	return "0";
}

//Elimina el ejemplar indicado, y rota todos los ejemplares a su derecha en el arreglo
void Libro::EliminarEjemplar(unsigned short index) {
	if (index == this->ObtenerEjemplares() - 1) {
		m_ISBN[index] = "";
	}
	else {
		for (unsigned short i = index; i < this->ObtenerEjemplares() - 2; i++) {
			m_ISBN[i] = m_ISBN[i + 1];
		}
	}
	this->RegistrarEjemplares(this->ObtenerEjemplares()-1);
}
#pragma endregion