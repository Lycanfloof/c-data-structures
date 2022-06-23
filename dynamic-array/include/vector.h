#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct vector
{
    void *array;
    size_t capacity;
    size_t element_size;
    size_t size;

} * vector;

vector vector_create(size_t);
void vector_destroy(vector);

void *vector_get(vector, size_t);
void vector_set(vector, size_t, void *);

void vector_add(vector, void *, size_t);
void vector_add_at(vector, size_t, void *, size_t);

void vector_add_vector(vector, vector);
void vector_add_vector_at(vector, size_t, vector);

void vector_sort(vector, char (*comp)(void *, void *));

void vector_remove(vector, void *);
void vector_remove_at(vector, size_t);

char vector_is_empty(vector);
size_t vector_size(vector);

void vector_clear(vector);

#endif // VECTOR_H