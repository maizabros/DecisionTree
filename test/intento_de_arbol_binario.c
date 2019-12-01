#include <stdio.h>
#include <stdlib.h>
#include "arbolBin.h"



bool esVacio(tipoArbolBin a){
	return a == NULL;
}

void nuevoArbolBin(tipoArbolBin *a){
	*a = NULL;
}

void errorArbolBin(char s[]){
	printf("\nError en el árbol binario: %s\n", s);
}

tipoArbolBin construir(tipoElementoArbolBin e, tipoArbolBin i, tipoArbolBin d){
	tipoArbolBin nuevo;
	nuevo = (celdaArbolBin*)malloc(sizeof(celdaArbolBin));
	nuevo->elem = e;
	nuevo->izda = i;
	nuevo->dcha = d;
	return nuevo;
}

void insertar(tipoArbolBin * a, tipoElementoArbolBin e, int tamano){
	///printf("	He entrado en la función\n");
	if (esVacio(*a)){
		///printf("		Voy a hacer un nodo nuevo\n");
		celdaArbolBin * nuevo;
		nuevo = (celdaArbolBin*)malloc(sizeof(celdaArbolBin));
		nuevo->elem = (datos *)malloc(sizeof(datos) * tamano); 
		for (int i = 0; i < tamano; i++){
			///printf("			Estoy metiendo el elemento\n");
			nuevo->elem[i] = e[i];
			///printf("			El elemento %d es: %f\n",i, nuevo->elem[i].popularity);
		}
		nuevo->izda = NULL;
		nuevo->dcha = NULL;
		*a = nuevo;
	}
	else{
		/**
		 * Y aquí entiendo que habría que volver a calcular el umbral o lo que toque,
		 * separar el vector en dos de nuevo y llamar con un vector al hijo izquierdo o
		 * al hijo derecho?? no lo tengo claro :(
		 */ 
	}

}


tipoElementoArbolBin devolverRaiz(tipoArbolBin a){
	return a->elem;
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
