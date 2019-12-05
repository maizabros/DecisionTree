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
 *        Updated:  5/12/19 19:04:52
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
#define NUM 1362 

int main(int argc, char* argv[]){

    char * headers;
	datos * vector_datos;
	datos * datos_ajuste;
	datos * datos_test;
    double errores_minEnt_arboles[4][2] = {{0.0f}};

    if(argc < 2){
		printf("Numero de argumentos invalido.\nNecesita indicar fichero CSV de datos.\n");
		return EXIT_FAILURE;
	} else {
        int fd = open(argv[1],O_RDONLY, 0400);
        recogerDatos(&vector_datos,&datos_ajuste,&datos_test,&headers,fd);
	}

    int totalVivos = 0;
    for(int i=0; i<NUM; i++){
        if(vector_datos[i].isAlive == 1)
            totalVivos++;
    }

    double minEnt;
    tipoArbolBin arbolito;
    arbolito = NULL;
    printf("\033[32mVAMOS A PLANTAR UNA ARBOLEDA ~(*w*)~\033[0m\n");
    
    printf("\033[34mVAMOS A PLANTAR UN ARBOL (*w*)\033[0m\n");
    printf("TAMAÑO = [%d]\n",NUM);

    minEnt = 0.01f;
    crearArbolDecision(&arbolito, vector_datos, NUM, minEnt);
    printf("\033[34mHEMOS PLANTADO UN ARBOL (*w*)\033[0m\n\n");
    errores_minEnt_arboles[0][0] = minEnt; 
    errores_minEnt_arboles[0][1] = testData(vector_datos, arbolito, 1362);
    errores_minEnt_arboles[1][0] = minEnt; 
    errores_minEnt_arboles[1][1] = testData(datos_ajuste, arbolito, 292);
    errores_minEnt_arboles[2][0] = minEnt; 
    errores_minEnt_arboles[2][1] = testData(datos_test, arbolito, 292);
    writeTreeCSV(errores_minEnt_arboles);
    arbolito = NULL; 

    minEnt = 0.001f;
    printf("\033[34mVAMOS A PLANTAR UN ARBOL (*w*)\033[0m\n");
    crearArbolDecision(&arbolito, vector_datos, NUM, minEnt);
    printf("\033[34mHEMOS PLANTADO UN ARBOL (*w*)\033[0m\n\n");
    errores_minEnt_arboles[0][0] = minEnt; 
    errores_minEnt_arboles[0][1] = testData(vector_datos, arbolito, 1362);
    errores_minEnt_arboles[1][0] = minEnt; 
    errores_minEnt_arboles[1][1] = testData(datos_ajuste, arbolito, 292);
    errores_minEnt_arboles[2][0] = minEnt; 
    errores_minEnt_arboles[2][1] = testData(datos_test, arbolito, 292);
    writeTreeCSV(errores_minEnt_arboles);
    arbolito = NULL; 

    minEnt = 0.0001f;
    printf("\033[34mVAMOS A PLANTAR UN ARBOL (*w*)\033[0m\n");
    crearArbolDecision(&arbolito, vector_datos, NUM, minEnt);
    printf("\033[34mHEMOS PLANTADO UN ARBOL (*w*)\033[0m\n\n");
    errores_minEnt_arboles[0][0] = minEnt; 
    errores_minEnt_arboles[0][1] = testData(vector_datos, arbolito, 1362);
    errores_minEnt_arboles[1][0] = minEnt; 
    errores_minEnt_arboles[1][1] = testData(datos_ajuste, arbolito, 292);
    errores_minEnt_arboles[2][0] = minEnt; 
    errores_minEnt_arboles[2][1] = testData(datos_test, arbolito, 292);
    writeTreeCSV(errores_minEnt_arboles);
    arbolito = NULL; 

    minEnt = 0.00001f;
    printf("\033[34mVAMOS A PLANTAR UN ARBOL (*w*)\033[0m\n");
    crearArbolDecision(&arbolito, vector_datos, NUM, minEnt);
    printf("\033[34mHEMOS PLANTADO UN ARBOL (*w*)\033[0m\n\n");
    errores_minEnt_arboles[0][0] = minEnt; 
    errores_minEnt_arboles[0][1] = testData(vector_datos, arbolito, 1362);
    errores_minEnt_arboles[1][0] = minEnt; 
    errores_minEnt_arboles[1][1] = testData(datos_ajuste, arbolito, 292);
    errores_minEnt_arboles[2][0] = minEnt; 
    errores_minEnt_arboles[2][1] = testData(datos_test, arbolito, 292);
    writeTreeCSV(errores_minEnt_arboles);
    arbolito = NULL; 

    printf("\033[32mHEMOS PLANTADO UNA ARBOLEDA ~(*w*)~\033[0m\n");
}
