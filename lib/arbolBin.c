#include <stdio.h>
#include <stdlib.h>
#include "arbolBin.h"

bool esVacio(tipoArbolBin a){
	return a == NULL;
}

void nuevoArbolBin(tipoArbolBin *a, datos * e, int tamano){
    *a = (celdaArbolBin *)malloc(sizeof(celdaArbolBin));
    (*a)->elem = (datos **)malloc(sizeof(datos *));
    (*(*a)->elem) = (datos *)malloc(sizeof(datos)*11);
    //for(int i=0; i<tamano; i++){
    if (e != NULL)
        *(*a)->elem = e;
        //(*a)->elem[i] = (datos *)malloc(sizeof(datos));
    //}
    (*a)->pregunta = -1;
    (*a)->izda = NULL;
    (*a)->dcha = NULL;
}

void errorArbolBin(char s[]){
	printf("\nError en el árbol binario: %s\n", s);
}



tipoElementoArbolBin devolverRaiz(tipoArbolBin a){
	return *a->elem;
}
/*
void preorden(tipoArbolBin a){
	tipoElementoArbolBin e;
	if (esVacio(a)){
		return;
	}
	else{
		e = devolverRaiz(a);
		printf("%d ", e);
		preorden(a->izda);
		preorden(a->dcha);
	}
}

void inorden(tipoArbolBin a){
	tipoElementoArbolBin e;
	if (esVacio(a)){
		return;
	}
	else{
		inorden(a->izda);
		e = devolverRaiz(a);
		printf("%d ", e);
		inorden(a->dcha);
	}
}

void postorden(tipoArbolBin a){
	tipoElementoArbolBin e;
	if (esVacio(a)){
		return;
	}
	else{
		postorden(a->izda);
		postorden(a->dcha);
		e = devolverRaiz(a);
		printf("%d ", e);
	}
}
*/
