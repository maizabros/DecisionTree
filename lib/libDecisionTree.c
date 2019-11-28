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
/* ***************************************************************************************************************** */
/* **   A PARTIR DE AQUI HASTA EL SIGUIENTE SEPARADOR SON LAS DECLARACIONES DE FUNCIONES VARIABLES SEGUN ENTRADA  ** */
/* ***************************************************************************************************************** */
#define FUNCIONES_SELECCION_DE_CLASE(nombreDato, tipoDato)                                                          \
    void cuenta_vivos_muertos_clase_##nombreDato(datos vect[N], tipoDato umbral, cuenta_datos_clases * resultados){ \
        (*resultados).clase_si_vivos=0;                                                                             \
        (*resultados).clase_no_vivos=0;                                                                             \
        (*resultados).clase_si_muertos=0;                                                                           \
        (*resultados).clase_no_muertos=0;                                                                           \
        for (int i = 0; i < N; i++) {                                                                               \
            if(vect[i].nombreDato < umbral){                                                                        \
                if(vect[i].isAlive == 1)                                                                            \
                    (*resultados).clase_no_vivos++;                                                                 \
                else                                                                                                \
                    (*resultados).clase_no_muertos++;                                                               \
            } else {                                                                                                \
                if(vect[i].isAlive == 1)                                                                            \
                    (*resultados).clase_si_vivos++;                                                                 \
                else                                                                                                \
                    (*resultados).clase_si_muertos++;                                                               \
            }                                                                                                       \
        }                                                                                                           \
        printf("\n");                                                                                               \
    }                                                                                                               \
/* *************************************************************************************************************** */
/* *************************************************************************************************************** */

FUNCIONES_SELECCION_DE_CLASE(male, bool);
FUNCIONES_SELECCION_DE_CLASE(book1, bool);
FUNCIONES_SELECCION_DE_CLASE(book2, bool);
FUNCIONES_SELECCION_DE_CLASE(book3, bool);
FUNCIONES_SELECCION_DE_CLASE(book4, bool);
FUNCIONES_SELECCION_DE_CLASE(book5, bool);
FUNCIONES_SELECCION_DE_CLASE(isMarried, bool);
FUNCIONES_SELECCION_DE_CLASE(isNoble, bool);
FUNCIONES_SELECCION_DE_CLASE(numDeadRelations, int);
FUNCIONES_SELECCION_DE_CLASE(popularity, float);
/* ******************************************* */
/* *   ESTA PARTE GENERA LAS FUNCIONES       * */
/* *   PARA CADA TIPO DE DATO DEL STRUCT     * */
/* *   DE DATOS.                             * */
/* *   SI NO ENTENDEIS COMO VA DECIDME xD    * */
/* ******************************************* */

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

float entropia(tipoElementoPila x){
	double arg1 = ((double)(x.vivos_Izq+x.muertos_Izq)/N);
	double arg2 = (x.vivos_Izq/(double)(x.vivos_Izq+x.muertos_Izq));
	double arg3;
    if (x.vivos_Izq > 0) arg3 = log2((double)(x.vivos_Izq+x.muertos_Izq)/x.vivos_Izq);
    else arg3 = 0;
	double arg4 = (x.muertos_Izq/(double)(x.vivos_Izq+x.muertos_Izq));
	double arg5;
    if (x.muertos_Izq > 0) arg5 = log2((double)(x.vivos_Izq+x.muertos_Izq)/x.muertos_Izq);
    else arg5 = 0;
	double arg6 = (((double)(x.vivos_Dch+x.muertos_Dch)/N));
	double arg7 = ((x.vivos_Dch/(double)(x.vivos_Dch+x.muertos_Dch)));
	double arg8;
    if (x.vivos_Dch > 0) arg8 = log2((double)(x.vivos_Dch+x.muertos_Dch)/x.vivos_Dch);
    else arg8 = 0;
	double arg9 = (x.muertos_Dch/(double)(x.vivos_Dch+x.muertos_Dch));
	double arg10;
    if (x.muertos_Dch > 0) arg10 = log2((double)(x.vivos_Dch+x.muertos_Dch)/x.muertos_Dch);
    else arg10 = 0;
	
	//printf("[arg1: %lf, arg2: %lf, arg3: %lf, arg4: %lf, arg5: %lf, arg6: %lf, arg7: %lf, arg8: %lf, arg9: %lf, arg10: %lf]\n",arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10);
	
	return ((arg1)*(arg2*arg3+arg4*arg5) + (arg6)*(arg7*arg8 + arg9*arg10));
}

float umbral(datos *vect, char* str_umbral){
	int total_Vivos=0,total_Muertos,PosEntMin=0;
	
    for(int j=0; j<N; j++){
		if(vect[j].isAlive==1) total_Vivos++;
	}
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

	total_Muertos=N-total_Vivos;
	tipoPila p;
	nuevaPila(&p);
	bool ant,sig;
	float Ent=100,umbral=0;
	float MinEnt=100;
	ant=(vect[0]).isAlive;
	sig=(vect[1]).isAlive;
	tipoElementoPila x;
    x.vivos_Izq=1;
    if(ant==0) x.muertos_Izq=1;
    else x.muertos_Izq=0;
    x.vivos_Dch=0;
    x.muertos_Dch=0;
	
    for(int i=1; i<N; i++){
		
		if(ant!=sig){
			x.muertos_Dch=total_Muertos-x.muertos_Izq;
			x.vivos_Dch=total_Vivos-x.vivos_Izq;
			x.pos=i;
			apilar(&p,x);
		}
		if(vect[i].isAlive==1){
			x.vivos_Izq++;
		} else{
			x.muertos_Izq++;
		}
		
		if(i<N){
			ant=(vect[i]).isAlive;
			sig=(vect[i+1]).isAlive;    //Aqui estas accediendo a vec[i+1] que no existe porque te sales 
                                        // de la tabla por eso he hecho el if para no salirte en la ultima
		}
	}

	while(!esNulaPila(p)){
		x = cima(p);
        //printf("\nX: [vivos_Izq = %d, vivos_dch = %d, muertos_izq = %d, muertos_dch = %d, pos = %d]\n",x.vivos_Izq,x.vivos_Dch,x.muertos_Izq,x.muertos_Dch,(int)x.pos);
        Ent=entropia(x);
        //printf("ENT: [%f]\n",Ent);
        //printf("POS_ENT: [%d]\n",(int)x.pos);
		if(Ent<MinEnt){
			MinEnt=Ent;
            //printf("\033[31mMINENT: [[%f]]\n",MinEnt);
            //printf("POS_ENT_MIN: [%d]\n\033[0m",(int)x.pos);
			PosEntMin=x.pos;
		}
        desapilar(&p);
	}
	Ent=entropia(x);
	if(Ent<MinEnt){
			MinEnt=Ent;
			PosEntMin=x.pos;
	} //Para tratar el ultimo elemento de la pila porque se quedaba sin tratar
	//Cálculo del umbral
    //printf("POSICION ENT MIN: %d\n\n",PosEntMin);
    if (strcmp(str_umbral,"numDeadRelations") == 0){
	    umbral = (((float)vect[PosEntMin].numDeadRelations+(float)vect[PosEntMin-1].numDeadRelations)/2);
    } else if (strcmp(str_umbral,"popularity") == 0)
	    umbral = ((vect[PosEntMin].popularity+vect[PosEntMin-1].popularity)/2);
    return umbral;

}
