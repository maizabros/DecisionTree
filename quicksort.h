typedef struct dat{
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

void quicksort_popularity(datos *, int, int);
void quicksort_numDeadRelations(datos *, int, int);
