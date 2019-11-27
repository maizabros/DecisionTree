/*
 * =====================================================================================
 *
 *       Filename:  libDecisionTree.c
 *
 *    Description:  Librería para el arbol de decisión
 *
 *        Version:  1.0
 *        Created:  24/11/19
 *       Compiler:  gcc
 *
 *         Author:  Adrian Maiza, Beatriz Lago, Erick Martínez 
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "quicksort.h"
#include "libfrag.h"
#include "pilaDeadAlive.h"

#define C_ENTRENO 1557
#define N C_ENTRENO
#define BUFF 1024
#define HEADERS_SIZE 128

void recogerDatos(datos ** vector_datos,char ** headers, int fd){

	int dup = dup2(fd, STDIN_FILENO);
	if(fd == -1 || dup == -1){
		perror("Error al redirigir fichero.");
		return;
	}
	close(fd);

	char * buffer = (char*)malloc(sizeof(char)*BUFF);
	(*vector_datos) = (datos*)malloc(C_ENTRENO*sizeof(datos));

	
	fgets(buffer, sizeof(char)*BUFF, stdin); 
	headers = fragBufferExtract(buffer);
	int i=0;
	while(fgets(buffer,sizeof(char)*BUFF,stdin) != NULL){
			char ** data = fragBufferExtract(buffer);
			
            if(i == N) break; // Asi podemos entrenarlo con cualquier cantidad de datos
			(*vector_datos)[i].male = atoi(data[0]);
			(*vector_datos)[i].book1 = atoi(data[1]);
			(*vector_datos)[i].book2 = atoi(data[2]);
			(*vector_datos)[i].book3 = atoi(data[3]);
			(*vector_datos)[i].book4 = atoi(data[4]);
            (*vector_datos)[i].book5 = atoi(data[5]);
			(*vector_datos)[i].isMarried = atoi(data[6]);
			(*vector_datos)[i].isNoble = atoi(data[7]);
			(*vector_datos)[i].numDeadRelations = atoi(data[8]);
			(*vector_datos)[i].popularity = atof(data[9]);
			(*vector_datos)[i].isAlive = atoi(data[10]);
			i++;
	}
	/*****************************************************************/
	/** PRINTEA LOS DATOS DESDE EL VECTOR DE STRUCT DATOS            */
    /*
	for(int i=0; i<11; i++){             
	    printf("%s",headers[i]);
		if (i<10) printf(", ");
	}
	printf("\n");

	for(int i=0; i<N; i++){
		printf((*vector_datos)[i].male ? " true, " : "false, ");
		printf((*vector_datos)[i].book1 ? " true, " : "false, ");
		printf((*vector_datos)[i].book2 ? " true, " : "false, ");
		printf((*vector_datos)[i].book3 ? " true, " : "false, ");
		printf((*vector_datos)[i].book4 ? " true, " : "false, ");
		printf((*vector_datos)[i].book5 ? " true, " : "false, ");
		printf((*vector_datos)[i].isMarried ? " true, " : "false, ");
		printf((*vector_datos)[i].isNoble ? " true, " : "false, ");
		if ((*vector_datos)[i].numDeadRelations < 10)
		    printf("%d  , ",(*vector_datos)[i].numDeadRelations);
		else
		    printf("%d , ",(*vector_datos)[i].numDeadRelations);
		printf("%f, ",(*vector_datos)[i].popularity);
		printf((*vector_datos)[i].isAlive ? " true" : "false");
		printf("\n");
	}
    */
	/*****************************************************************/
}



double entropia_clases(int clase_si, int clase_no, int clase_si_vivos, int clase_si_muertos, int clase_no_vivos, int clase_no_muertos){
	
}

double entropia_umbral(tipoElementoPila x){
	
	double arg1 = ((double)(x.vivos_Izq+x.muertos_Izq)/N);
	double arg2 = (x.vivos_Izq/(double)(x.vivos_Izq+x.muertos_Izq));
	double arg3;
    if (x.vivos_Izq > 0) {
		arg3 = log2((double)(x.vivos_Izq+x.muertos_Izq)/x.vivos_Izq);
    } else {
		arg3 = 0;
	}
	double arg4 = (x.muertos_Izq/(double)(x.vivos_Izq+x.muertos_Izq));
	double arg5;
    if (x.muertos_Izq > 0) {
		arg5 = log2((double)(x.vivos_Izq+x.muertos_Izq)/x.muertos_Izq);
    } else {
		arg5 = 0;
	}
	double arg6 = (((double)(x.vivos_Dch+x.muertos_Dch)/N));
	double arg7 = ((x.vivos_Dch/(double)(x.vivos_Dch+x.muertos_Dch)));
	double arg8;
    if (x.vivos_Dch > 0) {
		arg8 = log2((double)(x.vivos_Dch+x.muertos_Dch)/x.vivos_Dch);
    } else { 
		arg8 = 0;
	}
	double arg9 = (x.muertos_Dch/(double)(x.vivos_Dch+x.muertos_Dch));
	double arg10;
    if (x.muertos_Dch > 0) {
		arg10 = log2((double)(x.vivos_Dch+x.muertos_Dch)/x.muertos_Dch);
    } else {
		arg10 = 0;
	}
	//printf("[arg1: %lf, arg2: %lf, arg3: %lf, arg4: %lf, arg5: %lf, arg6: %lf, arg7: %lf, arg8: %lf, arg9: %lf, arg10: %lf]\n",arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10);
	
	return ((arg1)*(arg2*arg3+arg4*arg5) + (arg6)*(arg7*arg8 + arg9*arg10));
}

