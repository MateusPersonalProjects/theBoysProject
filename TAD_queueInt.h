#include <stdbool.h>
#include <stdio.h>

#define TAM 100

struct queue {
  int end;
  int line[TAM];
};

bool isFilledQ(struct queue *queue);

bool isEmptyQ(struct queue *queue);

bool emplaceQ(struct queue *queue, int member);

bool displaceQ(struct queue *queue, int *member);

bool showFrontQ(struct queue *queue, int *member);

bool jumpLineQ(struct queue *queue, int member, int position);
