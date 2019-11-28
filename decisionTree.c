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
    printf("UMBRALES:\n    popularity: %f\n    numDeadRelations: %d\n",umb_pop,umb_numDead);

    printf("DATOS POR CLASE:\n");
    
    cuenta_datos_clases res;
    cuenta_vivos_muertos_clase_male(vector_datos, 1, &res); 
    printf("    Male:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book1(vector_datos, 1, &res); 
    printf("    Book1:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book2(vector_datos, 1, &res); 
    printf("    Book2:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book3(vector_datos, 1, &res); 
    printf("    Book3:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book4(vector_datos, 1, &res); 
    printf("    Book4:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book5(vector_datos, 1, &res); 
    printf("    Book5:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_isMarried(vector_datos, 1, &res); 
    printf("    isMarried:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_isNoble(vector_datos, 1, &res); 
    printf("    isNoble:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_numDeadRelations(vector_datos, umb_numDead, &res); 
    printf("    NumDeadRelations:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_popularity(vector_datos, umb_pop, &res); 
    printf("    Popularity:\n");
    printf("        SI_Vivos: %d\n      SI_Muertos: %d\n        NO_Vivos: %d\n      NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
}
