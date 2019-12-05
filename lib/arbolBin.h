#ifndef ARBOL
#define ARBOL
#include <stdbool.h>
#include "libstruct.h"

typedef datos * tipoElementoArbolBin;
typedef struct celdaABin{
	 tipoElementoArbolBin * elem;
     bool isAlive;
     int pregunta;
     float umbral;
	 struct celdaABin *izda;
	 struct celdaABin *dcha;
 }celdaArbolBin; 
typedef celdaArbolBin *tipoArbolBin;

void nuevoArbolBin(tipoArbolBin *, datos *, int);

bool esVacio(tipoArbolBin);
#endif
