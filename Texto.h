#pragma once
#include <string>
#include <vector>
constexpr unsigned short ARRMAX = 5;

using namespace std;

class Texto
{
private:
	string m_Titulo, m_Autores[ARRMAX];

protected:
	bool p_EsLibro = false;
	unsigned short p_Year = 0;

	void EstablecerTitulo(string titulo);
	void EstablecerAutores(string autores[ARRMAX]);
	static bool EsNumero(char i);

public:
	unsigned short ObtenerYear() const;
	string ObtenerTitulo() const;
	bool EsLibro() const;
	vector<string> ObtenerAutores() const;
	string ObtenerAutores(unsigned short index) const;
};

