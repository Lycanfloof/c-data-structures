#include "../include/vector.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

void _check_capacity(vector vector)
{
    if (vector->size >= vector->capacity)
    {
        vector->capacity = vector->size + log2(vector->size);
        vector->array = realloc(vector->array, vector->capacity * vector->element_size);
    }
}

vector vector_create(size_t element_size)
{
    vector new_vector = calloc(1, sizeof(vector));

    if (new_vector != NULL)
    {
        new_vector->capacity = 2;
        new_vector->element_size = element_size;
        new_vector->size = 0;
        new_vector->array = calloc(new_vector->capacity, new_vector->element_size);

        if (new_vector->array == NULL)
        {
            free(new_vector);
            new_vector = NULL;
        }
    }
    return new_vector;
}

void vector_destroy(vector vector)
{
    free(vector->array);
    vector->array = NULL;

    free(vector);
    vector = NULL;
}

void *vector_get(vector vector, size_t index)
{
    if (index < 0 || index > vector->size - 1)
        return NULL;
    else
        return (((char *)vector->array) + index * vector->element_size);
}

void vector_set(vector vector, size_t index, void *element)
{
    if (index < 0 || index > vector->size - 1)
        return;
    else
    {
        memcpy(((char *)vector->array) + index * vector->element_size,
               element,
               vector->element_size);
    }
}

void vector_add(vector vector, void *element)
{
    _check_capacity(vector);

    memcpy(((char *)vector->array) + (vector->size) * vector->element_size,
           element,
           vector->element_size);
    vector->size++;
}