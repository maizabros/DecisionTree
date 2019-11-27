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

double umbral(datos *, char*, int);
void recogerDatos(datos**,char **,int);
double entropia_umbral(tipoElementoPila);
double entropia_clases(int clase_si, int clase_no, int clase_si_vivos, int clase_si_muertos, int clase_no_vivos, int clase_no_muertos);
