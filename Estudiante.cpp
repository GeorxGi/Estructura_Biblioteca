#include "Estudiante.h"

using namespace std;
#pragma region Constructor
Estudiante::Estudiante(bool GenerarVacia) {
	string nombre = "", cedula = "";
	fflush(stdin);
	if (!GenerarVacia) {
		do {
			cout << "Ingrese el nombre del estudiante: ";
			getline(cin, nombre);
		} while (nombre.empty());

		do {
			cout << "Ingrese la cedula del estudiante: ";
			cedula = "V" + to_string(RetornarNumero());
		} while (!ValidarCedula(cedula));
		m_Nombre = nombre; m_CI = cedula;
	}
}
#pragma endregion

#pragma region MetodosEstudiante
//Metodo encargado de todo el proceso de realizar un prestamo al estudiante
bool Estudiante::RealizarPrestamo(vector<Libro> libros, vector<Estudiante> estudiant) {
	short numPrest;
	bool libroYaPrestado;
	Estudiante stud = Estudiante(true);
	//Vector de tesis generico, necesario para llamar al metodo seleccion
	vector<Tesis> tes;

	do {
		cout << "Cuantos libros desea llevar como prestamo? (1 - 3)";
		numPrest = RetornarNumero();
	} while (numPrest < 1 || numPrest > 3);

	//Recorre para cada libro que se va a prestar
	for (short i = 0; i < numPrest; i++) {
		//Selecciona el indice del libro a prestar
		libroPrest[i].indiceLibro = Seleccion(libros, tes, true);

		if (libroPrest[i].indiceLibro == -1) {
			numPrest--;
		}
		else{
			libroYaPrestado = false;
			//Selecciona el indice del ejemplar a prestar
			libroPrest[i].indiceISBN = SeleccionISBN(libros.at(libroPrest[i].indiceLibro));

			//Recorre todos los libros ya prestados para verificar que no se presten dos veces el mismo libro
			for (unsigned short m = 0; m < i; m++) {
				if (libroPrest[m].indiceLibro == libroPrest[i].indiceLibro && libroPrest[m].indiceISBN == libroPrest[i].indiceISBN) {
					libroYaPrestado = true;
				}
			}

			if (libroPrest[i].indiceISBN == -1) {
				numPrest--;
			}
			else{
				//Ciclo entre todos los estudiantes cargados en memoria
				for (unsigned short j = 0; j < estudiant.size(); j++) {
					stud = estudiant.at(j);
					//Valida que el estudiante en memoria no sea el mismo que se esta manejando
					if (stud.ObtenerNombre() != ObtenerNombre()) {

						//Ciclo entre los libros que posee el estudiante del vector
						for (unsigned short k = 0; k < stud.ObtenerLibrosPrestados(); k++) {
							//Compara que el libro e ISBN sean iguales, en dado caso, el libro ya esta prestado
							if (stud.libroPrest[k].indiceLibro == libroPrest[i].indiceLibro && stud.libroPrest[k].indiceISBN == libroPrest[i].indiceISBN) {
								libroYaPrestado = true;
							}
						}
					}
				}
				if (libroYaPrestado) {
					ColorMsg("\nEl libro indicado ya ha sido prestado, intente nuevamente\n", LightRed);
					i--;
					system("pause");
				}
				else ColorMsg("\nLibro prestado correctamente\n", LightGreen);
			}
		}
	}
	m_LibrosPrestados = numPrest;
	if (numPrest != 0) {
		ColorMsg("\nPrestamos realizado exitosamente!", LightGreen);
	}
	else {
		ColorMsg("\nNo se realizo ningun prestamo, se descartara la informacion", LightYellow);
	}
	cout << endl;
	return numPrest != 0;
}

//Recibe la cadena de la cedula del estudiante y retorna un booleano si esta es una cedula relativamente valida
bool Estudiante::ValidarCedula(string ced) { return ced.size() > 1 && ced[1] != '0'; }
#pragma endregion

#pragma region RetornoDeDatos
//Retorna el nombre del estudiante
string Estudiante::ObtenerNombre() const{ return m_Nombre; }
//Retorna la cedula del estudiante
string Estudiante::obtenerCedula() const{ return m_CI; }
//Retorna la cantidad de libros que posee prestados el estudiante
unsigned short Estudiante::ObtenerLibrosPrestados() const{ return m_LibrosPrestados; }

//Retorna el indice en memoria del libro, en base al indice de la estructura
unsigned short Estudiante::ObtenerIndiceLibro(unsigned short index) const { return libroPrest[index].indiceLibro; }
//Retorna el indice en memoria del ISBN del libro, en base al indice de la estructura
unsigned short Estudiante::ObtenerIndiceISBN(unsigned short index) const { return libroPrest[index].indiceISBN; }
#pragma endregion

#pragma region MetodosInternos
//Recibe la lista de estudiantes cargados, y retorna si la cedula ingresada este repetida
bool ValidarEstudianteRepetido(Estudiante stud, vector<Estudiante> std) {
	Estudiante auxStd = Estudiante(true);

	for (unsigned short i = 0; i < std.size(); i++) {
		auxStd = std.at(i);
		if (stud.obtenerCedula() == auxStd.obtenerCedula()) return true;
	} return false;
}

//Maneja la consola para seleccionar un estudiante en base a su nombre
//Retorna -1 en caso de cancelar el proceso
int SeleccionarEstudiante(vector<Estudiante> estd) {
	char opt = ' ';
	int index = 0;
		if (estd.size() == 0) {
			ColorMsg("No se han podido encontrar prestamos registrados\n", LightRed);
			return -1;
		}
		else {
			Estudiante std = Estudiante(true);
			do {
				std = estd.at(index);
				cout << "\x1b[2K\r";
				ColorMsg("Nombre del estudiante: ", LightYellow); cout << std.ObtenerNombre() << endl;
				ColorMsg("Cedula del estudiante: ", LightYellow); cout << std.obtenerCedula() << "\x1b[A\r";
				opt = _getch();
				switch (opt) {
					//Up arrow
				case 72:
					if (++index > estd.size() - 1) index = 0;
					break;
					//Down arrow
				case 80:
					if (--index < 0) index = estd.size() - 1;
					break;
				case 27:
					return -1;
					break;
				}
				//enter
			} while (opt != 13);
		}
		cout << endl << endl;
		return index;
}

//Imprime en consola los datos relacionados a todos los prestamos cargados en memoria
void MostrarPrestamos(vector<Estudiante> estd, vector<Libro> libros) {
	ColorMsg("\n----------------------------------------------------------\n", LightYellow);
	int color = Green;
	Estudiante est = Estudiante(true);
	Libro lib = Libro(true);
	for (unsigned short i = 0; i < estd.size(); i++) {
		est = estd.at(i);

		ColorMsg("NOMBRE: ", color); cout << est.ObtenerNombre() << endl;

		ColorMsg("CEDULA: ", color); cout << est.obtenerCedula() << endl;

		ColorMsg("LIBROS PRESTADOS:\n", LightYellow);
		for (unsigned short j = 0; j < est.ObtenerLibrosPrestados(); j++) {
			lib = libros.at(est.ObtenerIndiceLibro(j));
			ColorMsg("TITULO: ", color); cout << lib.ObtenerTitulo() << endl;
			ColorMsg("#" + to_string(j + 1) + ": ", LightGreen);
			cout << lib.ObtenerISBN(est.ObtenerIndiceISBN(j)) << endl;
		}

		ColorMsg("\n----------------------------------------------------------\n", LightYellow);
	}
}
#pragma endregion