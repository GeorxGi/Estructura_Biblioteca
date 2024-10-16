#include "Funciones.h"
using namespace std;

//Muestra un mensaje en consola con el color ingresado
void ColorMsg(string mensaje, int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << mensaje;
	SetConsoleTextAttribute(hConsole, 7);
}

//Maneja la consola para seleccionar mediante las flechas un libro o tesis en base al titulo
//Retorna -1 en casos donde no se haya seleccionado un elemento
int Seleccion(vector<Libro> libros, vector<Tesis> tesis, bool esLibro) {
	char opt = ' ';
	int index = 0;
	if (esLibro) {
		if (libros.size() == 0) {
			ColorMsg("Aun no hay libros cargados\n", LightRed);
			return -1;
		}
		else {
			Libro lib = Libro(true);
			do {
				lib = libros.at(index);
				cout << "\x1b[2K\r";
				ColorMsg("TITULO: ", LightYellow); cout << lib.ObtenerTitulo();
				opt = _getch();
				switch (opt) {
					//Up arrow
				case 72:
					if (++index > libros.size() - 1) index = 0;
					break;
					//Down arrow
				case 80:
					if (--index < 0) index = libros.size() - 1;
					break;
				case 27:
					return -1;
					break;
				}
				//enter
			} while (opt != 13);
		}
	}
	else {
		if (tesis.size() == 0) {
			ColorMsg("Aun no hay tesis cargadas\n", LightRed);
			return -1;
		}
		else {
			Tesis tes = Tesis(true);
			do {
				tes = tesis.at(index);
				cout << "\x1b[2K" << "\r";
				ColorMsg("TITULO: ", LightYellow); cout << tes.ObtenerTitulo();
				opt = _getch();
				switch (opt) {
				case 72:
					if (++index > tesis.size() - 1) index = 0;
					break;
				case 80:
					if (--index < 0) index = tesis.size() - 1;
					break;
				case 27:
					return -1;
					break;
				}
			} while (opt != 13);
		}
	}
	cout << endl; return index;
}
//Maneja la consola para seleccionar el codigo ISBN del libro ingresado, retorna -1 en caso de cancelar o no ser posible
int SeleccionISBN(Libro lib) {
	char opt = ' ';
	short index = 0;
	if (lib.ObtenerEjemplares() != 0) {
		do {
			cout << "\x1b[2K\r";
			cout << "#" << index + 1 << ": ";
			ColorMsg("ISBN: ", LightYellow); cout << lib.ObtenerISBN(index);
			opt = _getch();
			switch (opt) {
			case 72:
				if (++index > lib.ObtenerEjemplares() - 1) index = 0;
				break;
			case 80:
				if (--index < 0) index = lib.ObtenerEjemplares() - 1;
				break;
			case 27:
				return -1;
				break;
			}
		} while (opt != 13);
		fflush(stdin);
		return index;
	}
	else {
		ColorMsg("No hay ejemplares disponibles", LightRed);
		fflush(stdin);
		return -1;
	}
}
//Maneja la consola para permitir el ingreso de seleccion Y/N y retorna la seleccion del usuario
bool SeleccionTrueFalse() {
	char opt;
	do {
		cout << "\x1b[2K" << "\r" << "[Y/N]:";
		opt = _getch();
		if (opt == 'Y' || opt == 'y') return true;
	} while (opt != 'N' && opt != 'n' && opt != 27);
	return false;
}

//Maneja la consola para solo permitir el ingreso de caracteres numericos, retornando un entero
//Retorna -1 en caso de que no se ingrese ningun numero
int RetornarNumero() {
	char key;
	string aux = "";
	cout << endl;
	do {
		key = _getch();
		if (key >= '0' && key <= '9') {
			aux += key;
			cout << key;
		}
		else if (key == 8 && !aux.empty()) {
			aux.erase(aux.end() - 1);
			cout << "\x1b[2K" << "\r" << aux;
		}
	} while (key != 13);
	cout << endl;
	if (aux.empty()) return -1;
	return stoi(aux);
}
//Retorna un booleano de acuerdo a si el caracter ingresado es numerico
bool EsNumero(char n) { return n >= '0' && n <= '9'; }

//Maneja la consola para permitir al usuario elegir un modelo ISBN predefinido
string GenerarModeloISBN() {
	string models[5] = { "978-XXX-XXX-XXXX", "978-XX-XXXX-XXX-X", "978-XXX-XX-XXX-XX", "978-XXXXX-X-XXX-X", "978-XXXX-XX-XX-XX" };
	short index = 0;
	char opt;
	cout << "Seleccione un modelo con el cual generar el ISBN de los ejemplares ";
	ColorMsg("(Utilice las flechas para alternar)\n", LightAqua);
	do {
		cout << "\x1b[2K" << "\r" << "Opcion " << index + 1 << ": " << models[index];
		opt = _getch();
		switch (opt) {
			//Up Arrow
		case 72:
			if (++index > 4) index = 0;
			break;
			//Down Arrow
		case 80:
			if (--index < 0) index = 4;
			break;
		}
		//Enter
	} while (opt != 13);

	return models[index];
}

