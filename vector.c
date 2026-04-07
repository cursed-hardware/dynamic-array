#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TYPE_INT,
  TYPE_DOUBLE,
} data_type_t;

typedef struct {
  void *data;
  size_t len;
  size_t capacity;
  data_type_t data_type;
} vector;

vector *make_vector(size_t capacity, data_type_t data_type) {
  vector *s = malloc(sizeof(vector));
  if (s == NULL)
    return NULL;

  s->len = 0;
  s->capacity = capacity;
  s->data_type = data_type;

  size_t size_of_data;
  switch (data_type) {
  case TYPE_INT:
    size_of_data = sizeof(int);
    break;
  case TYPE_DOUBLE:
    size_of_data = sizeof(double);
    break;
  default:
    return NULL;
  }

  s->data = malloc(capacity * size_of_data);
  if (s->data == NULL)
    return NULL;

  memset(s->data, 0, capacity * size_of_data);

  return s;
}

int main() {
  vector *v1 = make_vector(10, TYPE_INT);
  for (int i = 0; i < 10; i++) {
    *(int *)(v1->data) = i;
    printf("%d) %d\n", i, *(int *)(v1->data));
  }

  vector *v2 = make_vector(10, TYPE_DOUBLE);
  for (int i = 0; i < 10; i++) {
    *(double *)(v2->data) = i * 1.25;
    printf("%d) %f\n", i, *(double *)(v2->data));
  }
}
