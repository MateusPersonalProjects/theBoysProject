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
    evento->heroi = mundo->Herois[i];
    evento->base = mundo->bases[(mundo->Herois[i])->baseID];
    insertEventLef(&eventosFuturos, evento);
  }

  for (int i = 0; i < mundo->nMissoes; i++) {
    Evento *ev;
    int tempo = randomInteger(0, T_FIM_DO_MUNDO);

    inicializarEvento(&ev, tempo, 7);
    ev->missao = mundo->missoes[i];
    insertEventLef(&eventosFuturos, ev);
  }

  int relogioAtual = T_INICIO;

  while (relogioAtual <= T_FIM_DO_MUNDO) {
    int tipoEvento = eventosFuturos->inicio->tipo;
    Evento *proxEvent, *proxEventExtra;

    proxEventExtra = (Evento *)malloc(sizeof(Evento));

    Base *avisaBase;

    printf("%6d: ", relogioAtual);
    if (relogioAtual == eventosFuturos->inicio->tempo) {
      switch (tipoEvento) {
        // Trata evento chega
        case 0:
          printf("CHEGA HEROI %2d BASE %d (%2d/%2d) ",
                 eventosFuturos->inicio->heroi->id,
                 eventosFuturos->inicio->base->id,
                 eventosFuturos->inicio->base->presentes->elementos->size,
                 eventosFuturos->inicio->base->lotacao);
          proxEvent = chega(relogioAtual, eventosFuturos->inicio->heroi,
                            eventosFuturos->inicio->base);
          if (proxEvent->tipo == 1)
            printf("ESPERA\n");
          else
            printf("DESISTE\n");
          deleteEvent(&eventosFuturos);
          insertEventLef(&eventosFuturos, proxEvent);
          break;
        // Trata evento espera
        case 1:
          printf("ESPERA HEROI %2d BASE %d (%2d)\n",
                 eventosFuturos->inicio->heroi->id,
                 eventosFuturos->inicio->base->id,
                 eventosFuturos->inicio->base->fila->end);
          proxEvent = espera(relogioAtual, eventosFuturos->inicio->heroi,
                             eventosFuturos->inicio->base);
          deleteEvent(&eventosFuturos);
          insertEventLef(&eventosFuturos, proxEvent);
          break;
        // Trata evento desiste
        case 2:
          printf("DESISTE HEROI %2d BASE %d\n",
                 eventosFuturos->inicio->heroi->id,
                 eventosFuturos->inicio->base->id);
          proxEvent =
              desiste(relogioAtual, eventosFuturos->inicio->heroi, mundo);
          deleteEvent(&eventosFuturos);
          insertEventLef(&eventosFuturos, proxEvent);
          break;
        // Trata evento avisa
        case 3:
          // A base precisa ser guardada uma vez que terei que deletar o evento
          // para inserir os proximos
          printf("AVISA PORTEIRO BASE %d (%2d/%2d) ",
                 eventosFuturos->inicio->base->id,
                 eventosFuturos->inicio->base->presentes->elementos->size,
                 eventosFuturos->inicio->base->lotacao);

          printf("FILA [ ");
          displayQ(eventosFuturos->inicio->base->fila);
          printf("]\n");

          avisaBase = eventosFuturos->inicio->base;
          deleteEvent(&eventosFuturos);
          while (!baseCheia(avisaBase) && !isEmptyQ(avisaBase->fila)) {
            proxEvent = avisa(relogioAtual, avisaBase, mundo);
            insertEventLef(&eventosFuturos, proxEvent);
            printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d \n", relogioAtual,
                   proxEvent->base->id, proxEvent->heroi->id);
          }
          break;
        // Trata evento entra
        case 4:
          printf("ENTRA HEROI %2d BASE %d (%2d/%2d) SAI ",
                 eventosFuturos->inicio->heroi->id,
                 eventosFuturos->inicio->base->id,
                 eventosFuturos->inicio->base->presentes->elementos->size,
                 eventosFuturos->inicio->base->lotacao);

          proxEvent = entra(relogioAtual, eventosFuturos->inicio->heroi,
                            eventosFuturos->inicio->base);
          deleteEvent(&eventosFuturos);
          insertEventLef(&eventosFuturos, proxEvent);
          printf("%d\n", proxEvent->tempo);
          break;
        // Trata evento sai
        case 5:
          proxEvent = sai(relogioAtual, eventosFuturos->inicio->heroi,
                          eventosFuturos->inicio->base, mundo, &proxEventExtra);
          printf("SAI HEROI %2d BASE %d (%2d/%2d)\n",
                 eventosFuturos->inicio->heroi->id,
                 eventosFuturos->inicio->base->id,
                 eventosFuturos->inicio->base->presentes->elementos->size,
                 eventosFuturos->inicio->base->lotacao);

          deleteEvent(&eventosFuturos);
          insertEventLef(&eventosFuturos, proxEvent);
          insertEventLef(&eventosFuturos, proxEventExtra);
          break;
        // Trata evento viaja
        case 6:
          printf("VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d ",
                 eventosFuturos->inicio->heroi->id,
                 eventosFuturos->inicio->heroi->baseID,
                 eventosFuturos->inicio->base->id,
                 distCart(mundo->bases[eventosFuturos->inicio->heroi->baseID],
                          eventosFuturos->inicio->base),
                 eventosFuturos->inicio->heroi->velocidade);

          proxEvent = viaja(relogioAtual, eventosFuturos->inicio->heroi,
                            eventosFuturos->inicio->base, mundo);
          deleteEvent(&eventosFuturos);
          insertEventLef(&eventosFuturos, proxEvent);

          printf("CHEGA %d\n", proxEvent->tempo);
          break;

        // Trata evento missao
        case 7:
          if (!missao(relogioAtual, eventosFuturos->inicio->missao, mundo,
                      &proxEvent)) {
            deleteEvent(&eventosFuturos);
            insertEventLef(&eventosFuturos, proxEvent);
          }
          break;
      }
    } else
      printf("\n");
    if (eventosFuturos->inicio->tempo != relogioAtual) relogioAtual++;
  }
  printf("RODOU!\n");

  return 0;
}
