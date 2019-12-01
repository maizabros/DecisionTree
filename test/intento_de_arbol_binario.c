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


int calculo_minima_entropia(float ** entropias_clases){
	float min_entropia = 1.0;
    int clase_seleccionada = -1;
    printf("DATOS POR CLASE:\n");
    for(int i = 0; i<10; i++){
        printf("CLASE %d: [%f]\n",i+1,entropias_clases[i][0]);
        if(min_entropia > entropias_clases[i][0]){
            clase_seleccionada = i;
            min_entropia = entropias_clases[i][0];
        }
    }
	return clase_seleccionada;
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
