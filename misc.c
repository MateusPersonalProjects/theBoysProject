#include "misc.h"

int randomInteger(int min, int max) {
  int num, random;
  num = rand();
  random = (num % (max - min + 1)) + min;
  return random;
}
