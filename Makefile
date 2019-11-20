all: libfrag recogeDatos 
libfrag: libfrag.c
	@gcc -g -c libfrag.c
	$(info Compilando librería)

recogeDatos: recogeDatos.c libfrag.o
	@gcc -g -o recogeDatos recogeDatos.c libfrag.o
	$(info Compilando recogeDatos)

clean: 
	@rm -rf recogeDatos libfrag.o
	$(info Eliminando ejecutables)
