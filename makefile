parametrosCompilacao=-Wall -lm #-Wshadow
nomePrograma=theboys

all: $(nomePrograma)

$(nomePrograma): main.o entidades.o eventos.o misc.o TAD_lef.o TAD_linkedList.o TAD_queueInt.o TAD_set.o
	gcc -o $(nomePrograma) main.o entidades.o eventos.o misc.o TAD_lef.o TAD_linkedList.o TAD_queueInt.o TAD_set.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

entidades.o: entidades.h entidades.c
	gcc -c entidades.c $(parametrosCompilacao)

eventos.o: eventos.h eventos.c
	gcc -c eventos.c $(parametrosCompilacao)

misc.o: misc.h misc.c
	gcc -c misc.c $(parametrosCompilacao)

TAD_lef.o: TAD_lef.h TAD_lef.c
	gcc -c TAD_lef.c $(parametrosCompilacao)

TAD_linkedList.o: TAD_linkedList.h TAD_linkedList.c
	gcc -c TAD_linkedList.c $(parametrosCompilacao)

TAD_queueInt.o: TAD_queueInt.h TAD_queueInt.c
	gcc -c TAD_queueInt.c $(parametrosCompilacao)

TAD_set.o: TAD_set.h TAD_set.c
	gcc -c TAD_set.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