void MostrarVector(vector<Libro> libro) {
	ColorMsg("\n----------------------------------------------------------\n", LightYellow);
	int color = Green;
	Libro lib = Libro(true);
	for (unsigned short i = 0; i < libro.size(); i++) {
		lib = libro.at(i);

		ColorMsg("TITULO: ", color); cout << lib.ObtenerTitulo() << endl;

		ColorMsg("AUTORES:\n", color);
		for (unsigned short j = 0; j < ARREMAX; j++) {
			if (lib.ObtenerAutor(j).size() != 0) cout << lib.ObtenerAutor(j) << endl;
		}

		ColorMsg("EDITORIAL: ", color); cout << lib.ObtenerEditorial() << endl;

		ColorMsg("ANO DE PUBLICACION: ", color); cout << lib.ObtenerYear() << endl;

		ColorMsg("EJEMPLARES DISPONIBLES: ", color); cout << lib.ObtenerEjemplares() << endl;

		ColorMsg("ISBN por ejemplares:\n", color);

		for (unsigned short j = 0; j < lib.ObtenerEjemplares(); j++) {
			ColorMsg("#", LightBlue);
			cout << j + 1 << ": " << lib.ObtenerISBN(j) << endl;
		}

		ColorMsg("\n----------------------------------------------------------\n", LightYellow);
	}
}

void MostrarVector(vector<Tesis> tesis) {
	ColorMsg("\n----------------------------------------------------------\n", LightYellow);
	Tesis tes = Tesis(true);
	int color = Green;
	for (unsigned short i = 0; i < tesis.size(); i++) {
		tes = tesis.at(i);

		ColorMsg("TITULO: ", color); cout << tes.ObtenerTitulo() << endl;

		ColorMsg("AUTORES:\n", color);
		for (unsigned short j = 0; j < ARREMAX; j++) {
			if (tes.ObtenerAutor(j).size() != 0) cout << tes.ObtenerAutor(j) << endl;
		}

		ColorMsg("ASESOR:\n", color); cout << tes.ObtenerAsesor() << endl;

		ColorMsg("ANO DE PUBLICACION: ", color); cout << tes.ObtenerYear() << endl;

		ColorMsg("CARRERA: ", color); cout << tes.ObtenerCarrera() << endl;

		ColorMsg("EJEMPLARES DISPONIBLES: ", color); cout << tes.ObtenerEjemplares() << endl;

		ColorMsg("\n----------------------------------------------------------\n", LightYellow);
	}
}

//Genera libros genericos para DEBUG
vector <Libro> CargarLibrosGenericos(vector <Libro> libross) {
	vector <Libro> libros;
	if (libross.size() == 0) {
		string autor[ARREMAX] = { "Marta Rodriguez", "Luis Fernandez", "Elena Garcia", "Ricardo Perez", "Julia Torres" };
		Libro lib = Libro("La aventura del saber", autor, "Ediciones Sabiduria", "978-XXX-XXX-XXXX", 2015, 5);
		libros.push_back(lib);

		autor[0] = "Andres Silva"; autor[1] = "Carolina Herrera"; autor[2] = ""; autor[3] = ""; autor[4] = "";
		lib.ModificarDatos("Cocinando con amor", autor, "Cocina para Todos", "978-X-XXX-XXXX-XX", 2018, 8);
		libros.push_back(lib);

		autor[0] = "Andrea Ramirez"; autor[1] = "Gabriel Ortiz"; autor[2] = "Valeria mena"; autor[3] = ""; autor[4] = "";
		lib.ModificarDatos("Historias del mas alla", autor, "Editorial Misterio", "978-XX-X-XXXXX-XX", 2021, 2);
		libros.push_back(lib);

		ColorMsg("Libros genericos generados exitosamente!\n", LightGreen);
		return libros;
	}
	else {
		ColorMsg("Ya existen libros cargados en memoria.\n", LightRed);
		ColorMsg("Solo se pueden generar datos genericos si no hay datos cargados en memoria\n", LightYellow);
		return libross;
	}
}
//Genera tesis genericas para DEBUG
vector<Tesis> CargarTesisGenerica(vector<Tesis> tesiss) {
	vector<Tesis> tesis;
	if (tesiss.size() == 0) {
		string autor[ARREMAX];

		autor[0] = "Lorena Sanchez"; autor[1] = "Gustavo Diaz"; autor[2] = "Natalia Reyez"; autor[3] = "Enrique Gomez"; autor[4] = "Sofia Blanco";
		Tesis tes = Tesis("Desarrollo Sostenible en Zonas Rurales", autor, "Dr. Fernando Castillo", "Ingenieria Ambiental", 2022, 3);
		tesis.push_back(tes);

		autor[0] = "Maria Lopez"; autor[1] = "Jose Fernandez"; autor[2] = "Clara Gomez"; autor[3] = ""; autor[4] = "";
		tes.ModificarDatos("Implementacion de IA en Medicina", autor, "Dra. Laura Vega", "Ingenieria Biomedica", (USHORT)2023, (USHORT)6);
		tesis.push_back(tes);


		autor[0] = "Diego Perez"; autor[1] = "Lucia Gonzales"; autor[2] = "Miguel Castro"; autor[3] = "Sandra Torres"; autor[4] = "";
		tes.ModificarDatos("Analisis de Energias Renovables", autor, "Dr. Luis Hernandez", "Ingenieria Electrica", 2021, 1);
		tesis.push_back(tes);
		ColorMsg("Tesis genericas generados exitosamente!\n", LightGreen);
		return tesis;
	}
	else
	{
		ColorMsg("Ya existen tesis cargadas en memoria.\n", LightRed);
		ColorMsg("Solo se pueden generar datos genericos si no hay datos cargados en memoria\n", LightYellow);
		return tesiss;
	}
}
