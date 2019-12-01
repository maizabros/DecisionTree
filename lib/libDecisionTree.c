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
#include <signal.h>
#include "quicksort.h"
#include "libfrag.h"
#include "pilaDeadAlive.h"
//#include "libDecisionTree.h"
#include "arbolBin.h"

#define C_ENTRENO 15
#define BUFF 1024
#define HEADERS_SIZE 128
int N = C_ENTRENO;
float umb_popularity;
int umb_numDead;
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

void print_data(datos * vector_datos){
	/*****************************************************************/
	/** PRINTEA LOS DATOS DESDE EL VECTOR DE STRUCT DATOS            */
	printf("\n");

	for(int i=0; i<N; i++){
		printf(vector_datos[i].male ? " true, " : "false, ");
		printf(vector_datos[i].book1 ? " true, " : "false, ");
		printf(vector_datos[i].book2 ? " true, " : "false, ");
		printf(vector_datos[i].book3 ? " true, " : "false, ");
		printf(vector_datos[i].book4 ? " true, " : "false, ");
		printf(vector_datos[i].book5 ? " true, " : "false, ");
		printf(vector_datos[i].isMarried ? " true, " : "false, ");
		printf(vector_datos[i].isNoble ? " true, " : "false, ");
		if (vector_datos[i].numDeadRelations < 10)
		    printf("%d  , ",vector_datos[i].numDeadRelations);
		else
		    printf("%d , ",vector_datos[i].numDeadRelations);
		printf("%f, ",vector_datos[i].popularity);
		printf(vector_datos[i].isAlive ? " true" : "false");
		printf("\n");
	}
	/*****************************************************************/

}

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
}


float entropia_clases(cuenta_datos_clases res){

    double totalSi = res.clase_si_vivos + res.clase_si_muertos, 
        totalNo = res.clase_no_vivos + res.clase_no_muertos;
    double arg1 = ((double) res.clase_si_vivos/totalSi); 
    double arg2 = log2(totalSi/(double) res.clase_si_vivos);
    double arg3 = ((double) res.clase_si_muertos/totalSi); 
    double arg4 = log2(totalSi/(double) res.clase_si_muertos);
    double arg5 = ((double) res.clase_no_vivos/totalNo); 
    double arg6 = log2(totalNo/(double) res.clase_no_vivos);
    double arg7 = ((double) res.clase_no_muertos/totalNo); 
    double arg8 = log2(totalNo/(double) res.clase_no_muertos);
    if(totalSi == 0){
        arg1 = 0;
        arg2 = 0;
        arg3 = 0;
        arg4 = 0;
    } else if(res.clase_si_vivos == 0) arg2 = 0;
    else if(res.clase_si_muertos == 0) arg4 = 0;
    if(totalNo == 0){
        arg5 = 0;
        arg6 = 0;
        arg7 = 0;
        arg8 = 0;
    } else if(res.clase_no_vivos == 0) arg6 = 0;
    else if(res.clase_no_muertos == 0) arg8 = 0;
	//printf("[arg1: %lf, arg2: %lf, arg3: %lf, arg4: %lf, arg5: %lf, arg6: %lf, arg7: %lf, arg8: %lf]\n",arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);

    //printf("ENTROPIA_CLASE: [%f]\n\n",((totalSi/N) * ((arg1 * arg2) + (arg3 * arg4)) + (totalNo/N) * ((arg5 * arg6) + (arg7 * arg8))));
    return ((totalSi/N) * ((arg1 * arg2) + (arg3 * arg4)) + (totalNo/N) * ((arg5 * arg6) + (arg7 * arg8))); 
}

float entropia_umbral(tipoElementoPila x){
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

float umbral(datos * vect, char* str_umbral, int totalVivos){
	int total_Muertos,PosEntMin=0;
	bool ant,sig;
	float Ent=100,umbral=0;
	float MinEnt=100;
	
    if(strcmp(str_umbral, "popularity") == 0)
        quicksort_popularity(&vect, 0, N-1);
    else if(strcmp(str_umbral, "numDeadRelations") == 0)
        quicksort_numDeadRelations(&vect, 0, N-1);
    else{
        printf("\033[31mERROR en UMBRAL:\033[0m clase no válida\nSaliendo...\n\n");
        exit(EXIT_FAILURE);
    }
    print_data(vect);


	total_Muertos=N-totalVivos;
	tipoPila p;
	nuevaPila(&p);
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
			x.vivos_Dch=totalVivos-x.vivos_Izq;
			x.pos=i;
			apilar(&p,x);
		}
		if(vect[i].isAlive==1){
			x.vivos_Izq++;
		} else{
			x.muertos_Izq++;
		}
        ant = vect[i].isAlive;
        sig = vect[i+1].isAlive;
	}

	while(!esNulaPila(p)){
		x = cima(p);
        Ent=entropia_umbral(x);
		if(Ent<MinEnt){
            printf("ENTROPIA: [%f]\n",Ent);
			MinEnt=Ent;
			PosEntMin=x.pos;
		}
        desapilar(&p);
	}
	Ent=entropia_umbral(x);
	if(Ent<MinEnt){
            printf("ENTROPIA: [%f]\n",Ent);
			MinEnt=Ent;
			PosEntMin=x.pos;
	} //Para tratar el ultimo elemento de la pila porque se quedaba sin tratar
	//Cálculo del umbral
    if (strcmp(str_umbral,"numDeadRelations") == 0){
	    umbral = ((float)(vect[PosEntMin].numDeadRelations + vect[PosEntMin-1].numDeadRelations)/2);
    } else if (strcmp(str_umbral,"popularity") == 0)
	    umbral = ((vect[PosEntMin].popularity+vect[PosEntMin-1].popularity)/2);
    return umbral;

}

