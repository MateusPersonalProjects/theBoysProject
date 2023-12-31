#include "TAD_lef.h"
/*
  Função chega retorna um evento
  Verifica se é possivel entrar em uma base
  ou se o herói possui paciencia para aguardar na fila
*/
Evento *chega(int t, Heroi *h, Base *b);

// Funçãp espera retorna um evento
Evento *espera(int t, Heroi *h, Base *b);

// Função desiste retorna um evento
Evento *desiste(int t, Heroi *h, Mundo *world);

// Função avisa retorna um evento
Evento *avisa(int t, Base *b, Mundo *world);

// Função entra retorna um evento
Evento *entra(int t, Heroi *h, Base *b);

Evento *sai(int t, Heroi *h, Base *b, Mundo *world, Evento **extra);

// Função viaja retorna um evento
Evento *viaja(int t, Heroi *h, Base *d, Mundo *world);

/* Função responsavel por chegar se a missao pode ser realizada pelos herois de
 * uma base Retorna true caso possa, caso contrario retorna false
 */
bool missaoCheck(int t, LinkedList *distBases, Missao *missao, Mundo *mundo); 

// Adiciona pontos de experiencia para todos os herois dentro de uma base
void missaoExpAdder(Base *base, Mundo *mundo);

bool missao(int t, Missao *missao, Mundo *mundo, Evento **proxEvento);

void asteroide(Mundo *mundo);
