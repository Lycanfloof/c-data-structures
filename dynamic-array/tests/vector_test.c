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
        int intg;
        long long longl;

        intg = 621;     vector_add(v, &intg, sizeof(intg));
                        char r1 = v->size == 0;

        longl = 926;    vector_add(v, &longl, sizeof(longl));
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
        long long value;
        int intg;

        // [1, 4, 2, 3]
        value = 2;  vector_add_at(v, 0, &value, sizeof(value));
        value = 1;  vector_add_at(v, 0, &value, sizeof(value));
        value = 3;  vector_add_at(v, 2, &value, sizeof(value));
        value = 4;  vector_add_at(v, 1, &value, sizeof(value));
        intg = 5;   vector_add_at(v, 0, &intg, sizeof(intg));

        char r1 = ((long long *)(v->array))[0] == 1;
        char r2 = ((long long *)(v->array))[1] == 4;
        char r3 = ((long long *)(v->array))[2] == 2;
        char r4 = ((long long *)(v->array))[3] == 3;

        char r5 = v->size == 4;

        v = vector_destroy(v);

        return r1 && r2 && r3 && r4 && r5;
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
        long long value;
        int intg;

        value = 1;  vector_add(v, &value, sizeof(value));
        value = 2;  vector_add(v, &value, sizeof(value));
        value = 3;  vector_add(e, &value, sizeof(value));
        value = 4;  vector_add(e, &value, sizeof(value));
        intg = 5;   vector_add(c, &intg, sizeof(intg));

        vector_add_vector(v, c);
        vector_add_vector(v, e);

        char r1 = ((long long *)(v->array))[0] == 1;
        char r2 = ((long long *)(v->array))[1] == 2;
        char r3 = ((long long *)(v->array))[2] == 3;
        char r4 = ((long long *)(v->array))[3] == 4;

        char r5 = v->size == 4;

        v = vector_destroy(v);
        e = vector_destroy(e);
        c = vector_destroy(c);

        return r1 && r2 && r3 && r4 && r5;
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
        long long value;
        int intg;

        value = 1;  vector_add(v, &value, sizeof(value));
        value = 2;  vector_add(v, &value, sizeof(value));
        value = 3;  vector_add(v, &value, sizeof(value));
        value = 4;  vector_add(v, &value, sizeof(value));

        value = 1;  vector_add(e, &value, sizeof(value));
        value = 2;  vector_add(e, &value, sizeof(value));

        intg = 5;   vector_add(c, &intg, sizeof(intg));
                    vector_add(c, &intg, sizeof(intg));

        // [1, 1, 2, 2, 3, 4]
        vector_add_vector_at(v, 1, c);
        vector_add_vector_at(v, 1, e);

        char r1 = ((long long *)(v->array))[0] == 1;
        char r2 = ((long long *)(v->array))[1] == 1;
        char r3 = ((long long *)(v->array))[2] == 2;
        char r4 = ((long long *)(v->array))[3] == 2;
        char r5 = ((long long *)(v->array))[4] == 3;
        char r6 = ((long long *)(v->array))[5] == 4;

        char r7 = v->size == 6;

        v = vector_destroy(v);
        e = vector_destroy(e);
        c = vector_destroy(c);

        return r1 && r2 && r3 && r4 && r5 && r6 && r7;
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
        long long value;

        value = 621; vector_add(v, &value, sizeof(value));
        value = 926; vector_add(v, &value, sizeof(value));

        char r1 = *((long long *)vector_get(v, 0)) == 621;
        char r2 = *((long long *)vector_get(v, 1)) == 926;
        char r3 = vector_get(v, 100) == NULL;

        v = vector_destroy(v);

        return r1 && r2 && r3;
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
        long long value;
        int intg;

        value = 621;    vector_add(v, &value, sizeof(value));

        intg = 310;     vector_set(v, 0, &intg, sizeof(intg));
                        char r1 = ((long long *)(v->array))[0] == 621;

        value = 926;    vector_set(v, 0, &value, sizeof(value));
                        vector_set(v, 100, &value, sizeof(value));
                        char r2 = ((long long *)(v->array))[0] == 926;

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
        int a[] = {1793, 2073, 7079, 1965, 4141, 3559, 4126, 271, 5170, 5379, 3271, 248}; //Original order.
        int b[] = {248, 271, 1793, 1965, 2073, 3271, 3559, 4126, 4141, 5170, 5379, 7079}; //Ascending order.
        int c[] = {7079, 5379, 5170, 4141, 4126, 3559, 3271, 2073, 1965, 1793, 271, 248}; //Descending order.

        for (size_t i = 0; i < 12; i++)
        {
            vector_add(v, &a[i], sizeof(*a));
            vector_add(e, &a[i], sizeof(*a));
        }

        vector_sort(v, compare_int_asc);
        vector_sort(e, compare_int_desc);

        char r1 = 1, r2 = 1;

        for (size_t i = 0; i < 12; i++)
        {
            if (*((int *)v->array + i) != *(b + i))
            { r1 = 0; break;}
        }

        for (size_t i = 0; i < 12; i++)
        {
            if (*((int *)e->array + i) != *(c + i))
            { r2 = 0; break;}
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
        long long value;

        value = 621; vector_add(v, &value, sizeof(value));
        value = 926; vector_add(v, &value, sizeof(value));
        value = 621; vector_add(v, &value, sizeof(value));

        value = 926; vector_remove(v, &value);

        char r1 = ((long long *)(v->array))[0] == 621;
        char r2 = ((long long *)(v->array))[1] == 621;

        v = vector_destroy(v);

        return r1 && r2;
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
        long long value;

        value = 621; vector_add(v, &value, sizeof(value));
        value = 926; vector_add(v, &value, sizeof(value));
        value = 621; vector_add(v, &value, sizeof(value));

        vector_remove_at(v, 1);

        char r1 = ((long long *)(v->array))[0] == 621;
        char r2 = ((long long *)(v->array))[1] == 621;

        v = vector_destroy(v);

        return r1 && r2;
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
        long long value;

        value = 621; vector_add(v, &value, sizeof(value));
        value = 926; vector_add(v, &value, sizeof(value));
        value = 621; vector_add(v, &value, sizeof(value));
        value = 926; vector_add(v, &value, sizeof(value));

        vector_clear(v);

        char r1 = v->capacity == DEFAULT_CAPACITY;
        char r2 = v->size == 0;

        vector_destroy(v);

        return r1 && r2;
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
    char (*func[])(void) = {create_test, destroy_test, clear_test,
                            get_test, set_test,
                            add_test, add_at_test, add_vector_test, add_vector_at_test,
                            remove_test, remove_at_test,
                            sort_test};
    for (size_t i = 0; i < 12; i++)
    {
        printf("%s\n", assert(func[i]()));
    }
}