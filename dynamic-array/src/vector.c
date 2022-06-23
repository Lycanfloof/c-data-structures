#include "../include/vector.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

char _check_capacity(vector vector)
{
    if (vector->size >= vector->capacity)
    {
        size_t added_capacity = vector->size >= 4 ? log2(vector->size) : 1;
        size_t new_capacity = vector->size + added_capacity;

        void *tmp = realloc(vector->array, new_capacity * vector->element_size);

        if (tmp == NULL)
        {
            return 0;
        }
        else
        {
            vector->array = tmp;
            vector->capacity = new_capacity;
        }
    }

    return 1;
}

void _shift_and_place(vector vector, size_t index)
{
    char *arr_start = vector->array;
    size_t arr_index = arr_start + (index * vector->element_size);
    size_t arr_end = arr_start + (vector->size * vector->element_size);

    if (arr_index < arr_start || arr_index >= arr_end)
        return;
    else
    {
        while (arr_end > arr_index)
        {
            memcpy(arr_end, arr_end - vector->element_size, vector->element_size);
            arr_end -= vector->element_size;
        }
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
        memcpy(((char *)vector->array) + index * vector->element_size,
               element,
               vector->element_size);
}

void vector_add(vector vector, void *element)
{
    char able_to_add = _check_capacity(vector);

    if (!able_to_add)
        return;
    else
    {
        memcpy(((char *)vector->array) + (vector->size) * vector->element_size,
               element,
               vector->element_size);
        vector->size++;
    }
}

void vector_add_at(vector vector, size_t index, void *element)
{
    char able_to_add = _check_capacity(vector);

    if (!able_to_add)
        return;
    else
    {
        _shift_and_place(vector, index);

        memcpy(((char *)vector->array) + index * vector->element_size,
               element,
               vector->element_size);
        vector->size++;
    }
}