# Dictionary (C)

Uma biblioteca de **dicionário (mapa chave-valor)** implementada em **C**, utilizando **Linked List** para armazenamento dinâmico de dados.

A estrutura permite armazenar valores de qualquer tipo (`void*`), com suporte a:
- Inserção
- Atualização
- Busca
- Remoção
- Limpeza completa
- Iteração sobre os elementos


## ✨ Características

- Estrutura dinâmica
- Chaves do tipo `char*`
- Valores genéricos (`void*`)
- Armazenamento do tamanho real do dado
- Inserção sempre no início da lista
- Suporte a alteração automática de tamanho do valor
- Macros para facilitar o uso
- Liberação completa de memória

## 🚀 Como Usar

Inclua o arquivo no seu projeto:
```C
#include "dict.h"
```
Compile junto com seu código:
```sh
gcc main.c dict.c -o program
```

## 📦 Estrutura

```c
typedef struct entry{
    char* key;              //chave da entrada
    void* value;            //valor armazenado na entrada
    size_t element_size;    //tamanho em bytes do valor
    struct entry *next;     //Ponteiro para proxima entrada
} entry;
```
#### Campos:
|       Campo 	      |                 Descrição                  |
| ------------------- | ------------------------------------------ | 
|        key 	      |  chave para acesso ao valor em uma entrada |
|       value 	      |      valor armazenado em uma entrada       |
|   element_size 	  |  quantidade de bytes do valor armazenado   |
|       entry 	      | ponteiro para a proxima entrada armazenada |
```C
typedef struct
{
    entry *head;            //Ponteiro para o inicio da lista linkada
} Dict;
```
|       Campo 	      |                            Descrição                              |
| ------------------- | ----------------------------------------------------------------- | 
|       head 	      | ponteiro para o inicio da linked list com as entradas armazenadas |

## </> API
### Inicialização

```Dict* dict_init();```

Cria um dicionário vazio.
```C
Dict* dict = dict_init();
```

```Dict* dict_init_from_keys(keys_list, value, list_length, type);```

Cria um dicionário a partir de uma lista de chaves.

```C
char* keys[] = {"tab1","tab2","tab3"};
size_t keys_len = sizeof(keys)/sizeof(keys[0]);
Dict* dict = dict_init_from_keys(keys,10,keys_len,int);
```

---

### Inserção / Atualização
```dict_update(dict, key, value, type);```

Insere nova entrada se a chave não existir.

Atualiza o valor se a chave já existir.

Sempre insere no início da lista.
```C
Dict* dict = dict_init();

dict_update(dict, "v1", 1, int);
dict_update(dict, "v3", 3, int);
dict_update(dict, "v4", "teste cria", string);
```
---
### Busca
```dict_get(dict, key, type);```

Retorna o valor associado à chave.

```C
int value = dict_get(dict, "idade", int);
```
> ⚠️ Aviso: Responsabilidade do usuário saber o que está presente na chave para cast correto do valor retorno
> Há planos para incluir um dict_ref que retornaria o ponteiro para o valor
---
### Remoção
```dict_pop(dict, key, type);```

Remove a entrada da lista e retorna um ponteiro para uma cópia do valor.
```C
int* popped = (int*) dict_pop(dict, "v3", int);
```
> ⚠️ Aviso: Responsabilidade do usuário liberar o ponteiro posteriormente
```
free(valor_retornado);
```

---
### Limpeza
```void dict_clear(Dict* dict);```

Remove todas as entradas, mas mantém o dicionário.
```C
dict_clear(dict);
```
---
### Liberação Total
```void dict_free(Dict* dict);```

Libera todas as entradas e o próprio dicionário da memória.
```C
dict_free(dict);
```
---
### Iteração
```dict_items(dict, iterator)```

Macro para percorrer os elementos:


```C
dict_items(dict, it)
{
    printf("Key: %s\n", it->key);
}
```
> Internamente  ```for (entry *iterator = (dict)->head; iterator != NULL; iterator = iterator->next)```


> Mais exemplos presentes nos arquivos de demo
