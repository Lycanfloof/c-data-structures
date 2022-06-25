#include <stdlib.h>
#include <string.h>

#include "../include/vector.h"

char _check_required_capacity(vector *vector, size_t size)
{
    size_t required_capacity = size + DEFAULT_CAPACITY - (size % DEFAULT_CAPACITY);

    if (vector->capacity != required_capacity)
    {
        void *tmp = realloc(vector->array, required_capacity * vector->element_size);

        if (tmp == NULL)
        {
            return 0;
        }
        else
        {
            vector->array = tmp;
            vector->capacity = required_capacity;
        }
    }

    return 1;
}

void _left_shift(vector *vector, size_t index, size_t positions)
{
    if (index >= vector->size)
        return;
    else
    {
        char *array = vector->array;
        char *arr_index = array + index * vector->element_size;
        char *arr_end = array + (vector->size - 1) * vector->element_size;

        while (arr_index < arr_end - (positions - 1) * vector->element_size)
        {
            memcpy(arr_index,
                   arr_index + positions * vector->element_size,
                   vector->element_size);
            arr_index += vector->element_size;
        }
    }
}

void _right_shift(vector *vector, size_t index, size_t positions)
{
    if (index >= vector->size)
        return;
    else
    {
        char *array = vector->array;
        char *arr_index = array + index * vector->element_size;
        char *arr_end = array + (vector->size + positions - 1) * vector->element_size;

        while (arr_end > arr_index + (positions - 1) * vector->element_size)
        {
            memcpy(arr_end,
                   arr_end - positions * vector->element_size,
                   vector->element_size);
            arr_end -= vector->element_size;
        }
    }
}

vector *vector_create(size_t element_size)
{
    vector *new_vector = malloc(sizeof(vector));

    if (new_vector != NULL)
    {
        new_vector->capacity = DEFAULT_CAPACITY;
        new_vector->element_size = element_size;
        new_vector->size = 0;
        new_vector->array = malloc(new_vector->capacity * new_vector->element_size);

        if (new_vector->array == NULL)
        {
            free(new_vector);
            new_vector = NULL;
        }
    }

    return new_vector;
}

vector *vector_destroy(vector *vector)
{
    free(vector->array);
    vector->array = NULL;

    free(vector);
    vector = NULL;

    return vector;
}

void *vector_get(vector *vector, size_t index)
{
    if (index > vector->size - 1)
        return NULL;
    else
        return (((char *)vector->array) + index * vector->element_size);
}

void vector_set(vector *vector, size_t index, void *element, size_t element_size)
{
    if (index > vector->size - 1 || element_size != vector->element_size)
        return;
    else
        memcpy(((char *)vector->array) + index * vector->element_size,
               element,
               vector->element_size);
}

void vector_add(vector *vector, void *element, size_t element_size)
{
    if (element_size != vector->element_size)
        return;
    else
    {
        char able_to_add = _check_required_capacity(vector, vector->size + 1);

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

void vector_add_at(vector *vector, size_t index, void *element, size_t element_size)
{
    if (element_size != vector->element_size)
        return;
    else
    {
        char able_to_add = _check_required_capacity(vector, vector->size + 1);

        if (!able_to_add)
            return;
        else
        {
            _right_shift(vector, index, 1);

            memcpy(((char *)vector->array) + index * vector->element_size,
                   element,
                   vector->element_size);
            vector->size++;
        }
    }
}

void vector_add_vector(vector *destination, vector *source)
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

void vector_add_vector_at(vector *destination, size_t index, vector *source)
{
    if (source->element_size != destination->element_size)
        return;
    else
    {
        char able_to_add = _check_required_capacity(destination, destination->size + source->size);

        if (!able_to_add)
            return;
        else
        {
            _right_shift(destination, index, source->size);

            memcpy(((char *)destination->array) + index * destination->element_size,
                   source->array,
                   source->element_size * source->size);
            destination->size = destination->size + source->size;
        }
    }
}

char merge(size_t l, size_t m, size_t r, vector *vector, char (*comp)(void *, void *))
{
    char sorted = 0;

    size_t larr_size = (m - l + 1);
    size_t rarr_size = (r - m);

    char *arr = (char *)vector->array;
    char *larr = malloc(larr_size * vector->element_size);
    char *rarr = malloc(rarr_size * vector->element_size);

    if (larr != NULL && rarr != NULL)
    {
        memcpy(larr,
               arr + l * vector->element_size,
               larr_size * vector->element_size);
        memcpy(rarr,
               arr + (m + 1) * vector->element_size,
               rarr_size * vector->element_size);

        size_t inx = l;
        size_t linx = 0;
        size_t rinx = 0;

        while (linx < larr_size || rinx < rarr_size)
        {
            char comp_value = comp(larr + linx * vector->element_size,
                                   rarr + rinx * vector->element_size);

            if (rinx >= rarr_size || (!(linx >= larr_size) && comp_value <= 0))
            {
                memcpy(arr + inx * vector->element_size,
                       larr + linx * vector->element_size,
                       vector->element_size);
                inx++;
                linx++;
            }
            else
            {
                memcpy(arr + inx * vector->element_size,
                       rarr + rinx * vector->element_size,
                       vector->element_size);
                inx++;
                rinx++;
            }
        }
        sorted = 1;
    }

    if (larr != NULL)
        free(larr);
    if (rarr != NULL)
        free(rarr);

    return sorted;
}

char merge_sort(size_t l, size_t r, vector *vector, char (*comp)(void *, void *))
{
    if (l < r)
    {
        size_t m = (l + r) / 2;

        char res_fst_half = merge_sort(l, m, vector, comp);
        char res_scnd_half = merge_sort(m + 1, r, vector, comp);
        char res_merge = merge(l, m, r, vector, comp);

        return res_fst_half && res_scnd_half && res_merge;
    }
    else
    {
        return 1;
    }
}

void vector_sort(vector *vector, char (*comp)(void *, void *))
{
    merge_sort(0, vector->size - 1, vector, comp);
}

void vector_remove(vector *vector, void *element)
{
    char *array = vector->array;
    char *elem = (char *)element;

    for (size_t i = 0; i < vector->size; i++)
    {
        char is_equal = 1;

        for (size_t j = 0; j < vector->element_size; j++)
        {
            if (*(array + i * vector->element_size + j) != *(elem + j))
            {
                is_equal = 0;
                break;
            }
        }

        if (is_equal)
        {
            vector_remove_at(vector, i);
            break;
        }
    }
}

void vector_remove_at(vector *vector, size_t index)
{
    _left_shift(vector, index, 1);
    vector->size--;

    _check_required_capacity(vector, vector->size);
}

void vector_clear(vector *vector)
{
    void *tmp = realloc(vector->array, 2 * vector->element_size);

    if (tmp == NULL)
        return;
    else
    {
        vector->capacity = DEFAULT_CAPACITY;
        vector->size = 0;
    }
}