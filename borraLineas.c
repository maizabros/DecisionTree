/* ********************************************* */
/* * Programa borraLineas                      * */
/* ********************************************* */
/* * Este programa solo imprime por pantalla   * */
/* * las líneas que no este repetidas en el    * */
/* * fichero CSV errores_entMin_arboles.csv    * */
/* *                                           * */
/* * Para utilizar esas lineas considere       * */
/* * redirigir la salida del programa a otro   * */
/* * fichero CSV.                              * */
/* ********************************************* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/fragmenta.h"

#define BUFF 1024

int main(int argc, char* argv[]){

    FILE * f = fopen("csv/errores_entMin_arboles.csv", "r");
    char * buffer = (char*)malloc(sizeof(char)*BUFF);

    fgets(buffer,BUFF,f);
    char ** args1 = fragmenta(buffer);
    for(int i=0; i<6; i++){
        printf("%s ",args1[i]); 
    }
    printf("\n");
    while(fgets(buffer,BUFF,f) != NULL){
        
        char ** args2 = fragmenta(buffer);
        if (strcmp(args1[1],args2[1]) != 0 || strcmp(args1[3],args2[3]) !=0 || strcmp(args1[5],args2[5]) != 0){
            for(int i=0; i<6; i++){
                printf("%s ",args2[i]); 
                strcpy(args1[i],args2[i]);
            }
            printf("\n");
        }
    }
}
