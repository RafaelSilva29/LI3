#include "faturacao.h"


struct valores {
    int venda;
    int qtd;
    double faturado;
} valores;

struct faturacao {
    Produto prod;
    Valores N;
    Valores P;
    Faturacao left, right;
}faturacao;

struct cfaturacao {
    int qtF;
    Faturacao *mes[12];
}cfaturacao;


Faturacao insereProdsFat (Faturacao fat, char **lstP,int qtdP) {
    int i=qtdP/2;
    if (qtdP<=0) fat=NULL;
    else {
        fat = (Faturacao) calloc(1, sizeof(faturacao));
        fat->left = insereProdsFat(fat->left, lstP, i);
        fat->right = insereProdsFat(fat->right, lstP+i+1, qtdP-i-1);
        fat->prod = strToProduto(lstP[i]);
        fat->N = (Valores) calloc(1, sizeof(valores));
        fat->P = (Valores) calloc(1, sizeof(valores));
    }
    return fat;
}

CatFaturacao organizaFat (CatFaturacao cft, CatFiliais cfsT,char **lstP, int qtdP) {
    int i=0,j=0;
    for (i=0;i<12;i++)
        for (j=0;j<cft->qtF;j++){
            cft->mes[i][j] = insereProdsFat (cft->mes[i][j],lstP,qtdP);
        }
    cft = preencheQTDS(cfsT, cft);
    return cft;
}

CatFaturacao initCatFaturacao (int qtF) {
    int i=0,j=0;
    CatFaturacao cft = (CatFaturacao) calloc (1, sizeof(cfaturacao));
    cft->qtF = qtF;
    for (i=0;i<12;i++){
        cft->mes[i] = (Faturacao *) calloc (qtF, sizeof(faturacao));
    }
    for (i=0;i<12;i++)
        for (j=0;j<qtF;j++)
            cft->mes[i][j] = (Faturacao) calloc (1, sizeof(faturacao));
    return cft;
}

int qtdVenProdTipo (Faturacao fat, Produto prod, char t){
    int qtd = 0;
    if (fat!=NULL) {
        if(t=='N') {
            if (cmpProd(fat->prod, prod)==0) {
                qtd += (fat->N->venda);
            } else if (cmpProd(fat->prod, prod)>0)
                qtd += qtdVenProdTipo(fat->left, prod, t);
            else qtd += qtdVenProdTipo(fat->right, prod, t);
        }
        else if(t=='P') {
            if (cmpProd(fat->prod, prod)==0) {
                qtd += (fat->P->venda);
            } else if (cmpProd(fat->prod, prod)>0)
                qtd += qtdVenProdTipo(fat->left, prod, t);
            else qtd += qtdVenProdTipo(fat->right, prod, t);
        }
    }
    return qtd;
}

int qtdVenProdMesTipo(CatFaturacao cft, Produto produto, int mes, char t, int fil) {
    int i,qtd = 0;
    if(fil==0) {
        for(i=0;i<cft->qtF;i++) {
            qtd += qtdVenProdTipo(cft->mes[mes-1][i],produto,t);
        }
    } else qtd += qtdVenProdTipo(cft->mes[mes-1][fil-1],produto,t);
    return qtd;
}

int qtdProdTipo (Faturacao fat, Produto prod, char t){
    int qtd = 0;
    if (fat!=NULL) {
        if(t=='N') {
            if (cmpProd(fat->prod, prod)==0) {
                qtd += (fat->N->qtd);
            } else if (cmpProd(fat->prod, prod)>0)
                qtd += qtdProdTipo(fat->left, prod, t);
            else qtd += qtdProdTipo(fat->right, prod, t);
        }
        else if(t=='P') {
            if (cmpProd(fat->prod, prod)==0) {
                qtd += (fat->P->qtd);
            } else if (cmpProd(fat->prod, prod)>0)
                qtd += qtdProdTipo(fat->left, prod, t);
            else qtd += qtdProdTipo(fat->right, prod, t);
        }
    }
    return qtd;
}

int qtdProdMesTipo(CatFaturacao cft, Produto produto, int mes, char t, int fil) {
    int i,qtd = 0;
    if(fil==0) {
        for(i=0;i<cft->qtF;i++) {
            qtd += qtdProdTipo(cft->mes[mes-1][i],produto,t);
        }
    } else qtd += qtdProdTipo(cft->mes[mes-1][fil-1],produto,t);
    return qtd;
}

