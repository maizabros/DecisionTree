#include <stdio.h>
typedef struct dat{
	char nombre[100];
	int numDeadRelations;
	float popularity;
}datos;
void quicksort_popularity(datos *, int, int);
void quicksort_numDeadRelations(datos *, int, int);
int main(void){
	int n;
	printf("Introduce el número de elementos del vector: ");
	scanf("%d", &n);
	datos vector[n];
	for (int i = 0; i < n; i++){
		printf("\nPersonaje %d\n", i);
		printf("Introduce el nombre: ");
		scanf("%s", vector[i].nombre);
		printf("Introduce el número de muertes con el que está relacionado: ");
		scanf("%d", &vector[i].numDeadRelations);
		printf("Introduce el índice de popularidad: ");
		scanf("%f", &vector[i].popularity);
	}

	quicksort_popularity(vector, 0, n-1);
	printf("\nOrdenado por índice de popularidad:\n");
	for (int i = 0; i < n; i++){
		printf("%s  ", vector[i].nombre);
	}
	printf("\n");
	quicksort_numDeadRelations(vector, 0, n-1);
	printf("\nOrdenado por número de muertes:\n");
	for (int i = 0; i < n; i++){
		printf("%s  ", vector[i].nombre);
	}
	printf("\n");
	
	return 0;
}

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
		
		while (data[i].numDeadRelations < pivote.numDeadRelations && i < fin){
			i++;
		}
		while (data[d].numDeadRelations > pivote.numDeadRelations && d > ini){
			d--;
		}
		while (i < d){
			datos aux;
			aux = data[i];
			data[i] = data[d];
			data[d] = aux;
			while (data[i].numDeadRelations < pivote.numDeadRelations && i < fin){
				i++;
			}
			while (data[d].numDeadRelations > pivote.numDeadRelations && d > ini){
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

