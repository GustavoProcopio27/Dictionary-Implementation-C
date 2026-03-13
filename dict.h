#ifndef DICT_H
#define DICT_H

#include <stddef.h>


/**
 * @brief Estrutura que os valores presentes em uma entrada do dicionario, assim como o endereço para proxima entrada
 *
 * Armazena as entradas de forma dinâmica, permitindo crescimento conforme novos valores são adicionados
 *
**/
typedef struct entry{
    char* key;
    void* value;
    size_t element_size;
    struct _entry *next;
} entry;



/**
 * @brief Estrutura que armazena o início de uma Linked List de entradas de dicionario
 *
 * Armazena o inicio das entradas de dicionario, que se formam com (chave, valor, tamanho em bytes do valor)
 *
**/
typedef struct
{
    entry *head;
} Dict;



/**
 * @brief Macro para inicialização de um dicionario 
 *
 * O dicionario é iniciado vazio
 *
 * @return Ponteiro para o dicionario iniciado
**/
Dict* dict_init();



//===========================================================================================================================================



/**
 * @brief Macro para inicialização de um dicionario a partir de uma lista de chaves
 *
 * Caso a chave não existe, uma nova entrada é adicionada no dicionario.
 * Caso a chave já exista, o valor presente na entrada com esta chave é alterada para o valor passado
 *
 * @param key_list lista de strings representando as chaves a serem adicionadas
 * @param value valor padrão a ser inserido em todas chaves
 * @param list_length comprimento da lista passada
 * @param type tipo de dado do valor passado
 *
 * @return Ponteiro para o dicionario iniciado
**/
#define dict_init_from_keys(keys_list, value, list_length, type) (_dict_init_from_keys(keys_list, value, list_length, sizeof(type)))
Dict* _dict_init_from_keys(char** keys_list, void *value, size_t list_length, size_t element_size);



//===========================================================================================================================================



/**
 * @brief Macro para adição ou alteração de uma entrada do dicionario
 * 
 * Caso a chave não existe, uma nova entrada é adicionada no dicionario. 
 * Caso a chave já exista, o valor presente na entrada com esta chave é alterada para o valor passado
 * 
 * @param dict dict instanciado
 * @param key chave da entrada a ser alterada/inserida
 * @param value valor a ser inserido
 * @param type tipo de dado do valor presente
 *
**/
#define dict_update(dict, key, value, type)             \
    do{                                                 \
        type temp = (value);                            \
        (_dict_update(dict, key, &temp, sizeof(type)))  \
    }while(0)
void _dict_update(Dict* dict, char* key, void* value, size_t element_size);



//===========================================================================================================================================


 
/**
 * @brief Macro para busca de uma entrada do dicionario, devolvendo o valor presente na mesma.
 *
 * @param dict dict instanciado
 * @param key chave da entrada a ser buscada
 * @param type tipo de dado do valor presente 
 *
 * @returns Valor presente na entrada
**/
#define dict_get(dict, key, type) (*(type*)_dict_get(dict, key))
void* _dict_get(Dict* dict, char* key);



//===========================================================================================================================================




/**
 * @brief Macro para remoção de uma entrada do dicionario assim como liberação da memoria dela.
 * 
 * Internamente, além de remover a entrada, colocando o ponteiro da posição anterior da entrada 
 * removida para a posição da entrada posterior a removida, evitando quebra do link
 * 
 *
 * @param dict dict instanciado
 * @param key chave da entrada a ser removida
 * @param type tipo de dado do valor presente na entrada a ser removida 
 * 
 * @returns ponteiro para uma cópia do valor anteriormente presente na entrada removida
**/
#define dict_pop(dict, key, type) ((type*)_dict_pop(dict, key))
void* _dict_pop(Dict* dict, char* key);



//===========================================================================================================================================



/**
 * @brief Função para busca limpeza e liberação da memória alocada para as entradas do dicionario, levando o de volta ao estado inicial
 *
 * @param dict dict instanciado
**/
void dict_clear(Dict* dict);



//===========================================================================================================================================



/**
 * @brief Função para liberação da memória alocada para o dicionario
 *
 * @param dict dict instanciado
**/
void dict_free(Dict* dict);



//===========================================================================================================================================
//Isso daqui foi o chatgpt sendo genio para carai, nem sabia que podia criar um for com uma macro

#define dict_items(dict, iterator) \
    for (entry *iterator = (dict)->head; iterator != NULL; iterator = iterator->next)

#endif