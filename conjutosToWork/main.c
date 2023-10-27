#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"

// Função que imprime as opções ao usuário
int graphicInterface() {
  int num;
  printf(
      "\nQuais das operações deseja realizar?\n"
      "2 - União \n"
      "3 - Intercção\n"
      "4 - Existe\n"
      "5 - Contem\n"
      "6 - Imprime\n"
      "7 - Igual\n"
      "8 - Duplicado\n"
      "0 - Sair \n");
  scanf("%d", &num);
  return num;
}

// Realiza a união entre os conjuntos e o salv em result
bool uniao(LinkedList *listOne, LinkedList *listTwo, LinkedList *result) {
  Node *aux;

  // Insere todos os elementos de listOne em result
  aux = listOne->start;
  for (int i = 0; i < listOne->size; i++) {
    insertEnd(&result, aux->data);
    aux = aux->next;
  }

  // Insere os elementos de listTwo que nao estao em listONe dentro de result
  aux = listTwo->start;
  for (int i = 0; i < listTwo->size; i++) {
    if (!search(listOne, aux->data)) insertEnd(&result, aux->data);
    aux = aux->next;
  }
  return true;
}

// Realiza a interseccao entre dois conjuntos e o salva em result
bool interseccao(LinkedList *listOne, LinkedList *listTwo, LinkedList *result) {
  Node *aux;

  // Insere em result os elementos que estao em listOne e listTwo
  aux = listOne->start;
  for (int i = 0; i < listOne->size; i++) {
    if (search(listTwo, aux->data)) insertEnd(&result, aux->data);
    aux = aux->next;
  }
  return true;
}

// Retorna true se o elemento existe no conjunto, caso contrario retorna false
bool existe(LinkedList *list, int element) { return search(list, element); }

// Retorna true caso listTwo esteja dentro de listOne, caso contrario retorna
// false
bool contem(LinkedList *listOne, LinkedList *listTwo) {
  Node *aux;

  // Verifica se todos os elementos de listTwo estao em listOne
  aux = listTwo->start;
  for (int i = 0; i < listTwo->size; i++) {
    if (!search(listOne, aux->data)) return false;
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

int main(void) {
  // Define e inicializa as listas linkadas
  LinkedList *listOne, *listTwo, *listUniao, *listIntersec;

  listOne = (LinkedList *)malloc(sizeof(LinkedList));
  listOne->size = 0;
  listOne->start = NULL;

  listTwo = (LinkedList *)malloc(sizeof(LinkedList));
  listTwo->size = 0;
  listTwo->start = NULL;

  listUniao = (LinkedList *)malloc(sizeof(LinkedList));
  listUniao->size = 0;
  listUniao->start = NULL;

  listIntersec = (LinkedList *)malloc(sizeof(LinkedList));
  listIntersec->size = 0;
  listIntersec->start = NULL;

  // Parte responsável pela comunicação com o usuário
  int status = 1, num;

  // Preenche os conjuntos antes de iniciar as ações
  printf(
      "Bem - vindo!\nPor favor preencha os conjuntos antes de "
      "continuar...\n\n");
  printf(
      "PREENCHENDO CONJUNTO 1\n"
      "Digite -1 para parar de preencher o conjunto.\n");
  scanf("%d", &num);
  while (num != -1) {
    insertEnd(&listOne, num);
    scanf("%d", &num);
  }
  printf(
      "\nPREENCHENDO CONJUNTO 2\n"
      "Digite -1 para parar de preencher o conjunto.\n");
  scanf("%d", &num);
  while (num != -1) {
    insertEnd(&listTwo, num);
    scanf("%d", &num);
  }

  // Loop resposavel por executar as ações desejadas pelo usuário
  // A entrada do menu é salva em status e enquanto o usuário nao digitar 0 o
  // menu continuara sendo exibido
  while (status) {
    status = graphicInterface();
    switch (status) {
      case (2):
        uniao(listOne, listTwo, listUniao);
        printf("A união do conjunto...\n");
        displayLL(listUniao);
        printf("\n");
        break;

      case (3):
        interseccao(listOne, listTwo, listIntersec);
        printf("A intersecção do conjunto...\n");
        displayLL(listIntersec);
        printf("\n");
        break;

      case (4):
        printf("Qual valor você deseja verificar a existencia (Conjunto um): ");
        scanf("%d", &num);
        if (existe(listOne, num))
          printf("EXISTE\n");
        else
          printf("NAO EXISTE\n");
        break;

      case (5):
        if (contem(listOne, listTwo))
          printf("O conjunto um contem o conjunto dois\n");
        else
          printf("O conjunto um nao contem o conjunto dois\n");
        break;

      case (6):
        printf("Imprimindo conjunto 1...\n");
        imprime(listOne);
        printf("\nImprimindo conjunto 2...\n");
        imprime(listTwo);
        printf("\n");
        break;

      case (7):
        if (igual(listOne, listTwo))
          printf("Os conjuntos são iguais\n");
        else
          printf("Os conjuntos são diferentes");
        break;

      case (8):
        printf("Checando por elementos duplicados no conjunto 1....\n");
        if (!duplicado(listOne))
          printf("Não temos elementos duplicados no conjunto 1\n");
        printf("Checando por elementos duplicados no conjunto 2....\n");
        if (!duplicado(listTwo))
          printf("Não temos elementos duplicados no conjunto 2\n");
        break;
    }
  }

  free(listOne);
  free(listTwo);
  free(listUniao);
  free(listIntersec);
  return 0;
}
