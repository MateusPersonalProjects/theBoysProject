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
bool isEmpty(LinkedList *head);

// Insere um elemento no fim da lista linkada
void insertEnd(LinkedList **head, int element);

// Printa toda a lista linkada na tela
void displayLL(LinkedList *head);

// Procura um elemento na lista linkada
// Retorna true caso tenha encontrado e false caso não
bool search(LinkedList *head, int element);