double fatProdTipo (Faturacao fat, Produto prod, char t){
    double faturacao = 0;
    if (fat!=NULL) {
        if(t=='N') {
            if (cmpProd(fat->prod, prod)==0) {
                faturacao += (fat->N->faturado);
            } else if (cmpProd(fat->prod, prod)>0)
                faturacao += fatProdTipo(fat->left, prod, t);
            else faturacao += fatProdTipo(fat->right, prod, t);
        }
        if(t=='P') {
            if (cmpProd(fat->prod, prod)==0) {
                faturacao += (fat->P->faturado);
            } else if (cmpProd(fat->prod, prod)>0)
                faturacao += fatProdTipo(fat->left, prod, t);
            else faturacao += fatProdTipo(fat->right, prod, t);
        }
    }
    return faturacao;
}


double fatProdMesTipo(CatFaturacao cft, Produto produto, int mes, char t, int fil) {
    int i;
    double fat = 0;
    if(fil==0){
        for(i=0;i<cft->qtF;i++) {
            fat += fatProdTipo(cft->mes[mes-1][i],produto,t);
        }
    } else fat += fatProdTipo(cft->mes[mes-1][fil-1],produto,t);
    return fat;
}


Faturacao insereQTDSaux (Faturacao fat,Produto pr, char tipo,int qtd,double preco){
    if (fat!=NULL){
        if (cmpProd(pr, fat->prod)==0) {
            if (tipo=='N') {
                fat->N->venda++;
                fat->N->qtd+=qtd;
                fat->N->faturado+=qtd*preco;
            }
            else if (tipo=='P') {
                fat->P->venda++;
                fat->P->qtd+=qtd;
                fat->P->faturado+=qtd*preco;
            }
            return fat;
        }
        if (cmpProd(pr, fat->prod)<0)
            fat->left = insereQTDSaux(fat->left, pr, tipo, qtd, preco);
        else fat->right = insereQTDSaux(fat->right, pr, tipo, qtd, preco);
    }
    return fat;
}

CatFaturacao insereQTDS (CatFaturacao cft,Produto pr,int mes,int filial, char tipo,int qtd,double preco) {
    cft->mes[mes-1][filial-1] = insereQTDSaux (cft->mes[mes-1][filial-1],pr,tipo,qtd,preco);
    return cft;
}

double faturaMesAux (Faturacao fat, char tipo) {
    double fatura=0;
    if(fat!=NULL) {
        if (tipo=='N'){
            fatura += fat->N->faturado;
            fatura += faturaMesAux(fat->left, tipo);
            fatura += faturaMesAux(fat->right, tipo);
        }
        else {
            fatura += fat->P->faturado;
            fatura += faturaMesAux(fat->left, tipo);
            fatura += faturaMesAux(fat->right, tipo);
        }
    }
    return fatura;
}

double faturaMes(CatFaturacao cft, int mesI, int mesF, char tipo, int qtF) {
    int i,j;
    double fat=0;
    for(i=(mesI-1);i<mesF;i++){
        for(j=0;j<qtF;j++){
            fat += faturaMesAux(cft->mes[i][j],tipo);
        }
    }
    return fat;
}

int vendaMesAux (Faturacao fat, char tipo) {
    int fatura=0;
    if(fat!=NULL) {
        if (tipo=='N'){
            fatura += fat->N->venda;
            fatura += vendaMesAux(fat->left, tipo);
            fatura += vendaMesAux(fat->right, tipo);
        }
        else {
            fatura += fat->P->venda;
            fatura += vendaMesAux(fat->left, tipo);
            fatura += vendaMesAux(fat->right, tipo);
        }
    }
    return fatura;
}

int vendaMes(CatFaturacao cft, int mesI, int mesF, char tipo, int qtF) {
    int i,j;
    int qtd=0;
    for(i=(mesI-1);i<mesF;i++){
        for(j=0;j<qtF;j++){
            qtd += vendaMesAux(cft->mes[i][j],tipo);
        }
    }
    return qtd;
}

void deleteFaturacao (Faturacao fat) {
    if(fat!=NULL) {
        deleteFaturacao(fat->left);
        deleteFaturacao(fat->right);
        free(fat->prod);
        fat->N->faturado=0;
        fat->N->qtd=0;
        free(fat->N);
        fat->P->faturado=0;
        fat->P->qtd=0;
        free(fat->P);
        free(fat);
    }
}

void deleteCatFaturacao (CatFaturacao cft) {
    int i, j;
    if(cft!=NULL) {
        for(i=0;i<12;i++)
            for(j=0;j<cft->qtF;j++) {
                deleteFaturacao(cft->mes[i][j]);
            }
        cft->qtF=0;
    }
}
