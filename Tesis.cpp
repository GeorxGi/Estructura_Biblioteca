#include "Tesis.h"
#include "Funciones.h"

#include <iostream>
#include <conio.h>

#pragma region Constructores
//Constructor principal de la tesis
Tesis::Tesis(bool GenerarVacia) {
	if (!GenerarVacia) {
		ModificarDatos(false);
		printf("Tesis registrada exitosamente\n");
	}
}
Tesis::Tesis(string titulo, string autor[ARRMAX], string asesor, string carrera, unsigned short year, unsigned short numEjemp) {
	ModificarDatos(titulo, autor, asesor, carrera, year, numEjemp);
}
#pragma endregion

#pragma region RetornoDeDatos
//Retorna el asesor de la tesis
string Tesis::ObtenerAsesor() const { return m_Asesor; }
//Retorna la carrera a la que pertenece la tesis
string Tesis::ObtenerCarrera() const { return m_Carrera; }
#pragma endregion

#pragma region MetodosEspeciales
void Tesis::ModificarDatos(string titulo, string autor[ARRMAX], string asesor, string carrera, unsigned short year, unsigned short numEjemp) {
	EstablecerTitulo(titulo); EstablecerAutores(autor);
	RegistrarEjemplares(numEjemp);
	m_Asesor = asesor;        m_Carrera = carrera;
	p_Year = year;            p_EsLibro = true;
}
void Tesis::ModificarDatos(bool mostrarDatosAnteriores) {
	string titulo, autor[ARRMAX], asesor, carrera, straux, mensaje;
	unsigned short year = 0, numEjemp = 0, numAutor;
	char opt = ' ', aux;
	
	fflush(stdin);
	if (mostrarDatosAnteriores) ColorMsg("Titulo anterior: " + this->ObtenerTitulo() + "\n", Gray);
	do {
		cout << "Ingrese el titulo de la Tesis: ";
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
		cout << "Cuantos autores posee la Tesis? (1 - 5) = ";
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

	if (mostrarDatosAnteriores) ColorMsg("Asesor anterior: " + this->ObtenerAsesor() + "\n", Gray);
	do {
		cout << "Ingrese el nombre del asesor de la Tesis: ";
		getline(cin, asesor);
	} while (asesor.empty());

	if (mostrarDatosAnteriores) ColorMsg("Ejemplares registrados: " + to_string(this->ObtenerEjemplares()) + "\n", Gray);
	do {
		cout << "Cantidad de ejemplares a registrar (maximo " << MAXEJEMP << "): ";
		numEjemp = RetornarNumero();
	} while (numEjemp <= 0 || numEjemp > MAXEJEMP);
	if (mostrarDatosAnteriores) ColorMsg("Carrera anterior: " + this->ObtenerCarrera() + "\n", Gray);
	do {
		cout << "Ingrese la carrera a la que pertenece la Tesis: ";
		getline(cin, carrera);
	} while (carrera.empty());

	if (mostrarDatosAnteriores) ColorMsg("Anio de publicacion anterior: " + to_string(this->ObtenerYear()) + "\n", Gray);
	do {
		cout << "Ingrese el anio de publicacion de la Tesis (Entre 0 y 2024): ";
		year = RetornarNumero();
	} while (year < 0 || year > 2025);

	ModificarDatos(titulo, autor, asesor, carrera, year, numEjemp);
}

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
			auxAutor = auxTes.ObtenerAutor(j);
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
#pragma endregion

vector<Tesis> Tesis::FiltrarPorAsesor(string asesor, vector<Tesis> tesis) {
	vector<Tesis> retorno;
	Tesis auxTes = Tesis(true);
	string auxAsesor;
	bool esValido;
	for (unsigned short i = 0; i < tesis.size(); i++) {
		auxTes = tesis.at(i);
		esValido = true;
		auxAsesor = auxTes.ObtenerAsesor();
		for (unsigned short j = 0; j < asesor.size(); j++) {
			if (asesor[j] != auxAsesor[j]) {
				esValido = false;
				break;
			}
		}
		if (esValido) retorno.push_back(auxTes);
	}
	return retorno;
}