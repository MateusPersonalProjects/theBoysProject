#include "entidades.h"

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
    insertEndLL(&(habilidades->elementos), hab);
  }

  (*heroi)->habilidade = habilidades;
  return true;
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

  // Aloca memoria para o conjunto de habilidades
  if (!startSet(&habilidades)) return false;

  quantHab = randomInteger(6, 10);

  // Define as habilidades
  for (int i = 0; i < quantHab; i++) {
    hab = randomInteger(0, N_HABILIDADES);
    insertEndLL(&(habilidades->elementos), hab);
  }

  (*missao)->habilidades = habilidades;
  return true;
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

// int main(void) {
//   // ------------------ Teste Herois --------------------
//   // Heroi *osHerois[N_HEROIS];

//   srand(time(NULL));
//   // for (int i = 0; i < N_HEROIS; i++) {
//   //   startHeroi(&osHerois[i], i);
//   //   printf("Heroi: %d Habilidades: ", osHerois[i]->id);

//   //   displayLL(osHerois[i]->habilidade->elementos);
//   //   printf("\n");
//   // }

//   // // -------------------- Teste Bases --------------------
//   // Base *asBases[N_BASES];

//   // for (int i = 0; i < N_BASES; i++) {
//   //   startBase(&asBases[i], i);
//   //   printf("Base: %d Localização X: %d Y: %d \n", asBases[i]->id,
//   //          asBases[i]->local[0], asBases[i]->local[1]);
//   // }

//   // // ------------------- Teste Missoes ---------------------
//   // Missao *asMissoes[N_MISSOES];

//   // for (int i = 0; i < N_MISSOES; i++) {
//   //   startMissao(&asMissoes[i], i);
//   //   printf("Missao: %d Localização: (%d, %d) Habilidades: ",
//   //   asMissoes[i]->id,
//   //          asMissoes[i]->local[0], asMissoes[i]->local[1]);
//   //   displayLL(asMissoes[i]->habilidades->elementos);
//   //   printf("\n");
//   // }

//   Mundo *oMundo;
//   startMundo(&oMundo);

//   for (int i = 0; i < oMundo->nHerois; i++) {
//     printf("Heroi: %d Habilidades: ", oMundo->Herois[i]->id);

//     displayLL(oMundo->Herois[i]->habilidade->elementos);
//     printf("\n");
//   }

//   for (int i = 0; i < oMundo->nBases; i++) {
//     printf("Base: %d Localização X: %d Y: %d \n", oMundo->bases[i]->id,
//            oMundo->bases[i]->local[0], oMundo->bases[i]->local[1]);
//   }

//   for (int i = 0; i < oMundo->nMissoes; i++) {
//     printf("Missao: %d Localização: (%d, %d) Habilidades: ",
//            oMundo->missoes[i]->id, oMundo->missoes[i]->local[0],
//            oMundo->missoes[i]->local[1]);
//     displayLL(oMundo->missoes[i]->habilidades->elementos);
//     printf("\n");
//   }

//   return 0;
// }
