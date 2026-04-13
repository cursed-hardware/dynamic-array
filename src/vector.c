#include "vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_GROW_MULT 2

struct vector {
  void *data;    // Указатель на область памяти, содержащую данные
  int len;       // Длина вектора
  int capacity;  // Максимальная длина вектора
  int elem_size; // размер одного элемента вектора
};

// Выделяет память, инициализирует пол
vector_errors_t make_vector(vector *v, int capacity, int elem_size) {
  if (!v)
    return VECTOR_NULL_POINTER;

  if (!elem_size)
    return VECTOR_ZERO_ELEM_SIZE;

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
vector_errors_t vector_free(vector *v) {
  if (!v)
    return VECTOR_NULL_POINTER;

  v->capacity = 0;
  v->elem_size = 0;
  v->len = 0;

  free(v->data);
  v->data = NULL;

  return VECTOR_SUCCESS;
}

// Проверка возможности вставить новый элемент
static vector_errors_t check_capacity(vector *v) {
  if (v->len == v->capacity) {
    int new_capacity =
        (v->capacity == 0) ? 1 : (v->capacity * VECTOR_GROW_MULT);

    void *new_data = realloc(v->data, new_capacity * v->elem_size);
    if (!new_data)
      return VECTOR_REALLOC_ERROR;

    v->data = new_data;
    v->capacity = new_capacity;
  }

  return VECTOR_SUCCESS;
}

// Запись нового элемента в конец вектора
vector_errors_t vector_push_back(vector *v, const void *elem) {
  if (!v || !elem)
    return VECTOR_NULL_POINTER;

  vector_errors_t err = check_capacity(v);
  if (err != VECTOR_SUCCESS)
    return err;

  void *dest = (char *)v->data + v->len * v->elem_size;
  memcpy(dest, elem, v->elem_size);

  v->len++;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_pop_back(vector *v) {
  if (!v)
    return VECTOR_NULL_POINTER;
  if (v->len == 0)
    return VECTOR_ZERO_LEN;

  v->len--;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_insert(vector *v, const void *elem, int index) {
  if (!v || !elem)
    return VECTOR_NULL_POINTER;
  if (index < 0 || index > v->len)
    return VECTOR_OUT_OF_BOUND;

  vector_errors_t err = check_capacity(v);
  if (err != VECTOR_SUCCESS)
    return err;

  void *index_pointer = (char *)v->data + v->elem_size * index;
  void *move_dest = (char *)index_pointer + v->elem_size;
  memmove(move_dest, index_pointer, (v->len - index) * v->elem_size);
  memcpy(index_pointer, elem, v->elem_size);

  v->len++;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_erase(vector *v, int index) {
  if (!v)
    return VECTOR_NULL_POINTER;
  if (index < 0 || index > v->len)
    return VECTOR_OUT_OF_BOUND;

  void *index_pointer = (char *)v->data + v->elem_size * index;
  void *move_pointer = (char *)index_pointer + v->elem_size;
  memmove(move_pointer, index_pointer, (v->len - index) * v->elem_size);

  v->len--;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_reserve(vector *v, int cap) {
  if (!v)
    return VECTOR_NULL_POINTER;
  if (cap < v->len)
    return VECTOR_INVALID_LEN;

  void *new_data = realloc(v->data, cap);
  if (!new_data)
    return VECTOR_REALLOC_ERROR;

  v->data = new_data;
  v->capacity = cap;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_get(vector *v, void *out, int index) {
  if (!v || !out)
    return VECTOR_NULL_POINTER;
  if (index < 0 || index >= v->len)
    return VECTOR_OUT_OF_BOUND;

  memcpy(out, (char *)v->data + index * v->elem_size, v->elem_size);

  return VECTOR_SUCCESS;
}

vector_errors_t vector_get_len(vector *v, int *out) {
  if (!v)
    return VECTOR_NULL_POINTER;

  *out = v->len;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_get_cap(vector *v, int *out) {
  if (!v)
    return VECTOR_NULL_POINTER;

  *out = v->capacity;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_get_elem_size(vector *v, int *out) {
  if (!v)
    return VECTOR_NULL_POINTER;

  *out = v->elem_size;

  return VECTOR_SUCCESS;
}
