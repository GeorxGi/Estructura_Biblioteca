#pragma once
#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <string>
#include <Windows.h>
#include <conio.h>
#include <iostream>

#include "Libro.h"
#include "Tesis.h"
#include "Estudiante.h"

#pragma region Colores
constexpr int Black = 0;
constexpr int Blue = 1;
constexpr int Green = 2;
constexpr int Aqua = 3;
constexpr int Red = 4;
constexpr int Purple = 5;
constexpr int Yellow = 6;
constexpr int White = 7;
constexpr int Gray = 8;
constexpr int LightBlue = 9;
constexpr int LightGreen = 10;
constexpr int LightAqua = 11;
constexpr int LightRed = 12;
constexpr int LightPurple = 13;
constexpr int LightYellow = 14;
constexpr int BrightWhite = 15;
#pragma endregion
//Segun documentacion, constexpr es una variable que se calcula en tiempo de compilacion y no ejecucion
//dando como resultado un mejor rendimiento, seguramente no afecte mucho, pero bueno, ahi esta

//Tamaño maximo para el arreglo de autores y algunos arreglos genericos
constexpr unsigned short ARREMAX = 5;

using namespace std;
//Muestra un mensaje en consola con el color ingresado
void ColorMsg(string mensaje, int color);

//Maneja la consola para seleccionar mediante las flechas un libro o tesis en base al titulo
//Retorna -1 en casos donde no se haya seleccionado un elemento
int Seleccion(vector<Libro> libros, vector<Tesis> tesis, bool esLibro);
//Maneja la consola para seleccionar el codigo ISBN del libro ingresado, retorna -1 en caso de cancelar o no ser posible
int SeleccionISBN(Libro lib);
//Maneja la consola para permitir el ingreso de seleccion Y/N y retorna la seleccion del usuario
bool SeleccionTrueFalse();
//Maneja la consola para seleccionar un ISBN del libro ingresado
int SeleccionISBN(Libro lib);

//Maneja la consola para solo permitir el ingreso de caracteres numericos, retornando un entero
int RetornarNumero();
//Retorna un booleano de acuerdo a si el caracter ingresado es numerico
bool EsNumero(char n);

//Maneja la consola para permitir al usuario elegir un modelo ISBN predefinido
string GenerarModeloISBN();

void MostrarVector(vector<Libro> libro);

void MostrarVector(vector<Tesis> tesis);

//Genera libros genericos para DEBUG
vector <Libro> CargarLibrosGenericos(vector <Libro> libross);
//Genera tesis genericas para DEBUG
vector<Tesis> CargarTesisGenerica(vector<Tesis> tesiss);

#endif


