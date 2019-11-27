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

#define BUFF 1024
#define N 1557

int main(int argc, char* argv[]){

    char * headers;
	datos * vector_datos;
	int total_Vivos = 0;
    if(argc < 2){
		printf("Numero de argumentos invalido.\nNecesita indicar fichero CSV de datos.\n");
		return EXIT_FAILURE;
	} else {
        int fd = open(argv[1],O_RDONLY, 0400);
        recogerDatos(&vector_datos,&headers,fd);
	}
	
	for(int j=0; j<N; j++){
		if(vector_datos[j].isAlive==1) total_Vivos++;
	}
	
    int umb_numDead =(int)umbral(vector_datos,"numDeadRelations",total_Vivos);
    double umb_pop = umbral(vector_datos,"popularity",total_Vivos);
    printf("UMBRALES:\n    popularity: %lf\n    numDeadRelations: %d\n",umb_pop,umb_numDead);
}
