#pragma once
#include "Texto.h"
using namespace std;

class Tesis : public Texto {
private:
	string m_Asesor, m_Carrera;
	
public:
	//Constructor principal de la tesis, recibe un booleano que indica si la tesis a generar debe estar vacia o cargar datos
	Tesis(bool GenerarVacia);
	Tesis(string titulo, string autor[ARRMAX], string asesor, string carrera, unsigned short year, unsigned short numEjemp);
	//Retorna el asesor de la tesis
	string ObtenerAsesor() const;
	//Retorna la carrera a la que pertenece la tesis
	string ObtenerCarrera() const;
	//Recibe el nombre del autor y un vector con todas las Tesis almacenadas y retorna un vector con
	//todas las tesis que cumplen con las mismas letras indicadas del autor
	vector<Tesis> FiltrarPorAutor(string autor, vector<Tesis> tesis);

	void ModificarDatos(string titulo, string autor[ARRMAX], string asesor, string carrera, unsigned short year, unsigned short numEjemp);
	void ModificarDatos(bool mostrarDatosAnteriores);
};

