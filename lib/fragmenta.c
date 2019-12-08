/**********************************/
/*       LIBRERIA FRAGMENTA       */
/**********************************/
/* Autor: Adrian Maiza            */
/* Fecha: 30/10/2018              */
/* Version 1.0                    */
/**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **fragmenta(const char *buffer){ //Esta funcion fragmenta un buffer de entrada en una lista de strings con cada argumento como elemento de la lista
   char *b_copy;
   char **arg;
   char *token; 
   int  i=0,cont_p; //Variable de recorrido y variable contador

	b_copy = (char *)malloc(strlen(buffer)+1); //Asigna memoria a b_copy con el tamaño de buffer
   strcpy(b_copy,buffer); //Copia el buffer en b_copy
   
   token = strtok((char *)buffer," ");  //copia en token el primer argumento
   while (token != NULL) { //Este bucle cuenta el numero de argumentos que hay en buffer
		if (strlen(token)>0) { //Mientras el tamaño del token se amayor a 0 
			cont_p++;
		}
      token = strtok(NULL," "); //copia en token el siguiente argumento

   }

   arg = (char**) malloc((cont_p)*sizeof(char *)); //Asgina memoria a arg con el tamaño de un char* por el numero de argumentos

   token = strtok(b_copy," "); //copia en token el primer argumento

   while (token != NULL){ //Mientras el argumento no sea nulo sigue iterando
		if (strlen(token)>0){ //Mientras el tamaño del token sea mayor a 0
			arg[i]=(char*)malloc(strlen(token)+1); //Asigna memoria a arg[i] con el tamaño del token +1
      	strcpy(arg[i],token); //Copia el contenido del token en arg[i]
      	i++;
		}
		token = strtok(NULL," "); //Asigna a token el siguiente argumento
   } 
   arg[i]=NULL; //Asigna NULL al ultimo elemento  
	free(b_copy); //Libera la copia del buffer
   return arg; //Devuelve la lista de argumentos
}


void delete_arg(char** arg){

   int i=0;

  	if(arg != NULL){ //Mientras arg no sea nulo
		while (arg[i] != NULL){ //Mientras arg[i] no sea nulo
     		free(arg[i]); //Libera memoria de arg[i]
	  		i++;
	  	}
  		free(arg); //Libera memoria de arg
  	}
}

//El ultimo bucle de delete_arg es necesario para ir eliminando cad arg[i] uno a uno antes de elimniar arg.
//Asi se elimina por completo
