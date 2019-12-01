#include "quicksort.h"

#define QUICK_SORT_TIPO(nombreDato)                                     \
void quicksort_##nombreDato(datos * data[], int ini, int fin){            \
	if (ini < fin){                                                     \
		int i = ini + 1;                                                \
		int d = fin;                                                    \
		datos pivote = (*data)[ini];                                       \
		                                                                \
		while ((*data)[i].nombreDato <= pivote.nombreDato && i < fin){     \
			i++;                                                        \
		}                                                               \
		while ((*data)[d].nombreDato >= pivote.nombreDato && d > ini){     \
			d--;                                                        \
		}                                                               \
		while (i < d){                                                  \
			datos aux;                                                  \
			aux = (*data)[i];                                              \
			(*data)[i] = (*data)[d];                                          \
			(*data)[d] = aux;                                              \
			while ((*data)[i].nombreDato <= pivote.nombreDato && i < fin){ \
				i++;                                                    \
			}                                                           \
			while ((*data)[d].nombreDato >= pivote.nombreDato && d > ini){ \
				d--;                                                    \
			}                                                           \
                                                                        \
		}                                                               \
		datos aux;                                                      \
		aux = (*data)[d];                                                  \
		(*data)[d] = pivote;                                               \
		(*data)[ini] = aux;                                                \
		                                                                \
		quicksort_##nombreDato(data, ini, d-1);                         \
		quicksort_##nombreDato(data, d+1, fin);                         \
		                                                                \
	}                                                                   \
}                                                                       \

QUICK_SORT_TIPO(popularity);
QUICK_SORT_TIPO(numDeadRelations);
