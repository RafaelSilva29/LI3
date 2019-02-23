#include "produtos.h"
#define maxbufferPC 64


struct prods {
	Produto produto;
	CatProds left, right;
	int balance;
} cprods;

struct prod{
    char *nome;
}produto;

typedef struct list_Pods {
    int tam;
    char **produto;
}ListProds;


CatProds rotateLeftP (CatProds cps) {
    CatProds aux;
    
    if ((! cps)||(! cps->right)) {
        printf("Erro\n");
    }
    else {
        aux = cps->right;
        cps->right = aux->left;
        aux->left = cps;
        cps = aux;
    }
    
    return cps;
}

CatProds rotateRightP (CatProds cps) {
    CatProds aux;
    if ((! cps)||(! cps->left)) {
        printf("Erro\n");
    }
    else {
        aux = cps->left;
        cps->left = aux->right;
        aux->right = cps;
        cps = aux;
    }
    
    return cps;
}

CatProds balanceLeftP(CatProds cps) {
    if (cps->left->balance==-1) {
        /*Rotacao simples a direita*/
        cps = rotateRightP(cps);
        cps->balance = 0;
        cps->right->balance = 0;
    }
    else {
        /*Dupla rotacao*/
        cps->left = rotateLeftP(cps->left);
        cps = rotateRightP(cps);
        switch (cps->balance) {
            case 0:
                cps->left->balance = 0;
                cps->right->balance = 0;
                break;
            case 1:
                cps->left->balance = -1;
                cps->right->balance = 0;
                break;
            case -1:
                cps->left->balance = 0;
                cps->right->balance = 1;
        }
        cps->balance = 0;
    }
    return cps;
}

CatProds balanceRightP (CatProds cps) {
    if (cps->right->balance==1) {
        /*Rotacao simples a esquerda*/
        cps = rotateLeftP(cps);
        cps->balance=0;
        cps->left->balance=0;
    }
    else {
        /*Dupla rotacao*/
        cps->right = rotateRightP(cps->right);
        cps = rotateLeftP(cps);
        switch (cps->balance) {
            case 0:
                cps->left->balance=0;
                cps->right->balance=0;
                break;
            case -1:
                cps->left->balance=0;
                cps->right->balance=1;
                break;
            case 1:
                cps->left->balance=-1;
                cps->right->balance=0;
        }
        cps->balance=0;
    }
    return cps;
}

CatProds insereLeftP (CatProds cps,Produto pr, int *cresceu) {
    cps->left = insereProduto(cps->left, pr, cresceu);
    if (*cresceu) {
        switch (cps->balance) {
            case 1:
                cps->balance=0;
                *cresceu=0;
                break;
            case 0:
                cps->balance=-1;
                *cresceu=1;
                break;
            case -1:
                cps = balanceLeftP(cps);
                *cresceu=0;
        }
    }
    return cps;
}

CatProds insereRightP (CatProds cps,Produto pr, int *cresceu) {
    cps->right = insereProduto (cps->right, pr, cresceu);
    if (*cresceu) {
        switch (cps->balance) {
            case -1:
                cps->balance=0;
                *cresceu=0;
                break;
            case 0:
                cps->balance=1;
                *cresceu=1;
                break;
            case 1:
                cps = balanceRightP(cps);
                *cresceu=0;
        }
    }
    return cps;
}

CatProds insereProduto (CatProds cps, Produto produto, int *cresceu) {
	if (cps==NULL) {
		cps = (CatProds) malloc (sizeof(cprods));
		cps->produto = produto;
		cps->left = NULL;
		cps->right = NULL;
		cps->balance=0;
        *cresceu=1;
		return cps;
	}
	else if (strcmp(produto->nome,cps->produto->nome)<0) {
		cps = insereLeftP (cps,produto,cresceu);
	}
	else {
		cps = insereRightP (cps,produto,cresceu);
	}
	return cps;
}

