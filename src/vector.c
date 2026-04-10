#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_GROW_MULT 2

typedef enum {
  VECTOR_SUCCESS,              // Успешное выполнение
  VECTOR_EQUALS_NULL,          // Проверка на нулевой вектор не пройдена
  VECTOR_MALLOC_ERROR,         // Ошибка при аллокации памяти
  VECTOR_REALLOC_ERROR,        // Ошибка при аллокации памяти
  VECTOR_ELEM_SIZE_EQUALS_ZERO // Размер элемента вектора равен нулю
} vector_errors_t;

typedef struct {
  void *data;       // Указатель на область памяти, содержащую данные
  size_t len;       // Длина вектора
  size_t capacity;  // Максимальная длина вектора
  size_t elem_size; // размер одного элемента вектора
} vector;

// Выделяет память, инициализирует поля структуры вектора
vector_errors_t make_vector(vector *v, size_t capacity, size_t elem_size) {
  if (!v)
    return VECTOR_EQUALS_NULL;

  if (!elem_size)
    return VECTOR_ELEM_SIZE_EQUALS_ZERO;

  if (capacity) {
    v->data = malloc(capacity * elem_size);
    if (v->data == NULL)
      return VECTOR_MALLOC_ERROR;
  } else {
    v->data = NULL;
  }

  v->len = 0;
  v->elem_size = elem_size;
  v->capacity = capacity;

  return VECTOR_SUCCESS;
}

// Освобождает память массива данных и вектора
vector_errors_t free_vector(vector *v) {
  if (!v)
    return VECTOR_EQUALS_NULL;

  v->capacity = 0;
  v->elem_size = 0;
  v->len = 0;

  free(v->data);
  v->data = NULL;

  return VECTOR_SUCCESS;
}

// Запись нового элемента в конец вектора
vector_errors_t vector_push_back(vector *v, const void *elem) {
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
  vector v1;
  make_vector(&v1, 10, sizeof(int));

  vector_push_back(&v1, &(int){10});
  for (int i = 0; i < 10; i++) {
    printf("%d) %d\n", i, (((int *)(v1.data))[i]));
  }

  free_vector(&v1);
}
