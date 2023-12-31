#include "entidades.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*
 * Inicializa um heroi
 * Retorna true se foi possivel alocar memória, se não retorna false
 */
bool startHeroi(Heroi **heroi, int id) {
  Set *habilidades;
  int quantHab, hab;

  // Aloca memoria para o heroi
  *heroi = (Heroi *)malloc(sizeof(Heroi));
  if (*heroi == NULL) return false;

  // Define seus atributos padroes
  (*heroi)->id = id;
  (*heroi)->exp = 0;
  (*heroi)->paciencia = randomInteger(0, 100);
  (*heroi)->velocidade = randomInteger(50, 5000);

  // Define Sua quantidade de habilidades
  quantHab = randomInteger(1, 3);

  // Inicializa o conjunto de habilidades do heroi
  if (!startSet(&habilidades)) return false;

  // Insere habilidades do conjunto de habilidades
  for (int i = 0; i < quantHab; i++) {
    hab = randomInteger(0, N_HABILIDADES);
    insertEndLL(&(habilidades->elementos), hab, 0);
  }

  (*heroi)->habilidade = habilidades;
  return true;
}

// Free em todos os atributos de heroi
void cleanHeroi(Heroi *heroi) {
  cleanSet(heroi->habilidade);
  free(heroi);
}

/*
 * Inicializa uma base
 * Retorna true se foi possivel alocar memória, se não retorna false
 */
bool startBase(Base **base, int id) {
  Set *inside;
  Queue *line;

  // Aloca memoria para a base
  *base = (Base *)malloc(sizeof(Base));
  if (*base == NULL) return false;

  // Define atributos padroes
  (*base)->id = id;
  (*base)->local[0] = randomInteger(0, N_TAMANHO_MUNDO - 1);
  (*base)->local[1] = randomInteger(0, N_TAMANHO_MUNDO - 1);
  (*base)->lotacao = randomInteger(3, 10);

  // Inicializa o conjunto de herois dentro da base
  if (!startSet(&inside)) return false;
  // Inicializa a fila de espera
  if (!startQueue(&line, N_HEROIS)) return false;

  (*base)->presentes = inside;
  (*base)->fila = line;
  return true;
}

// Retorna true caso a base esteja cheia, caso contrario retorna false
bool baseCheia(Base *b) {
  if (b->lotacao == b->presentes->elementos->size) return true;
  return false;
}

// Retorna a distancia cartesiana entre duas bases
int distCart(Base *b, Base *d) {
  int distancia;
  int xB = b->local[0], xD = d->local[0], yB = b->local[1], yD = d->local[1];

  distancia = sqrt(((xD - xB) * (xD - xB)) + ((yD - yB) * (yD - yB)));
  return distancia;
}

// Free em todos os atributos de base
void cleanBase(Base *base) {
  cleanSet(base->presentes);
  cleanQ(base->fila);
  free(base);
}
/*
 * Inicializa uma missao
 * Retorna true se foi possivel alocar memória, se não retorna false
 */
bool startMissao(Missao **missao, int id) {
  Set *habilidades;
  int quantHab, hab;

  // Aloca memoria para a missao
  *missao = (Missao *)malloc(sizeof(Missao));
  if (*missao == NULL) return false;

  // Define atributos padroes
  (*missao)->id = id;
  (*missao)->local[0] = randomInteger(0, N_TAMANHO_MUNDO - 1);
  (*missao)->local[1] = randomInteger(0, N_TAMANHO_MUNDO - 1);
  (*missao)->status = false;
  // Aloca memoria para o conjunto de habilidades
  if (!startSet(&habilidades)) return false;

  quantHab = randomInteger(6, 10);

  // Define as habilidades
  for (int i = 0; i < quantHab; i++) {
    hab = randomInteger(0, N_HABILIDADES);
    insertEndLL(&(habilidades->elementos), hab, 0);
  }

  (*missao)->habilidades = habilidades;
  return true;
}

int distCartMissao(Base *b, Missao *d) {
  int distancia;
  int xB = b->local[0], xD = d->local[0], yB = b->local[1], yD = d->local[1];

  distancia = sqrt(((xD - xB) * (xD - xB)) + ((yD - yB) * (yD - yB)));
  return distancia;
}

// Retorna a quantidade de missoes cumpridas
int logMissoesCumpridas(Mundo *mundo) {
  int result = 0;
  for (int i = 0; i < N_MISSOES; i++) {
    if (mundo->missoes[i]->status) result++;
  }
  return result;
}

// Free em todos os atributos da missao
void cleanMissao(Missao *missao) {
  cleanSet(missao->habilidades);
  free(missao);
}
/*
 * Inicializa o mundo
 * Retorna true se foi possivel alocar memória, se não retorna false
 */
bool startMundo(Mundo **mundo) {
  // Aloca memoria para o mundo
  *mundo = (Mundo *)malloc(sizeof(Mundo));
  if (*mundo == NULL) return false;

  // Define atributos padroes
  (*mundo)->nHerois = N_HEROIS;
  (*mundo)->nBases = N_BASES;
  (*mundo)->nMissoes = N_MISSOES;
  (*mundo)->nHabilidades = N_HABILIDADES;

  // Inicializa herois do mundo
  for (int i = 0; i < (*mundo)->nHerois; i++)
    if (!startHeroi(&((*mundo)->Herois[i]), i)) return false;

  // Inicializa bases do mundo
  for (int i = 0; i < (*mundo)->nBases; i++)
    if (!startBase(&((*mundo)->bases[i]), i)) return false;

  // Inicializa Missoes do mundo
  for (int i = 0; i < (*mundo)->nMissoes; i++)
    if (!startMissao(&((*mundo)->missoes[i]), i)) return false;

  return true;
}

// Free em todos os atribrutos do mundo
void cleanMundo(Mundo *mundo) {
  for (int i = 0; i < mundo->nHerois; i++) cleanHeroi(mundo->Herois[i]);

  for (int i = 0; i < mundo->nBases; i++) cleanBase(mundo->bases[i]);

  for (int i = 0; i < mundo->nMissoes; i++) cleanMissao(mundo->missoes[i]);
  free(mundo);
}
