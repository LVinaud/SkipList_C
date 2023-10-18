#include "item.h"
#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
Projeto BCC - 2023 
Lázaro Pereira Vinaud Neto - 14675396
Gabriel Antunes Afonso de Araujo - 14571077
*/
int main() {
  SKIPLIST *lista;
  char operacao[10]; // variável que armazena as instruções de cada operacao durante a entrada
  srand(time(NULL));
  lista = skipList_criar();
  if (lista == NULL) {
    return 1;
  }
  
  // Lendo as entradas do usuário até que "operacao" receba EOF 
  while (scanf(" %s", operacao) > 0) {
    
    // Para insercao temos que alocar um novo verbete e uma nova descrição a cada novo item inserido na lista
    if (strcmp("insercao", operacao) == 0) {
      //clock_t inicio = clock();
      char *verbete = (char *) malloc(51);
      char *descricao = (char *) malloc(141);
      scanf(" %s", verbete);
      scanf(" %[^\n]s", descricao);
      ITEM *inserido = item_criar(verbete, descricao);
      if (!skipList_inserir(lista, inserido)) {
        item_apagar(&inserido);
        printf("OPERACAO INVALIDA\n");
      }
      //clock_t fim = clock();
      //printf("A inserção demorou %lf segundos.\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
    }

    else if (strcmp("alteracao", operacao) == 0) {
      //clock_t inicio = clock();
      char *verbete = (char *) malloc(51);
      char *descricao = (char *) malloc(141);
      scanf(" %s", verbete);
      scanf("  %[^\n]s", descricao);

      ITEM *alterado = skipList_buscar(lista, verbete);

      if (alterado == NULL) {
        printf("OPERACAO INVALIDA\n");
        free(verbete);
        free(descricao);
      } else {
        item_set(alterado, verbete, descricao);
      }
      //clock_t fim = clock();
      //printf("A alteração demorou %lf segundos.\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
    }

    else if (strcmp("remocao", operacao) == 0) {
      //clock_t inicio = clock();
      char *verbete = (char *)malloc(51);
      scanf(" %s", verbete);

      ITEM *removido = skipList_remover(lista, verbete);
      if (removido == NULL) {
        printf("OPERACAO INVALIDA\n");
      } else {
        item_apagar(&removido);
      }
      free(verbete);
      verbete = NULL;
      //clock_t fim = clock();
      //printf("A remocao demorou %lf segundos.\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
    }
      
    else if (strcmp("busca", operacao) == 0) {
      //clock_t inicio = clock();
      char *verbete = (char *)malloc(51);
      scanf(" %s", verbete);

      ITEM *buscado = skipList_buscar(lista, verbete);
      if (buscado == NULL) {
        printf("OPERACAO INVALIDA\n");
      } else {
        item_imprimir(buscado);
      }
      free(verbete);
      verbete = NULL;
      //clock_t fim = clock();
      //printf("A busca demorou %lf segundos.\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
    }

    else if (strcmp("impressao", operacao) == 0) {
      //clock_t inicio = clock();
      char letra;
      scanf(" %c", &letra);

      if (!impressao_iniciais(lista, letra)) {
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", letra);
      }
      clock_t fim = clock();
      //printf("A impressao demorou %lf segundos.\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
    }
  }

  skipList_apagar(&lista);
  return 0;
}
