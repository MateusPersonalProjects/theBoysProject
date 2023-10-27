#include <stdbool.h>
#include <stdio.h>

#define TAM 100

// Define a estrutura da fila
struct queue {
  int end;
  int line[TAM];
};

// Returna true caso a fila esteja cheia, caso nao esteja retorna falso
bool isFilled(struct queue *queue) {
  if (queue->end == TAM)
    return true;
  else
    return false;
}

// Retorna true caso a fila esteja vazia, caso nao esteja retorna falso
bool isEmpty(struct queue *queue) {
  if (queue->end == 0)
    return true;
  else
    return false;
}

// Adiciona um novo item na fila
bool emplace(struct queue *queue, int member) {
  if (isFilled(queue))
    return false;
  else {
    queue->line[queue->end] = member;
    (queue->end)++;
    return true;
  }
}

// Retira um item da fila e o retorna em *member
bool displace(struct queue *queue, int *member) {
  if (isEmpty(queue)) {
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
bool showFront(struct queue *queue, int *member) {
  if (isEmpty(queue))
    return false;
  else {
    *member = queue->line[0];
    return true;
  }
}

// Permite adicionar um novo item em qualquer posição da fila
bool jumpLine(struct queue *queue, int member, int position) {
  if (isFilled(queue))
    return false;

  else if (isEmpty(queue) || position > queue->end) {
    emplace(queue, member);
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
//   struct queue kleber;
//   kleber.end = 0;

//   int member;

//   for (int i = 0; i < 10; i++) emplace(&kleber, 0 + i);

//   jumpLine(&kleber, 99, 10);

//   for (int i = 0; i < 11; i++) {
//     displace(&kleber, &member);
//     printf("%d ", member);
//   }

//   return 0;
// }
