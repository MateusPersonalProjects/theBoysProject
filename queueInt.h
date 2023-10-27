#include <stdbool.h>
#include <stdio.h>

#define TAM 100

struct queue {
  int end;
  int line[TAM];
};

bool isFilled(struct queue *queue);

bool isEmpty(struct queue *queue);

bool emplace(struct queue *queue, int member);

bool displace(struct queue *queue, int *member);

bool showFront(struct queue *queue, int *member);

bool jumpLine(struct queue *queue, int member, int position);
