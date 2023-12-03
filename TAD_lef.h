#include "entidades.h"

/*
 Define a estrutura de evento

 Relação de tipos
 0 - Chega, 1 - Espera, 2 - Desiste, 3 - Avisa, 4 - Entra
 5 - Sai, 6 - Viaja
*/
typedef struct evento{
  int tempo;
  int tipo;
  Heroi *heroi;
  Base *base;
  Missao *missao;
  struct evento *prox;

} Evento;


typedef struct lef{
  int tam;
  Evento *inicio;

} Lef;

// Inicializa um evento
// Retorna true caso tenha conseguido alocar memoria
// caso contrario retorna false
bool inicializarEvento(Evento **evento, int time, int tipo); 

// Inicializa uma lista de eventos futuros
// Retorna true caso tenha conseguido alocar memoria
// caso contrario retorna false
bool inicializarLef(Lef **lef); 

// Verifica se a Lef esta vazia
// Retorna true caso esteja se nao retorna false
bool isEmptyLef(Lef *lef);

// Insere um evento de forma ordenada na lef
void insertEventLef(Lef **lef, Evento *evento);

// Deleta o primeiro evento da Lef
// Retorna true se foi possivel deletar o evento
// Se não retorna false
bool deleteEvent(Lef **lef);

void cleanLef(Lef *lef);
