#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Define a estrutura de Nodos da Lista Linkada
typedef struct Node {
  int data;
  struct Node *next;
} Node;

// Define a a cabeça da lista linkada
typedef struct LinkedList {
  int size;
  struct Node *start;
} LinkedList;

// Verifica se a lista linkada esta vazia
// Retorna true caso esteja, caso não esteja retorna false
bool isEmpty(LinkedList *head) {
  if (head->start == NULL) return true;
  return false;
}

// Insere um elemento no fim da lista linkada
void insertEnd(LinkedList **head, int element) {
  Node *auxNode, *new;

  // Cria um novo nodo para ser inserido
  if ((new = (Node *)malloc(sizeof(Node))) == NULL) {
    printf("Erro de alocação de memória!");
    return;
  }

  new->data = element;
  new->next = NULL;

  // Caso a lista esteja vazia atribui o novo nodo ao inicio
  if (isEmpty(*head))
    (*head)->start = new;
  else {
    auxNode = (*head)->start;
    while (auxNode->next != NULL) auxNode = auxNode->next;
    auxNode->next = new;
  }
  ((*head)->size)++;
}

// Printa toda a lista linkada na tela
void displayLL(LinkedList *head) {
  if (!isEmpty(head)) {
    Node *auxNode;
    auxNode = head->start;
    for (int i = 0; i < head->size; i++) {
      printf("%d ", auxNode->data);
      auxNode = auxNode->next;
    }
  } else
    printf("Lista Vazia!");
}

// Procura um elemento na lista linkada
// Retorna true caso tenha encontrado e false caso não
bool search(LinkedList *head, int element) {
  if (!isEmpty(head)) {
    Node *auxNode;
    auxNode = head->start;
    for (int i = 0; i < head->size; i++) {
      if (element == auxNode->data) return true;
      auxNode = auxNode->next;
    }
    return false;
  } else {
    printf("Lista Vazia!");
    return false;
  }
}

/* ---------------- EXEMPLO DE USO DA BIBLIOTECA ------------ */
/*
int main(void) {
  LinkedList *listOne;
  listOne = (LinkedList *)malloc(sizeof(LinkedList));
  listOne->size = 0;
  listOne->start = NULL;

  for (int i = 0; i < 100; i++) {
    insertEnd(&listOne, i);
  }
  displayLL(listOne);
  if (search(listOne, 100))
    printf("\nEncontrei aeho!\n");
  else
    printf("Nao encotrei\n");

  free(listOne);
}
*/
