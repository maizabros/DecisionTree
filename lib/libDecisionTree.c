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
//#include "libDecisionTree.h"
#include "arbolBin.h"

#define C_ENTRENO 1557 
#define C_TEST 389 
#define BUFF 1024
#define HEADERS_SIZE 128
int N = C_ENTRENO;
double umb_popularity;
int umb_numDead;
bool clase_utilizada[10] = {false};
double medias_ganancias[10][2] = {{0.0}};
int aciertos = 0;
int numero_de_datos_en_hojas = 0; 
/* ***************************************************************************************************************** */
/* **   A PARTIR DE AQUI HASTA EL SIGUIENTE SEPARADOR SON LAS DECLARACIONES DE FUNCIONES VARIABLES SEGUN ENTRADA  ** */
/* ***************************************************************************************************************** */
#define FUNCIONES_SELECCION_DE_CLASE(nombreDato, tipoDato)                                                          \
    void cuenta_vivos_muertos_clase_##nombreDato(datos * vect, int tamano, tipoDato umbral, cuenta_datos_clases * resultados){ \
        (*resultados).clase_si_vivos=0;                                                                             \
        (*resultados).clase_no_vivos=0;                                                                             \
        (*resultados).clase_si_muertos=0;                                                                           \
        (*resultados).clase_no_muertos=0;                                                                           \
        for (int i = 0; i < tamano; i++) {                                                                          \
            if(umbral == 0.0f){																						\
                if(vect[i].nombreDato <= umbral){                                                                   \
                    if(vect[i].isAlive == 1)                                                                        \
                        (*resultados).clase_no_vivos++;                                                             \
                    else                                                                                            \
                        (*resultados).clase_no_muertos++;                                                           \
                } else {                                                                                            \
                    if(vect[i].isAlive == 1)                                                                        \
                        (*resultados).clase_si_vivos++;                                                             \
                    else                                                                                            \
                        (*resultados).clase_si_muertos++;                                                           \
                }                                                                                                   \
            } else {                                                                                                \
                if(vect[i].nombreDato < umbral){                                                                    \
                    if(vect[i].isAlive == 1)                                                                        \
                        (*resultados).clase_no_vivos++;                                                             \
                    else                                                                                            \
                        (*resultados).clase_no_muertos++;                                                           \
                } else {                                                                                            \
                    if(vect[i].isAlive == 1)                                                                        \
                        (*resultados).clase_si_vivos++;                                                             \
                    else                                                                                            \
                        (*resultados).clase_si_muertos++;                                                           \
                }                                                                                                   \
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
FUNCIONES_SELECCION_DE_CLASE(popularity, double);
/* ******************************************* */
/* *   ESTA PARTE GENERA LAS FUNCIONES       * */
/* *   PARA CADA TIPO DE DATO DEL STRUCT     * */
/* *   DE DATOS.                             * */
/* ******************************************* */

void print_data(datos * vector_datos, int n){
	/*****************************************************************/
	/** PRINTEA LOS DATOS DESDE EL VECTOR DE STRUCT DATOS            */
	printf("\n");

	for(int i=0; i<n; i++){
		printf(vector_datos[i].male ? " true, " : "false, ");
		printf(vector_datos[i].book1 ? " true, " : "false, ");
		printf(vector_datos[i].book2 ? " true, " : "false, ");
		printf(vector_datos[i].book3 ? " true, " : "false, ");
		printf(vector_datos[i].book4 ? " true, " : "false, ");
		printf(vector_datos[i].book5 ? " true, " : "false, ");
		printf(vector_datos[i].isMarried ? " true, " : "false, ");
		printf(vector_datos[i].isNoble ? " true, " : "false, ");
		    printf("%2f, ",vector_datos[i].numDeadRelations);
		printf("%.18F, ",vector_datos[i].popularity);
		printf(vector_datos[i].isAlive ? " true" : "false");
		printf("\n");
	}
	/*****************************************************************/

}

void recogerDatos(datos ** vector_datos, datos ** datos_a_comprobar,char ** headers, int fd){

	int dup = dup2(fd, STDIN_FILENO);
	if(fd == -1 || dup == -1){
		perror("Error al redirigir fichero.");
		return;
	}
	close(fd);

	char * buffer = (char*)malloc(sizeof(char)*BUFF);
	(*vector_datos) = (datos*)malloc(C_ENTRENO*sizeof(datos));
	(*datos_a_comprobar) = (datos*)malloc(C_TEST*sizeof(datos));

	
	fgets(buffer, sizeof(char)*BUFF, stdin); 
	headers = fragBufferExtract(buffer);
	int i=0;
	while(fgets(buffer,sizeof(char)*BUFF,stdin) != NULL){
			
            if(i == N) break; // Asi podemos entrenarlo con cualquier cantidad de datos
			char ** data = fragBufferExtract(buffer);
			(*vector_datos)[i].male = atoi(data[0]);
			(*vector_datos)[i].book1 = atoi(data[1]);
			(*vector_datos)[i].book2 = atoi(data[2]);
			(*vector_datos)[i].book3 = atoi(data[3]);
			(*vector_datos)[i].book4 = atoi(data[4]);
            (*vector_datos)[i].book5 = atoi(data[5]);
			(*vector_datos)[i].isMarried = atoi(data[6]);
			(*vector_datos)[i].isNoble = atoi(data[7]);
			(*vector_datos)[i].numDeadRelations = atof(data[8])/10.0f;
			(*vector_datos)[i].popularity = strtod(data[9],NULL);
			(*vector_datos)[i].isAlive = atoi(data[10]);
			i++;
	}
    i = 0;
	do{
			char ** data = fragBufferExtract(buffer);
			
            if(i == C_TEST) break; // Asi podemos entrenarlo con cualquier cantidad de datos
			(*datos_a_comprobar)[i].male = atoi(data[0]);
			(*datos_a_comprobar)[i].book1 = atoi(data[1]);
			(*datos_a_comprobar)[i].book2 = atoi(data[2]);
			(*datos_a_comprobar)[i].book3 = atoi(data[3]);
			(*datos_a_comprobar)[i].book4 = atoi(data[4]);
            (*datos_a_comprobar)[i].book5 = atoi(data[5]);
			(*datos_a_comprobar)[i].isMarried = atoi(data[6]);
			(*datos_a_comprobar)[i].isNoble = atoi(data[7]);
			(*datos_a_comprobar)[i].numDeadRelations = strtod(data[8],NULL)/10.0f;
			(*datos_a_comprobar)[i].popularity = strtod(data[9],NULL);
			(*datos_a_comprobar)[i].isAlive = atoi(data[10]);
			i++;
    } while(fgets(buffer,sizeof(char)*BUFF,stdin) != NULL);
}


double entropia_clases(cuenta_datos_clases res){

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
	//printf("CLASE[arg1: %lf, arg2: %lf, arg3: %lf, arg4: %lf, arg5: %lf, arg6: %lf, arg7: %lf, arg8: %lf]\n",arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);

    //printf("ENTROPIA_CLASE: [%.18F]\n\n",((totalSi/N) * ((arg1 * arg2) + (arg3 * arg4)) + (totalNo/N) * ((arg5 * arg6) + (arg7 * arg8))));
    return ((totalSi/N) * ((arg1 * arg2) + (arg3 * arg4)) + (totalNo/N) * ((arg5 * arg6) + (arg7 * arg8))); 
}

double entropia_umbral(tipoElementoPila x){
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
	
	//printf("UMBRAL[arg1: %lf, arg2: %lf, arg3: %lf, arg4: %lf, arg5: %lf, arg6: %lf, arg7: %lf, arg8: %lf, arg9: %lf, arg10: %lf]\n",arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10);
	
	return ((arg1)*(arg2*arg3+arg4*arg5) + (arg6)*(arg7*arg8 + arg9*arg10));
}

double umbral(datos * vect, char* str_umbral, int totalVivos){
	double total_Muertos;
    int PosEntMin=0;
	bool ant,sig;
	double Ent=100,umbral=0;
	double MinEnt=100;
	
    if(strcmp(str_umbral, "popularity") == 0)
        quicksort_popularity(&vect, 0, N-1);
    else if(strcmp(str_umbral, "numDeadRelations") == 0)
        quicksort_numDeadRelations(&vect, 0, N-1);
    else{
        printf("\033[31mERROR en UMBRAL:\033[0m clase no válida\nSaliendo...\n\n");
        exit(EXIT_FAILURE);
    }
    //print_data(vect);


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
            //printf("ENTROPIA %s: [%.18F]\n",str_umbral,Ent);
			MinEnt=Ent;
			PosEntMin=x.pos;
		}
        desapilar(&p);
	}
	Ent=entropia_umbral(x);
	if(Ent<MinEnt){
            //printf("ENTROPIA %s: [%.18F]\n",str_umbral,Ent);
			MinEnt=Ent;
			PosEntMin=x.pos;
	} //Para tratar el ultimo elemento de la pila porque se quedaba sin tratar
	//Cálculo del umbral
    if (strcmp(str_umbral,"numDeadRelations") == 0){
	    umbral = ((double)(vect[PosEntMin].numDeadRelations + vect[PosEntMin-1].numDeadRelations)/2);
    } else if (strcmp(str_umbral,"popularity") == 0)
	    umbral = ((vect[PosEntMin].popularity+vect[PosEntMin-1].popularity)/2);
    return umbral;

}

