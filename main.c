#include "eventos.h"

int main(void) {
  srand(time(NULL));

  /* --------------- GENESIS DO MUNDO ------------------------ */

  // Cria-se o mundo e o inicializa
  Mundo *mundo;
  if (!startMundo(&mundo)) {
    printf("Erro Fatal! Impossivel alocar memória.\n");
    return 1;
  }

  // Cria-se a LEF e a inicializa
  Lef *eventosFuturos;
  if (!inicializarLef(&eventosFuturos)) {
    printf("Erro Fatal! Impossivel alocar memória.\n");
  }

  /* ---------------- EVENTOS INICIAIS ---------------------- */

  // Herois brotam do void e vão para as bases
  for (int i = 0; i < mundo->nHerois; i++) {
    Evento *evento;
    int tempo = randomInteger(0, 4320);
    (mundo->Herois[i])->baseID = randomInteger(0, (mundo->nBases) - 1);

    // Cria o evento da chegada no heroi na base
    inicializarEvento(&evento, tempo, 0);
  }

  int relogioAtual = T_INICIO;

  while (relogioAtual <= T_FIM_DO_MUNDO) {
    int tipoEvento = eventosFuturos->inicio->tipo;
    Evento *proxEvent, *proxEventExtra;

    Base *avisaBase;

    printf("HELP %d:", relogioAtual);
    switch (tipoEvento) {
      // Trata evento chega
      case 0:
        proxEvent = chega(relogioAtual, eventosFuturos->inicio->heroi,
                          eventosFuturos->inicio->base);
        deleteEvent(&eventosFuturos);
        insertEventLef(&eventosFuturos, proxEvent);
        break;
      // Trata evento espera
      case 1:
        proxEvent = espera(relogioAtual, eventosFuturos->inicio->heroi,
                           eventosFuturos->inicio->base);
        deleteEvent(&eventosFuturos);
        insertEventLef(&eventosFuturos, proxEvent);
        break;
      // Trata evento desiste
      case 2:
        proxEvent = desiste(relogioAtual, eventosFuturos->inicio->heroi, mundo);
        deleteEvent(&eventosFuturos);
        insertEventLef(&eventosFuturos, proxEvent);
        break;
      // Trata evento avisa
      case 3:
        // A base precisa ser guardada uma vez que terei que deletar o evento
        // para inserir os proximos
        avisaBase = eventosFuturos->inicio->base;
        deleteEvent(&eventosFuturos);
        while (!baseCheia(avisaBase) && !isEmptyQ(avisaBase->fila)) {
          proxEvent = avisa(relogioAtual, avisaBase, mundo);
          insertEventLef(&eventosFuturos, proxEvent);
        }
        break;
      // Trata evento entra
      case 4:
        proxEvent = entra(relogioAtual, eventosFuturos->inicio->heroi,
                          eventosFuturos->inicio->base);
        deleteEvent(&eventosFuturos);
        insertEventLef(&eventosFuturos, proxEvent);
        break;
      // Trata evento sai
      case 5:
        proxEvent = sai(relogioAtual, eventosFuturos->inicio->heroi,
                        eventosFuturos->inicio->base, mundo, proxEventExtra);
        deleteEvent(&eventosFuturos);
        insertEventLef(&eventosFuturos, proxEvent);
        insertEventLef(&eventosFuturos, proxEventExtra);
        break;
      // Trata evento viaja
      case 6:
        proxEvent = viaja(relogioAtual, eventosFuturos->inicio->heroi,
                          eventosFuturos->inicio->base, mundo);
        deleteEvent(&eventosFuturos);
        insertEventLef(&eventosFuturos, proxEvent);
        break;
    }
    if (eventosFuturos->inicio->tempo != relogioAtual) relogioAtual++;
  }
  printf("RODOU!\n");

  return 0;
}
