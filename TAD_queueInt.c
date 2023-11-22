#include "TAD_queueInt.h"

#include <stdio.h>
#include <stdlib.h>

bool startQueue(Queue **line, int tam) {
  *line = (Queue *)malloc(sizeof(Queue));
  if (*line == NULL) return false;

  (*line)->line = (int *)malloc(tam * sizeof(int));
  return true;
}

// Returna true caso a fila esteja cheia, caso nao esteja retorna falso
bool isFilledQ(struct queue *queue, int tam) {
  if (queue->end == tam)
    return true;
  else
    return false;
}

// Retorna true caso a fila esteja vazia, caso nao esteja retorna falso
bool isEmptyQ(struct queue *queue) {
  if (queue->end == 0)
    return true;
  else
    return false;
}

// Adiciona um novo item na fila
bool emplaceQ(struct queue *queue, int member, int tam) {
  if (isFilledQ(queue, tam))
    return false;
  else {
    queue->line[queue->end] = member;
    (queue->end)++;
    return true;
  }
}

// Retira um item da fila e o retorna em *member
bool displaceQ(struct queue *queue, int *member) {
  if (isEmptyQ(queue)) {
    member = NULL;
    return false;
  } else {
    int *linePtr, *linePtrAux, *end;

    linePtr = queue->line;
    linePtrAux = linePtr + 1;
    end = linePtr + queue->end;

    *member = *linePtr;
    while (linePtr < end) {
      *linePtr = *linePtrAux;
      linePtr++;
      linePtrAux++;
    }
    (queue->end)--;
    return true;
  }
}

// Retorna o primeiro item da fila em *member
bool showFrontQ(struct queue *queue, int *member) {
  if (isEmptyQ(queue))
    return false;
  else {
    *member = queue->line[0];
    return true;
  }
}

// Permite adicionar um novo item em qualquer posição da fila
bool jumpLineQ(struct queue *queue, int member, int position, int tam) {
  if (isFilledQ(queue, tam))
    return false;

  else if (isEmptyQ(queue) || position > queue->end) {
    emplaceQ(queue, member, tam);
    return true;
  }

  else {
    int *linePtr, *linePtrAux, *end;

    linePtr = (queue->line) + (position);
    end = (queue->line) + (queue->end);
    linePtrAux = end + 1;

    while (end > linePtr - 1) {
      *linePtrAux = *end;
      end--;
      linePtrAux--;
    }

    (queue->end)++;
    *linePtr = member;
    return true;
  }
}

// int main(void) {
//   Queue *fila;

//   startQueue(&fila, 10);

//   for (int i = 0; i < 10; i++) emplaceQ(fila, i);
//   for (int i = 0; i < 10; i++) printf("%d ", fila->line[i]);

//   return 0;
// }
