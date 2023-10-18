#ifndef ITEM_H
  #define ITEM_H
    #include <stdbool.h>
    
    typedef struct item_ ITEM;
    
    ITEM *item_criar(char *verbete, char *descricao);
    bool item_apagar(ITEM **item);
    bool item_set(ITEM *item, char *verbete, char *descricao);
    char *item_getverbete(ITEM *item);
    char item_getinicial(ITEM* item);
    char *item_getdescricao(ITEM *item);
    void item_imprimir(ITEM *item);

#endif