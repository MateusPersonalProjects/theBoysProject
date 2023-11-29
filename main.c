#include "eventos.h"

int main(void) {
  srand(time(NULL));

  Mundo *mundo;
  if (!startMundo(&mundo)) {
    printf("Erro Fatal! Impossivel alocar memória.\n");
    return 1;
  }

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
        break;
      // Trata evento entra
      case 4:
        break;
      // Trata evento sai
      case 5:
        break;
      // Trata evento viaja
      case 6:
        break;
    }
    if (eventosFuturos->inicio->tempo != relogioAtual) relogioAtual++;
  }

  return 0;
}
