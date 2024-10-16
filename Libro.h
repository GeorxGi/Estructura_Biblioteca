#pragma once
#include "Texto.h"

using namespace std;

class Libro : public Texto {
private:
    string m_ISBN[MAXEJEMP], m_Editorial;

protected:
    //Valida que la cadena ingresada posea un formato ISBN valido
    bool ValidarISBN(string isbn);

public:
    //Constructor independiente que se encarga de validaciones y entrada de datos
    Libro(bool GenerarVacio);
    Libro(string titulo, string autor[ARRMAX], string editorial, string modeloISBN, unsigned short year, unsigned short numEjemp);


    //Retorna el ISBN del ejemplar indicado
    string ObtenerISBN(short ejemplar) const;
    //Retorna la editorial del libro
    string ObtenerEditorial() const;

    //Recibe el nombre del autor y un vector con todos los libros almacenados y retorna un vector con
    //todos los libros cuyos autores posean interseccion con el nombre ingresado
    vector<Libro> FiltrarPorAutor(string autor, vector<Libro> libros);

    //Metodo encargado de recibir los datos necesarios para generar/modificar los datos de un libro
    void ModificarDatos(string titulo, string autor[ARRMAX], string editorial, string modeloISBN, unsigned short year, unsigned short numEjemp);
    //Metodo encargado de manejar la consola para ingresar datos de un libro
    void ModificarDatos(bool mostrarDatosAnteriores);

    //Recibe la estructura del ISBN del tipo "XXX-XXX-XX-XXXX-X", retorna el ISBN generado aleatoriamente
    //Retornara un string vacio en caso de recibir un modelo ISBN no valido
    string GenerarISBN(string modelo);

    //Elimina el ejemplar indicado, y rota todos los ejemplares a su derecha en el arreglo
    void EliminarEjemplar(unsigned short index);    
};  

