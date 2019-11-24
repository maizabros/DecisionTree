#include "quicksort.h"


void quicksort_popularity(datos data[], int ini, int fin){
	if (ini < fin){
		int i = ini + 1;
		int d = fin;
		datos pivote = data[ini];
		
		while (data[i].popularity <= pivote.popularity && i < fin){
			i++;
		}
		while (data[d].popularity >= pivote.popularity && d > ini){
			d--;
		}
		while (i < d){
			datos aux;
			aux = data[i];
			data[i] = data[d];
			data[d] = aux;
			while (data[i].popularity <= pivote.popularity && i < fin){
				i++;
			}
			while (data[d].popularity >= pivote.popularity && d > ini){
				d--;
			}

		}
		datos aux;
		aux = data[d];
		data[d] = pivote;
		data[ini] = aux;
		
		quicksort_popularity(data, ini, d-1);
		quicksort_popularity(data, d+1, fin);
		
	}
}
void quicksort_numDeadRelations(datos data[], int ini, int fin){
	if (ini < fin){
		int i = ini + 1;
		int d = fin;
		datos pivote = data[ini];
		
		while (data[i].numDeadRelations <= pivote.numDeadRelations && i < fin){
			i++;
		}
		while (data[d].numDeadRelations >= pivote.numDeadRelations && d > ini){
			d--;
		}
		while (i < d){
			datos aux;
			aux = data[i];
			data[i] = data[d];
			data[d] = aux;
			while (data[i].numDeadRelations <= pivote.numDeadRelations && i < fin){
				i++;
			}
			while (data[d].numDeadRelations >= pivote.numDeadRelations && d > ini){
				d--;
			}

		}
		datos aux;
		aux = data[d];
		data[d] = pivote;
		data[ini] = aux;
		
		quicksort_numDeadRelations(data, ini, d-1);
		quicksort_numDeadRelations(data, d+1, fin);
		
	}
}
