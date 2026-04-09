#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_GROW_MULT 2

typedef enum {
  VECTOR_SUCCESS,       // Успешное выполнение
  VECTOR_EQUALS_NULL,   // Проверка на нулевой вектор не пройдена
  VECTOR_MALLOC_ERROR,  // Ошибка при аллокации памяти
  VECTOR_REALLOC_ERROR, // Ошибка при аллокации памяти
} vector_errors_t;

typedef struct {
  void *data;
  size_t len;
  size_t capacity;
  size_t elem_size;
} vector;

// Выделяет память под вектор, инициализирует переменные структуры вектора
// В случае неудачи при выделении памяти возвращает нулевой указатель
// В случае успеха возвращает указатель на вектор
vector *make_vector(size_t capacity, size_t elem_size) {
  vector *v = malloc(sizeof(vector));
  if (!v)
    return NULL;

  v->len = 0;
  v->elem_size = elem_size;
  v->capacity = capacity;

  if (capacity) {
    v->data = malloc(capacity * elem_size);
    if (v->data == NULL)
      return NULL;
  }

  return v;
}

// Освобождает память массива данных и вектора
// Возвращает коды ошибок описанные в vector_errors_t
vector_errors_t free_vector(vector *v) {
  if (!v)
    return VECTOR_EQUALS_NULL;

  free(v->data);
  free(v);

  return VECTOR_SUCCESS;
}

vector_errors_t vector_push_back(vector *v, void *elem) {
  if (!v || !elem)
    return VECTOR_EQUALS_NULL;

  if (v->len == v->capacity) {
    size_t new_capacity =
        (v->capacity == 0) ? 1 : (v->capacity * VECTOR_GROW_MULT);

    void *new_data = realloc(v->data, new_capacity * v->elem_size);
    if (!new_data)
      return VECTOR_REALLOC_ERROR;

    v->data = new_data;
    v->capacity = new_capacity;
  }

  char *dest = (char *)v->data + v->len * v->elem_size;
  memcpy(dest, elem, v->elem_size);

  v->len++;

  return VECTOR_SUCCESS;
}

int main() {
  vector *v1 = make_vector(10, sizeof(int));

  vector_push_back(v1, &(int){10});
  for (int i = 0; i < 10; i++) {
    printf("%d) %d\n", i, (((int *)(v1->data))[i]));
  }
  free_vector(v1);
}
