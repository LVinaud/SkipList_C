#include "item.h"
#include <stdio.h>
#include <stdlib.h>

// Cada item do dicionário consiste de uma palavra (verbete) e sua descricão,
// ambas strings com limite máximo definido no enunciado
struct item_ {
  char *verbete;
  char *descricao;
};

/* 
Função que será utilizada para receber a letra inicial de cada palavra.
Se o item for nulo, retorna o caractere '\0'.
*/
char item_getinicial(ITEM* item) {
  if(item == NULL) {
    return '\0';
  }
  return item->verbete[0];
}

/*
A função item criar recebe como parâmetro duas strings previamente alocadas
e cria um novo item.
*/
ITEM *item_criar(char *verbete, char *descricao) {
  ITEM *item;

  item = (ITEM *)malloc(sizeof(ITEM));
  if (item != NULL) {
    item->verbete = verbete;
    item->descricao = descricao;
    return item;
  }
  return NULL;
}

/*
A função item apagar desaloca seu verbete e descrição, bem como o próprio item.
*/
bool item_apagar(ITEM **item) {
  if (*item != NULL) {
    
    free((*item)->verbete);
    (*item)->verbete = NULL;
    free((*item)->descricao);
    (*item)->descricao = NULL;
    free(*item);
    (*item) = NULL;
    
    return true;
  }
  return false;
}

//A função item_set usada na alteração de palavras, recebe verbete e descrição alocados previamente e insere eles no item.
bool item_set(ITEM *item, char *verbete, char *descricao) {
  if (item != NULL) {
    item->verbete = verbete;
    item->descricao = descricao;
    return true;
  }
  return false;
}

//Retorna o ponteiro para a string do verbete do item
char *item_getverbete(ITEM *item) {
  if (item != NULL) {
    return item->verbete;
  }
  return NULL;
}

//Retorna o ponteiro para a string do verbete do item
char *item_getdescricao(ITEM *item) {
  if (item != NULL) {
    return item->descricao;
  }
  return NULL;
}

//Usado para imprimir o item
void item_imprimir(ITEM *item) {
  if (item != NULL) {
    printf("%s ", item->verbete);
    printf("%s\n", item->descricao);
  }
  else
    printf("\nItem apagado.\n\n");
}