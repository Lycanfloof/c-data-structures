#include <stdio.h>
#include <stdlib.h>

#include "../include/vector.h"

char create_test() // Implemented.
{
    vector *v = vector_create(sizeof(long long));

    if (v != NULL)
    {
        char r1 = v->array != NULL;
        char r2 = v->capacity == 2;
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

char add_at_test()
{
}

char add_vector_test()
{
}

char add_vector_at_test()
{
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

char sort_test()
{
}

char remove_test()
{
}

char remove_at_test()
{
}

char is_empty_test()
{
}

char size_test()
{
}

char clear_test()
{
}

char *assert(char value)
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

    printf("%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5);
}