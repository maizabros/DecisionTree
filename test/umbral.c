#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "pilaEnterosDinamicaEDITADO.h"

#define N 1557

typedef struct datos_t{
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
int main(void){
}
float umbral(datos *vect, char* str_umbral){
	int total_Vivos,total_Muertos,PosEntMin=0;
	for(int j=0;j<N;j++){
		if(vect[j].isAlive==1) total_Vivos++;
	}
	total_Muertos=N-total_Vivos;
	tipoPila p;
	nuevaPila(&p);
	bool ant,sig;
	float Ent=0,umbral=0;
	float MinEnt=100;
	ant=(vect[0]).isAlive;
	sig=(vect[1]).isAlive;
	tipoElementoPila x;

	for(int i=1;i<=N;i++){
		if(vect[i].isAlive==1){
			x.muertos_Izq=i-x.vivos_Izq;
			x.vivos_Izq++;
		} else{
			x.vivos_Izq=i-x.muertos_Izq;
			x.muertos_Izq++;
		}
		if(ant!=sig){
			x.muertos_Dch=total_Muertos-x.muertos_Izq;
			x.vivos_Dch=total_Vivos-x.vivos_Izq;
			x.pos=i;
			apilar(&p,x);
		}
		if(i<N){
			ant=(vect[i]).isAlive;
			sig=(vect[i+1]).isAlive;                        //Aqui estas accediendo a vec[i+1] que no existe porque te sales de la tabla por eso he hecho el if para no salirte en la ultima
		}
	}
	while((p)->sig!=NULL){
		
		Ent=(x.pos/N)*((x.vivos_Izq/x.pos)*log2(x.pos/x.vivos_Izq)+(x.muertos_Izq/x.pos)*log2(x.pos/x.muertos_Izq))+((N-x.pos+1)/N)*
            ((x.vivos_Dch/x.pos)*log2(x.pos/x.vivos_Dch)+(x.muertos_Dch/x.pos)*log2(x.pos/x.muertos_Dch));
		if(Ent<MinEnt){
			MinEnt=Ent;
			PosEntMin=x.pos;
		}
		p=(p)->sig;
	}
	Ent=(x.pos/N)*((x.vivos_Izq/x.pos)*log2(x.pos/x.vivos_Izq)+(x.muertos_Izq/x.pos)*log2(x.pos/x.muertos_Izq))+((N-x.pos)/N)*
        ((x.vivos_Dch/x.pos)*log2(x.pos/x.vivos_Dch)+(x.muertos_Dch/x.pos)*log2(x.pos/x.muertos_Dch));
	if(Ent<MinEnt){
			MinEnt=Ent;
			PosEntMin=x.pos;
	}							//Para tratar el ultimo elemento de la pila porque se quedaba sin tratar
	//Calculo del umbral
    if (strcmp(str_umbral,"numDeadRelations"))
	    umbral = ((vect[PosEntMin].numDeadRelations+vect[PosEntMin-1].numDeadRelations)/2);
    else if (strcmp(str_umbral,"popularity"))
	    umbral = ((vect[PosEntMin].popularity+vect[PosEntMin-1].popularity)/2);
    return umbral;

}
