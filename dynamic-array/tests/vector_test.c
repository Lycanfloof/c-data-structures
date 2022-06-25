#include <stdio.h>
#include <stdlib.h>

#include "../include/vector.h"

char create_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        char r1 = v->array != NULL;
        char r2 = v->capacity == DEFAULT_CAPACITY;
        char r3 = v->element_size == sizeof(long long);
        char r4 = v->size == 0;

        free(v->array);
        v->array = NULL;

        free(v);
        v = NULL;

        return r1 && r2 && r3 && r4;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char destroy_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        v = vector_destroy(v);
        return v == NULL;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char add_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        int intg = 621;
        long long longl = 926;

        vector_add(v, &intg, sizeof(intg));
        char r1 = v->size == 0;

        vector_add(v, &longl, sizeof(longl));
        char r2 = v->size == 1 && ((long long *)(v->array))[0] == 926;

        v = vector_destroy(v);

        return r1 && r2;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char add_at_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        long long long1 = 1;
        long long long2 = 2;
        long long long3 = 3;
        long long long4 = 4;
        int intg = 5;

        // [1, 4, 2, 3]
        vector_add_at(v, 0, &long2, sizeof(long2));
        vector_add_at(v, 0, &long1, sizeof(long1));
        vector_add_at(v, 2, &long3, sizeof(long3));
        vector_add_at(v, 1, &long4, sizeof(long4));
        vector_add_at(v, 0, &intg, sizeof(intg));

        long long value1 = *((long long *)vector_get(v, 0));
        long long value2 = *((long long *)vector_get(v, 1));
        long long value3 = *((long long *)vector_get(v, 2));
        long long value4 = *((long long *)vector_get(v, 3));

        v = vector_destroy(v);

        return value1 == long1 && value2 == long4 && value3 == long2 && value4 == long3;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char add_vector_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));
    vector *e = vector_create(sizeof(long long));
    vector *c = vector_create(sizeof(int));

    if (v != NULL && e != NULL && c != NULL)
    {
        long long long1 = 1;
        long long long2 = 2;
        long long long3 = 3;
        long long long4 = 4;
        int intg = 5;

        vector_add(v, &long1, sizeof(long1));
        vector_add(v, &long2, sizeof(long2));

        vector_add(e, &long3, sizeof(long3));
        vector_add(e, &long4, sizeof(long4));

        vector_add(c, &intg, sizeof(intg));

        vector_add_vector(v, c);
        vector_add_vector(v, e);

        long long value1 = *((long long *)vector_get(v, 0));
        long long value2 = *((long long *)vector_get(v, 1));
        long long value3 = *((long long *)vector_get(v, 2));
        long long value4 = *((long long *)vector_get(v, 3));

        v = vector_destroy(v);
        e = vector_destroy(e);
        c = vector_destroy(c);

        return value1 == long1 && value2 == long2 && value3 == long3 && value4 == long4;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char add_vector_at_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));
    vector *e = vector_create(sizeof(long long));
    vector *c = vector_create(sizeof(int));

    if (v != NULL && e != NULL && c != NULL)
    {
        long long long1 = 1;
        long long long2 = 2;
        long long long3 = 3;
        long long long4 = 4;
        int intg = 5;

        vector_add(v, &long1, sizeof(long1));
        vector_add(v, &long2, sizeof(long2));
        vector_add(v, &long3, sizeof(long3));
        vector_add(v, &long4, sizeof(long4));

        vector_add(e, &long1, sizeof(long1));
        vector_add(e, &long2, sizeof(long2));

        vector_add(c, &intg, sizeof(intg));
        vector_add(c, &intg, sizeof(intg));

        // [1, 1, 2, 2, 3, 4]
        vector_add_vector_at(v, 1, c);
        vector_add_vector_at(v, 1, e);

        long long value1 = *((long long *)vector_get(v, 0));
        long long value2 = *((long long *)vector_get(v, 1));
        long long value3 = *((long long *)vector_get(v, 2));
        long long value4 = *((long long *)vector_get(v, 3));
        long long value5 = *((long long *)vector_get(v, 4));
        long long value6 = *((long long *)vector_get(v, 5));

        v = vector_destroy(v);
        e = vector_destroy(e);
        c = vector_destroy(c);

        char r1 = value1 == long1;
        char r2 = value2 == long1;
        char r3 = value3 == long2;
        char r4 = value4 == long2;
        char r5 = value5 == long3;
        char r6 = value6 == long4;

        return r1 && r2 && r3 && r4 && r5 && r6;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char get_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        long long longl1 = 621;
        long long longl2 = 926;

        vector_add(v, &longl1, sizeof(longl1));
        vector_add(v, &longl2, sizeof(longl2));

        void *ptr = vector_get(v, 100);
        long long value1 = *((long long *)vector_get(v, 0));
        long long value2 = *((long long *)vector_get(v, 1));

        v = vector_destroy(v);

        return ptr == NULL && value1 == longl1 && value2 == longl2;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char set_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        long long longl1 = 621;
        int intg = 310;
        long long longl2 = 926;
        long long value;

        vector_add(v, &longl1, sizeof(longl1));

        vector_set(v, 0, &intg, sizeof(intg));
        value = *((long long *)vector_get(v, 0));
        char r1 = value == longl1;

        vector_set(v, 0, &longl2, sizeof(longl2));
        value = *((long long *)vector_get(v, 0));
        char r2 = value == longl2;

        vector_set(v, 100, &longl2, sizeof(longl2));

        v = vector_destroy(v);

        return r1 && r2;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char compare_int_asc(void *int_a, void *int_b)
{
    if (*((int *)int_a) < *((int *)int_b))
        return -1;
    else if (*((int *)int_a) > *((int *)int_b))
        return 1;
    else
        return 0;
}

char compare_int_desc(void *int_a, void *int_b)
{
    if (*((int *)int_a) > *((int *)int_b))
        return -1;
    else if (*((int *)int_a) < *((int *)int_b))
        return 1;
    else
        return 0;
}

char sort_test() // Implemented.
{
    vector *v = vector_create(sizeof(int));
    vector *e = vector_create(sizeof(int));

    if (v != NULL && e != NULL)
    {
        int a[] = {1793, 2073, 7079, 1965, 4141, 3559, 4126, 271, 5170, 5379, 3271, 248};
        size_t sz = sizeof(a) / sizeof(*a);

        for (size_t i = 0; i < sz; i++)
        {
            vector_add(v, &a[i], sizeof(*a));
            vector_add(e, &a[i], sizeof(*a));
        }

        int b[] = {248, 271, 1793, 1965, 2073, 3271, 3559, 4126, 4141, 5170, 5379, 7079};
        int c[] = {7079, 5379, 5170, 4141, 4126, 3559, 3271, 2073, 1965, 1793, 271, 248};

        vector_sort(v, compare_int_asc);
        vector_sort(e, compare_int_desc);

        char r1 = 1;

        for (size_t i = 0; i < sz; i++)
        {
            if (*((int *)v + i) != *(b + i))
            {
                r1 = 0;
                break;
            }
        }

        char r2 = 1;

        for (size_t i = 0; i < sz; i++)
        {
            if (*((int *)e + i) != *(c + i))
            {
                r2 = 0;
                break;
            }
        }

        v = vector_destroy(v);
        e = vector_destroy(e);

        return r1 && r2;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char remove_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        long long longl1 = 621;
        long long longl2 = 926;

        vector_add(v, &longl1, sizeof(longl1));
        vector_add(v, &longl2, sizeof(longl2));
        vector_add(v, &longl1, sizeof(longl1));

        vector_remove(v, &longl2);

        long long value1 = *((long long *)vector_get(v, 0));
        long long value2 = *((long long *)vector_get(v, 1));

        v = vector_destroy(v);

        return value1 == longl1 && value2 == longl1;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char remove_at_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        long long longl1 = 621;
        long long longl2 = 926;

        vector_add(v, &longl1, sizeof(longl1));
        vector_add(v, &longl2, sizeof(longl2));
        vector_add(v, &longl1, sizeof(longl1));

        vector_remove_at(v, 1);

        long long value1 = *((long long *)vector_get(v, 0));
        long long value2 = *((long long *)vector_get(v, 1));

        v = vector_destroy(v);

        return value1 == longl1 && value2 == longl1;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char clear_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));
    if (v != NULL)
    {
        long long longl1 = 621;
        long long longl2 = 926;

        vector_add(v, &longl1, sizeof(longl1));
        vector_add(v, &longl2, sizeof(longl2));
        vector_add(v, &longl1, sizeof(longl1));
        vector_add(v, &longl2, sizeof(longl2));

        vector_clear(v);

        char r = v->capacity == DEFAULT_CAPACITY && v->size == 0;

        vector_destroy(v);

        return r;
    }
    else
    {
        printf("Memory allocation couldn't be done.");
        return 0;
    }
}

char *assert(char value) // Implemented.
{
    return value != 0 ? "passed" : "failed";
}

int main(void)
{
    char *s1 = assert(create_test());
    char *s2 = assert(destroy_test());
    char *s3 = assert(add_test());
    char *s4 = assert(get_test());
    char *s5 = assert(set_test());
    char *s6 = assert(add_at_test());
    char *s7 = assert(add_vector_test());
    char *s8 = assert(add_vector_at_test());
    char *s9 = assert(clear_test());
    char *s10 = assert(remove_test());
    char *s11 = assert(remove_at_test());
    char *s12 = assert(sort_test());

    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12);
}