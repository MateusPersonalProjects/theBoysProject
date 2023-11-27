#include "entidades.h"

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