void calculo_entropia_clases(datos * vect, double totalVivos, double entropias_clases[10][2]){

    cuenta_datos_clases res;
    double totalMuertos = N - totalVivos;
    double entropia_C = -(totalVivos/N)*log2(totalVivos/N)-(totalMuertos/N)*log2(totalMuertos/N); 
    umb_numDead = umbral(vect,"numDeadRelations",(int)totalVivos);
    umb_popularity = umbral(vect, "popularity", totalVivos);
    printf("\nUMBRALES:\nnumDead [%d]\npopularity [%.18F]\n",(int)(umb_numDead*10.0f),umb_popularity);
    /*
    *entropias_clases = (double**)malloc(sizeof(double*)*10);
    for(int i=0; i<10; i++){
        (*entropias_clases)[i] = (double *)malloc(sizeof(double)*2);
    }
    */
    cuenta_vivos_muertos_clase_male(vect, N, 1, &res); 
    entropias_clases[0][0] = entropia_C - entropia_clases(res);
    entropias_clases[0][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book1(vect, N, 1, &res); 
    entropias_clases[1][0] = entropia_C - entropia_clases(res);
    entropias_clases[1][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book2(vect, N, 1, &res); 
    entropias_clases[2][0] = entropia_C - entropia_clases(res);
    entropias_clases[2][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book3(vect, N, 1, &res); 
    entropias_clases[3][0] = entropia_C - entropia_clases(res);
    entropias_clases[3][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book4(vect, N, 1, &res); 
    entropias_clases[4][0] = entropia_C - entropia_clases(res);
    entropias_clases[4][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_book5(vect, N, 1, &res); 
    entropias_clases[5][0] = entropia_C - entropia_clases(res);
    entropias_clases[5][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_isMarried(vect, N, 1, &res); 
    entropias_clases[6][0] = entropia_C - entropia_clases(res);
    entropias_clases[6][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_isNoble(vect, N, 1, &res); 
    entropias_clases[7][0] = entropia_C - entropia_clases(res);
    entropias_clases[7][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_popularity(vect, N, umb_popularity, &res); 
    entropias_clases[8][0] = entropia_C - entropia_clases(res);
    entropias_clases[8][1] = res.clase_si_vivos + res.clase_si_muertos;
    cuenta_vivos_muertos_clase_numDeadRelations(vect, N, umb_numDead, &res); 
    entropias_clases[9][0] = entropia_C - entropia_clases(res);
    entropias_clases[9][1] = res.clase_si_vivos + res.clase_si_muertos;
    printf("\033[31m");
    for (int i = 0; i < 10; i++) {
       printf("Clase %d: [%.18F][%d]",i,entropias_clases[i][0], (int)entropias_clases[i][1]); 
       printf("[%s]\n",clase_utilizada[i] ? " true" : "false");
        medias_ganancias[i][0] += entropias_clases[i][0];
        medias_ganancias[i][1]++;
    }
    printf("\033[0m");
}

int calculo_minima_entropia(double entropias_clases[10][2]){
	double min_entropia = -0.1f; //Para que cuando haya 0 al menos elija a una
    int clase_seleccionada = -1;
    //printf("DATOS POR CLASE:\n");
    for(int i = 0; i<10; i++){
        //printf("CLASE %d: [%.18F]\n",i+1,entropias_clases[i][0]);
        if(min_entropia < entropias_clases[i][0] && !clase_utilizada[i]){
            clase_seleccionada = i;
            min_entropia = entropias_clases[i][0];
        }
    }
    if(clase_seleccionada != -1 && clase_seleccionada < 8)
        clase_utilizada[clase_seleccionada] = true;
	return clase_seleccionada;
}

void crearArbolDecision(tipoArbolBin * a, datos * e, int tamano){
    /*
    printf("\033[34m\033[21m");
    print_data(e,tamano);
    printf("\033[0m");
    */
    N = tamano;
    double totalVivos = 0;
    for(int i=0; i<tamano; i++){
        if(e[i].isAlive == 1)
            totalVivos++;
    }
    double totalMuertos = tamano - totalVivos;
    double entropia_C = -(totalVivos/N)*log2(totalVivos/N)-(totalMuertos/N)*log2(totalMuertos/N); 
    printf( "FUNCION CREAR ARBOL : ENTROPIA_C = [%.18F]\n",entropia_C);
    if (tamano == totalVivos || tamano == totalMuertos || tamano == 0 || isnan(entropia_C)){
        //if(tamano == 0) tamano = 20;
        //~ for(int i=0; i<10; i++)
            //~ printf("LA GANCIA DE LA CLASE %d es = [%.18F]\n",i,medias_ganancias[i][0]/medias_ganancias[i][1]);
        //~ printf("\033[34mESTOY EN UNA HOJA\033[0m\n");
        //~ printf("\033[34mTAMAÑO DEL VECTOR = %d\033[0m\n",tamano);
        if(esVacio(*a))
            nuevoArbolBin(a, e, tamano); 
        //~ printf("\033[34mSIGO EN UNA HOJA\033[0m\n");
        if(totalVivos >= totalMuertos)
            (*a)->isAlive = true; 
        else
            (*a)->isAlive = false; 
        printf("\033[32m        SOY UNA HOJA\033[0m\n");
        numero_de_datos_en_hojas += tamano;
        //free((*a)->elem);
        return;
    } else {
        if(esVacio(*a))
            nuevoArbolBin(a, e, tamano); 
		double entropias_clases[10][2];
        printf("\033[32m");
		calculo_entropia_clases(e , (double) totalVivos, entropias_clases);
        printf("\033[0m");
		datos * vectHijoI;
		datos * vectHijoD;
		int clase_seleccionada = calculo_minima_entropia(entropias_clases);
        if (entropias_clases[clase_seleccionada][0] < 0.0001f){
			        numero_de_datos_en_hojas += tamano;

            printf("\033[32m YA NO HAY MAS CLASES!\033[0m\n");
            //~ for(int i=0; i<10; i++)
                //~ printf("LA GANCIA DE LA CLASE %d es = [%.18F]\n",i,medias_ganancias[i][0]/medias_ganancias[i][1]);
            if(totalVivos >= totalMuertos)
                (*a)->isAlive = true; 
            else
                (*a)->isAlive = false; 
            printf("\033[32m        SOY UNA HOJA\033[0m\n");
            if(clase_seleccionada!= -1)
				clase_utilizada[clase_seleccionada] = false;
            return;
        }

        (*a)->pregunta = clase_seleccionada; //Asigna la pregunta que se hará para recorrer el arbol
        //printf("\033[33m    EL TAMAÑO DE HIJOI = %d\n   EL TAMAÑO DE HIJOD = %d\033[0m\n",(int)entropias_clases[clase_seleccionada][1], (int)(tamano - (int)entropias_clases[clase_seleccionada][1]));

		vectHijoI = (datos *)malloc(sizeof(datos) * (int)entropias_clases[clase_seleccionada][1]);
		vectHijoD = (datos *)malloc(sizeof(datos) * (tamano - (int)entropias_clases[clase_seleccionada][1]));

        //printf("\033[33m    EL TAMAÑO DEL VECTOR HIJOI = %lu\n   EL TAMAÑO DEL VECTOR HIJOD = %lu\033[0m\n",sizeof(*vectHijoI), sizeof(*vectHijoD));
        
		printf("·· SELECCIONADA CLASE: ");
		int x = 0, y = 0;
		switch(clase_seleccionada){
			case 0:
				printf("\033[31m male");
                for (int i = 0; i < tamano; i++){
					if (e[i].male){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
				}
				
				break;
			case 1:
				printf("\033[31m book1");
                for (int i = 0; i < tamano; i++){
					if (e[i].book1){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
				}
				break;
				
			case 2:
				printf("\033[31m book2");
                for (int i = 0; i < tamano; i++){
					if (e[i].book2){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
				}
				break;
			case 3:
				printf("\033[31m book3");
                for (int i = 0; i < tamano; i++){
					if (e[i].book3){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
				}
				break;
			case 4:
				printf("\033[31m book4");
                for (int i = 0; i < tamano; i++){
					if (e[i].book4){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
				}
				break;
			case 5:
				printf("\033[31m book5");
                for (int i = 0; i < tamano; i++){
					if (e[i].book5){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
				}
				break;
			case 6:
				printf("\033[31m isMarried");
                for (int i = 0; i < tamano; i++){
					if (e[i].isMarried){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
				}
				break;
			case 7:
				printf("\033[31m isNoble");
                for (int i = 0; i < tamano; i++){
					if (e[i].isNoble){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
				}
				break;
			case 8:
				printf("\033[31m popularity");
				if (umb_popularity != 0.0f){
					for (int i = 0; i < tamano; i++){
						if (e[i].popularity >= umb_popularity){
							vectHijoI[x] = e[i];
							x++;
						} else {
							vectHijoD[y] = e[i];
							y++;
						}
						(*a)->umbral = umb_popularity;
					}
				} else {
					for (int i = 0; i < tamano; i++){
						if (e[i].popularity > umb_popularity){
							vectHijoI[x] = e[i];
							x++;
						} else {
							vectHijoD[y] = e[i];
							y++;
						}
						(*a)->umbral = umb_popularity;
					}
				}
				break;
			case 9:
				printf("\033[31m numDeadRelations");
                /*
                cuenta_datos_clases res;
                cuenta_vivos_muertos_clase_numDeadRelations(e, tamano, umb_numDead, &res);
                if((res.clase_si_vivos+res.clase_no_vivos) > (res.clase_si_muertos + res.clase_no_muertos))
                    (*a)->isAlive = true;
                else
                    (*a)->isAlive = false;
                (*a)->pregunta = -1;
                */
                 // Todo esto es porque peta con numDeadRelations JEJ
                for (int i = 0; i < tamano; i++){
					if (e[i].numDeadRelations > umb_numDead){
						vectHijoI[x] = e[i];
						x++;
					} else {
						vectHijoD[y] = e[i];
						y++;
					}
                    (*a)->umbral = umb_numDead;
				}
				break;
		}

    
        printf("  entropia[%.18F] clase_si[%d]\033[0m\n",entropias_clases[clase_seleccionada][0], x); 
        printf("UMB_POP = [%F]\n",umb_popularity);
        printf("AL HIJO IZQUIERDO VAN ESTOS ELEMENTOS: ");
		print_data(vectHijoI, x); 
		printf("AL HIJO DERECHO VAN ESTOS ELEMENTOS: ");
		print_data(vectHijoD, y); 
        
		
        printf("    \033[34m\033[21mHIJO IZQUIERDO\033[0m\n");
		crearArbolDecision(&((*a)->izda), vectHijoI, x);
        //free(vectHijoI);
        printf("    \033[34m\033[21mHIJO DERECHO\033[0m\n");
		crearArbolDecision(&((*a)->dcha), vectHijoD, y); 
        //free(vectHijoD);
        if(clase_seleccionada!= -1)
            clase_utilizada[clase_seleccionada] = false;
        //free(e);
        
    } 
}


bool asignarIsAlive(datos dato, tipoArbolBin a){
    bool isAliveParaElDato;
    if(a->pregunta == -1){
        //~ printf("ESTOY EN UNA HOJA\n");
        //~ printf("%s\n", a->isAlive ? "\033[32mESTOY VIVO\033[0m" : "\033[31mESTOY MUERTO\033[0m");
        return a->isAlive;
    } else {
        bool hijoIzq = false;
        switch(a->pregunta){
            case 0:
                if(dato.male)
                    hijoIzq = true;
                break;
            case 1:
                if(dato.book1)
                    hijoIzq = true;
                break;
            case 2:
                if(dato.book2)
                    hijoIzq = true;
                break;
            case 3:
                if(dato.book3)
                    hijoIzq = true;
                break;
            case 4:
                if(dato.book4)
                    hijoIzq = true;
            case 5:
                if(dato.book5)
                    hijoIzq = true;
                break;
            case 6:
                if(dato.isMarried)
                    hijoIzq = true;
                break;
            case 7:
                if(dato.isNoble)
                    hijoIzq = true;
                break;
            case 8:
                if(dato.popularity >= a->umbral)
                    hijoIzq = true;
                break;
            case 9:
                if(dato.numDeadRelations > a->umbral)
                    hijoIzq = true;
                break;
        }
        
        if (hijoIzq)
            isAliveParaElDato = asignarIsAlive(dato, a->izda); 
        else
            isAliveParaElDato = asignarIsAlive(dato, a->dcha); 
        
        return isAliveParaElDato;
    }
}


void testData(datos * testData, tipoArbolBin a){

    FILE * f = fopen("csv/testDataAsignado.csv","w+");
    for (int i=0; i<C_ENTRENO; i++){
        bool b = asignarIsAlive(testData[i],a);
        if (testData[i].isAlive == b) aciertos++;
        testData[i].isAlive = b;
        fprintf(f,"%d,",testData[i].male);
        fprintf(f,"%d,",testData[i].book1);
        fprintf(f,"%d,",testData[i].book2);
        fprintf(f,"%d,",testData[i].book3);
        fprintf(f,"%d,",testData[i].book4);
        fprintf(f,"%d,",testData[i].book5);
        fprintf(f,"%d,",testData[i].isMarried);
        fprintf(f,"%d,",testData[i].isNoble);
        fprintf(f,"%d,",(int)(testData[i].numDeadRelations*10.0f));
        fprintf(f,"%.18F,",testData[i].popularity);
        fprintf(f,"%d\n",testData[i].isAlive);
    } 

    printf("\033[32mTOTAL ACIERTOS = [%d]\nPORCENTAJE ACIERTOS = [%.18F]\033[0m\n",aciertos,(double)aciertos/(double)C_ENTRENO);
	printf("NUM TOTAL DATOS EN HOJAS %d\n",numero_de_datos_en_hojas);
}
