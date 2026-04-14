#include "../src/vector.h"
#include <stdio.h>

#define INT(x) (&(int){x})

int main() {
  vector v;
  vector_make(&v, 10, sizeof(int));
  vector_push_back(&v, INT(10));
  return 0;
}
