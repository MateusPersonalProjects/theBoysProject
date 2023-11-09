#include "missao.h"
#include "base.h"
#include "heroi.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 6)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)


typedef struct mundo{
  int nHerois;
  Heroi Herois[N_HEROIS];
  int nBases;
  Base bases[N_BASES];
  int nMissoes;
  Missao missoes[N_MISSOES];
  int nHabilidades;
  int tamanhoMundo[2];
  int relogio;
}Mundo;
