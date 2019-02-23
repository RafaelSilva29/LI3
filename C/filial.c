#include "filial.h"
#define maxbufferV 128


struct filiais {
	Venda venda;
	struct filiais *left, *right;
	int balance;
} cfiliais;

struct venda {
	Produto produto;
	double preco;
	int qtd;
	char tipoNP;
	Cliente cliente;
	int mes;
	int filial;
} venda;

CatFiliais insereVenda(CatFiliais cfs,Venda v,int *cresceu);
CatFiliais insereVendaOrgC(CatFiliais cfs,Venda v,int *cresceu);

CatFiliais rotateLeftV (CatFiliais cfs) {
    CatFiliais aux;
    if ((! cfs)||(! cfs->right)) {
        printf("Erro\n");
    }
    else {
        aux = cfs->right;
        cfs->right = aux->left;
        aux->left = cfs;
        cfs = aux;
    }
    return cfs;
}

CatFiliais rotateRightV (CatFiliais cfs) {
    CatFiliais aux;
    if ((! cfs)||(! cfs->left)) {
        printf("Erro\n");
    }
    else {
        aux = cfs->left;
        cfs->left = aux->right;
        aux->right = cfs;
        cfs = aux;
    }
    return cfs;
}

CatFiliais balanceLeftV (CatFiliais cfs) {
    if (cfs->left->balance==-1) {
        /*Rotacao simples a direita*/
        cfs = rotateRightV(cfs);
        cfs->balance = 0;
        cfs->right->balance = 0;
    }
    else {
        /*Dupla rotacao*/
        cfs->left=rotateLeftV(cfs->left);
        cfs = rotateRightV(cfs);
        switch (cfs->balance) {
            case 0:
                cfs->left->balance=0;
                cfs->right->balance=0;
                break;
            case 1:
                cfs->left->balance=-1;
                cfs->right->balance=0;
                break;
            case -1:
                cfs->left->balance=0;
                cfs->right->balance=1;
        }
        cfs->balance=0;
    }
    return cfs;
}

CatFiliais balanceRightV (CatFiliais cfs) {
    if (cfs->right->balance==1) {
        /* Rotacao simples a esquerda*/
        cfs = rotateLeftV(cfs);
        cfs->balance = 0;
        cfs->left->balance = 0;
    }
    else {
        /*Dupla rotacao*/
        cfs->right = rotateRightV(cfs->right);
        cfs = rotateLeftV(cfs);
        switch (cfs->balance) {
            case 0:
                cfs->left->balance=0;
                cfs->right->balance=0;
                break;
            case -1:
                cfs->left->balance=0;
                cfs->right->balance=1;
                break;
            case 1:
                cfs->left->balance=-1;
                cfs->right->balance=0;
        }
        cfs->balance=0;
    }
    return cfs;
}

CatFiliais insereLeftV (CatFiliais cfs,Venda v, int *cresceu) {
    cfs->left = insereVenda(cfs->left, v, cresceu);
    if (*cresceu) {
        switch (cfs->balance) {
            case 1:
                cfs->balance=0;
                *cresceu=0;
                break;
            case 0:
                cfs->balance=-1;
                *cresceu=1;
                break;
            case -1:
                cfs=balanceLeftV(cfs);
                *cresceu=0;
        }
    }
    return cfs;
}

CatFiliais insereRightV (CatFiliais cfs,Venda v, int *cresceu) {
    cfs->right = insereVenda(cfs->right, v, cresceu);
    if (*cresceu) {
        switch (cfs->balance) {
            case -1:
                cfs->balance=0;
                *cresceu=0;
                break;
            case 0:
                cfs->balance=1;
                *cresceu=1;
                break;
            case 1:
                cfs = balanceRightV(cfs);
                *cresceu=0;
        }
    }
    return cfs;
}

