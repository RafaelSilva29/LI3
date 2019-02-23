/*faturacao.h*/
#ifndef faturacao_h
#define faturacao_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Estrutura de dados dos Valores de cada Produto, a sua quantidade e a faturação. */
typedef struct valores* Valores;

/* Estrutura de dados de cada Faturação de cada Produto. */
typedef struct faturacao* Faturacao;

/* Estrutura que define o Catálogo de Faturação. */
typedef struct cfaturacao* CatFaturacao;

#include "clientes.h"
#include "produtos.h"
#include "filial.h"

/* Função que inicializa o Catálogo de Faturação. */
CatFaturacao initCatFaturacao (int qtF);

/**
 * Função responsável pela organização do Catálogo de Faturação,
 recebendo um Catálogo de Faturação, um Catálogo de Fliais, um array de strings de Produtos e a quantidade de Produtos,
 retornando o Catálogo de Produtos organizado. */
CatFaturacao organizaFat (CatFaturacao cft, CatFiliais cfsT, char **lstP, int qtdP);

int qtdVenProdMesTipo(CatFaturacao cft, Produto produto, int mes, char t, int fil);

/** 
 * Função que calcula a quantidade vendida de um dado produto, num dado mês e o seu tipo de Venda,
 recendo um Catálogo de Faturação, um Produto, um mês, um char(tipo de Venda efectuado) e as quantidade de filiais,
 retornado a quantida vendida. */
int qtdProdMesTipo(CatFaturacao cft, Produto produto, int mes, char t, int fil);

/** 
 * Função que calcula o valor faturado dum dado produto num dado mês e que tipo de Venda foi efetuado,
 a mesma recebe um Catálogo de Faturação, um Produto, um mês, um char(tipo de Venda) e a quantidade de filiais existentes,
 devolvendo o valor faturado desse Produto. */
double fatProdMesTipo(CatFaturacao cft, Produto produto, int mes, char t, int fil);

/** 
 * Função responsável por calcular quais os produtos que nuncam foram comprados,
a mesma recebe um Catálogo de Faturação e devolve uma lista de strings com os Produtos não comprados. */
char** prodNuncaComprados (CatFaturacao cft);

/**
 * Função responsável por inserir as quantidades de um dado Produto num Catálogo de Faturação,
 para isso a mesma recebe um Catálogo de Faturação, um Produto, um mês, uma filial, o tipo de Venda, a quantidade vendida e o seu preço,
 retornando o Catálogo de Faturaçâo com esses dados inseridos. */
CatFaturacao insereQTDS (CatFaturacao cft,Produto pr,int mes,int filial, char tipo,int qtd,double preco);

/** 
 * Função responsável por criar uma lista de Produtos com os Produtos nao comprados,
 esta função recebe um Catálogo de Faturação, uma lista de Produtos, e uma lista de Produtos vazia,
 retonando uma lista com os Produtos nao comprados. */
char** criaLstProdNC(char** lstProdNC, char** lstProds, CatFaturacao catFat);

/** 
 * Função responsável por calcular a facturação total entre dois meses, para executar essa tarefa a função recebe,
 um Catálogo de Faturação, um intervalo entre dois meses, o tipo de Venda e a quantidade de Filiais, e retorna o valor faturando entre esses dois meses. */
double faturaMes(CatFaturacao cft, int mesI, int mesF, char tipo, int qtF);

/**
 * Função responsável por calcular a quantidade de produtos vendidos entre dois meses,
 esta recebe um Catálogo de Faturação, dois meses, o tipo de venda e o número de filiais,
 retornando a quantidade vendida de Produtos entre esses dois meses. */
int vendaMes(CatFaturacao cft, int mesI, int mesF, char tipo, int qtF);

/* Esta função tem como tarefa apagar o Catálogo de Faturação para se poder introduzir novos dados. */
void deleteCatFaturacao (CatFaturacao cft);

#endif
