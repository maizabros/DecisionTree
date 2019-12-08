/****************************************************/
/* Libreria de funciones para Sistemas Operativos   */
/****************************************************/
/* Last update: 14/10/2019                          */
/* Version: 0.1.7                                   */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfrag.h"

char **fragBufferExtract(const char *buffer);
void delArg(char **arg,int n);
void buffTreat (char *buffer);

char **fragBufferExtract(const char *buffer) {

	char **arg, *copy, *token;
	copy = (char*)calloc(strlen(buffer)+1, sizeof(char));
	strcpy(copy, buffer);
	int words = 1;
	token = strtok((char*)buffer,",");
	while(token!=NULL) {
		if (strlen(token) > 0)
			words++;
		token = strtok(NULL,",");
	}

	arg = (char**) malloc(words*sizeof(char*));
	int i = 0;
	token = strtok(copy,",");
	while(token != NULL) {
		if (strlen(token) > 0) {
			arg[i] = (char*)calloc(strlen(token)+1, sizeof(char));
			strcpy(arg[i],token);
			i++;
		}
		token = strtok(NULL,",");
	}
	arg[i] = NULL;
	buffTreat(arg[i-1]);
	free(copy);
	return(arg);
}

void delArg(char ** arg,int n) {

	for (int i = 0; i<n; i++){
		free((arg)[i]);
	}
	free(arg);
}

void buffTreat(char * buffer) {

	for(int i = 0; i < strlen(buffer)+1; i++) {
		if(buffer[i] == '\n'){
			buffer[i] = '\0';
		}
	}
}
