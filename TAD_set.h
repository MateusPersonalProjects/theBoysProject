#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "TAD_linkedList.h"

typedef struct set{
  LinkedList *elementos;
} Set;

bool startSet(Set **conjunto);
// Realiza a união entre os conjuntos e o salv em result
bool uniao(LinkedList *listOne, LinkedList *listTwo, LinkedList *result);

bool uniaoPlus(LinkedList *listOne, LinkedList *result);
// Realiza a interseccao entre dois conjuntos e o salva em result
bool interseccao(LinkedList *listOne, LinkedList *listTwo, LinkedList *result);

// Retorna true se o elemento existe no conjunto, caso contrario retorna false
bool existe(LinkedList *list, int element);

// Retorna true caso listTwo esteja dentro de listOne, caso contrario retorna
// false
bool contem(LinkedList *listOne, LinkedList *listTwo);

// Imprime um conjunto
void imprime(LinkedList *list);

// Retorna true caso os conjuntos forem iguais, caso contrario retorna false
bool igual(LinkedList *listOne, LinkedList *listTwo);

bool duplicado(LinkedList *list);