CatFiliais insereVenda(CatFiliais cfs,Venda v,int *cresceu) {
	if (cfs==NULL) {
		cfs = (CatFiliais) malloc (sizeof(cfiliais));
		cfs->venda = v;
		cfs->right = NULL;
		cfs->left = NULL;
        cfs->balance=0;
		*cresceu=1;
	}
	else if (cmpProd(v->produto,cfs->venda->produto)<0) {
		cfs = insereLeftV (cfs,v,cresceu);
	}
	else {
		cfs = insereRightV (cfs,v,cresceu);
	}
	return cfs;
}

Venda strToVendaValida(char *s, CatProds cps, CatClientes ccs) {
	Venda v = (Venda) malloc (sizeof(venda));
    
	v->produto = strToProduto(strtok(strsep(&s," "),"\r\n"));
	if (!existeProduto(cps,v->produto)) return NULL;
    
	v->preco = atof(strsep(&s," "));
	if (v->preco<0 || v->preco>=1000) return NULL;
    
	v->qtd = atoi(strsep(&s," "));
	if (v->qtd<1 || v->qtd>200) return NULL;
    
	v->tipoNP=strsep(&s," ")[0];
	if (v->tipoNP!='N' && v->tipoNP!='P') return NULL;
    
	v->cliente = strToCliente(strtok(strsep(&s," "),"\r\n"));
    if (!existeCliente(ccs,v->cliente)) return NULL;
    
    v->mes = atoi(strsep(&s," "));
	if (v->mes<1 || v->mes>12) return NULL;
    
	v->filial = atoi(strsep(&s," "));
	if (v->filial<1 || v->filial>3) return NULL;
    
	return v;
}

CatFiliais lerVendas (char *s, CatFiliais cfs, CatProds cps, CatClientes ccs, int fil) {
	FILE *file = fopen(s,"r");
    char vendaStr[maxbufferV];
	Venda vendaLida = (Venda) malloc (sizeof(venda));
    int *cresceu = (int *) malloc (sizeof(int));
	rewind(file);
	while (fgets(vendaStr,maxbufferV,file)!=NULL) {
        if (vendaStr[strlen(strtok(vendaStr,"\r\n"))-1] == (fil+'0')){
            vendaLida = strToVendaValida(strtok(vendaStr,"\r\n"),cps,ccs);
            if (vendaLida) {
                if (vendaLida->filial==fil) cfs = insereVenda(cfs,vendaLida,cresceu);
            }
        }
    }
    free (cresceu);
    free (vendaLida);
    fclose(file);
	return cfs;
}

CatFiliais initCatFiliais(void) {
	CatFiliais cfs = NULL;
	return cfs;
}


int qtdProdCompraCliente (CatFiliais cfs, char *cliente,int mes){
    int qtd=0;
    if(cfs!=NULL){
        qtd += qtdProdCompraCliente (cfs->left,cliente,mes);
        if((strcmp(cliente,clienteToStr(cfs->venda->cliente))==0) && cfs->venda->mes==mes)
            qtd += cfs->venda->qtd;
        qtd += qtdProdCompraCliente (cfs->right,cliente,mes);
    }
    return qtd;
}


int qtdVProdMesTipoFil (CatFiliais cfs, Produto pr, int mes, char tipo, int fil) {
    int t=0;
    if (cfs!=NULL) {
        if (cmpProd(cfs->venda->produto, pr)==0) {
            fprintf(stderr, "1");
            if (cfs->venda->mes==mes && cfs->venda->tipoNP==tipo && cfs->venda->filial==fil) {
                t+=cfs->venda->qtd;
            }
        }
        t+=qtdVProdMesTipoFil(cfs->left, pr, mes, tipo, fil);
        t+=qtdVProdMesTipoFil(cfs->right, pr, mes, tipo, fil);
        /*if (cmpProd(pr, cfs->venda->produto)>0) t+=qtdVProdMesTipoFil(cfs->left, pr, mes, tipo, fil);
        else t+=qtdVProdMesTipoFil(cfs->right, pr, mes, tipo, fil);*/
    }
    return t;
}

