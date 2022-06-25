#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define DEFAULT_CAPACITY 8

typedef struct vector
{
    void *array;
    size_t capacity;
    size_t element_size;
    size_t size;

} vector;

/*
 * Creates a new vector with an initial capacity of 8.

 * Arguments:
 *  element_size -> The size of the elements to be stored in the array.
 *
 * Returns:
 *  The pointer containing the address of the vector in memory.
 */
vector *vector_create(size_t element_size);

/*
 * Deletes the given vector and frees its memory.
 * You need to pass the pointer of an initialized vector, otherwise you'll get undefined behaviour.
 *
 * Arguments:
 *  vector -> The pointer of the vector to be deleted.
 *
 * Returns:
 *  A null pointer (so you can assign it to the vector pointer).
 */
vector *vector_destroy(vector *vector);

/*
 * Returns the pointer of an element at the given position in the array.
 *
 * Arguments:
 *  vector -> The pointer of the vector containing the elements.
 *  index -> The given position in the array.
 *
 * Returns:
 *  The pointer of an element at the given position in the array.
 */
void *vector_get(vector *vector, size_t index);

/*
 * Replaces the element at the specified position with the value stored in the given pointer.
 * The pointer's element must be the same size as the vector's element size.
 *
 * Arguments:
 *  vector -> The pointer of the vector containing the element to be replaced.
 *  index -> The position of the element to be replaced.
 *  element -> The pointer of the element that'll replace the other one.
 *  element_size -> The size of the element to be added.
 */
void vector_set(vector *vector, size_t index, void *element, size_t element_size);

/*
 * Appends the given element to the end of the array, modifying its capacity if necessary.
 * The pointer's element must be the same size as the vector's element size.
 * The capacity is increased by a factor of 8 when it is needed.
 *
 * Arguments:
 *  vector -> The vector in which the element is to be added.
 *  element -> The pointer of the element to be added.
 *  element_size -> The size of the element to be added.
 */
void vector_add(vector *vector, void *element, size_t element_size);

/*
 * Appends the given element to the specified position in the array, modifying its capacity if necessary.
 * The pointer's element must be the same size as the vector's element size.
 * The capacity is increased by a factor of 8 when it is needed.
 *
 * Arguments:
 *  vector -> The vector in which the element is to be added.
 *  index -> The position in which the element is to be added.
 *  element -> The pointer of the element to be added.
 *  element_size -> The size of the element to be added.
 */
void vector_add_at(vector *vector, size_t index, void *element, size_t element_size);

/*
 * Appends the elements of the given vector to the end of the array, modifying its capacity if necessary.
 * The given vector must have the same element size as the other one.
 * The capacity is increased by a factor of 8 when it is needed.
 *
 * Arguments:
 *  destination -> The pointer of the vector that'll receive the elements.
 *  source -> The pointer of the vector with the elements to be added.
 */
void vector_add_vector(vector *destination, vector *source);

/*
 * Appends the elements of the given vector to the specified position in the array, modifying its capacity if necessary.
 * The given vector must have the same element size as the other one.
 * The capacity is increased by a factor of 8 when it is needed.
 *
 * Arguments:
 *  destination -> The pointer of the vector that'll receive the elements.
 *  index -> The position in which the elements are to be added.
 *  source -> The pointer of the vector with the elements to be added.
 */
void vector_add_vector_at(vector *destination, size_t index, vector *source);

/*
 * Sorts the given vector using Merge Sort and a comparator function.
 *
 * Arguments:
 *  vector -> The pointer of the vector to be sorted.
 *  comp -> The operation used to make comparations between elements.
 */
void vector_sort(vector *vector, char (*comp)(void *, void *));

/*
 * Removes the first instance of the given element in the array.
 * The given element has to be the same size as the vector's element size.
 *
 * Arguments:
 *  vector -> The pointer of the vector in which the element is to be removed.
 *  element -> The pointer of the element to be removed.
 */
void vector_remove(vector *vector, void *element);

/*
 * Removes an element at the specified position in the array.
 *
 * Arguments:
 *  vector -> The pointer of the vector in which the element is to be removed.
 *  index -> The position of the element to be removed.
 */
void vector_remove_at(vector *vector, size_t index);

/*
 * Removes all the stored elements in the given vector and sets its capacity to 8.
 *
 * Arguments:
 *  vector -> The pointer of the given vector.
 */
void vector_clear(vector *vector);

#endif // VECTOR_H