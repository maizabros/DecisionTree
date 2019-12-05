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
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "quicksort.h"
#include "libfrag.h"
#include "pilaDeadAlive.h"
#include "arbolBin.h"

#define C_ENTRENO 1362 
#define C_AJUSTE 292
#define C_TEST 292
#define BUFF 1024
#define HEADERS_SIZE 128
int N = C_ENTRENO;
double umb_popularity;
int umb_numDead;
int aciertos = 0;
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

void recogerDatos(datos ** vector_datos, datos ** datos_ajuste, datos ** datos_test,char ** headers, int fd){

	int dup = dup2(fd, STDIN_FILENO);
	if(fd == -1 || dup == -1){
		perror("Error al redirigir fichero.");
		return;
	}
	close(fd);

	char * buffer = (char*)malloc(sizeof(char)*BUFF);
	(*vector_datos) = (datos*)malloc(C_ENTRENO*sizeof(datos));
	(*datos_ajuste) = (datos*)malloc(C_AJUSTE*sizeof(datos));
	(*datos_test) = (datos*)malloc(C_TEST*sizeof(datos));

	
	fgets(buffer, sizeof(char)*BUFF, stdin); 
	headers = fragBufferExtract(buffer);
	int i=0;
	while(fgets(buffer,sizeof(char)*BUFF,stdin) != NULL){
			
            if(i == C_ENTRENO) break;
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
            if(i == C_AJUSTE) break;
			char ** data = fragBufferExtract(buffer);

			(*datos_ajuste)[i].male = atoi(data[0]);
			(*datos_ajuste)[i].book1 = atoi(data[1]);
			(*datos_ajuste)[i].book2 = atoi(data[2]);
			(*datos_ajuste)[i].book3 = atoi(data[3]);
			(*datos_ajuste)[i].book4 = atoi(data[4]);
            (*datos_ajuste)[i].book5 = atoi(data[5]);
			(*datos_ajuste)[i].isMarried = atoi(data[6]);
			(*datos_ajuste)[i].isNoble = atoi(data[7]);
			(*datos_ajuste)[i].numDeadRelations = strtod(data[8],NULL)/10.0f;
			(*datos_ajuste)[i].popularity = strtod(data[9],NULL);
			(*datos_ajuste)[i].isAlive = atoi(data[10]);
			i++;
    } while(fgets(buffer,sizeof(char)*BUFF,stdin) != NULL);
    i = 0;
	do{
            if(i == C_TEST) break;
			char ** data = fragBufferExtract(buffer);
			
			(*datos_test)[i].male = atoi(data[0]);
			(*datos_test)[i].book1 = atoi(data[1]);
			(*datos_test)[i].book2 = atoi(data[2]);
			(*datos_test)[i].book3 = atoi(data[3]);
			(*datos_test)[i].book4 = atoi(data[4]);
            (*datos_test)[i].book5 = atoi(data[5]);
			(*datos_test)[i].isMarried = atoi(data[6]);
			(*datos_test)[i].isNoble = atoi(data[7]);
			(*datos_test)[i].numDeadRelations = strtod(data[8],NULL)/10.0f;
			(*datos_test)[i].popularity = strtod(data[9],NULL);
			(*datos_test)[i].isAlive = atoi(data[10]);
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
	
	return ((arg1)*(arg2*arg3+arg4*arg5) + (arg6)*(arg7*arg8 + arg9*arg10));
}

double umbral(datos * vect, char* str_umbral, int totalVivos){

	double total_Muertos;
    int PosEntMin = 0;
	bool ant,sig;
	double Ent = 100, umbral = 0;
	double MinEnt = 100;
	
    if(strcmp(str_umbral, "popularity") == 0)
        quicksort_popularity(&vect, 0, N-1);
    else if(strcmp(str_umbral, "numDeadRelations") == 0)
        quicksort_numDeadRelations(&vect, 0, N-1);
    else{
        printf("\033[31mERROR en UMBRAL:\033[0m clase no válida\nSaliendo...\n\n");
        exit(EXIT_FAILURE);
    }

	total_Muertos = N - totalVivos;
	tipoPila p;
	nuevaPila(&p);
	ant = (vect[0]).isAlive;
	sig = (vect[1]).isAlive;
	tipoElementoPila x;
    x.vivos_Izq = 1;

    if(ant == 0) x.muertos_Izq = 1;
    else x.muertos_Izq = 0;
    x.vivos_Dch = 0;
    x.muertos_Dch = 0;
	
    for(int i=1; i<N; i++){
		if(ant != sig){
			x.muertos_Dch = total_Muertos - x.muertos_Izq;
			x.vivos_Dch = totalVivos - x.vivos_Izq;
			x.pos = i;
			apilar(&p,x);
		}
		if(vect[i].isAlive == 1){
			x.vivos_Izq++;
		} else{
			x.muertos_Izq++;
		}
        ant = vect[i].isAlive;
        sig = vect[i+1].isAlive;
	}

	while(!esNulaPila(p)){
		x = cima(p);
        Ent = entropia_umbral(x);
		if(Ent<MinEnt){
			MinEnt = Ent;
			PosEntMin = x.pos;
		}
        desapilar(&p);
	}
	Ent=entropia_umbral(x);
	if(Ent<MinEnt){
			MinEnt = Ent;
			PosEntMin = x.pos;
	} //Para tratar el ultimo elemento de la pila porque se quedaba sin tratar
	//Cálculo del umbral
    if (strcmp(str_umbral,"numDeadRelations") == 0){
	    umbral = ((double)(vect[PosEntMin+1].numDeadRelations + vect[PosEntMin].numDeadRelations)/2);
    } else if (strcmp(str_umbral,"popularity") == 0)
	    umbral = ((double)(vect[PosEntMin+1].popularity+vect[PosEntMin].popularity)/2);
    return umbral;

}

void calculo_entropia_clases(datos * vect, double totalVivos, double entropias_clases[10][2]){

    cuenta_datos_clases res;
    double totalMuertos = N - totalVivos;
    double arg1 = -(totalVivos/N)*log2(totalVivos/N);
    if (totalVivos == 0) arg1 = 0;
    double arg2 = -(totalMuertos/N)*log2(totalMuertos/N);
    if (totalMuertos== 0) arg2 = 0;
    double entropia_C = arg1 + arg2; 
    umb_numDead = umbral(vect,"numDeadRelations",(int)totalVivos);
    umb_popularity = umbral(vect, "popularity", totalVivos);

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

}

int calculo_maxima_ganancia(double entropias_clases[10][2]){
	double max_ganancia = -0.1f; //Para que cuando haya 0 al menos elija a una
    int clase_seleccionada = -1;

    for(int i = 0; i<10; i++){
        if(max_ganancia < entropias_clases[i][0]){
            clase_seleccionada = i;
            max_ganancia = entropias_clases[i][0];
        }
    }

	return clase_seleccionada;
}

void crearArbolDecision(tipoArbolBin * a, datos * e, int tamano, double entMin){

    N = tamano;
    double totalVivos = 0;
    for(int i=0; i<tamano; i++){
        if(e[i].isAlive == 1)
            totalVivos++;
    }
    double totalMuertos = tamano - totalVivos;
    double arg1 = -(totalVivos/N)*log2(totalVivos/N);
    if (totalVivos == 0) arg1 = 0;
    double arg2 = -(totalMuertos/N)*log2(totalMuertos/N);
    if (totalMuertos== 0) arg2 = 0;
    double entropia_C = arg1 + arg2; 
    if (tamano == 0 || isnan(entropia_C) || entropia_C <= entMin){
        if(esVacio(*a))
            nuevoArbolBin(a, e, tamano); 

        if(entropia_C > 0.0f){
            if(totalVivos >= totalMuertos)
                (*a)->isAlive = true; 
            else
                (*a)->isAlive = false; 
        } else
            (*a)->isAlive = e[0].isAlive;
        return;

    } else {
        if(esVacio(*a))
            nuevoArbolBin(a, e, tamano); 
		double entropias_clases[10][2];
		calculo_entropia_clases(e , (double) totalVivos, entropias_clases);

		datos * vectHijoI;
		datos * vectHijoD;
		int clase_seleccionada = calculo_maxima_ganancia(entropias_clases);
        if (entropias_clases[clase_seleccionada][0] <= 0.0001f  || entropia_C <= entMin){

            if(entropia_C > 0.0f){
                if(totalVivos >= totalMuertos)
                   (*a)->isAlive = true; 
                else
                   (*a)->isAlive = false; 
            } else {
                (*a)->isAlive = e[0].isAlive;
            }
            return;
        }

        (*a)->pregunta = clase_seleccionada; //Asigna la pregunta que se hará para recorrer el arbol

		vectHijoI = (datos *)malloc(sizeof(datos) * (int)entropias_clases[clase_seleccionada][1]);
		vectHijoD = (datos *)malloc(sizeof(datos) * (tamano - (int)entropias_clases[clase_seleccionada][1]));
        
		int x = 0, y = 0;
		switch(clase_seleccionada){
			case 0:
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
				if (umb_numDead != 0.0f){
                    for (int i = 0; i < tamano; i++){
                        if (e[i].numDeadRelations >= umb_numDead){
                            vectHijoI[x] = e[i];
                            x++;
                        } else {
                            vectHijoD[y] = e[i];
                            y++;
                        }
                        (*a)->umbral = umb_numDead;
                    }
                } else {
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
                }
				break;
		}

		crearArbolDecision(&((*a)->izda), vectHijoI, x, entMin);
		crearArbolDecision(&((*a)->dcha), vectHijoD, y, entMin); 
    } 
}


bool asignarIsAlive(datos dato, tipoArbolBin a){
    bool isAliveParaElDato;
    if(a->pregunta == -1){
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
                if (a->umbral != 0.0f){
                    if(dato.popularity >= a->umbral)
                        hijoIzq = true;
                } else {
                    if(dato.popularity > a->umbral)
                        hijoIzq = true;
                }
                break;
            case 9:
                if (a->umbral != 0.0f){
                    if(dato.numDeadRelations >= a->umbral)
                        hijoIzq = true;
                } else {
                    if(dato.numDeadRelations > a->umbral)
                        hijoIzq = true;
                }
                break;
        }
        
        if (hijoIzq)
            isAliveParaElDato = asignarIsAlive(dato, a->izda); 
        else
            isAliveParaElDato = asignarIsAlive(dato, a->dcha); 
        
        return isAliveParaElDato;
    }
}

double testData(datos * testData, tipoArbolBin a, int tamano){

    aciertos=0.0f;
    FILE * f = fopen("csv/testDataAsignado.csv","w+");
    for (int i=0; i<tamano; i++){
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

    printf("NUMERO DE DATOS DE ENTRENAMIENTO = [%d]\n",C_ENTRENO);
    printf("NUMERO DE DATOS DE AJUST = [%d]\n",C_AJUSTE);
    printf("NUMERO DE DATOS DE TEST = [%d]\n",C_TEST);
    printf("\033[32mTOTAL ACIERTOS = [%d]\n",aciertos);
    printf("PORCENTAJE ACIERTOS = [%.18F]\033[0m\n",(double)aciertos/(double)tamano);
    return (1.0f - ((double)aciertos/(double)tamano));
}

void writeTreeCSV(double e[4][2]){

    FILE * f = fopen("csv/errores_minEnt_arboles.csv", "a");

    for (int i=0; i<4; i++)
        fprintf(f,"%F %F ",e[i][0], e[i][1]);
    fprintf(f,"\n");

}
