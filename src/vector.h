#ifndef VECTOR_H_
#define VECTOR_H_

typedef enum {
  VECTOR_SUCCESS,        // Успешное выполнение
  VECTOR_NULL_POINTER,   // Проверка на нулевой вектор не пройдена
  VECTOR_MALLOC_ERROR,   // Ошибка при аллокации памяти
  VECTOR_REALLOC_ERROR,  // Ошибка при аллокации памяти
  VECTOR_ZERO_ELEM_SIZE, // Размер элемента вектора равен нулю
  VECTOR_ZERO_LEN,       // Длина вектора равна нулю
  VECTOR_OUT_OF_BOUND,   // Искомый индекс вне индексов вектора
  VECTOR_INVALID_LEN,    // Невалидная длина для realloc
} vector_errors_t;

// Структура вектора
typedef struct vector vector; 

// Создание и освобождение вектора
vector_errors_t vector_make(vector *v, int capacity, int elem_size);
vector_errors_t vector_free(vector *v);

// Добавление элемента в конец вектора и удаление его оттуда же
vector_errors_t vector_push_back(vector *v, const void *elem);
vector_errors_t vector_pop_back(vector *v);

// Вставка элемента по индексу со сдвигом вправо
// и удаление элемента по индексу со двигом влево
vector_errors_t vector_insert(vector *v, const void *elem, int index);
vector_errors_t vector_erase(vector *v, int index);

// Увеличение вместимости вектора
vector_errors_t vector_reserve(vector *v, int cap);

// Поулчение указателя на элемент по индексу
vector_errors_t vector_get(vector *v, void *out, int index);

// Получение значений структуры
vector_errors_t vector_get_len(vector *v, int *out);
vector_errors_t vector_get_cap(vector *v, int *out);
vector_errors_t vector_get_elem_size(vector *v, int *out);

#endif
