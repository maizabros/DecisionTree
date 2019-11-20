#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include "libfrag.h"

#define C_ENTRENO 1557
#define BUFF 1024

typedef struct datos{
	bool male;
	bool book1;
	bool book2;
	bool book3;
	bool book4;
	bool book5;
	bool isMarried;
	bool isNoble;
	int numDeadRelations;
	float popularity;
	bool isAlive;
}datos;

int main(int argc, char* argv[]){

	char * buffer = (char*)malloc(sizeof(char)*BUFF);
	datos vector_datos[C_ENTRENO*sizeof(datos)];


	if(argc < 2){
		printf("Numero de argumentos invalido.\nNecesita indicar fichero CSV de datos.\n");
		return EXIT_FAILURE;
	} else {
		int fd = open(argv[1], O_RDONLY, 0400);
		int dup = dup2(fd, STDIN_FILENO);
		if(fd == -1 || dup == -1){
			perror("Error al redirigir fichero.");
			return EXIT_FAILURE;
		}
		close(fd);
	}
	
	fgets(buffer, sizeof(char)*BUFF, stdin); 
	printf("Buffer: %s\n",buffer);

	char ** headers = fragBufferExtract(buffer);
	int i=0;
	for(int i=0; i<11; i++){
		printf("%s",headers[i]);
		if (i<10) printf(", ");
	}
	while(fgets(buffer,sizeof(char)*BUFF,stdin) != NULL){
			char ** data = fragBufferExtract(buffer);
			
			vector_datos[i].male = atoi(data[0]);
			vector_datos[i].book1 = atoi(data[1]);
			vector_datos[i].book2 = atoi(data[2]);
			vector_datos[i].book3 = atoi(data[3]);
			vector_datos[i].book4 = atoi(data[4]);
			vector_datos[i].book5 = atoi(data[5]);
			vector_datos[i].isMarried = atoi(data[6]);
			vector_datos[i].isNoble = atoi(data[7]);
			vector_datos[i].numDeadRelations = atoi(data[8]);
			vector_datos[i].popularity = atof(data[9]);
			vector_datos[i].isAlive = atoi(data[10]);
			i++;
	}
	/*****************************************************************/
	/** PRINTEA LOS DATOS DESDE EL VECTOR DE STRUCT DATOS
	
	//~ for(int i=0; i<11; i++){             
		//~ printf("%s",headers[i]);
		//~ if (i<10) printf(", ");
	//~ }
	//~ printf("\n");

	//~ for(int i=0; i<1557; i++){
		//~ printf(vector_datos[i].male ? "true, " : "false, ");
		//~ printf(vector_datos[i].book1 ? "true, " : "false, ");
		//~ printf(vector_datos[i].book2 ? "true, " : "false, ");
		//~ printf(vector_datos[i].book3 ? "true, " : "false, ");
		//~ printf(vector_datos[i].book4 ? "true, " : "false, ");
		//~ printf(vector_datos[i].book5 ? "true, " : "false, ");
		//~ printf(vector_datos[i].isMarried ? "true, " : "false, ");
		//~ printf(vector_datos[i].isNoble ? "true, " : "false, ");
		//~ if (vector_datos[i].numDeadRelations < 10)
			//~ printf("%d  ,",vector_datos[i].numDeadRelations);
		//~ else
			//~ printf("%d ,",vector_datos[i].numDeadRelations);
		//~ printf("%f, ",vector_datos[i].popularity);
		//~ printf(vector_datos[i].isAlive ? "true" : "false");
		//~ printf("\n");
	//~ }
	/*****************************************************************/
	
}
