#ifndef SKIPLIST_H
#define SKIPLIST_H

#define TAM_MAX 20 // tamanho máximo de niveis que a lista pode possuir
#define PROB                                                                   \
  2 // probabilidade de, durante uma inserção, ser alocado um novo nível naquela
    // posição
#include "item.h"
#include <stdbool.h>

typedef struct skipList_ SKIPLIST;

SKIPLIST *skipList_criar();
bool skipList_apagar(SKIPLIST **lista);
bool skipList_inserir(SKIPLIST *lista, ITEM *item);
ITEM *skipList_buscar(SKIPLIST *lista, char *verbete);
ITEM *skipList_remover(SKIPLIST *lista, char *verbete);
bool impressao_iniciais(SKIPLIST *lista, char inicial);
bool lista_vazia(SKIPLIST *lista);
int lista_tamanho(SKIPLIST *lista);
void lista_imprimir(SKIPLIST *lista);

#endif
