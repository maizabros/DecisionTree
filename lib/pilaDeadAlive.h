/*
  FICHERO: pilaEnterosDinamica.h
  VERSION: 1.0.0
  HISTORICO:
  Creado por Aránzazu Jurío Munárriz el 09/09/19.
  
  Este fichero se crea sólo con intenciones de coordinación docente y como
  ayuda a sus alumnos y alumnas. La autora desautoriza expresamente su difusión, copia
  o exhibición pública (salvo entre los alumnos de las asignaturas 240301 y 250301 del
  grado en Ingeniería Informática de la UPNA).
*/

#include <stdbool.h>

typedef struct tipoElementoPila_t{
	int pos;
	int vivos_Izq;	
	int vivos_Dch;	
	int muertos_Izq;	
	int muertos_Dch;	
}tipoElementoPila;
typedef struct celdaP{
	 tipoElementoPila elem;
	 struct celdaP *sig;
 } celdaPila; 
typedef celdaPila* tipoPila;

void nuevaPila(tipoPila *);

void apilar(tipoPila *, tipoElementoPila);

void desapilar(tipoPila *);

tipoElementoPila cima(tipoPila);

bool esNulaPila(tipoPila);