double faturadoVProdMesTipoFil (CatFiliais cfs, Produto pr, int mes, char tipo, int fil) {
    double t=0;
    if (cfs!=NULL) {
        if (cmpProd(cfs->venda->produto, pr)==0){
            fprintf(stderr,"2");
            if (cfs->venda->mes==mes && cfs->venda->tipoNP==tipo && cfs->venda->filial==fil)
                t+=cfs->venda->qtd*cfs->venda->preco;
        
        }
        t+=faturadoVProdMesTipoFil(cfs->left, pr, mes, tipo, fil);
        t+=faturadoVProdMesTipoFil(cfs->right, pr, mes, tipo, fil);
        /* if (cmpProd(cfs->venda->produto, pr)>0)
            t+=faturadoVProdMesTipoFil(cfs->left, pr, mes, tipo, fil);
        else t+=faturadoVProdMesTipoFil(cfs->right, pr, mes, tipo, fil);*/
    }
    return t;
}

int existeCF (Cliente cl,CatFiliais cfs, int fil) {
    if (cfs!=NULL) {
        if (cmpClientes(cl,cfs->venda->cliente)==0) return 1;
        if (cmpClientes(cl,cfs->venda->cliente)<0)
            return existeCF(cl, cfs->left,fil);
        else return existeCF(cl, cfs->right,fil);
    }
    return 0;
}


char** clientesTodasFiliais (char **lstClientesTF, int qtC, CatFiliais cfsT, int qtF) {
    int i=0,j=0,ex=0,z=0;
    Cliente clAux;
    char **aux = (char **) calloc (1,sizeof(char *));
    aux[0] = (char *) calloc (1,sizeof(char));
    for (i=0;i<qtC;i++) {
        ex=0;
        clAux=strToCliente(lstClientesTF[i]);
        for (j=0;j<qtF && ex==j;j++){
            ex += existeCF(clAux,cfsT,j);
        }
        if (ex==qtF) {
            aux[z] = (char *) calloc (strlen(lstClientesTF[i]),sizeof(char));
            strcpy(aux[z++], lstClientesTF[i]);
            aux = (char **) realloc (aux,(z+1)*sizeof(char *));
            aux[z] = (char *) calloc (1,sizeof(char));
        }
    }
    return aux;
}

CatFiliais insereLeftVC (CatFiliais cfs,Venda v, int *cresceu) {
    cfs->left = insereVendaOrgC(cfs->left, v, cresceu);
    if (*cresceu) {
        switch (cfs->balance) {
            case 1:
                cfs->balance=0;
                *cresceu=0;
                break;
            case 0:
                cfs->balance=-1;
                *cresceu=1;
                break;
            case -1:
                cfs=balanceLeftV(cfs);
                *cresceu=0;
        }
    }
    return cfs;
}

CatFiliais insereRightVC (CatFiliais cfs,Venda v, int *cresceu) {
    cfs->right = insereVendaOrgC(cfs->right, v, cresceu);
    if (*cresceu) {
        switch (cfs->balance) {
            case -1:
                cfs->balance=0;
                *cresceu=0;
                break;
            case 0:
                cfs->balance=1;
                *cresceu=1;
                break;
            case 1:
                cfs = balanceRightV(cfs);
                *cresceu=0;
        }
    }
    return cfs;
}

CatFiliais insereVendaOrgC(CatFiliais dest,Venda v,int *cresceu) {
    if (dest==NULL) {
        dest = (CatFiliais) malloc (sizeof(cfiliais));
        dest->venda = v;
        dest->right = NULL;
        dest->left = NULL;
        dest->balance=0;
        *cresceu=1;
    }
    else if (cmpClientes(v->cliente,dest->venda->cliente)<0) {
        dest = insereLeftVC (dest,v,cresceu);
    }
    else {
        dest = insereRightVC (dest,v,cresceu);
    }
    return dest;
}