double umbral(datos *vect, char* str_umbral, int total_Vivos){
	
	int total_Muertos = N-total_Vivos,
		PosEntMin=0;
	
    if(strcmp(str_umbral, "popularity") == 0){
        quicksort_popularity(vect, 0, N-1);
        //printf(" POPULARITY\n");
        /******************************************************/
        /*  
        printf("\nOREDNADO POR POPULARITY:\n\n");
        for(int i=0; i<N; i++){
            printf(vect[i].male ? " true, " : "false, ");
            printf(vect[i].book1 ? " true, " : "false, ");
            printf(vect[i].book2 ? " true, " : "false, ");
            printf(vect[i].book3 ? " true, " : "false, ");
            printf(vect[i].book4 ? " true, " : "false, ");
            printf(vect[i].book5 ? " true, " : "false, ");
            printf(vect[i].isMarried ? " true, " : "false, ");
            printf(vect[i].isNoble ? " true, " : "false, ");
            if (vect[i].numDeadRelations < 10)
                printf("%d  , ",vect[i].numDeadRelations);
            else
                printf("%d , ",vect[i].numDeadRelations);
            printf("%f, ",vect[i].popularity);
            printf(vect[i].isAlive ? " true" : "false");
            printf("\n");
        }
        */
        /******************************************************/
    } else if(strcmp(str_umbral, "numDeadRelations") == 0){
        quicksort_numDeadRelations(vect, 0, N-1);
        //printf(" NUMDEADRELATIONS \n");
        /******************************************************/
        /* printf("\nOREDNADO POR NUMDEADRELATIONS:\n\n");
        for(int i=0; i<N; i++){
            printf(vect[i].male ? " true, " : "false, ");
            printf(vect[i].book1 ? " true, " : "false, ");
            printf(vect[i].book2 ? " true, " : "false, ");
            printf(vect[i].book3 ? " true, " : "false, ");
            printf(vect[i].book4 ? " true, " : "false, ");
            printf(vect[i].book5 ? " true, " : "false, ");
            printf(vect[i].isMarried ? " true, " : "false, ");
            printf(vect[i].isNoble ? " true, " : "false, ");
            if (vect[i].numDeadRelations < 10)
                printf("%d  , ",vect[i].numDeadRelations);
            else
                printf("%d , ",vect[i].numDeadRelations);
            printf("%f, ",vect[i].popularity);
            printf(vect[i].isAlive ? " true" : "false");
            printf("\n");
        }
        */
        /******************************************************/
    }
	double Ent = 100, umbral = 0;
    double MinEnt = 100;
    
	total_Muertos = N - total_Vivos;
    tipoPila p;
    nuevaPila( & p);
    bool ant, sig;
    
    ant = (vect[0]).isAlive;
    sig = (vect[1]).isAlive;
    tipoElementoPila x;
    
    x.vivos_Izq = 1;
    if (ant == 0) x.muertos_Izq = 1;
    else x.muertos_Izq = 0;
    x.vivos_Dch = 0;
    x.muertos_Dch = 0;

    for (int i = 1; i < N; i++) {
		if (ant != sig) {
			x.muertos_Dch = total_Muertos - x.muertos_Izq;
			x.vivos_Dch = total_Vivos - x.vivos_Izq;
			x.pos = i;
			apilar( & p, x);
		}
		if (vect[i].isAlive == 1) {
			x.vivos_Izq++;
		} else {
			x.muertos_Izq++;
		} 
    }

    while (!esNulaPila(p)) {
      x = cima(p);
      Ent = entropia_umbral(x);
      if (Ent < MinEnt) {
        MinEnt = Ent;
        PosEntMin = x.pos;
      }
      desapilar( & p);
    }
    Ent = entropia_umbral(x);
    if (Ent < MinEnt) { //Para tratar el ultimo elemento de la pila porque se quedaba sin tratar
      MinEnt = Ent;
      PosEntMin = x.pos;
    } 
    //Cálculo del umbral
    if (strcmp(str_umbral, "numDeadRelations") == 0) {
      umbral = ((vect[PosEntMin].numDeadRelations + vect[PosEntMin - 1].numDeadRelations) / 2);
    } else if (strcmp(str_umbral, "popularity") == 0)
      umbral = ((vect[PosEntMin].popularity + vect[PosEntMin - 1].popularity) / 2);
    return umbral;

}