Produto strToProduto (char *s) {
	Produto aux = (Produto) malloc (sizeof(produto));
    aux->nome = (char *) calloc ((strlen(s)+1),sizeof(char));
    strcpy(aux->nome,s);
	return aux;
}

CatProds lerProds(CatProds cps, char *s){
	FILE *file = fopen(s,"r");
	Produto prod = (Produto) malloc (sizeof(produto));
    char aux[maxbufferPC];
    int cresceu;
	rewind(file);
	while (fgets(aux,maxbufferPC,file)!=NULL) {
        prod = strToProduto(strtok(aux,"\r\n"));
		cps = insereProduto (cps,prod,&cresceu);
    }
    free(prod);
    fclose(file);
	return cps;
}

CatProds initCatProds(void) {
	CatProds cps = NULL;
	return cps;
}

int cmpProd (Produto pr1, Produto pr2) {
    if (strcmp(pr1->nome,pr2->nome)==0)
        return 0;
    else if (strcmp(pr1->nome,pr2->nome)>0)
        return 1;
    else return -1;
}

int existeProduto(CatProds cps, Produto pr) {
	if (cps==NULL) return 0;
	else {
		int x = cmpProd(pr,cps->produto);
		switch(x) {
			case 0:
				return 1;
			case -1:
				return existeProduto(cps->left,pr);
			case 1:
				return existeProduto(cps->right,pr);
			default:
				return 0;
		}
	}
	return 0;
}

int totalProdutosLetra (CatProds cps, char c) {
    int i=0;
    if (cps!=NULL){
        if (c==cps->produto->nome[0]) i=1;
        i += totalProdutosLetra(cps->left,c);
        i += totalProdutosLetra(cps->right,c);
    }
    return i;
}

int totalProdutos (CatProds cps) {
    int i=0;
    if (cps!=NULL){
        i=1;
        i += totalProdutos (cps->left);
        i += totalProdutos (cps->right);
    }
    return i;
}


ListProds* toArrayLetra (CatProds cps, char c,ListProds *aux){
    if (cps!=NULL) {
        aux = toArrayLetra(cps->left, c, aux);
        if (cps->produto->nome[0]==c)
            strcpy(aux->produto[aux->tam++],cps->produto->nome);
        aux = toArrayLetra(cps->right, c, aux);
    }
    return aux;
}

char** listaProLetra (CatProds cps,char c) {
    ListProds *aux = (ListProds *) calloc (1, sizeof(ListProds));
    if (cps!=NULL){
        int i, x = totalProdutosLetra(cps,c);
        aux->tam = 0;
        aux->produto = (char **) calloc (x+1,sizeof(char *));
        for (i=0;i<x+1;i++)
            aux->produto[i] = (char *) calloc((strlen(cps->produto->nome)+1),sizeof(char));
        aux = toArrayLetra(cps,c,aux);
    }
    return aux->produto;
}

ListProds* toArrayP (CatProds cps, ListProds *aux){
    if (cps!=NULL) {
        aux = toArrayP(cps->left, aux);
        strcpy(aux->produto[aux->tam++],cps->produto->nome);
        aux = toArrayP(cps->right, aux);
    }
    return aux;
}


char** listaProdutos (CatProds cps) {
    ListProds *aux = (ListProds *) calloc (1, sizeof(ListProds));
    if (cps!=NULL){
        int i, x = totalProdutos(cps);
        aux->tam = 0;
        aux->produto = (char **) calloc (x+1,sizeof(char *));
        for (i=0;i<x+1;i++)
            aux->produto[i] = (char *) calloc((strlen(cps->produto->nome)+1),sizeof(char));
        aux = toArrayP(cps,aux);
    }
    return aux->produto;
}


char* produtoToStr (Produto pr) {
    char *aux = (char *) calloc (strlen(pr->nome),sizeof(produto));
    strcpy(aux,pr->nome);
    return aux;
}

void deleteCatProds (CatProds cps) {
    if(cps!=NULL) {
        deleteCatProds(cps->left);
        deleteCatProds(cps->right);
        free(cps->produto);
        cps->balance=0;
        free(cps);
    }
}