CatFiliais juntaFilialAux (CatFiliais dest, CatFiliais src) {
    int *cresceu = (int *) malloc (sizeof(int));
    if (src!=NULL){
        dest = insereVendaOrgC(dest, src->venda, cresceu);
        dest = juntaFilialAux(dest, src->left);
        dest = juntaFilialAux(dest, src->right);
    }
    return dest;
}


CatFiliais juntaFiliais (CatFiliais cfs[], int qtF) {
    int i=0;
    CatFiliais cAux = NULL;
    for (i=0;i<qtF;i++)
        cAux = juntaFilialAux(cAux,cfs[i]);
    return cAux;
}


CatFaturacao preencheQTDS (CatFiliais cfsT, CatFaturacao cft) {
    if (cfsT!=NULL){
        cft = preencheQTDS(cfsT->left,cft);
        cft = insereQTDS(cft,cfsT->venda->produto,cfsT->venda->mes,cfsT->venda->filial, cfsT->venda->tipoNP,cfsT->venda->qtd,cfsT->venda->preco);
        cft = preencheQTDS(cfsT->right,cft);
    }
    return cft;
}

int tamanho (CatFiliais cfs) {
    int i=0;
    if (cfs!=NULL) {
        i=1;
        i+=tamanho(cfs->left);
        i+=tamanho(cfs->right);
    }
    return i;
}

int arrayLen (char** lst) {
    int i=0;
    for (i=0;lst[i][0]!='\0';i++);
    return i;
}

char** clientesCompraProd (char **lstCl, CatFiliais cfs, Produto prod, int tipo) {
    int l=0;
    if(cfs!=NULL && prod) {
        if (cmpProd(prod, cfs->venda->produto)<=0) lstCl=clientesCompraProd(lstCl, cfs->left, prod, tipo);
        if(cmpProd(prod, cfs->venda->produto)==0 && cfs->venda->tipoNP==tipo) {
            l = arrayLen(lstCl);
            lstCl[l] = (char *) calloc((strlen(produtoToStr(prod))+1),sizeof(char));
            strcpy(lstCl[l++], clienteToStr(cfs->venda->cliente));
            lstCl = (char **) realloc (lstCl,(l+1)*sizeof(char *));
            lstCl[l] = (char *) calloc(1, sizeof(char));
        }
        if (cmpProd(prod, cfs->venda->produto)>=0)
            lstCl = clientesCompraProd(lstCl, cfs->right, prod, tipo);
    }
    return lstCl;
}

int produtoComprado (Produto produto, CatFiliais cfs){
    if(cfs!=NULL) {
        if(cmpProd(produto, cfs->venda->produto)==0)
            if (cfs->venda->qtd!=0) return 1;
        if (cmpProd(produto, cfs->venda->produto)<=0)
            if (produtoComprado(produto, cfs->left)==1) return 1;
        if (cmpProd(produto, cfs->venda->produto)>=0)
            if  (produtoComprado(produto, cfs->right)==1) return 1;
    }
    return 0;
}

int clienteComprou (Cliente cliente, CatFiliais cfsT){
    if(cfsT!=NULL) {
        if (cmpClientes(cliente, cfsT->venda->cliente)<=0)
            if (clienteComprou(cliente, cfsT->left)==1) return 1;
        if(cmpClientes(cliente, cfsT->venda->cliente)==0)
            if (cfsT->venda->qtd!=0) return 1;
        if (cmpClientes(cliente, cfsT->venda->cliente)>=0)
            if  (clienteComprou(cliente, cfsT->right)==1) return 1;
    }
    return 0;
}

void deleteCatFiliais (CatFiliais cfs) {
    if(cfs!=NULL) {
        deleteCatFiliais(cfs->left);
        deleteCatFiliais(cfs->right);
        free(cfs->venda->cliente);
        free(cfs->venda->produto);
        cfs->venda->mes=0;
        cfs->venda->filial=0;
        cfs->venda->qtd=0;
        cfs->venda->preco=0;
        cfs->venda->tipoNP='\0';
        cfs->balance=0;
        free(cfs);
    }
}
