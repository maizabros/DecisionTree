#ifndef LIBSTRUCT
#define LIBSTRUCT
#include <stdbool.h>
#define C_ENTRENO 1362
#define C_AJUSTE 192
#define C_TEST 192
typedef struct dat{
	bool male;
	bool book1;
	bool book2;
	bool book3;
	bool book4;
	bool book5;
	bool isMarried;
	bool isNoble;
	double numDeadRelations;
	double popularity;
	bool isAlive;
}datos;
typedef struct cuenta_datos{
    int clase_si_vivos;
    int clase_si_muertos;
    int clase_no_vivos;
    int clase_no_muertos;
}cuenta_datos_clases;
#endif
