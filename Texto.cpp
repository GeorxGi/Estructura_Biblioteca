#include "Texto.h"

using namespace std;

//Evalua si el caracter ingresado es numerico
bool Texto::EsNumero(char i) {
	return i > '0' && i < '9';
}

void Texto::EstablecerTitulo(string titulo) {
	m_Titulo = titulo;
}

void Texto::EstablecerAutores(string autores[ARRMAX]) {
	for (unsigned short i = 0; i < ARRMAX; i++)
	{
		m_Autores[i] = autores[i];
	}
}

//Retorna un vector con el nombre de todos los autores
vector<string> Texto::ObtenerAutores() const{
	vector<string> aux;
	//recorre los autores, en lo que encuentra un espacio vacio, interpreta que no hay mas autores y retorna
	for (unsigned short i = 0; i < ARRMAX; i++) {
		if (m_Autores[i] == "") break;
		aux.push_back(m_Autores[i]);
	}
	return aux;
}
//Recibe el indice del autor (entre 1 y 5) y retorna el nombre en caso de existir en dicho indice
string Texto::ObtenerAutores(unsigned short index) const {
	if (index >= 0 && index < ARRMAX) return m_Autores[index];
	else return "";
}

string Texto::ObtenerTitulo() const { return m_Titulo; }
unsigned short Texto::ObtenerYear() const { return p_Year; }

bool Texto::EsLibro() const { return p_EsLibro; }
static bool EsNumero(char i) { return i > '0' && i < '9'; }