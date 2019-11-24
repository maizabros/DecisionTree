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

#define C_ENTRENO 11
#define N 11 
#define BUFF 1024

int main(int argc, char* argv[]){

    char * headers;
	datos * vector_datos;
    if(argc < 2){
		printf("Numero de argumentos invalido.\nNecesita indicar fichero CSV de datos.\n");
		return EXIT_FAILURE;
	} else {
        int fd = open(argv[1],O_RDONLY, 0400);
        recogerDatos(&vector_datos,&headers,fd);
	}

    int umb_numDead =(int)umbral(vector_datos,"numDeadRelations");
    float umb_pop = umbral(vector_datos,"popularity");
    printf("UMBRALES:\n     popularity: %f\nnumDeadRelations: %d\n",umb_pop,umb_numDead);
}
