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
typedef struct no_ NO;
struct no_ {
  ITEM *item;
  NO *proximo;
  NO *baixo;
};

struct skipList_ {
  NO *inicio; // O primeiro nó sempre será o do canto superior esquerdo, sendo que cada nível começa com um nó cabeça.
  int tamanho; // Informa a quantidade de elementos armazenados na lista
};

// Função que cria a lista em si, além dos nós cabeças de todos o níveis, uma vez que TAM_MAX já é pré-definido
SKIPLIST *skipList_criar() {
  SKIPLIST *lista;
  lista = (SKIPLIST *)malloc(sizeof(SKIPLIST));

  if (lista != NULL) {
    lista->tamanho = 0;

    // Criamos o nó cabeça do nível 0 e, depois em um loop criamos os dos outros níveis, fazendo-os apontar para o anterior (ou seja, criamos os níveis de baixo para cima)
    NO *cabeca = (NO *)malloc(sizeof(NO));
    if (cabeca == NULL) {
      exit(1);
    }
    cabeca->proximo = NULL;
    cabeca->item = NULL;
    cabeca->baixo = NULL;

    NO *baixo = cabeca;
    for (int i = 0; i < TAM_MAX - 1; i++) {
      cabeca = (NO *)malloc(sizeof(NO));
      if (cabeca == NULL) {
        exit(1);
      }
      cabeca->proximo = NULL;
      cabeca->item = NULL;
      cabeca->baixo = baixo;
      baixo = cabeca;
    }
    lista->inicio = cabeca;
    return lista;
  }
  return NULL;
}
/* a função de apagar funciona percorrendo TAM_MAX nós cabeças a partir do mais alto
e apagando tudo que está à sua direita, após isso apaga a si mesmo e avança para o nivel a
baixo guardado anteriormente. os itens só serão apagados na última camada, para evitar double free.
*/

bool skipList_apagar(SKIPLIST **lista) {
  if(*lista == NULL) {
    return false;
  }
  
  NO* aux = (*lista)->inicio;  // Variável que percorrerá os nós da lista
  
  while(aux != NULL) {
    NO* prox = aux->baixo;     // Variável que guarda o próximo nó cabeça

    // Apagando todos os nós do nível atual à direita do nó cabeça
    while(aux->proximo != NULL) {
      NO* removido = aux->proximo;
      aux->proximo = removido->proximo;

      if(aux->baixo == NULL)
        item_apagar(&removido->item);
      
      free(removido);
    }
    
    // apagando o nó cabeça do nível atual
    free(aux);
    aux = prox;
  }
  // após tudo isso da free na propria lista
  free(*lista);
  *lista = NULL;
  return true;
}

/*
Função de inserção, a função funciona com nó auxiliar começando no nó cabeça mais alto da lista.
Esse nó vai para a sua direita enquanto o próximo não for nulo e nem maior do que o item a ser inserido.
Isso significa que ele pode ser o item. Após ir tudo pra direita, ele desce e checa se o seu seu verbete é igual ao que se quer inserir, caso sim retorna falso. Toda vez que desce, o nó aux é 
inserido em um vetor antes de ser inserido. começando com o indice TAM_MAX - 1, que representa o nível em que está e descendo até o 0.
no nível 0 ele faz o mesmo trajeto à direita e guarda o último aux na posição vetornos[0].
O nó mais baixo é então criado obrigatoriamente. O Nó criado recebe seu proximo como sendo o proximo
do vetornos[0] e atualiza o proximo desse vetor como o nó criado. após isso, sorteia-se um número de niveis
enquanto o numero aleatorio gerado for par, aumenta se um nivel. que é o numero de iterações do for
que criará novos nós seguindo a mesma logica em cima do no no nivel 0.
*/
bool skipList_inserir(SKIPLIST *lista, ITEM *item) {
  if (lista == NULL || item == NULL) {
    return false;
  }

  NO *vetornos[TAM_MAX];
  NO *aux = lista->inicio;
  int indice = TAM_MAX - 1;

  // todos os niveis acima do 0
  while (aux->baixo != NULL) {
    while (aux->proximo != NULL && (strcmp(item_getverbete(aux->proximo->item), item_getverbete(item)) <= 0)) {
      aux = aux->proximo;
    }
    // se for igual, para a função e retorna falso
    if ((aux->item != NULL) && (strcmp(item_getverbete(aux->item), item_getverbete(item)) == 0)) {
      return false;
    }
    
    vetornos[indice] = aux;
    indice--;
    aux = aux->baixo;
  }
  // nivel 0
  while ((aux->proximo != NULL) && (strcmp(item_getverbete(aux->proximo->item), item_getverbete(item)) <= 0)) {
    aux = aux->proximo;
  }
  // se for igual, para a função e retorna falso
  if ((aux->item != NULL) &&
      (strcmp(item_getverbete(aux->item), item_getverbete(item)) == 0)) {
    return false;
  }
  vetornos[indice] = aux;
  for (int i = 0; i < TAM_MAX; i++) {
    if (vetornos[i] == NULL) {
      printf("ERRO\n");
      exit(1);
    }
  }
  NO *inserido = (NO *)malloc(sizeof(NO));
  inserido->item = item;
  inserido->proximo = vetornos[0]->proximo;
  vetornos[0]->proximo = inserido;
  inserido->baixo = NULL;

  // quantos niveis acima do 0 tem que criar
  int niveis = 0;
  while (rand() % 2 == 0 && (niveis < TAM_MAX - 2)) {
    niveis++;
  }
  
  for (int i = 0; i < niveis; i++) {
    NO *inserido = (NO *)malloc(sizeof(NO));
    inserido->item = item;
    inserido->proximo = vetornos[i + 1]->proximo;
    vetornos[i + 1]->proximo = inserido;
    // o baixo é o proximo do vetornos anterior.
    inserido->baixo = vetornos[i]->proximo;
  }

  lista->tamanho++;
  return true;
}

