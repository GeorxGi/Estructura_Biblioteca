#pragma once
#include "Texto.h"
using namespace std;

class Tesis : public Texto {
private:
	string m_Asesor, m_Carrera;

	
public:
	Tesis(bool GenerarVacia);
	Tesis(string titulo, string autor[ARRMAX], string asesor, string carrera, unsigned short year);
	string ObtenerAsesor() const;
	string ObtenerCarrera() const;
	vector<Tesis> FiltrarPorAutor(string autor, vector<Tesis> tesis);
	void ModificarDatos(string titulo, string autor[ARRMAX], string asesor, string carrera, unsigned short year);
};

