/*clientes.h*/
#ifndef clientes_H 
#define clientes_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Estrutura de Catálogo de Clientes. */
typedef struct clientes* CatClientes;

/* Definição do tipo Cliente. */
typedef struct cliente* Cliente;

/* Esta funçao incializa o Catálogo de Clientes. */
CatClientes initCatClientes();

/** 
 * Função responsável por ler cada tipo Cliente do ficheiro input de Clientes,
 onde esta recebe um Catálogo de Clientes e o caminho para o ficheiro. */
CatClientes lerClientes (CatClientes ccs, char *s);

/**
 * Função que tem como objetivo a inserção de cada um dos Clientes para o Catálogo de Clientes,
 esta recebe um Catálogo de Clientes, um Cliente e um int que indica quando o Cliente foi adicionado, retorna o Catalogo de Clientes completo. */
CatClientes insereCliente(CatClientes ccs, Cliente cli, int *cresceu);

/**
 * Esta função tem como propósito verificar se existe um Cliente num Catálogo de Clientes,
 para executar essa tarefa a função recebe um Catálogo de Clientes e um Cliente e retorna 1 se existir esse Cliente num Catálogo de Clientes. */
int existeCliente(CatClientes ccs, Cliente cl);

/* Esta funçao tranforma o tipo string para o tipo Cliente. */
Cliente strToCliente (char *s);

/* Esta função tranforma o tipo Cliente para o tipo string */
char* clienteToStr (Cliente cl);

/**
 * Esta função transforma o Catalogo de Clientes num array de strings de Clientes,
 dando-lhe um Catalogo de Clientes e retornado o array de strings de clientes. */
char** listaClientes (CatClientes ccs);

/**
 * Esta função calcula quantos Clientes existem no Catálogo de Clientes,
 dando-lhe um Catálogo de Clientes e esta vai retornar o número total de Clientes. */
int totalClientes (CatClientes ccs);

/**
 * Esta função compara dois Clientes e verifica se os mesmo são iguais,
 dando-lhe dois Clientes e retorna 1 se foram iguais. */
int cmpClientes (Cliente cl1, Cliente cl2);

/* Esta função tem como tarefa apagar o Catálogo de Clientes para se poder introduzir novos dados. */
void deleteCatClientes (CatClientes ccs);

#endif
