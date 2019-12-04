/*
 * =====================================================================================
 *
 *       Filename:  decisionTree.c
 *
 *    Description:  Arbol de decisión para ver si un personaje literario está
 *                  vivo o muerto.
 *
 *        Version:  1.0
 *        Created:  24/11/19 18:02:19
 *       Revision:  8/12/19 
 *       Compiler:  gcc
 *
 *         Authors: Adrian Maiza, Bea Lago y Erick Martínez 
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "lib/libDecisionTree.h"
//#include "lib/arbolBin.h"

#define BUFF 1024
#define NUM 1557

int main(int argc, char* argv[]){

    char * headers;
	datos * vector_datos;
	datos * datos_a_comprobar;
    if(argc < 2){
		printf("Numero de argumentos invalido.\nNecesita indicar fichero CSV de datos.\n");
		return EXIT_FAILURE;
	} else {
        int fd = open(argv[1],O_RDONLY, 0400);
        recogerDatos(&vector_datos,&datos_a_comprobar,&headers,fd);
	}

    int totalVivos = 0;
    for(int i=0; i<NUM; i++){
        if(vector_datos[i].isAlive == 1)
            totalVivos++;
    }

    tipoArbolBin arbolito;
    arbolito = NULL;
    
    printf("VAMOS A PLANTAR UN ARBOL (*w*)\n");
    printf("TAMAÑO = [%d]\n",NUM);
    crearArbolDecision(&arbolito, vector_datos, NUM);
    printf("HEMOS PLANTADO UN ARBOL (*w*)\n");
    testData(vector_datos, arbolito);
    
    
}
