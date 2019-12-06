/*
 * =====================================================================================
 *
 *       Filename:  libDecisionTree.h
 *
 *    Description:  Librería para el arbol de decisión
 *
 *        Version:  1.0
 *        Created:  24/11/19
 *       Compiler:  gcc
 *
 *         Author:  Adrian Maiza, Beatriz Lago, Erick Martínez 
 *
 * =====================================================================================
 */
#include <stdbool.h>
#include "libstruct.h"
#include "pilaDeadAlive.h"
#include "arbolBin.h"

#define FUNCIONES_SELECCION_DE_CLASE(nombreDato, tipoDato)                                                          \
    void cuenta_vivos_muertos_clase_##nombreDato(datos vect[], int tamano, tipoDato umbral, cuenta_datos_clases * resultados); \



void print_data(datos * vector_datos, int);
float umbral(datos *, char*, int);
void recogerDatos(datos**,datos**,datos**,char **,int);
float entropia_umbral(tipoElementoPila);
float entropia_clases(cuenta_datos_clases);
void calculo_entropia_clases(datos *, float, float **);
int calculo_maxima_ganancia(float **);
void crearArbolDecision(tipoArbolBin *, datos *, int, double, int, int);
bool asignarIsAlive(datos, tipoArbolBin);
double testData(datos *, tipoArbolBin, int);
void writeTreeCSV(double[3][2]);

FUNCIONES_SELECCION_DE_CLASE(male, bool);
FUNCIONES_SELECCION_DE_CLASE(book1, bool);
FUNCIONES_SELECCION_DE_CLASE(book2, bool);
FUNCIONES_SELECCION_DE_CLASE(book3, bool);
FUNCIONES_SELECCION_DE_CLASE(book4, bool);
FUNCIONES_SELECCION_DE_CLASE(book5, bool);
FUNCIONES_SELECCION_DE_CLASE(isMarried, bool);
FUNCIONES_SELECCION_DE_CLASE(isNoble, bool);
FUNCIONES_SELECCION_DE_CLASE(numDeadRelations, int);
FUNCIONES_SELECCION_DE_CLASE(popularity, float);
