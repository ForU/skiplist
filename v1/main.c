#include <stdio.h>
#include <stdlib.h>

#include "skip_list.h"

int main(int argc, char *argv[])
{
    if ( argc == 1 ) {
        printf("Usage: %s integer(s)\n", argv[0]);
        return 0;
    }

    skip_list_t* sl = skip_list_create();
    int key = 0;
    int i = 1, rc = 0;

    for ( i = 1; i < argc; ++i ) {
        key = atoi(argv[i]);
        printf("insert key:%2d, return:%2d\n",
               key, skip_list_insert(key, key, sl));
    }
    printf("\n");

    int value;
    for ( i = 1; i < argc; ++i ) {
        key = atoi(argv[i]);
        rc = skip_list_search(key, &value, sl);
        printf("search key:%2d, return:%2d", key, rc);
        rc ? printf(", value:%2d\n", value): printf("\n");
    }
    printf("\n");

    for ( i = 1; i < argc; ++i ) {
        key = atoi(argv[i]);
        printf("delete key:%2d, return:%2d\n",
               key, skip_list_delete(key, key, sl));
    }
    printf("\n");

    for ( i = 1; i < argc; ++i ) {
        key = atoi(argv[i]);
        rc = skip_list_search(key, &value, sl);
        printf("search key:%2d, return:%2d", key, rc);
        rc ? printf(", value:%2d\n", value): printf("\n");
    }
    printf("\n");

    skip_list_destroy(sl);

    return 0;
}
