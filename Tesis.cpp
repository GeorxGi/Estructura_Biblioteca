#include "Tesis.h"
#include <iostream>
#include <conio.h>
#include <fstream>

//Constructor principal de la tesis
Tesis::Tesis(bool GenerarVacia) {
	if (!GenerarVacia) {
		string titulo, autor[ARRMAX], asesor, carrera, straux;
		unsigned short year = 0;
		char opt = ' ', aux;
		do {
			printf("Ingrese el titulo de la Tesis: ");
			getline(cin, titulo);
		} while (titulo.empty());

		do {
			printf("Cuantos autores posee la Tesis? (1 - 5) = ");
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
			printf("Ingrese el nombre del asesor de la Tesis: ");
			getline(cin, asesor);
		} while (asesor.empty());

		do {
			printf("Ingrese la carrera a la que pertenece la Tesis: ");
			getline(cin, carrera);
		} while (carrera.empty());

		do {
			printf("Ingrese el anio de publicacion de la Tesis (Entre 0 y 2024): ");
			cin >> year;
		} while (year < 0 || year > 2025);

		EstablecerTitulo(titulo); EstablecerAutores(autor);
		m_Asesor = asesor;        m_Carrera = carrera;
		p_Year = year;            p_EsLibro = true;

		system("pause");
		printf("Tesis registrada exitosamente\n");
	}
}
Tesis::Tesis(string titulo, string autor[ARRMAX], string asesor, string carrera, unsigned short year) {

	EstablecerTitulo(titulo); EstablecerAutores(autor);
	m_Asesor = asesor;        m_Carrera = carrera;
	p_Year = year;            p_EsLibro = true;
}

void Tesis::ModificarDatos(string titulo, string autor[ARRMAX], string asesor, string carrera, unsigned short year) {
	EstablecerTitulo(titulo); EstablecerAutores(autor);
	m_Asesor = asesor;        m_Carrera = carrera;
	p_Year = year;            p_EsLibro = true;
}

//Retorna el asesor de la tesis
string Tesis::ObtenerAsesor() const  { return m_Asesor; }
//Retorna la carrera a la que pertenece la tesis
string Tesis::ObtenerCarrera() const { return m_Carrera; }

//Recibe el nombre del autor y un vector con todas las Tesis almacenadas y retorna un vector con
//todas las tesis que cumplen con las mismas letras indicadas del autor
vector<Tesis> Tesis::FiltrarPorAutor(string autor, vector<Tesis> tesis) {
	vector<Tesis> retorno;
	Tesis auxTes = Tesis(true);
	string auxAutor;
	bool EsValido;
	//Recorre todas las tesis del vector
	for (unsigned short i = 0; i < tesis.size(); i++) {
		auxTes = tesis.at(i);
		//Recorre todos los autores de la tesis
		for (unsigned short j = 0; j < ARRMAX; j++) {
			EsValido = true;
			auxAutor = auxTes.ObtenerAutores(j);
			//Recorre todos los caracteres del nombre del autor ingresado
			for (unsigned short k = 0; k < autor.size(); k++) {
				if (autor[k] != auxAutor[k]) {
					EsValido = false;
					break;
				}
			}
			if (EsValido) retorno.push_back(auxTes);
		}
	}
	return retorno;
}