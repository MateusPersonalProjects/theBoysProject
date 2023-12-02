#include "TAD_linkedList.h"

bool inicializarLL(LinkedList **head) {
  *head = (LinkedList *)malloc(sizeof(LinkedList));
  if (*head != NULL) {
    (*head)->size = 0;
    (*head)->start = NULL;
    return true;
  } else
    printf("Erro Fatal - não foi possível alocar memória!");
  return false;
}

// Verifica se a lista encadeada esta vazia
// Retorna true caso esteja, caso não esteja retorna false
bool isEmptyLL(LinkedList *head) {
  if (head->start == NULL) return true;
  return false;
}

// Insere um elemento no fim da lista duplamente encadeada
void insertEndLL(LinkedList **head, int element, int auxElement) {
  Node *auxNode, *new;

  // Cria um novo nodo para ser inserido
  if ((new = (Node *)malloc(sizeof(Node))) == NULL) {
    printf("Erro de alocação de memória!");
    return;
  }

  new->data = element;
  new->auxData = auxElement;
  new->next = NULL;

  // Caso a lista esteja vazia atribui o novo nodo ao inicio
  if (isEmptyLL(*head)) {
    (*head)->start = new;
  } else {
    auxNode = (*head)->start;
    while (auxNode->next != NULL) auxNode = auxNode->next;
    auxNode->next = new;
  }
  ((*head)->size)++;
}

// Printa toda a lista encadeada na tela
void displayLL(LinkedList *head) {
  if (!isEmptyLL(head)) {
    Node *auxNode;
    auxNode = head->start;
    while (auxNode->next != NULL) {
      printf("%d ", auxNode->data);
      auxNode = auxNode->next;
    }
    printf("%d ", auxNode->data);
  } else
    printf("Lista Vazia!");
}

/* Procura um elemento na lista linkada
 Retorna true caso tenha encontrado e false caso não */
bool searchLL(LinkedList *head, int element, Node **result) {
  if (!isEmptyLL(head)) {
    Node *auxNode;
    auxNode = head->start;
    for (int i = 0; i < (head->size); i++) {
      if (element == auxNode->data) {
        *result = auxNode;
        return true;
      }
      auxNode = auxNode->next;
    }
    return false;
  } else {
    return false;
  }
}

// Deleta um node da lista duplamente encadeada
void deleteNodeLL(LinkedList *head, Node *node) {
  Node *aux, *auxTwo;

  if (head->start == node)
    head->start = node->next;
  else {
    aux = head->start;
    auxTwo = node->next;

    // Iteramos até encontrar o node que aponta para o qual queremos excluir
    while (aux->next != node) aux = aux->next;
    // Ao encontrar trocamos o node para qual ele aponta para aquele que o que
    // iremos excluir aponta
    aux->next = auxTwo;
  }
  head->size = (head->size) - 1;
  free(node);
}

// Encontra o valor mínimo dentro da lista
bool minLL(Node *inicio, Node **returning) {
  Node *aux, *min;
  bool status;

  status = false;
  aux = min = inicio;
  while (aux != NULL) {
    if (aux->data <= min->data) {
      status = true;
      min = aux;
    }
    aux = aux->next;
  }
  *returning = min;
  return status;
}

// Função de swap para lista encadeada
void swapLL(LinkedList *head, Node *one, Node *two) {
  Node *tempOne, *tempTwo, *aux;
  tempOne = tempTwo = head->start;

  if (head->start == one) {
    head->start = two;
    while (tempTwo->next != two) tempTwo = tempTwo->next;
    tempTwo->next = one;
  }

  else if (head->start == two) {
    head->start = one;
    while (tempOne->next != one) tempOne = tempOne->next;
    tempOne->next = two;
  }

  else {
    // Encontra quais são os nodes que apontam para os nodes que quero trocar
    while (tempOne->next != one) tempOne = tempOne->next;
    while (tempTwo->next != two) tempTwo = tempTwo->next;
    // realiza a troca de apontamento
    tempOne->next = two;
    tempTwo->next = one;
  }

  aux = one->next;
  one->next = two->next;
  two->next = aux;
}

// Ordena uma ou lista encadeada
// Utiliza selection sort
void sortLL(LinkedList *head) {
  Node *aux, *min;
  int count;
  for (count = 0; count < head->size; count++) {
    aux = head->start;
    for (int i = 0; i < count; i++) aux = aux->next;
    if (minLL(aux, &min)) swapLL(head, aux, min);
  }
}
