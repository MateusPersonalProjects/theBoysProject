#include "eventos.h"

/*
  Função chega retorna um evento
  Verifica se é possivel entrar em uma base
  ou se o herói possui paciencia para aguardar na fila
*/
Evento *chega(int t, Heroi *h, Base *b) {
  bool espera;
  Evento *proxEvento;

  // Verifica se ha espaço base e se a fila esta vazia
  if (!baseCheia(b) && isEmptyQ(b->fila)) espera = true;
  // Caso contrario verifica se o heroi possui paciencia para aguardar na fila
  else
    espera = ((h->paciencia) > (10 * (b->fila->end) + 1));

  // Caso espera true criamos o evento espera
  if (espera) {
    inicializarEvento(&proxEvento, t, 1);
    proxEvento->heroi = h;
    proxEvento->base = b;
    // Caso contrario cria-se o evento desiste
  } else {
    inicializarEvento(&proxEvento, t, 2);
    proxEvento->heroi = h;
    proxEvento->base = b;
  }

  // O evento criado é retornado para que posso ser inserido na Lef
  return proxEvento;
}

// Funçãp espera retorna um evento
Evento *espera(int t, Heroi *h, Base *b) {
  Evento *proxEvento;

  // Colocamos o heroi na fila de espera da base
  emplaceQ(b->fila, h->id, N_HEROIS);

  // inicialiamos o proximo evento avisa
  inicializarEvento(&proxEvento, t, 3);
  proxEvento->base = b;

  return proxEvento;
}

// Função desiste retorna um evento
Evento *desiste(int t, Heroi *h, Mundo *world) {
  Evento *proxEvento;

  // Pega-se o id de uma base aleatorio dentro do mundo
  int randomBase = randomInteger(0, N_BASES - 1);

  // Inicializamos o proximo evento viaja
  inicializarEvento(&proxEvento, t, 6);
  proxEvento->heroi = h;
  proxEvento->base = world->bases[randomBase];

  return proxEvento;
}

// Função avisa retorna um evento
Evento *avisa(int t, Base *b, Mundo *world) {
  Evento *proxEvento;
  int *idHeRetirado;
  Heroi *hRetirado;

  // Retira-se heroi da fila da base b
  displaceQ(b->fila, idHeRetirado);
  // Identificamos quem é o heroi apartir de seu id
  hRetirado = world->Herois[*idHeRetirado];

  // Inserimos o heroi no conjunto de presentes da base b
  insertEndLL(&(b->presentes->elementos), hRetirado->id);

  // Inicializa o proximo evento entra
  inicializarEvento(&proxEvento, t, 4);
  proxEvento->heroi = hRetirado;
  proxEvento->base = b;

  return proxEvento;
}

// Função entra retorna um evento
Evento *entra(int t, Heroi *h, Base *b) {
  Evento *proxEvento;

  int tpb = 15 + h->paciencia * randomInteger(1, 20);

  // Inicializa o proximo evento sai
  inicializarEvento(&proxEvento, t + tpb, 5);
  proxEvento->base = b;
  proxEvento->heroi = h;

  return proxEvento;
}

Evento *sai(int t, Heroi *h, Base *b, Mundo *world, Evento *extra) {
  Evento *proxEventoV, *proxEventoA;
  Node *heroiSaindo;

  // Pega-se o id de uma base aleatorio dentro do mundo
  int randomBase = randomInteger(0, N_BASES - 1);

  // Procura o heroi dentro da base;
  searchLL(b->presentes->elementos, h->id, &heroiSaindo);

  // Retira o heroi da base
  deleteNodeLL(b->presentes->elementos, heroiSaindo);

  // Inicializa o proximo evento viaja
  inicializarEvento(&proxEventoV, t, 6);
  proxEventoV->heroi = h;
  proxEventoV->base = world->bases[randomBase];

  // Inicializa o proximo evento avisa
  inicializarEvento(&proxEventoA, t, 3);
  proxEventoA->heroi = h;
  proxEventoA->base = b;

  // Extra recebe o proximo evento avisa
  extra = proxEventoA;

  return proxEventoV;
}

void viaja(int t, Heroi *h, Base *b) {}
