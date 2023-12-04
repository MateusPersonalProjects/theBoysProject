#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Define a estrutura de Nodos da Lista Encadeada
typedef struct Node {
  int data;
  int auxData;
  struct Node *next;
} Node;

// Define a cabeça da lista encadeada
typedef struct LinkedList {
  int size;
  struct Node *start;
} LinkedList;

bool inicializarLL(LinkedList **head);

// Verifica se a lista encadeada esta vazia
// Retorna true caso esteja, caso não esteja retorna false
bool isEmptyLL(LinkedList *head);

// Insere um elemento no fim da lista duplamente encadeada
void insertEndLL(LinkedList **head, int element, int auxElement);

// Insere de forma ordenada em uma Linked List
bool insertOrdLL(LinkedList **head, int data, int auxData);
// Printa toda a lista encadeada na tela
void displayLL(LinkedList *head);

/* Procura um elemento na lista linkada
 Retorna true caso tenha encontrado e false caso não */
bool searchLL(LinkedList *head, int element, Node **result);

// Deleta um node da lista duplamente encadeada
void deleteNodeLL(LinkedList *head, Node *node);

// Encontra o valor mínimo dentro da lista
bool minLL(Node *inicio, Node **returning);

// Função de swap para lista encadeada
void swapLL(LinkedList *head, Node *one, Node *two);

// Ordena uma ou lista encadeada
// Utiliza selection sort
void sortLL(LinkedList *head);

void cleanLL(LinkedList *head);