// Buscamos a partir do item mais acima à esquerda, descendo um nível sempre que
// o proximo de aux for maior ou nulo, dessa maneira só é necessário checar se o item
// é o buscado quando os loops pararem, ou seja, estou no nivel 0 e o próximo é maior ou nulo.
ITEM *skipList_buscar(SKIPLIST *lista, char *verbete) {
  if (lista == NULL || lista_vazia(lista)) {
    return NULL;
  }

  NO *aux = lista->inicio; // Ponteiro que percorre a lista

  // Percorrendo todos os niveis com exceção do 0. 
  while (aux->baixo != NULL) {
    while (aux->proximo != NULL && (strcmp(item_getverbete(aux->proximo->item), verbete) <= 0)) {
      aux = aux->proximo;
    }
    aux = aux->baixo;
  }
  
  // Percorrendo o nível 0 até achar um item maior ou nulo.
  while ((aux->proximo != NULL) && (strcmp(item_getverbete(aux->proximo->item), verbete) <= 0)) {
    aux = aux->proximo;
  }
  // Se for igual, retorna. Senão, nulo.
  if ((aux->item != NULL) && (strcmp(item_getverbete(aux->item), verbete) == 0))
    return aux->item;
  return NULL;
}

// a função skiplist remover guarda os nós na descida no vetor e depois percorre esse vetor checando se o proximo é igual ao que será removido. se sim, atualiza os parêmetros e remove os nós em sequencia.
ITEM *skipList_remover(SKIPLIST *lista, char *verbete) {
  if (lista == NULL || lista_vazia(lista)) {
    return NULL;
  }
  NO *aux = lista->inicio; // Variável que percorre a lista, buscando o item a ser removido
  NO *vetor[TAM_MAX];      // vetor que guarda os nós de cada descida de nível
  int indice = TAM_MAX - 1;
  ITEM *resposta = NULL;
  
  // Percorrendo a lista, verificando se aux->proximo é nulo ou maior/igual que o item buscado até nível 0
  while (aux->baixo != NULL) {
    while ((aux->proximo != NULL) && (strcmp(item_getverbete(aux->proximo->item), verbete) < 0)) {
      aux = aux->proximo;
    }
    
    vetor[indice] = aux;
    indice--;
    aux = aux->baixo;
  }

  // Percorrendo o nível zero
  while ((aux->proximo != NULL) && (strcmp(item_getverbete(aux->proximo->item), verbete) < 0)) {
    aux = aux->proximo;
  }

  vetor[indice] = aux;

  // Removendo o nó do item buscado e os seus níveis (caso existam).
  for (int i = 0; i < TAM_MAX; i++) {
    if ((vetor[i]->proximo != NULL) && (vetor[i]->proximo->item != NULL) &&
        (strcmp(item_getverbete(vetor[i]->proximo->item), verbete) == 0)) {
      NO *removido = vetor[i]->proximo;
      resposta = removido->item;
      vetor[i]->proximo = removido->proximo;
      free(removido);
    }
  }
  // como a resposta só deixa de ser nula no caso de encontrar algo igual. caso ela nao seja nula removeu alguem e o tamanho diminui
  if (resposta != NULL)
    lista->tamanho--;
  return resposta;
}

// Função que, a partir de uma busca, imprime todas as palavras com uma mesma letra inicial
bool impressao_iniciais(SKIPLIST *lista, char inicial) {
  if (lista == NULL || lista_vazia(lista))
    return false;

  NO *aux = lista->inicio; // Variável que percorrerá a lista
  bool achou = false;      // Variável que informa se há palavras iniciadas com a letra recebida

  // Percorrendo a lista até o nível 0
  while (aux->baixo != NULL) {
    //a variavel aux só vai descer, se a próxima palavra for maior ou igual a letra buscada, sendo assim nao corre o risco de pular palavras
    while ((aux->proximo != NULL) && (item_getinicial(aux->proximo->item) < inicial)) {
      aux = aux->proximo;
    }
    aux = aux->baixo;
  }

  // Percorrendo o nível 0 até encontrar a primeira palavra com a inicial buscada
  while ((aux->proximo != NULL) && (item_getinicial(aux->proximo->item) < inicial))
    aux = aux->proximo;

  // Condição que verifica se o próximo nó contem a primeira palavra com a inicial buscada
  if ((aux->proximo != NULL) && (item_getinicial(aux->proximo->item) == inicial)) {
    achou = true;
    aux = aux->proximo;
  }

  // Loop que imprime todas as palavras com a inicial informada.
  while ((aux != NULL) && (item_getinicial(aux->item) == inicial)) {
    item_imprimir(aux->item);
    aux = aux->proximo;
  }

  return achou;
}

// Função que verifica se a lista está vazia a partir da variável "tamanho" da struct
bool lista_vazia(SKIPLIST *lista) {
  if (lista == NULL)
    return false;
  return ((lista->tamanho == 0) ? true : false);
}

// Função que retorna o tamanho da lista criada
int lista_tamanho(SKIPLIST *lista) {
  if (lista == NULL) {
    return -1;
  }
  return lista->tamanho;
}

// Função extra que imprime todos os itens da lista (foi usada em alguns debugs)
void lista_imprimir(SKIPLIST *lista) {
  if (lista == NULL)
    return;

  NO *aux = lista->inicio;

  while (aux->baixo != NULL) {
    aux = aux->baixo;
  }

  while (aux->proximo != NULL) {
    aux = aux->proximo;
    item_imprimir(aux->item);
  }
  return;
}