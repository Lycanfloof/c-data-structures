#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct vector
{
    void *array;
    size_t capacity;
    size_t element_size;
    size_t size;

} vector;

/*
 * Creates a new vector with an initial capacity of 2.

 * Arguments:
 *  element_size -> The size in bytes of the elements to be stored in the array.
 *
 * Returns:
 *  The pointer containing the address of the vector in memory.
 */
vector *vector_create(size_t);

/*
 * Deletes the given vector and frees its memory.
 * You need to pass a vector which has been created, otherwise you'll get undefined behaviour.
 *
 * Arguments:
 *  vector -> The vector to be deleted.
 *
 * Returns:
 *  A null pointer (so you can assign it to the vector pointer).
 */
vector *vector_destroy(vector *);

/*
 * Returns the pointer of an element at the given position in the array.
 *
 * Arguments:
 *  vector -> The vector containing the elements.
 *  index -> The given position in the array.
 *
 * Returns:
 *  The pointer of an element at the given position in the array.
 */
void *vector_get(vector *, size_t);

/*
 * Replaces the element at the specified position with the given one.
 * The given element has to be the same size as the vector's element size.
 *
 * Arguments:
 *  vector -> The vector containing the element to be replaced.
 *  index -> The position of the element to be replaced.
 *  element -> The element that'll replace the other one.
 *  element_size -> The size of the element to be added.
 */
void vector_set(vector *, size_t, void *, size_t);

/*
 * Appends the given element to the end of the array.
 * The given element has to be the same size as the vector's element size.
 *
 * Arguments:
 *  vector -> The vector in which the element is to be added.
 *  element -> The element to be added.
 *  element_size -> The size of the element to be added.
 */
void vector_add(vector *, void *, size_t);

/*
 * Appends the given element to the specified position in the array.
 * The given element has to be the same size as the vector's element size.
 *
 * Arguments:
 *  vector -> The vector in which the element is to be added.
 *  index -> The position in which the element is to be added.
 *  element -> The element to be added.
 *  element_size -> The size of the element to be added.
 */
void vector_add_at(vector *, size_t, void *, size_t);

/*
 * Appends the elements of the given vector to the end of the array.
 * The given vector has to have the same element size as the other one.
 *
 * Arguments:
 *  destination -> The vector that'll receive the elements.
 *  source -> The vector with the elements to be added.
 */
void vector_add_vector(vector *, vector *);

/*
 * Appends the elements of the given vector to the specified position in the array.
 * The given vector has to have the same element size as the other one.
 *
 * Arguments:
 *  destination -> The vector that'll receive the elements.
 *  index -> The position in which the elements are to be added.
 *  source -> The vector with the elements to be added.
 */
void vector_add_vector_at(vector *, size_t, vector *);

/*
 * Sorts the given vector using Quick Sort and a comparator.
 *
 * Arguments:
 *  vector -> The vector to be sorted.
 *  comp -> The operation used to make comparations between elements.
 */
void vector_sort(vector *, char (*)(void *, void *));

/*
 * Removes the first instance of the given element in the array.
 * The given element has to be the same size as the vector's element size.
 *
 * Arguments:
 *  vector -> The vector in which the element is to be removed.
 *  element -> The element to be removed.
 */
void vector_remove(vector *, void *);

/*
 * Removes an element at the specified position in the array.
 *
 * Arguments:
 *  vector -> The vector in which the element is to be removed.
 *  index -> The position of the element to be removed.
 */
void vector_remove_at(vector *, size_t);

/*
 * Returns 1 if the given vector contains no elements, otherwise it returns 0.
 *
 * Arguments:
 *  vector -> The given vector.
 *
 * Returns:
 *  1 if the given vector contains no elements, otherwise it returns 0.
 */
char vector_is_empty(vector *);

/*
 * Returns the number of elements stored in the given vector.
 *
 * Arguments:
 *  vector -> The given vector.
 *
 * Returns:
 *  The number of elements stored in the vector.
 */
size_t vector_size(vector *);

/*
 * Removes all the stored elements in the given vector.
 *
 * Arguments:
 *  vector -> The given vector.
 */
void vector_clear(vector *);

#endif // VECTOR_H