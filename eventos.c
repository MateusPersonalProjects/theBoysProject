#include "eventos.h"

#include <stdlib.h>
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
    espera = ((h->paciencia) > (10 * (b->fila->end)));

  // Caso espera true criamos o evento espera
  if (espera) {
    inicializarEvento(&proxEvento, t, 1);
    proxEvento->heroi = h;
    proxEvento->base = b;
    h->baseID = b->id;
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

  idHeRetirado = (int *)malloc(sizeof(int));

  // Retira-se heroi da fila da base b
  displaceQ(b->fila, idHeRetirado);
  // Identificamos quem é o heroi apartir de seu id
  hRetirado = world->Herois[*idHeRetirado];

  // Inserimos o heroi no conjunto de presentes da base b
  insertEndLL(&(b->presentes->elementos), hRetirado->id, 0);

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

Evento *sai(int t, Heroi *h, Base *b, Mundo *world, Evento **extra) {
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
  *extra = proxEventoA;

  return proxEventoV;
}

// Função viaja retorna um evento
Evento *viaja(int t, Heroi *h, Base *d, Mundo *world) {
  Evento *proxEvento;
  int distancia, duracao;

  // Calcula a distancia cartesiana entre duas bases
  distancia = distCart(world->bases[h->baseID], d);
  duracao = distancia / h->velocidade;

  // inicializa o proximo evento chega
  inicializarEvento(&proxEvento, t + duracao, 0);
  proxEvento->heroi = h;
  proxEvento->base = d;

  return proxEvento;
}

/* Função responsavel por chegar se a missao pode ser realizada pelos herois de
 * uma base Retorna true caso possa, caso contrario retorna false
 */
bool missaoCheck(int t, LinkedList *distBases, Missao *missao, Mundo *mundo) {
  LinkedList *habHerois;
  Base *baseAtual;
  Heroi *heroiAtual;
  bool flag = false;
  Node *walker;

  inicializarLL(&habHerois);
  // Verifica todas as bases
  while (!isEmptyLL(distBases) && !flag) {
    baseAtual = mundo->bases[distBases->start->auxData];

    // Ponteiro para o node da linked list que possui o id do heroi atual
    walker = baseAtual->presentes->elementos->start;

    while (walker != NULL) {
      heroiAtual = mundo->Herois[walker->data];
      // Realiza a união das habilidades
      uniaoPlus(heroiAtual->habilidade->elementos, habHerois);
      // Passa para o proximo heroi dentro da base
      walker = walker->next;
    }

    flag = contem(habHerois, missao->habilidades->elementos);

    printf("%6d: MISSAO %d BASE %d: [", t, missao->id, baseAtual->id);
    displayLL(habHerois);
    printf("]\n");
    // Limpa a lista de habHerois
    while (!isEmptyLL(habHerois)) deleteNodeLL(habHerois, habHerois->start);

    if (!flag)
      // Retira a base da lista
      deleteNodeLL(distBases, distBases->start);
  }

  free(habHerois);

  return flag;
}

// Adiciona pontos de experiencia para todos os herois dentro de uma base
void missaoExpAdder(Base *base, Mundo *mundo) {
  Node *walkerHeroi;
  Heroi *heroiAtual;

  walkerHeroi = base->presentes->elementos->start;

  while (walkerHeroi != NULL) {
    heroiAtual = mundo->Herois[walkerHeroi->data];
    (heroiAtual->exp)++;
    walkerHeroi = walkerHeroi->next;
  }
}

bool missao(int t, Missao *missao, Mundo *mundo, Evento **proxEvento) {
  LinkedList *distBases;
  bool flag;

  // Inicializa uma lista de bases
  inicializarLL(&distBases);

  // Calcula o dist entre base e missao
  for (int i = 0; i < N_BASES; i++)
    insertEndLL(&distBases, (int)distCartMissao(mundo->bases[i], missao), i);

  // Ordena pela distancia
  // printf("\nAntes de ordenar\n");
  // sortLL(distBases);
  // printf("\nOrdenado\n");

  // Verifica se foi possivel realizar a missão
  flag = missaoCheck(t, distBases, missao, mundo);

  if (flag) {
    // Muda status da missao para cumprida
    missao->status = true;

    // Adiciona experiencia para todos os herois da base
    missaoExpAdder(mundo->bases[distBases->start->auxData], mundo);

    printf("%6d: MISSAO %d CUMPRIDA BASE %d HEROIS: [", t, missao->id,
           distBases->start->auxData);
    displayLL(mundo->bases[distBases->start->auxData]->presentes->elementos);
    printf("]\n");
  } else {
    inicializarEvento(proxEvento, (t + (24 * 60)), 7);
    (*proxEvento)->missao = missao;
  }
  // Limpa a lista de bases
  while (!isEmptyLL(distBases)) deleteNodeLL(distBases, distBases->start);
  free(distBases);
  return flag;
}

// Um asteroide cai no mundo e destroi tudo
void asteroide(Mundo *mundo) { cleanMundo(mundo); }

// int main(void) {
//   Mundo *mundo;
//   Evento extra;
//   int tempo = 1;

//   startMundo(&mundo);

//   chega(tempo, mundo->Herois[0], mundo->bases[0]);

//   espera(tempo, mundo->Herois[0], mundo->bases[0]);

//   desiste(tempo, mundo->Herois[0], mundo);

//   avisa(tempo, mundo->bases[0], mundo);

//   entra(tempo, mundo->Herois[0], mundo->bases[0]);

//   sai(tempo, mundo->Herois[0], mundo->bases[0], mundo, &extra);

//   viaja(tempo, mundo->Herois[0], mundo->bases[0], mundo);

//   return 0;
// }
