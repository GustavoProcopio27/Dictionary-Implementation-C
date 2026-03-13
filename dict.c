#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dict.h"

inline static bool compare_str(char* key1, char*key2)
{
    return strcmp(key1, key2)==0;
}


Dict* dict_init()
{
    Dict *ptr = malloc(sizeof(Dict));
    if(ptr == NULL) exit(1);
    ptr->head = NULL;
    return ptr;
}

Dict* _dict_init_from_keys(char** keys_list,void* value, size_t list_length, size_t element_size)
{
    if(keys_list==NULL) exit(1);
    Dict *ptr = malloc(sizeof(Dict));
    if (ptr == NULL) exit(1);
    ptr->head = NULL;
    for(size_t i=0;i<list_length;i++)
    {
        _dict_update(ptr,keys_list[i],value,element_size);
    }

    return ptr;
}

void _dict_update(Dict *dict, char *key, void *value, size_t element_size) 
{
    if(dict==NULL) exit(1);
    entry *current = dict->head;
    while(current!=NULL)
    {
        if(compare_str(current->key, key))
        {
            if(current->element_size!=element_size)
            {
                void* value_with_realocated_space = realloc(current->value, element_size);
                if(value_with_realocated_space==NULL) exit(1);
                current->value = value_with_realocated_space;
                current->element_size = element_size;

            }
            memcpy(current->value, value, element_size);
            return;
        }
        current = current->next; //Em teoria isso deve me levar até o final da linked list
    }



    entry* new_entry = malloc(sizeof(entry));
    if(new_entry == NULL) exit(1);

    new_entry->key = strdup(key);
    new_entry->value = malloc(element_size);
    new_entry->element_size = element_size;

    memcpy(new_entry->value,value,element_size);
    new_entry->next = dict->head;
    dict->head = new_entry;
};

void* _dict_get(Dict *dict, char *key) 
{
    if(dict==NULL) exit(1);

    entry *current = dict->head;
    while (current != NULL)
    {
        if (compare_str(current->key, key))
        {
            return current->value;
        }
        current = current->next; 
    }
    return NULL;
};

void* _dict_pop(Dict *dict, char *key)
{
    if(dict==NULL) exit(1);

    entry *current = dict->head;
    entry *prev = NULL;
    while (current != NULL)
    {

        if (compare_str(current->key, key))
        {
            void *popped_value = malloc(current->element_size);
            memcpy(popped_value, current->value, current->element_size);

            if(prev==NULL)
                dict->head = current->next; // Se o elemento removido for o primeiro da lista, muda o inicio da lista para o proximo elemento
            else
                prev->next = current->next; // muda o ponteiro da anterior anterior para o da proxima entrada da removida

            free(current->key);
            free(current->value);
            free(current);

            return popped_value;
        }
        prev=current;
        current = current->next;
    }
    return NULL;
}

void dict_clear(Dict *dict)
{
    if(dict==NULL) exit(1);

    entry *current = dict->head;
    while(current!=NULL)
    {
        entry *next = current->next; 
        free(current->key);
        free(current->value);
        free(current);

        current = next;
    }
    dict->head = NULL;
}

void dict_free(Dict *dict)
{
    dict_clear(dict); //limpa e libera as entradas alocadas
    free(dict);
}
