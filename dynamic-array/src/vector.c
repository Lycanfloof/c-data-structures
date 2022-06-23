#include "../include/vector.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

char _check_required_capacity(vector vector, size_t size)
{
    if (size >= vector->capacity)
    {
        size_t extra_capacity = size >= 4 ? log2(size) : 1;
        size_t new_capacity = size + extra_capacity;

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

void _shift_elements(vector vector, size_t index)
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

void vector_set(vector vector, size_t index, void *element, size_t element_size)
{
    if (index < 0 || index > vector->size - 1 || element_size != vector->element_size)
        return;
    else
        memcpy(((char *)vector->array) + index * vector->element_size,
               element,
               vector->element_size);
}

void vector_add(vector vector, void *element, size_t element_size)
{
    if (element_size != vector->element_size)
        return;
    else
    {
        char able_to_add = _check_required_capacity(vector, vector->size);

        if (!able_to_add)
            return;
        else
        {
            memcpy(((char *)vector->array) + vector->size * vector->element_size,
                   element,
                   vector->element_size);
            vector->size++;
        }
    }
}

void vector_add_at(vector vector, size_t index, void *element, size_t element_size)
{
    if (element_size != vector->element_size)
        return;
    else
    {
        char able_to_add = _check_required_capacity(vector, vector->size);

        if (!able_to_add)
            return;
        else
        {
            _shift_elements(vector, index);

            memcpy(((char *)vector->array) + index * vector->element_size,
                   element,
                   vector->element_size);
            vector->size++;
        }
    }
}

void vector_add_vector(vector destination, vector source)
{
    if (destination->element_size != source->element_size)
        return;
    else
    {
        char able_to_add = _check_required_capacity(destination, destination->size + source->size);

        if (!able_to_add)
            return;
        else
        {
            memcpy(((char *)destination->array) + destination->size * destination->element_size,
                   source->array,
                   source->element_size * source->size);
            destination->size = destination->size + source->size;
        }
    }
}