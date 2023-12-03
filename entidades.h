#include "TAD_queueInt.h"
#include "TAD_set.h"
#include "misc.h"
#include <time.h>

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 6)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)

// -------------------------- DEFINE A ENTIDADE HEROI ------------------------
typedef struct heroi {
  int id;
  Set *habilidade;
  int paciencia;
  int velocidade;
  int exp;
  int baseID;
} Heroi;

bool startHeroi(Heroi **heroi, int id);

// -------------------------- DEFINE A ENTIDADE BASE --------------------------
typedef struct base {
  int id;
  int lotacao;
  Set *presentes;
  Queue *fila;
  int local[2];
} Base;

bool startBase(Base **base, int id);

bool baseCheia(Base *b);

int distCart(Base *b, Base *d);
// -------------------------- DEFINE A ENTIDADE MISSAO -------------------------
typedef struct missao {
  int id;
  Set *habilidades;
  int local[2];
  bool status;
} Missao;

bool startMissao(Missao **missao, int id);

int distCartMissao(Base *b, Missao *d);
// ----------------------- DEFINE A ENTIDADE MUNDO -----------------------------
typedef struct mundo {
  int nHerois;
  Heroi *Herois[N_HEROIS];
  int nBases;
  Base *bases[N_BASES];
  int nMissoes;
  Missao *missoes[N_MISSOES];
  int nHabilidades;
  int tamanhoMundo[2];
  int relogio;
} Mundo;

bool startMundo(Mundo **mundo);

int logMissoesCumpridas(Mundo *mundo);
