#include "Texto.h"

using namespace std;

#pragma region RegistroDeDatos

//Establece el nombre de los autores de la obra
void Texto::EstablecerAutores(string autores[ARRMAX]) {
	for (unsigned short i = 0; i < ARRMAX; i++)
	{
		m_Autores[i] = autores[i];
	}
}

//Establece el titulo de la obra
void Texto::EstablecerTitulo(string titulo) {
	m_Titulo = titulo;
}

//Recibe la cantidad de ejemplares a registrar, retorna un booleano en base a si el valor ingresado esta dentro de rango
bool Texto::RegistrarEjemplares(unsigned short cantidad) {
	if (cantidad >= 0 && cantidad < MAXEJEMP) {
		m_Ejemplares = cantidad;
		return true;
	}
	return false;
}
#pragma endregion

#pragma region RetornoDeDatos
//Retorna un vector con el nombre de todos los autores
vector<string> Texto::ObtenerAutores() const {
	vector<string> aux;
	//recorre los autores, en lo que encuentra un espacio vacio, interpreta que no hay mas autores y retorna
	for (unsigned short i = 0; i < ARRMAX; i++) {
		if (m_Autores[i] == "") break;
		aux.push_back(m_Autores[i]);
	}
	return aux;
}
//Recibe el indice del autor (entre 1 y 5) y retorna el nombre en caso de existir en dicho indice
string Texto::ObtenerAutor(unsigned short index) const {
	if (index >= 0 && index < ARRMAX) return m_Autores[index];
	else return "";
}
//Retorna el titulo de la obra
string Texto::ObtenerTitulo() const { return m_Titulo; }
//Retorna el año de publicacion de la obra
unsigned short Texto::ObtenerYear() const { return p_Year; }

//Retorna la cantidad de ejemplares que posee la obra
unsigned short Texto::ObtenerEjemplares() const { return m_Ejemplares; }
#pragma endregion

#pragma region Operadores
//Booleano que indica si el texto es un libro, en caso contrario, una tesis
bool Texto::EsLibro() const { return p_EsLibro; }
#pragma endregion

