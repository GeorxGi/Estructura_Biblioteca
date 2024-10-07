#pragma once
#include "Texto.h"

using namespace std;

class Libro : public Texto {
private:
    string m_ISBN, m_Editorial;
    bool ValidarISBN(string isbn);

public:
    Libro(bool GenerarVacio);
    Libro(string titulo, string autor[ARRMAX], string editorial, string isbn, unsigned short year);
    string ObtenerISBN() const;
    string ObtenerEditorial() const;
    vector<Libro> FiltrarPorAutor(string autor, vector<Libro> libros);
    void ModificarDatos(string titulo, string autor[ARRMAX], string editorial, string isbn, unsigned short year);
};

