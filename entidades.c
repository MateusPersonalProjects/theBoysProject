#include "entidades.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool startHeroi(Heroi **heroi, int id) {
  Set *habilidades;
  int quantHab, hab;

  *heroi = (Heroi *)malloc(sizeof(Heroi));
  if (*heroi == NULL) return false;

  (*heroi)->id = id;
  (*heroi)->exp = 0;
  (*heroi)->paciencia = randomInteger(0, 100);
  (*heroi)->velocidade = randomInteger(50, 5000);

  quantHab = randomInteger(1, 3);

  startSet(&habilidades);

  for (int i = 0; i < quantHab; i++) {
    hab = randomInteger(0, N_HABILIDADES);
    insertEndLL(&(habilidades->elementos), hab);
  }

  (*heroi)->habilidade = habilidades;
  return true;
}

bool startBase(Base **base, int id) {
  Set *inside;
  Queue *line;

  *base = (Base *)malloc(sizeof(Base));
  if (*base == NULL) return false;

  (*base)->id = id;
  (*base)->local[0] = randomInteger(0, N_TAMANHO_MUNDO - 1);
  (*base)->local[1] = randomInteger(0, N_TAMANHO_MUNDO - 1);

  startSet(&inside);
  startQueue(&line, N_HEROIS);

  (*base)->presentes = inside;
  (*base)->fila = line;
  return true;
}

bool startMissao(Missao **missao, int id) {
  Set *habilidades;
  int quantHab, hab;

  *missao = (Missao *)malloc(sizeof(Missao));
  if (*missao == NULL) return false;

  (*missao)->id = id;
  (*missao)->local[0] = randomInteger(0, N_TAMANHO_MUNDO - 1);
  (*missao)->local[1] = randomInteger(0, N_TAMANHO_MUNDO - 1);

  if (!startSet(&habilidades)) return false;

  quantHab = randomInteger(6, 10);

  for (int i = 0; i < quantHab; i++) {
    hab = randomInteger(0, N_HABILIDADES);
    insertEndLL(&(habilidades->elementos), hab);
  }

  (*missao)->habilidades = habilidades;
  return true;
}

bool startMundo(Mundo **mundo) {
  (*mundo)->nHerois = N_HEROIS;
  (*mundo)->nBases = N_BASES;
  (*mundo)->nMissoes = N_MISSOES;
  (*mundo)->nHabilidades = N_HABILIDADES;

  for (int i = 0; i < (*mundo)->nHerois; i++)
    if (!startHeroi(&((*mundo)->Herois[i]), i)) return false;

  for (int i = 0; i < (*mundo)->nBases; i++)
    if (!startBase(&((*mundo)->bases[i]), i)) return false;

  for (int i = 0; i < (*mundo)->nMissoes; i++)
    if (!startMissao(&((*mundo)->missoes[i]), i)) return false;

  return true;
}

int main(void) {
  // ------------------ Teste Herois --------------------
  Heroi *osHerois[N_HEROIS];

  srand(time(NULL));
  for (int i = 0; i < N_HEROIS; i++) {
    startHeroi(&osHerois[i], i);
    printf("Heroi: %d Habilidades: ", osHerois[i]->id);

    displayLL(osHerois[i]->habilidade->elementos);
    printf("\n");
  }

  // -------------------- Teste Bases --------------------
  Base *asBases[N_BASES];

  for (int i = 0; i < N_BASES; i++) {
    startBase(&asBases[i], i);
    printf("Base: %d Localização X: %d Y: %d \n", asBases[i]->id,
           asBases[i]->local[0], asBases[i]->local[1]);
  }

  // ------------------- Teste Missoes ---------------------
  Missao *asMissoes[N_MISSOES];

  for (int i = 0; i < N_MISSOES; i++) {
    startMissao(&asMissoes[i], i);
    printf("Missao: %d Localização: (%d, %d) Habilidades: ", asMissoes[i]->id,
           asMissoes[i]->local[0], asMissoes[i]->local[1]);
    displayLL(asMissoes[i]->habilidades->elementos);
    printf("\n");
  }

  return 0;
}
