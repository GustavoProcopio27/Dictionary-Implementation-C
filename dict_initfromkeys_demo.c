#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
// gcc dict.c dict_initfromkeys_demo.c -o fromkeys_demo && ./fromkeys_demo
int main()
{
    char* keys[] = {"tab1","tab2","tab3"};
    size_t keys_len = sizeof(keys)/sizeof(keys[0]);
    Dict* dict = dict_init_from_keys(keys,10,keys_len,int);

    dict_items(dict, it)
    {
        printf("%s -> %d\n", it->key, *(int*)it->value);
    }

    return 0;
}