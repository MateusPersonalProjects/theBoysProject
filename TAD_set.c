#include "TAD_set.h"

#include <stdlib.h>

bool startSet(Set **conjunto) {
  *conjunto = (Set *)malloc(sizeof(Set));
  if (*conjunto == NULL) return false;
  inicializarLL(&(*conjunto)->elementos);
  return true;
}

// Realiza a união entre os conjuntos e o salv em result
bool uniao(LinkedList *listOne, LinkedList *listTwo, LinkedList *result) {
  Node *aux, *searched;

  // Insere todos os elementos de listOne em result
  aux = listOne->start;
  for (int i = 0; i < listOne->size; i++) {
    insertEndLL(&result, aux->data, 0);
    aux = aux->next;
  }

  // Insere os elementos de listTwo que nao estao em listONe dentro de result
  aux = listTwo->start;
  for (int i = 0; i < listTwo->size; i++) {
    if (!searchLL(listOne, aux->data, &searched))
      insertEndLL(&result, aux->data, 0);
    aux = aux->next;
  }
  return true;
}

// Realiza a união entre os conjuntos e o salv em result
bool uniaoPlus(LinkedList *listOne, LinkedList *result) {
  Node *aux, *searched;

  // Insere os elementos de listOne que nao estao em result dentro de result
  aux = listOne->start;
  for (int i = 0; i < listOne->size; i++) {
    if (!searchLL(result, aux->data, &searched))
      insertEndLL(&result, aux->data, 0);
    aux = aux->next;
  }
  return true;
}

// Realiza a interseccao entre dois conjuntos e o salva em result
bool interseccao(LinkedList *listOne, LinkedList *listTwo, LinkedList *result) {
  Node *aux, *searched;

  // Insere em result os elementos que estao em listOne e listTwo
  aux = listOne->start;
  for (int i = 0; i < listOne->size; i++) {
    if (searchLL(listTwo, aux->data, &searched))
      insertEndLL(&result, aux->data, 0);
    aux = aux->next;
  }
  return true;
}

// Retorna true se o elemento existe no conjunto, caso contrario retorna false
bool existe(LinkedList *list, int element) {
  Node *searched;
  return searchLL(list, element, &searched);
}

// Retorna true caso listTwo esteja dentro de listOne, caso contrario retorna
// false
bool contem(LinkedList *listOne, LinkedList *listTwo) {
  Node *aux, *searched;

  // Verifica se todos os elementos de listTwo estao em listOne
  aux = listTwo->start;
  for (int i = 0; i < listTwo->size; i++) {
    if (!searchLL(listOne, aux->data, &searched)) return false;
    aux = aux->next;
  }
  return true;
}

// Imprime um conjunto
void imprime(LinkedList *list) { displayLL(list); }

// Retorna true caso os conjuntos forem iguais, caso contrario retorna false
bool igual(LinkedList *listOne, LinkedList *listTwo) {
  // Se os tamanhos forem diferentes os conjuntos não são iguais
  if (listOne->size != listTwo->size) return false;

  // Os conjuntos serão iguais se e somente se listOne estiver contido em
  // listTwo e listTwo estiver contido em ListOne
  else if (!contem(listOne, listTwo) || !contem(listTwo, listOne))
    return false;
  return true;
}

bool duplicado(LinkedList *list) {
  int count;
  bool status = false;
  Node *aux, *auxExtra;

  aux = list->start;
  for (int i = 0; i < list->size; i++) {
    count = 0;
    auxExtra = list->start;
    for (int j = 0; j < list->size; j++) {
      if (aux->data == auxExtra->data) count++;
      auxExtra = auxExtra->next;
    }
    if (count > 1) {
      printf("Elemento %d apareceu %d vezes\n", aux->data, count);
      status = true;
    }
    aux = aux->next;
  }
  return status;
}

// int main(void) {
//   Set *conjunto1, *conjunto2;

//   startSet(&conjunto1);
//   startSet(&conjunto2);

//   for (int i = 0; i <= 10; i++) insertEndLL(&(conjunto1->elementos), i, 0);
//   uniaoPlus(conjunto1->elementos, conjunto2->elementos);

//   displayLL(conjunto1->elementos);
//   printf("KLeber\n");
//   displayLL(conjunto2->elementos);

//   return 0;
// }
