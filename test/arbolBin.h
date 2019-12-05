#include <stdbool.h>
#include "libstruct.h"

typedef datos * tipoElementoArbolBin;
typedef struct celdaABin{
	 tipoElementoArbolBin elem;
	 struct celdaABin *izda;
	 struct celdaABin *dcha;
 }celdaArbolBin; 
typedef celdaArbolBin *tipoArbolBin;

void nuevoArbolBin(tipoArbolBin *);

void errorArbolBin(char s[]);

tipoElementoArbolBin devolverRaiz(tipoArbolBin);
/*
void preorden(tipoArbolBin);

void inorden(tipoArbolBin);

void postorden(tipoArbolBin);

bool esVacio(tipoArbolBin);
*/
//void insertar(tipoArbolBin *, tipoElementoArbolBin, int);
