/*produtos.h*/
#ifndef produtos_H 
#define produtos_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura de Catálogo de Produtos. */
typedef struct prods* CatProds;

/* Definição do tipo Produto. */
typedef struct prod* Produto;

/*Inicializa o Catálogo de Produtos. */
CatProds initCatProds();

/**
 * Função que le os Produtos do ficheiro de input de Produtos,
 recebendo um Catálogo de Produtos vazio e um caminho para o dado ficheiro, devolvendo o Catálogo de Produtos. */
CatProds lerProds(CatProds cps, char *s);

/** 
 * Funcão que insere um Produto num Catálogo de Produtos,
 esta recebe um Catálogo de Produtos, um Produto e um int que indica quando um Produto foi inserido, retornando o Catálogo de Produtos. */
CatProds insereProduto (CatProds cps, Produto produto, int *cresceu);

/** 
 * Função que verifica se um dado Produto existe num Catálogo de Produtos,
 recebe um Catálogo de Produtos e um Produto, retornando 1 se existir esse Produto no Catálogo de Produtos. */
int existeProduto(CatProds cps, Produto pr);

/** 
 * Função que transforma o Catálogo de Clientes em um array de strings de Produtos,
 recebendo um Catálogo de Produtos, retornado um array de strings de Produtos.*/ 
char** listaProdutos (CatProds cps);

/** 
 * Função que dado um Catálogo de Produtos e um char(letra) e apresenta um array de strings de produtos começados por esse char,
 esta recebe um Catálogo de Produtos e um char(letra), retornando um array de strings de Produtos começado por essa letra.*/
char** listaProLetra (CatProds cps,char c);

/**
 * Função que transforma uma dada string no tipo Produto,
 recebe uma string e retorna essa string no tipo Produto. */
Produto strToProduto (char *s);

/** 
 * Função que transforma o tipo Produto numa string,
 recebe um Produto e retorna uma string com esse Produto. */
char* produtoToStr (Produto pr);

/** 
 * Função que verififca se dois Produtos são iguais,
 recebe dois Produtos, retorna 1 se for verdade. */
int cmpProd (Produto pr1, Produto pr2);

/** 
 * Função que calcula o número total de Produtos existentes no Catálogo de Clientes,
 dando-lhe um Catálogo de Produtos, retorna o número total de Produtos. */
int totalProdutos (CatProds cps);

/** 
 * Função que calcula o número total de produtos de um dado char(letra) no Catálogo de Produtos,
 recebe um Catálogo de Produtos e um char(letra), retona o total de Produtos começados por esse char(letra). */
int totalProdutosLetra (CatProds cps, char c);

/* Esta função tem como tarefa apagar o Catálogo de Produtos para se poder introduzir novos dados. */
void deleteCatProds (CatProds cps);

#endif
