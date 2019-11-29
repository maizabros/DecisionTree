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

    int totalVivos = 0;
    for(int i=0; i<N; i++){
        if(vector_datos[i].isAlive == 1)
            totalVivos++;
    }
    //int umb_numDead =(int)umbral(vector_datos,"numDeadRelations",totalVivos);
    //float umb_pop = umbral(vector_datos,"popularity",totalVivos);
    //printf("UMBRALES:\n    popularity: %f\n    numDeadRelations: %d\n",umb_pop,umb_numDead);
    
    float * entropias_clases;

    calculo_entropia_clases(vector_datos, (float) totalVivos, &entropias_clases);

    float min_entropia = 1.0;
    int clase_seleccionada = -1;
    printf("DATOS POR CLASE:\n");
    for(int i = 0; i<10; i++){
        printf("CLASE %d: [%f]\n",i+1,entropias_clases[i]);
        if(min_entropia > entropias_clases[i]){
            clase_seleccionada = i;
            min_entropia = entropias_clases[i];
        }
    }

    printf("·· SELECCIONADA CLASE");
    switch(clase_seleccionada){
        case 0:
            printf("\033[31m male\033[0m\n");
            break;
        case 1:
            printf("\033[31m book1\033[0m\n");
            break;
        case 2:
            printf("\033[31m book2\033[0m\n");
            break;
        case 3:
            printf("\033[31m book3\033[0m\n");
            break;
        case 4:
            printf("\033[31m book4\033[0m\n");
            break;
        case 5:
            printf("\033[31m book5\033[0m\n");
            break;
        case 6:
            printf("\033[31m isMarried\033[0m\n");
            break;
        case 7:
            printf("\033[31m isNoble\033[0m\n");
            break;
        case 8:
            printf("\033[31m numDeadRelations\033[0m\n");
            break;
        case 9:
            printf("\033[31m popularity\033[0m\n");
            break;
    }

/* 
    cuenta_datos_clases res; 
    cuenta_vivos_muertos_clase_male(vector_datos, 1, &res); 
    printf("    Male:\n");
    printf("        SI_Vivos: %d   SI_Muertos: %d    NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book1(vector_datos, 1, &res); 
    printf("    Book1:\n");
    printf("        SI_Vivos: %d   SI_Muertos: %d    NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book2(vector_datos, 1, &res); 
    printf("    Book2:\n");
    printf("        SI_Vivos: %d   SI_Muertos: %d    NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book3(vector_datos, 1, &res); 
    printf("    Book3:\n");
    printf("        SI_Vivos: %d   SI_Muertos: %d    NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book4(vector_datos, 1, &res); 
    printf("    Book4:\n");
    printf("        SI_Vivos: %d   SI_Muertos: %d    NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_book5(vector_datos, 1, &res); 
    printf("    Book5:\n");
    printf("        SI_Vivos: %d   SI_Muertos: %d    NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_isMarried(vector_datos, 1, &res); 
    printf("    isMarried:\n");
    printf("        SI_Vivos: %d   SI_Muertos: %d    NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_isNoble(vector_datos, 1, &res); 
    printf("    isNoble:\n");
    printf("        SI_Vivos: %d   SI_Muertos: %d    NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_numDeadRelations(vector_datos, umb_numDead, &res); 
    printf("    NumDeadRelations:\n");
    printf("        SI_Vivos: %d    SI_Muertos: %d      NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
    cuenta_vivos_muertos_clase_popularity(vector_datos, umb_pop, &res); 
    printf("    Popularity:\n");
    printf("        SI_Vivos: %d    SI_Muertos: %d      NO_Vivos: %d    NO_Muertos: %d\n\n",res.clase_si_vivos,res.clase_si_muertos,res.clase_no_vivos,res.clase_no_muertos);
*/
}
