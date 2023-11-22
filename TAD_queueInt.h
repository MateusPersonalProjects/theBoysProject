#include <stdbool.h>

typedef struct queue {
  int end;
  int *line;
} Queue;

bool startQueue(Queue **line, int tam);

bool isFilledQ(struct queue *queue, int tam);

bool isEmptyQ(struct queue *queue);

bool emplaceQ(struct queue *queue, int member, int tam);

bool displaceQ(struct queue *queue, int *member);

bool showFrontQ(struct queue *queue, int *member);

bool jumpLineQ(struct queue *queue, int member, int position, int tam);
