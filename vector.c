#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  TYPE_INT,
  TYPE_DOUBLE,
  TYPE_CUSTOM,
} type_of_data_t;

typedef struct {
  void *data;
  size_t len;
  size_t capacity;
  size_t size_of_data;
} slice;

slice *make_slice(size_t capacity, size_t sizeo_of_data) {
  slice *s = malloc(sizeof(slice));
  if (s == NULL)
    return NULL;

  s->len = 0;
  s->capacity = capacity;
  s->size_of_data = sizeo_of_data;

  s->data = malloc(capacity * sizeo_of_data);
  if (s->data == NULL)
    return NULL;

  memset(s->data, 0, capacity * sizeo_of_data);

  return s;
}

int main() {
  slice *s = make_slice(10, sizeof(int));
  for (int i = 0; i < 10; i++) {
    *(int *)(s->data) = i;
    printf("%d) %d\n", i, *(int *)(s->data));
  }
}
