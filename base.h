#include "TAD_queueInt.h"
#include "TAD_set.h"

typedef struct base{
  int id;
  int lotacao;
  LinkedList presentes; // Conjunto
  struct queue fila;
  int local[2];
}Base;

void avisa;

