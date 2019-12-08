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
#include <string.h>
#include <fcntl.h>
#include "lib/libDecisionTree.h"
#include "lib/libstruct.h"

char * procesar(char * putoComa){ //Si se tiene una distribución en es-ES cambia la ',' por '.'
    for(int i=0; i<strlen(putoComa); i++){
        if(putoComa[i] == ',') putoComa[i] = '.';
    }
    return putoComa;
}

int main(int argc, char* argv[]){

    char ** headers;
	datos * vector_datos;
	datos * datos_ajuste;
	datos * datos_test;
    double errores_entMin_arboles[3][2] = {{0.0f}};

    if(argc < 2){
		printf("\033[31mNumero de argumentos invalido.\033[0m\n\n");
        printf("Necesita indicar fichero CSV de datos (en la carpeta ./csv tiene los datos de entrenamiento).\n");
		printf("También es posible añadir la entropía mínima o el máximo de hijos (profundidad).\n");
        printf("Si el tercer argumento es mayor o igual a 1 se asumirá que se desea podar por profundidad.\n");
        printf("En otro caso se utilizará el tercer argumento como entropía mínima para podar el árboln\n");
        printf("Si no se especifica un tercer argumento no se podará el árbol.\n"); 
		printf("Ejemplos:\n");
		printf("./decisionTree csv/problem_book.csv 4           |  Éste generará un árbol con profundidad máxima de 4 hijos\n");
		printf("./decisionTree csv/problem_book.csv 0.02547     |  Éste generará un árbol con entropía mínima de 0.02547\n");
		printf("./decisionTree csv/problem_book.csv             |  Éste generará un árbol sin podar\n"); 
		return EXIT_FAILURE;
	} else {
        int fd = open(argv[1],O_RDONLY, 0400);
        recogerDatos(&vector_datos,&datos_ajuste,&datos_test,&headers,fd);
	}

    int totalVivos = 0;
    for(int i=0; i<C_ENTRENO; i++){
        if(vector_datos[i].isAlive == 1)
            totalVivos++;
    }

    double corte = 0.0f; 
    if(argc > 2){
    char * corteConPosiblePunto = procesar(argv[2]); //Las distribucionoes en castellano usan ',' en vez de '.'  
    corte = strtod(corteConPosiblePunto, NULL);
    }
    int contMax = 0;    //maxima profundidad o número de hijos que tendrá el árbol
    double entMin = 0.0f;  // mínima entropía que tendran que tener los nodos para seguin creciendo el árbol
                    // también se utilizara para convertir en hoja si ninguna clase consigue mejor ganancia 
                    // que este dato
    if (corte >= 1.0f){ // significa que se cortará el árbol a partir de su profundidad
        printf("Asumiendo que quiere podar el árbol por \033[34mPROFUNDIDAD\033[0m\n");
        contMax = (int)corte;
    } else if(corte != 0.0f){            // significa que se cortará el árbol a partir de su entropua mínima
        printf("Asumiendo que quiere podar el árbol por \033[34mENTROPÍA MÍNIMA\033[0m\n");
        entMin = corte;
    } else
        printf("Asumiendo que no quiere podar el árbol\nSi quiere podarlo especifíquelo con el tercer argumento\n(número >= 1: Profundidad | múmero < 1: por entropía mínima\n\n)");
    tipoArbolBin arbolito;
    arbolito = NULL;
    
    printf("NÚMERO DE DATOS DE ENTRENAMIENTO = [%d]\n",C_ENTRENO);
    printf("NÚMERO DE DATOS DE AJUSTE = [%d]\n",C_AJUSTE);
    printf("NÚMERO DE DATOS DE TEST = [%d]\n",C_TEST);
    printf("Nota: si desea cambiar estos números, cambie las definiciones C_ENTRENO, C_AJUSTE y C_TEST en lib/libstruct.h\n");


    printf("\033[32mCreando árbol a partir de los datos...\033[0m\n");
    crearArbolDecision(&arbolito, vector_datos, headers, C_ENTRENO, entMin, 0, contMax);
    printf("\033[32mÁrbol creado\033[0m\n");
    errores_entMin_arboles[0][0] = (double)corte; 
    
    printf("DATOS DE ENTRENAMIENTO:\n");
    errores_entMin_arboles[0][1] = testData(vector_datos, arbolito, C_ENTRENO);
    errores_entMin_arboles[1][0] = (double)corte; 
    printf("DATOS DE AJUSTE:\n");
    errores_entMin_arboles[1][1] = testData(datos_ajuste, arbolito, C_AJUSTE);
    errores_entMin_arboles[2][0] = (double)corte; 
    printf("DATOS DE TEST:\n");
    errores_entMin_arboles[2][1] = testData(datos_test, arbolito, C_TEST);
    writeTreeCSV(errores_entMin_arboles);
    eliminarArbol(&arbolito);
    arbolito = NULL; 
}
