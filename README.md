<h1 align="center">Skiplist_C</h1>

## Introdução
  Este projeto foi desenvolvido com o intuíto de estudar a estrutura de dados "SkipList", usando-a para desenvolver um dicionário digital que realize operações de busca, inserção e remoção de palavras otimizadas, utilizando TADs na linguagem C.

## Conceitos teóricos empregados

### Tipo abstrato de dados (TAD)
<p align="justify">
  Consiste na definição dos dados armazenados na estrutura e das operações que um outro programador usuário poderá realizar sobre ela de forma separada da implementação. Assim, ele não só passa a ser um conceito independente de linguagem como também garante o encapsulamento do código e o ocultamento da informação (ou seja, o programador usuário só poderá ter acesso aos dados por meio daquilo que foi definido do TAD). 
</p>
<p align="justify">
  Por fim, vale citar que o TAD facilita a manutenção e o reúso de códigos em softwares com programação estruturada.
</p>

### SkipLists
<p align="justify">
  SkipLists são estruturas de dados probabilísticas que derivam da estrutura "lista encadeada". Nesse sentido, elas podem possuir n elementos x (onde x1 representa o primeiro a ser inserido e xn o último) e permitem operações de busca, inserção e remoção em qualquer ponto da estrutura. Porém, a principal diferença está na sua natureza probabilística e no seu uso com dados ordenados.
</p>
<p align="justify">
  Diferentemente das listas encadeadas comuns (as quais consistem em uma única lista de nós que apontam sempre para o seu sucessor) as SkipLists possuem, além dos nós, diferentes níveis que formam listas àcima da "principal" (geralmente representada pelo nível 0), sendo que cada nó de um nível aponta para o seu semelhante no nível de baixo. Porém os outros níveis não possúem nós para todos os elementos inseridos na lista (uma vez que a decisão da criação dos nós de um novo elemento inserido para essas "camadas" é feita por um algorítimo probabílistco). Assim, os níveis superiores servem como atalhos, pois permitem o acesso de nós distantes na estrutura sem percorre-la por inteiro (Coisa que fica restrita ao nível 0).
</p>
<p align="justify">
   Dessa forma, uma SkipList se torna muito proprícia para a inserção, busca e remoção de elementos ordenadamente, pois todas essas operações terão complexidade O(log n), enquanto outros tipos de listas encadeadas e ordenadas conseguirão no máximo complexidade O(n).
</p>

## Funcionalidade
<p align="justify">
  A lógica do dicionário consiste em 5 operações: inserção de palavras e suas definições, buscá-las, remove-las, alterar a definição (ou seja o significado) de uma palavra já inserida e imprimir a lista de palavras inseridas que começem com uma inicial informada pelo usuário. Para isso, foram utilizados dois TADs: o Item, que consiste na string verbete (a palavra em si) e definição (o seu significado) e a SkipList que os armazenará ordenadamente.
</p>
<p align="justify">
  Assim, o usuário executa essas operações por meio da entrada dos seguintes comandos:
  - insercao <verbete> <definicao>
  - busca <verbete>
  - remocao <verbete>
  - alteracao <verbete> <nova_descrição>
  - impressao <letra_inicial>
</p>
<p align="justify">
  Além disso, EOF é utilizado como comando de parada para o programa, e caso o usuário tente realizar alguma operação invalidada em um dadao momento (apagar, buscar ou alterar um item inexistente e tentar reinserir uma mesma palavra) será retornada a mensagem: "operação inválida" e caso ele tente imprimir a lista de palavras de uma determinada letra, mas não houver nenhuma palavra que inicie com essa letra armazenada será impressa a mensagem: "Nao ha palavras que iniciam com a letra __".
</p>

## Implementação

## Desenvolvedores
- Lazaro Pereira Vinald
- Gabriel Antunes Afnso de Araujo
