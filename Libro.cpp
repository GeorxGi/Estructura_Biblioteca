#include "Libro.h"
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

//Constructor independiente que se encarga de validaciones y entrada de datos
Libro::Libro(bool GenerarVacio) {
	if (!GenerarVacio) {
		string titulo, autor[ARRMAX], isbn, editorial, straux;
		unsigned short year = 0;
		char opt = ' ', aux;

		do {
			printf("Ingrese el titulo del libro: ");
			getline(cin, titulo);
		} while (titulo.empty());

		do {
			printf("Cuantos autores posee el libro? (1 - 5) = ");
			opt = _getch(); cout << opt << endl;
		} while (!EsNumero(opt) || (opt < 48 || opt > 53));
		opt -= 48;

		for (unsigned short i = 0; i < opt; i++) {
			cout << "Autor #" << i + 1 << ": ";
			getline(cin, autor[i]);
			if (autor[i].empty()) {
				if (i > 0) {
					printf("Entrada vacia, desea dejar de ingresar autores? [Y/N]");
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

		do {
			printf("Ingrese la editorial del libro: ");
			getline(cin, editorial);
		} while (editorial.empty());

		do {
			printf("Ingrese el ISBN del libro (Debe contener 13 numeros y un minimo de 3 separadores \"-\"): \n");
			getline(cin, isbn);
		} while (ValidarISBN(isbn));

		do {
			printf("Ingrese el anio de publicacion del libro (Entre 0 y 2024): ");
			cin >> year;
		} while (year < 0 || year > 2025);

		EstablecerTitulo(titulo); EstablecerAutores(autor);
		m_Editorial = editorial;  m_ISBN = isbn;
		p_Year = year;            p_EsLibro = true;

		system("pause");
		printf("Libro registrado exitosamente\n");
	}
}
Libro::Libro(string titulo, string autor[ARRMAX], string editorial, string isbn, unsigned short year) {
	EstablecerTitulo(titulo); EstablecerAutores(autor);
	m_Editorial = editorial;  m_ISBN = isbn;
	p_Year = year;            p_EsLibro = true;
}

void Libro::ModificarDatos(string titulo, string autor[ARRMAX], string editorial, string isbn, unsigned short year) {
	EstablecerTitulo(titulo); EstablecerAutores(autor);
	m_Editorial = editorial;  m_ISBN = isbn;
	p_Year = year;            p_EsLibro = true;
}

//Recibe una cadena y valida que posea un formato ISBN valido
bool Libro::ValidarISBN(string isbn) {
	unsigned short cont = 0, cont2 = 0;
	if (isbn.size() > 13) {
		for (unsigned short i = 0; i < isbn.size(); i++) {
			if (EsNumero(isbn[i])) {
				cont++;
			}
			else if (isbn[i] == '-' && i != 0) {
				//No añado operadores && para evitar evaluar la posicion -1 y sufrir rebalse de memoria
				if (i > 0) {
					if (isbn[i - 1] == '-') {
						return false;
					}
				}
				else {
					cont2++;
				}
			}
			else {
				return false;
			}
		}
		return cont == 13 && cont2 > 3;
	}
	return false;
}
//Retorna el ISBN del libro
string Libro::ObtenerISBN() const { return m_ISBN; }
//Retorna la editorial del libro
string Libro::ObtenerEditorial() const { return m_Editorial; }

//Recibe el nombre del autor y un vector con todos los libros almacenados y retorna un vector con
//todos los libros que cumplen con las mismas letras indicadas del autor
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
			auxAutor = auxlib.ObtenerAutores(j);
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