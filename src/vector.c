#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_GROW_MULT 2

typedef enum {
  VECTOR_SUCCESS,        // Успешное выполнение
  VECTOR_EQUALS_NULL,    // Проверка на нулевой вектор не пройдена
  VECTOR_MALLOC_ERROR,   // Ошибка при аллокации памяти
  VECTOR_REALLOC_ERROR,  // Ошибка при аллокации памяти
  VECTOR_ZERO_ELEM_SIZE, // Размер элемента вектора равен нулю
  VECTOR_ZERO_LEN,       // Длина вектора равна нулю
  VECTOR_OUT_OF_BOUND,   // Искомый индекс вне индексов вектора
} vector_errors_t;

typedef struct {
  void *data;    // Указатель на область памяти, содержащую данные
  int len;       // Длина вектора
  int capacity;  // Максимальная длина вектора
  int elem_size; // размер одного элемента вектора
} vector;

// Выделяет память, инициализирует поля структуры вектора
vector_errors_t make_vector(vector *v, int capacity, int elem_size) {
  if (!v)
    return VECTOR_EQUALS_NULL;

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
    return VECTOR_EQUALS_NULL;

  v->capacity = 0;
  v->elem_size = 0;
  v->len = 0;

  free(v->data);
  v->data = NULL;

  return VECTOR_SUCCESS;
}

vector_errors_t check_capacity(vector *v) {
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
    return VECTOR_EQUALS_NULL;

  vector_errors_t err = check_capacity(v);
  if (err != VECTOR_SUCCESS)
    return err;

  void *dest = (char *)v->data + v->len * v->elem_size;
  memcpy(dest, elem, v->elem_size);

  v->len++;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_insert(vector *v, const void *elem, int index) {
  if (!v || !elem)
    return VECTOR_EQUALS_NULL;
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

vector_errors_t vector_pop_back(vector *v) {
  if (!v)
    return VECTOR_EQUALS_NULL;
  if (v->len == 0)
    return VECTOR_ZERO_LEN;

  v->len--;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_get(vector *v, void *out, int index) {
  if (!v || !out)
    return VECTOR_EQUALS_NULL;
  if (index < 0 || index >= v->len)
    return VECTOR_OUT_OF_BOUND;

  memcpy(out, (char *)v->data + index * v->elem_size, v->elem_size);

  return VECTOR_SUCCESS;
}

vector_errors_t vector_get_len(vector *v, int *out) {
  if (!v)
    return VECTOR_EQUALS_NULL;

  *out = v->len;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_get_cap(vector *v, int *out) {
  if (!v)
    return VECTOR_EQUALS_NULL;

  *out = v->capacity;

  return VECTOR_SUCCESS;
}

vector_errors_t vector_get_elem_size(vector *v, int *out) {
  if (!v)
    return VECTOR_EQUALS_NULL;

  *out = v->elem_size;

  return VECTOR_SUCCESS;
}

int main() {
  vector v1;
  make_vector(&v1, 10, sizeof(int));

  vector_push_back(&v1, &(int){10});
  vector_push_back(&v1, &(int){20});
  vector_push_back(&v1, &(int){30});
  vector_push_back(&v1, &(int){40});
  vector_push_back(&v1, &(int){50});
  vector_push_back(&v1, &(int){60});
  vector_pop_back(&v1);

  int len, cap, size;
  vector_get_len(&v1, &len);
  vector_get_cap(&v1, &cap);
  vector_get_elem_size(&v1, &size);

  printf("Len: %d\nCap: %d\nElem size: %d\n", len, cap, size);
  for (int i = 0; i < len; i++) {
    printf("%d) %d\n", i, (((int *)(v1.data))[i]));
  }

  int out1, out2, out3;
  vector_get(&v1, &out1, 2);
  vector_get(&v1, &out2, 3);
  vector_get(&v1, &out3, 4);
  printf("2 elem is %d\n", out1);
  printf("3 elem is %d\n", out2);
  printf("4 elem is %d\n", out3);

  vector_insert(&v1, &(int){42}, 2);
  for (int i = 0; vector_get_len(&v1, &len), i < len; i++) {
    printf("%d) %d\n", i, (((int *)(v1.data))[i]));
  }
  vector_free(&v1);
}
