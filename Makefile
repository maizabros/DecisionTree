###############################################################
default: decisionTree 

###############################################################
# Programa principal
decisionTree: 
	@gcc -g -o decisionTree decisionTree.c  lib/libDecisionTree.o lib/libfrag.o lib/pilaDeadAlive.o lib/quicksort.o -lm
	$(info Compilando programa principal DECISIONTREE)


###############################################################
# LIBRERIAS
libfrag: lib/libfrag.c
	@gcc -g -c lib/libfrag.c -o lib/libfrag.o
	$(info Compilando librería libfrag para fragmentar CSV)

quicksort: lib/quicksort.c
	@gcc -g -c lib/quicksort.c -o lib/quicksort.o
	@cd ..
	$(info Compilando libreria quicksort modificada)

pilaEnteros: lib/pilaDeadAlive.c
	@gcc -g -c lib/pilaDeadAlive.c -o lib/pilaDeadAlive.o
	$(info Compilando libreria pilaDeadAlive)

libDecisionTree: lib/libDecisionTree.c lib/libfrag.o lib/quicksort.o lib/pilaDeadAlive.o
	@gcc -shared -g -c lib/libDecisionTree.c -Llib -lfrag -lquicksort -lpilaDeadAlive -o lib/libDecisionTree.o
	$(info Compilando libreria libDecisionTree) 

lib: libfrag quicksort pilaEnteros libDecisionTree
###############################################################

###############################################################
# Cleaners
cleanTree: 
	@rm -rf decisionTree
	$(info Eliminando objetos de las librerias)
cleanLib: 
	@rm -rf lib/*.o
	$(info Eliminando ejecutables)
cleanAll: cleanTree cleanLib
###############################################################

all: lib decisionTree
###############################################################
