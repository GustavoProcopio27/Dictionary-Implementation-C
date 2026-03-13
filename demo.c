#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
// gcc dict.c demo.c -o demo && ./demo
typedef char* string;
int main()
{
    Dict* dict = dict_init();

    dict_update(dict, "v1", 1, int);
    dict_update(dict, "v4", 2, int);
    dict_update(dict, "v3", 3, int);

    
    
    printf("valor da chave %s: %d\n", "v4",dict_get(dict, "v4", int));
    dict_update(dict, "v4", "teste cria", string);
    printf("valor da chave %s: %s\n\n", "v4",dict_get(dict, "v4", string));
    dict_update(dict, "v4", 2, int);

    dict_items(dict, it){
        printf("entry: %s -> %d\n", it->key, *(int*)it->value);
    }
    int* popped = (int*) dict_pop(dict, "v3", int);
    printf("\nO valor retirado foi: %d\n\n", *popped);

    dict_items(dict, it){
        printf("entry: %s -> %d\n", it->key, *(int*)it->value);
    }
    dict_free(dict);
    free(popped);
    return 0;
}