void calculo_entropia_clases(datos * vect, float totalVivos, float *** entropias_clases){

    cuenta_datos_clases res;
    float totalMuertos = N - totalVivos;
    float entropia_C = -(totalVivos/N)*log2(totalVivos/N)-(totalMuertos/N)*log2(totalMuertos/N); 
    umb_numDead = (int)umbral(vect,"numDeadRelations",(int)totalVivos);
    umb_popularity = umbral(vect, "popularity", totalVivos);
    printf("\nUMBRALES:\nnumDead [%d]\npopularity [%f]\n",umb_numDead,umb_popularity);
    *entropias_clases = (float**)malloc(sizeof(float*)*10);
    for(int i=0; i<10; i++){
        (*entropias_clases)[i] = (float *)malloc(sizeof(float)*2);
    }
    cuenta_vivos_muertos_clase_male(vect, 1, &res); 
    (*entropias_clases)[0][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[0][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book1(vect, 1, &res); 
    (*entropias_clases)[1][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[1][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book2(vect, 1, &res); 
    (*entropias_clases)[2][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[2][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book3(vect, 1, &res); 
    (*entropias_clases)[3][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[3][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book4(vect, 1, &res); 
    (*entropias_clases)[4][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[4][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book5(vect, 1, &res); 
    (*entropias_clases)[5][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[5][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_isMarried(vect, 1, &res); 
    (*entropias_clases)[6][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[6][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_isNoble(vect, 1, &res); 
    (*entropias_clases)[7][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[7][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_popularity(vect, umb_popularity, &res); 
    (*entropias_clases)[8][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[8][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_numDeadRelations(vect, umb_numDead, &res); 
    (*entropias_clases)[9][0] = entropia_C - entropia_clases(res);
    (*entropias_clases)[9][1] = res.clase_si_vivos + res.clase_si_muertos;
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

void crearArbol(tipoArbolBin * a, tipoElementoArbolBin e, int tamano, int totalVivos){
    signal(SIGABRT,SIG_IGN);
	printf("	He entrado en la función\n");
	if (esVacio(*a)){
		printf("		Voy a hacer un nodo nuevo\n");
		celdaArbolBin * nuevo;
		nuevo = (celdaArbolBin*)malloc(sizeof(celdaArbolBin));
		nuevo->elem = (datos *)malloc(sizeof(datos) * tamano); 
		for (int i = 0; i < tamano; i++){
			///printf("			Estoy metiendo el elemento\n");
			nuevo->elem[i] = e[i];
			///printf("			El elemento %d es: %f\n",i, nuevo->elem[i].popularity);
		}
		nuevo->izda = NULL;
		nuevo->dcha = NULL;
		*a = nuevo;
	}
	else{
		/**
		 * Y aquí entiendo que habría que volver a calcular el umbral o lo que toque,
		 * separar el vector en dos de nuevo y llamar con un vector al hijo izquierdo o
		 * al hijo derecho?? no lo tengo claro :(
		 */
		float ** entropias_clases;
		calculo_entropia_clases(e , (float) totalVivos, &entropias_clases);
		datos * hijoI;
		datos * hijoD;
		int clase_seleccionada = calculo_minima_entropia(entropias_clases);
		hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[clase_seleccionada][1]);
		hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[clase_seleccionada][1]));
		printf("·· SELECCIONADA CLASE");
		switch(clase_seleccionada){
			case 0:
				printf("\033[31m male\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
                for (int i = 0; i < tamano; i++){
					if (e[i].male){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				
				break;
			case 1:
				printf("\033[31m book1\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].book1){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
				
			case 2:
				printf("\033[31m book2\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].book2){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
			case 3:
				printf("\033[31m book3\033[0m\n");

				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].book3){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
			case 4:
				printf("\033[31m book4\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].book4){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
			case 5:
				printf("\033[31m book5\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].book5){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
			case 6:
				printf("\033[31m isMarried\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].isMarried){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
			case 7:
				printf("\033[31m isNoble\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].isNoble){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
			case 8:
				printf("\033[31m popularity\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].numDeadRelations < umb_numDead){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
			case 9:
				printf("\033[31m numDeadRelations\033[0m\n");
				hijoI = (datos *)malloc(sizeof(datos) * entropias_clases[0][1]);
				hijoD = (datos *)malloc(sizeof(datos) * (tamano - entropias_clases[0][1]));
				
				for (int i = 0; i < tamano; i++){
					if (e[i].popularity < umb_popularity){
						hijoI[i] = e[i];
					}
					else{
						hijoD[i] = e[i];
					}
				}
				break;
		}
		crearArbol(&((*a)->izda), hijoI, entropias_clases[clase_seleccionada][1], totalVivos);
		crearArbol(&((*a)->dcha), hijoD, tamano - entropias_clases[clase_seleccionada][1], totalVivos);
	}

}
