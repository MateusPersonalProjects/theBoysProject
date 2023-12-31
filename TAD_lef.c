#include "TAD_lef.h"

// Inicializa um evento
// Retorna true caso tenha conseguido alocar memoria
// caso contrario retorna false
bool inicializarEvento(Evento **evento, int time, int tipo) {
  *evento = (Evento *)malloc(sizeof(Evento));
  if (*evento == NULL) return false;
  (*evento)->tempo = time;
  (*evento)->tipo = tipo;
  (*evento)->base = NULL;
  (*evento)->heroi = NULL;
  (*evento)->missao = NULL;
  (*evento)->prox = NULL;
  return true;
}

// Inicializa uma lista de eventos futuros
// Retorna true caso tenha conseguido alocar memoria
// caso contrario retorna false
bool inicializarLef(Lef **lef) {
  *lef = (Lef *)malloc(sizeof(Lef));
  if (*lef == NULL) return false;
  (*lef)->tam = 0;
  (*lef)->inicio = NULL;
  return true;
}

// Verifica se a Lef esta vazia
// Retorna true caso esteja se nao retorna false
bool isEmptyLef(Lef *lef) {
  if (lef->inicio == NULL) return true;
  return false;
}

// Insere um evento de forma ordenada na Lef
void insertEventLef(Lef **lef, Evento *evento) {
  Evento *aux, *auxProx;
  // Caso a Lef esteja vazia, o evento é inserido no inicio
  if (isEmptyLef((*lef)))
    (*lef)->inicio = evento;
  else {
    aux = (*lef)->inicio;

    // Tratando caso do inicio
    if (evento->tempo <= aux->tempo) {
      (*lef)->inicio = evento;
      evento->prox = aux;
    }

    else {
      while ((aux->prox != NULL) && (evento->tempo >= (aux->prox)->tempo)) {
        aux = aux->prox;
      }
      if (aux->prox == NULL)
        aux->prox = evento;
      else {
        auxProx = aux->prox;
        aux->prox = evento;
        evento->prox = auxProx;
      }
    }
  }
  (*lef)->tam++;
}

// Deleta o primeiro evento da Lef
// Retorna true se foi possivel deletar o evento
// Se não retorna false
bool deleteEvent(Lef **lef) {
  Evento *aux, *toClean;
  if (isEmptyLef(*lef)) return false;

  toClean = (*lef)->inicio;

  // Pego proximo evento da lista e torno ele o primeiro
  aux = (*lef)->inicio->prox;
  (*lef)->inicio = aux;

  // Limpo da memoria o evento que era o primeiro
  toClean = NULL;
  free(toClean);
  return true;
}

// Free em todos os elementos da lista de eventos futuros
void cleanLef(Lef *lef) {
  while (!isEmptyLef(lef)) deleteEvent(&lef);
  free(lef);
}
