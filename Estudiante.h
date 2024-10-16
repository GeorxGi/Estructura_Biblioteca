#pragma once
#include <string>
#include "Funciones.h"
#include "Libro.h"

using namespace std;

struct LibroPrestado
{
	short indiceLibro = 0, indiceISBN = 0;
};

class Estudiante
{
private:
	string m_Nombre, m_CI;
	unsigned short m_LibrosPrestados = 0;
	LibroPrestado libroPrest[3];
	
public:
	Estudiante(bool GenerarVacia);
	bool RealizarPrestamo(vector<Libro> libros, vector<Estudiante> estudiant);
	//Recibe la cadena de la cedula del estudiante y retorna un booleano si esta es una cedula relativamente valida
	bool ValidarCedula(string ced);

	string ObtenerNombre() const;
	string obtenerCedula() const;
	unsigned short ObtenerLibrosPrestados() const;
	//Retorna el indice en memoria del libro, en base al indice de la estructura
	unsigned short ObtenerIndiceLibro(unsigned short index) const;
	//Retorna el indice en memoria del ISBN del libro, en base al indice de la estructura
	unsigned short ObtenerIndiceISBN(unsigned short index) const;
};

//Recibe la lista de estudiantes cargados, y retorna si la cedula ingresada este repetida
bool ValidarEstudianteRepetido(Estudiante stud, vector<Estudiante> std);

//Maneja la consola para seleccionar un estudiante en base a su nombre
//Retorna -1 en caso de cancelar el proceso
int SeleccionarEstudiante(vector<Estudiante> estd);

//Imprime en consola los datos relacionados a todos los prestamos cargados en memoria
void MostrarPrestamos(vector<Estudiante> estd, vector<Libro> libros);