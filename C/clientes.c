#include "clientes.h"
#define maxbufferPC 64


struct clientes {

	Cliente cliente;

	CatClientes right, left;

	/*-1-> mais na esquerda     0->igual      1->mais na direita*/
	int balance;
} cclientes;


struct cliente {
	char *nome;
} cliente;


typedef struct list_Cls {
    int tam;
    char **cliente;
}ListCls;

CatClientes rotateLeftC (CatClientes ccs) {
    CatClientes aux;
    
    if (ccs!=NULL && ccs->right!=NULL) {
        aux = ccs->right;
        ccs->right = aux->left;
        aux->left = ccs;
        ccs = aux;
    }
    
    return ccs;
}

CatClientes rotateRightC (CatClientes ccs) {
    CatClientes aux;
    
    if (ccs!=NULL && ccs->left!=NULL) {
        aux = ccs->left;
        ccs->left = aux->right;
        aux->right = ccs;
        ccs = aux;
    }
    
    return ccs;
}

CatClientes balanceLeftC (CatClientes ccs) {
    if (ccs->left->balance==-1) {
        /*Rotacao simples a direita*/
        ccs = rotateRightC(ccs);
        ccs->balance=0;
        ccs->right->balance=0;
    }
    else {
        /*Dupla rotacao*/
        ccs->left=rotateLeftC(ccs->left);
        ccs = rotateRightC(ccs);
        switch (ccs->balance) {
            case 0:
                ccs->left->balance=0;
                ccs->right->balance=0;
                break;
            case 1:
                ccs->left->balance=-1;
                ccs->right->balance=0;
                break;
            case -1:
                ccs->left->balance=0;
                ccs->right->balance=1;
        }
        ccs->balance=0;
    }
    return ccs;
}

CatClientes balanceRightC (CatClientes ccs) {
    if (ccs->right->balance==1) {
        /*Rotacao simples a esquerda*/
        ccs = rotateLeftC(ccs);
        ccs->balance=0;
        ccs->left->balance=0;
    }
    else {
        /*Dupla rotacao*/
        ccs->right = rotateRightC(ccs->right);
        ccs = rotateLeftC(ccs);
        switch (ccs->balance) {
            case 0:
                ccs->left->balance=0;
                ccs->right->balance=0;
                break;
            case -1:
                ccs->left->balance=0;
                ccs->right->balance=1;
                break;
            case 1:
                ccs->left->balance=-1;
                ccs->right->balance=0;
        }
        ccs->balance=0;
    }
    return ccs;
}

CatClientes insereLeftC (CatClientes ccs, Cliente cl, int *cresceu) {
    ccs->left= insereCliente (ccs->left, cl, cresceu);
    if (*cresceu) {
        switch (ccs->balance) {
            case 1:
                ccs->balance=0;
                *cresceu=0;
                break;
            case 0:
                ccs->balance=-1;
                *cresceu=1;
                break;
            case -1:
                ccs = balanceLeftC(ccs);
                *cresceu=0;
        }
    }
    return ccs;
}

CatClientes insereRightC (CatClientes ccs, Cliente cl, int *cresceu) {
    ccs->right = insereCliente (ccs->right,cl,cresceu);
    if (*cresceu) {
        switch (ccs->balance) {
            case -1:
                ccs->balance=0;
                *cresceu=0;
                break;
            case 0:
                ccs->balance=1;
                *cresceu=1;
                break;
            case 1:
                ccs = balanceRightC(ccs);
                *cresceu=0;
        }
    }
    return ccs;
}

CatClientes insereCliente (CatClientes ccs, Cliente cl, int *cresceu) {
    if (ccs==NULL){
        ccs = (CatClientes) malloc (sizeof(cclientes));
        ccs->cliente = cl;
        ccs->right=NULL;
        ccs->left=NULL;
        ccs->balance = 0;
        *cresceu=1;
    }
    else if (strcmp(cl->nome,ccs->cliente->nome)<0) {
        ccs = insereLeftC (ccs,cl,cresceu);
    }
    else {
        ccs = insereRightC(ccs,cl,cresceu);
    }
    return(ccs);
}


Cliente strToCliente (char *s) {
	Cliente aux = (Cliente) malloc (sizeof(cliente));
    aux->nome = (char *) calloc((strlen(s)+1), sizeof(char));
    strcpy(aux->nome,s);
	return aux;
}

CatClientes lerClientes (CatClientes ccs, char *s) {
	FILE *file = fopen(s,"r");
	Cliente cli = (Cliente) malloc (sizeof(cliente));
    char aux[maxbufferPC];
	int cresceu;
	rewind(file);
	while (fgets(aux,maxbufferPC,file)!=NULL) {
		cli = strToCliente(strtok(aux,"\r\n"));
		ccs = insereCliente(ccs,cli,&cresceu);
    }
    free(cli);
    fclose(file);
	return ccs;
}


CatClientes initCatClientes(void) {
	CatClientes ccs = NULL;
	return ccs;
}


int existeCliente (CatClientes ccs, Cliente cl) {
    if (ccs!=NULL){
        if (strcmp(ccs->cliente->nome,cl->nome)==0)
            return 1;
        else if (strcmp(cl->nome,ccs->cliente->nome)<0)
            return(existeCliente(ccs->left,cl));
        else return (existeCliente(ccs->right,cl));
    }
    return 0;
}

char* clienteToStr (Cliente cl) {
    return cl->nome;
}

ListCls* toArrayC (CatClientes ccs, ListCls *aux){
    if (ccs!=NULL) {
        aux = toArrayC(ccs->left, aux);
        strcpy(aux->cliente[aux->tam++],ccs->cliente->nome);
        aux = toArrayC(ccs->right, aux);
    }
    return aux;
}


char** listaClientes (CatClientes ccs) {
    ListCls *aux = (ListCls *) calloc (1, sizeof(ListCls));
    if (ccs!=NULL){
        int i, x = totalClientes(ccs);
        aux->tam = 0;
        aux->cliente = (char **) malloc ((x+1)*sizeof(char *));
        for (i=0;i<x+1;i++)
            aux->cliente[i] = (char *) malloc((strlen(ccs->cliente->nome)+1)*sizeof(char));
        aux = toArrayC(ccs,aux);
    }
    return aux->cliente;
}

int totalClientes (CatClientes ccs) {
    int i=0;
    if (ccs!=NULL){
        i=1;
        i += totalClientes (ccs->left);
        i += totalClientes (ccs->right);
    }
    return i;
}

int cmpClientes (Cliente cl1, Cliente cl2) {
    if (strcmp(cl1->nome,cl2->nome)<0)
        return -1;
    else if (strcmp(cl1->nome,cl2->nome)>0)
        return 1;
    else return 0;
}

void deleteCatClientes (CatClientes ccs) {
    if(ccs!=NULL) {
        deleteCatClientes(ccs->left);
        deleteCatClientes(ccs->right);
        free(ccs->cliente);
        ccs->balance=0;
        free(ccs);
    }
}


