/*filial.h*/
#ifndef filial_H 
#define filial_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura que define o Catálogo de Filiais */
typedef struct filiais* CatFiliais;

/* Definiçao do tipo Venda */
typedef struct venda* Venda;

#include "clientes.h"
#include "produtos.h"
#include "faturacao.h"

/** 
 * Função responsável por ler cada Venda para o Catálogo de Filiais,
 recebendo um Catálogo de Produtos, um Catálogo de Filiais, um Catálogo de Clientes, um camiho para o ficheiro input de Vendas e quantas filiais existem,
 retornando um Catálogo de Filiais. */
CatFiliais lerVendas (char *s, CatFiliais cfs, CatProds cps, CatClientes ccs, int fil);

/* Função responsável por inicializar o Catálogo de Filiais. */
CatFiliais initCatFiliais();

/** 
 * Função que calcula a quantidade de Produtos comprados por um Cliente num dado mês,
 para isso a função recebe um Catálogo de Filiais, um Cliente e o mês que se pretende calcular,
 retornando a quantidade total. */
int qtdProdCompraCliente (CatFiliais cfs, char *cliente,int mes);

/** 
 * Função responsável por calcular a quantidade de um dado Produto, num dado mês, a filial a que pertence e o tipo de Venda feita,
 recebendo um Cátalogo de Filiais, um Produto, um mês, o tipo de Venda e uma filial,
 retornando a dita quantidade. */
int qtdVProdMesTipoFil (CatFiliais cfs, Produto pr, int mes, char tipo, int fil);

/** 
 * Função que calcula o valor faturado num Produto, num dado mês, o seu tipo de Venda e a filial a que pertencem,
 recebe um Catálogo de Filiais, um Produto, um mês, o tipo de Venda, e uma filial,
 retornado o valor faturado desse Produto. */
double faturadoVProdMesTipoFil (CatFiliais cfs, Produto pr, int mes, char tipo, int fil);

/** 
 * Função que transforma todos os Clientes presentes num Catálogo de Fliais duma dada filial para um lista de filiais,
 a mesma recebe um Catálogo de Filiais, a quantidade de Clientes existentes, uma Filial e uma lista de Clientes de todas as filiais,
 retornando uma lista de Clientes com os Clientes dessa Filial. */
char** clientesTodasFiliais (char **lstClientesTF, int qtC, CatFiliais cfsT, int qtF);

/** 
 * Função responsável pela junção de vários Catálogo de Filiais num so único Catálogo,
 recebendo para isso um array de Catálogo de Filiais e a quantidade de filiais existentes,
 retornando um Catálogo de Filiais. */
CatFiliais juntaFiliais (CatFiliais cfs[], int qtF);

/** 
 * Função responsável por preencher um Catálogo de Faturação com as quantidades de cada Venda de cada Produto,
 recebendo um Catálogo de Filiais e um Catálogo de Faturação, retornando o Catálogo de Faturação final. */
CatFaturacao preencheQTDS (CatFiliais cfsT, CatFaturacao cft);

/** 
 * Função que calcula o tamanho de cada Catálogo de Filiais,
 recebendo um Catálogo de Produtos, retornando o tamanho desse mesmo. */
int tamanho (CatFiliais cfs);

/** 
 * Função que transforma todos os produtos presentes no Catálogo de Filiais para uma lista de Produtos diferenciada pelo tipo de Venda,
 a mesma recebe um Catálogo de Filiais, um Produto e o tipo de venda efectuado, retornando a lista de Produtos por tipo de Vendas */ 
char** clientesCompraProd (char** lstClientes, CatFiliais cfs, Produto prod, int tipo);

/** 
 * Função que verifica se um dado Cliente efectuou compras, esta função recebe um Catálogo de Clientes e um Cliente,
 e verifica se o mesmo existe no Catálogo de Filiais, retorna 1 se for verdade. */
int clienteComprou (Cliente cliente, CatFiliais cfsT);

/** 
 * Função que verifica se um dado Produto é comprado, para isso a função recebe
 um Catálogo de Filiais e um Produto, caso esse Produto existir a função retorna 1.*/
int produtoComprado (Produto produto, CatFiliais cfs);

/* Esta função tem como tarefa apagar o Catálogo de Filiais para se poder introduzir novos dados. */
void deleteCatFiliais (CatFiliais cfs);

#endif
