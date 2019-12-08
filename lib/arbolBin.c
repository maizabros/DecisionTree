#include <stdio.h>
#include <stdlib.h>
#include "arbolBin.h"

bool esVacio(tipoArbolBin a){
	return a == NULL;
}

void nuevoArbolBin(tipoArbolBin *a, datos * e, int tamano){
    *a = (celdaArbolBin *)malloc(sizeof(celdaArbolBin));
    if(tamano > 0){
        (*a)->elem = (datos **)malloc(sizeof(datos *));
        (*(*a)->elem) = (datos *)malloc(sizeof(datos)*tamano);
        *(*a)->elem = e;
    }
    (*a)->umbral = -1.0f;
    (*a)->pregunta = -1;
    (*a)->izda = NULL;
    (*a)->dcha = NULL;
}
