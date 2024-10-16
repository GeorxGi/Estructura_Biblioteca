#pragma once
#include <string>
#include <vector>
constexpr unsigned short ARRMAX = 5;
constexpr unsigned short MAXEJEMP = 10;

using namespace std;

class Texto
{
private:
	string m_Titulo, m_Autores[ARRMAX];
	unsigned short m_Ejemplares = 0;

protected:
	bool p_EsLibro = false;
	unsigned short p_Year = 0;
	//Establece el titulo de la obra
	void EstablecerTitulo(string titulo);
	//Establece el nombre de los autores de la obra
	void EstablecerAutores(string autores[ARRMAX]);
	//Recibe la cantidad de ejemplares a registrar, retorna un booleano en base a si el valor ingresado esta dentro de rango
	bool RegistrarEjemplares(unsigned short cantidad);

public:
	//Retorna el titulo de la obra
	string ObtenerTitulo() const;
	//Retorna un vector con el nombre de todos los autores
	vector<string> ObtenerAutores() const;
	//Recibe el indice del autor (entre 1 y 5) y retorna el nombre en caso de existir en dicho indice
	string ObtenerAutor(unsigned short index) const;
	//Retorna el año de publicacion de la obra
	unsigned short ObtenerYear() const;
	//Booleano que indica si el texto es un libro, en caso contrario, una tesis
	bool EsLibro() const;
	//Retorna la cantidad de ejemplares que posee la obra
	unsigned short ObtenerEjemplares() const;
};