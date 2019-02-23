/**

@mainpage GereVendas

"GereVendas" é um programa, cujo principal objectivo é "Gestão das Vendas de uma Cadeia de Distribuição com 3 Filiais" \n
Nesta versão são gerados dois catálogos, o de produtos e o de clientes. \n

@author Alexandre Teixeira -- a73547
@author Bruno Sousa -- a74330
@author Rafael Silva -- a74264

*/

#include "clientes.h"
#include "produtos.h"
#include "filial.h"
#include "faturacao.h"

#define maxbufferPC 64
#define maxbufferV 128

/*-----------------------------QUERY 1.3---------------------------------*/
int free_ALL (CatClientes ccs, CatProds cps, CatFiliais cfs[],CatFaturacao cft, int qtF) {
    int i;
    deleteCatProds(cps);
    deleteCatClientes(ccs);
    for(i=0;i<qtF;i++)
        deleteCatFiliais(cfs[i]);
    deleteCatFaturacao(cft);
    return 1;
}


/*-----------------------------QUERY 12---------------------------------*/
void nrProdClientesNUsados(CatFiliais cfs[], CatProds cps, CatClientes ccs, int qtF) {
    int i, j=0, z=0, qtdP=0, qtdC=0;
    char **lstProds = NULL;
    char **lstClientes = NULL;
    CatFiliais catAux = juntaFiliais(cfs, qtF);
    lstProds = listaProdutos(cps);
    lstClientes = listaClientes(ccs);
    while(lstProds[z][0]!='\0') {
        j=0;
        for (i=0;i<qtF;i++) {
            if (produtoComprado(strToProduto(lstProds[z]),cfs[i])==0){
                j++;
            }
        }
        if (j==qtF) qtdP++;
        z++;
    }
    z=0;
    while(lstClientes[z][0]!='\0') {
        if (clienteComprou(strToCliente(lstClientes[z]),catAux)==0){
            qtdC++;
        }
        z++;
    }
    fprintf(stderr,"Total de Produtos Nunca Comprados: %d\n",qtdP);
    fprintf(stderr,"Total de Clientes Que Nunca Compraram: %d\n",qtdC);
}

/*-----------------------------QUERY 8---------------------------------*/
void apresentaClientesComPF(CatFiliais cfs[]) {
    int fil, i=0;
    char prodAux[maxbufferPC], prod[maxbufferPC], filAux[maxbufferPC];
    char **lstClientesN = (char **) calloc(1, sizeof(char *));
    char **lstClientesP = (char **) calloc(1, sizeof(char *));
    lstClientesN[0] = (char *) calloc(1, sizeof(char));
    lstClientesP[0] = (char *) calloc(1, sizeof(char));
    fprintf(stderr,"Insira o Produto: ");
    if (fgets(prodAux,64,stdin)) {
        strcpy(prod,strtok(prodAux,"\n\r"));
        fprintf(stderr,"Insira  a Filial: ");
        if (fgets(filAux,3,stdin)) {
            fil = atoi(filAux);
            lstClientesN = clientesCompraProd(lstClientesN, cfs[fil-1],strToProduto(prod),'N');
            lstClientesP = clientesCompraProd(lstClientesP, cfs[fil-1],strToProduto(prod),'P');
        }
        i=0;
        if (lstClientesN[0][0]!='\0') {
            fprintf(stderr, "Tipo N");
            while (lstClientesN[i][0]!='\0') {
                fprintf(stderr, "  |  %s", lstClientesN[i++]);
            }
            fprintf(stderr, "  |\n");
        }
        i=0;
        if (lstClientesP[0][0]!='\0') {
            fprintf(stderr, "Tipo P");
            while (lstClientesP[i][0]!='\0') {
                fprintf(stderr, "  |  %s", lstClientesP[i++]);
            }
            fprintf(stderr, "  |\n");
        }
    }
}

/*-----------------------------QUERY 7---------------------------------*/
void apresentaCliCompraTodasFiliais (CatClientes catClientes, CatFiliais catFiliais[],int qtF) {
    int qtC = totalClientes(catClientes), i=0, sw=0,z=0,y=0;
    char **lstClientes = listaClientes(catClientes), letter[3];
    char **lstClientesTF = NULL;
    CatFiliais catFAux = juntaFiliais(catFiliais, qtF);
    lstClientesTF = clientesTodasFiliais(lstClientes,qtC,catFAux,qtF);
    for (y=0;lstClientesTF[y][0];y++);
    while (lstClientesTF[i][0]!='\0' && sw!=1) {
        if (z==120) {
            fprintf(stderr,"---------------------Enter para Apresentar Mais-------------------%d/%d",i/120,(y/120)+((y%120)/(y%120)));
            fgets (letter,3,stdin);
            if (letter[0]=='\n' || letter[0]=='\r') {i--;z=0;}
            else {sw=1;/*trigger=0;*/}
        }
        else {
            fprintf(stderr, "  |  %s",lstClientesTF[i]);
            if ((i%6)==5) fprintf(stderr, "  |\n");
            z++;
        }
        i++;
    }
    fprintf(stderr,"\n-------------------Enter para Menu Anterior------------------");
    if(fgets(letter,3,stdin)) return;
}

/*-----------------------------QUERY 6---------------------------------*/
void apresentaFaturacaoEntreMeses(CatFaturacao cft,int qtF) {
    int init,fin, vendaP = 0,vendaN = 0;
    double fatP=0,fatN=0;
    char intervalo[maxbufferPC], inicio[maxbufferPC], fim[maxbufferPC];
    fprintf(stderr,"Insira o Intervalo: ");
    if(fgets(intervalo,64,stdin)) {
        strcpy(inicio,strtok(intervalo,"."));
        strcpy(fim,strtok(NULL,"]"));
        init=atoi(&inicio[1]);
        fin=atoi(&fim[1]);
        fatN += faturaMes(cft, init,fin, 'N', qtF);
        fatP += faturaMes(cft, init,fin, 'P', qtF);
        vendaN += vendaMes(cft, init, fin, 'N', qtF);
        vendaP += vendaMes(cft, init, fin, 'P', qtF);

        fprintf(stderr,"Faturação em relação a N, no intervalo de meses [%d..%d]: %.2f\n",init,fin,fatN);
        fprintf(stderr,"Faturação em relação a P, no intervalo de meses [%d..%d]: %.2f\n",init,fin,fatP);
        fprintf(stderr,"Vendas em relação a N, no intervalo de meses [%d..%d]: %d\n",init,fin,vendaN);
        fprintf(stderr,"Vendas em relação a P, no intervalo de meses [%d..%d]: %d\n",init,fin,vendaP);
    }
    fprintf(stderr,"\n----------------------Enter para Menu Anterior---------------------");
    if (fgets(inicio,3,stdin)) return;
}

/*-----------------------------QUERY 5---------------------------------*/
void apresentaNmrPComC (CatFiliais cfs[],int qtF) {
    int i, mes, qtd, esp, espAux1, espAux2;
    char clienteAux[maxbufferPC], cliente[maxbufferPC], mesAux[3];
    fprintf(stderr,"Insira o Cliente: ");
    if (fgets(clienteAux,64,stdin)) {
        strcpy(cliente,strtok(clienteAux,"\n\r"));
        fprintf(stderr,"Insira mês (0 - Global): ");
        if (fgets(mesAux,3,stdin)) {
            mes = atoi(mesAux);
            if(mes!=0) {
                fprintf(stderr,"--------------------\n");
                fprintf(stderr,"Mês      |    %d    |",mes);
                for(i=0;i<qtF;i++){
                    fprintf(stderr,"\n--------------------\n");
                    fprintf(stderr,"Filial %d |",i+1);
                    qtd = qtdProdCompraCliente(cfs[i],cliente,mes);
                    espAux1=qtd;
                    for (espAux2=1;espAux1>9;espAux2++) espAux1/=10;
                    for (esp=0;esp<((9-espAux2)/2);esp++)
                        fprintf(stderr," ");
                    fprintf(stderr,"%d",qtd);
                    for (esp=((9-espAux2)/2)+espAux2;esp<9;esp++)
                        fprintf(stderr," ");
                    fprintf(stderr,"|");
                }
            }
            else {
                fprintf(stderr,"----------------------------------------------------------------------------------------------------------------------------------\n");
                fprintf(stderr,"Mês      |    1    |    2    |    3    |    4    |    5    |    6    |    7    |    8    |    9    |   10    |   11    |   12    |");
                for(i=0;i<qtF;i++) {
            fprintf(stderr,"\n----------------------------------------------------------------------------------------------------------------------------------\n");
                    fprintf(stderr,"Filial %d |",i+1);
                    for (mes=1;mes<=12;mes++) {
                        qtd = qtdProdCompraCliente(cfs[i],cliente,mes);
                        espAux1=qtd;
                        for (espAux2=1;espAux1>9;espAux2++) espAux1/=10;
                        for (esp=0;esp<((9-espAux2)/2);esp++) fprintf(stderr," ");
                        fprintf(stderr,"%d",qtd);
                        for (esp=((9-espAux2)/2)+espAux2;esp<9;esp++) fprintf(stderr," ");
                        fprintf(stderr,"|");
                    }
                }
            }
            fprintf(stderr,"\n-----------------------------------------------------Enter para Menu Anterior-----------------------------------------------------");
            if (fgets (mesAux,3,stdin)) return;
        }
    }
}

/*-----------------------------QUERY 4---------------------------------*/
void apresentaProdutosNC (CatProds catProds, CatFaturacao catFat) {
    int i, z=0, y=0, qtd=0, sw=0, fil;
    char **lstProds = NULL, **lstProdNC = (char **) calloc(1, sizeof(char *)), letter[3], filAux[maxbufferPC];
    lstProdNC[0] = (char *) calloc(1, sizeof(char));
    lstProds = listaProdutos(catProds);
    fprintf(stderr,"Insere a Filial (0 - Global): ");
    if(fgets(filAux,64,stdin)){
        fil = atoi(filAux);
        while(lstProds[z][0]!='\0') {
            qtd=0;
            for (i=1;i<=12;i++){
                qtd += qtdProdMesTipo(catFat,strToProduto(lstProds[z]),i,'P',fil);
                qtd += qtdProdMesTipo(catFat,strToProduto(lstProds[z]),i,'N',fil);
            }
            if (qtd==0){
                lstProdNC[y] = (char *) calloc(strlen(lstProds[z]), sizeof(char));
                strcpy(lstProdNC[y++], lstProds[z]);
                lstProdNC = (char **) realloc (lstProdNC,(y+1)*sizeof(char *));
                lstProdNC[y] = (char *) calloc(1, sizeof(char));
            }
            z++;
        }
        i=0;
        z=0;
        while (lstProdNC[i][0]!='\0' && sw!=1) {
            if (z==120) {
                fprintf(stderr,"---------------------Enter para Apresentar Mais-------------------%d/%d",i/120,(y/120)+((y%120)/(y%120)));
                fgets (letter,3,stdin);
                if (letter[0]=='\n' || letter[0]=='\r') {i--;z=0;}
                else {sw=1;/*trigger=0;*/}
            }
            else {
                fprintf(stderr, "  |  %s",lstProdNC[i]);
                if ((i%6)==5) fprintf(stderr, "  |\n");
                z++;
            }
            i++;
        }
        fprintf(stderr,"\n-------------------Enter para Menu Anterior------------------");
        if(fgets(letter,3,stdin)) return;
    }
}


/*-----------------------------QUERY 3---------------------------------*/
void apresentaVendasProdMes(CatFaturacao cft) {
    int mes, qtdN=0, qtdP=0,qtdVN=0, qtdVP=0, fil=0;
    double fatN, fatP;
    char produtoAux[maxbufferPC], mesAux[3], filAux[maxbufferPC];
    Produto produto;
    fprintf(stderr,"Insira a Filial (0 - Global): ");
    if (fgets(filAux,3,stdin)) {
        fil = atoi(filAux);
        fprintf(stderr,"Insira o Produto: ");
        if (fgets(produtoAux,64,stdin)) {
            produto = strToProduto(strtok(produtoAux,"\n\r"));
            fprintf(stderr,"Insira mês: ");
            if (fgets(mesAux,3,stdin)) {
                mes = atoi(mesAux);
                qtdVP = qtdVenProdMesTipo(cft,produto,mes,'P',fil);
                qtdVN = qtdVenProdMesTipo(cft,produto,mes,'N',fil);
                qtdP = qtdProdMesTipo(cft,produto,mes,'P',fil);
                qtdN = qtdProdMesTipo(cft,produto,mes,'N',fil);
                fatP = fatProdMesTipo(cft,produto,mes,'P',fil);
                fatN = fatProdMesTipo(cft,produto,mes,'N',fil);
                if(qtdP==0 && qtdN==0)
                    fprintf(stderr,"-----O Produto Não Foi Comprado-----");
                else {
                    fprintf(stderr,"----------------------------------\n");
                    fprintf(stderr,"          Produto %s\n",produtoAux);
                    fprintf(stderr,"----------------------------------\n");
                    fprintf(stderr,"              Mês %d\n",mes);
                    fprintf(stderr,"----------------------------------\n");
                    if(fil==0) fprintf(stderr,"              Global\n");
                    else fprintf(stderr,"             Filial %d\n",fil);
                    if(qtdP!=0) {
                        fprintf(stderr,"----------------------------------\n");
                        fprintf(stderr,"              Tipo P\n");
                        fprintf(stderr,"Quantidade de Vendas: %d\n",qtdVP);
                        fprintf(stderr,"Quantidade de Produtos: %d\n",qtdP);
                        fprintf(stderr,"Faturação: %.2f\n",fatP);
                        fprintf(stderr,"-----Enter para Menu Anterior-----");
                    }
                    if(qtdN!=0) {
                        fprintf(stderr,"----------------------------------\n");
                        fprintf(stderr,"              Tipo N\n");
                        fprintf(stderr,"Quantidade de Vendas: %d\n",qtdVN);
                        fprintf(stderr,"Quantidade de Produtos: %d\n",qtdN);
                        fprintf(stderr,"Faturação: %.2f\n",fatN);
                        fprintf(stderr,"-----Enter para Menu Anterior-----");
                    }
                }
            }
        }
    }
    if (fgets (mesAux,3,stdin)) return;
}


/*-----------------------------QUERY 2---------------------------------*/
void apresentaProdutos (CatProds cps) {
    int i=0, z=0, trigger=-1,total = 0,sw=0;
    char tr[3], letter[3];
    char **lstProdutos = NULL;
    fprintf(stderr,"----------------------------MENU  PRODUTOS----------------------------\n");
    fprintf(stderr,"1-Apresentar por Letra\n2-Apresentar todos\n0-Menu Principal\nInput: ");
    if (fgets(tr,3,stdin)){
        trigger = atoi(tr);
        if (trigger == 1) {
            fprintf(stderr, "Insira a Letra: ");
            if(fgets(letter,3,stdin)){
                total = totalProdutosLetra(cps,letter[0]);
                lstProdutos = listaProLetra(cps,letter[0]);
            }
        }
        else if (trigger == 2) {
            total = totalProdutos(cps);
            lstProdutos = listaProdutos(cps);
        }
        else if (trigger!=0)
            fprintf(stderr,"%d - Input não definido.\n",trigger);
        
        if (trigger==1 || trigger==2) {
            while(lstProdutos[i][0]!='\0' && sw!=1){
                if (z==120) {
                    fprintf(stderr,"---------------------Enter para Apresentar Mais-------------------%d/%d",i/120,(total/120)+((total%120)/(total%120)));
                    fgets (letter,3,stdin);
                    if (letter[0]=='\n' || letter[0]=='\r') {i--;z=0;}
                    else {sw=1;trigger=0;}
                }
                else {
                    fprintf(stderr, "  |  %s",lstProdutos[i]);
                    if ((i%6)==5) fprintf(stderr, "  |\n");
                    z++;
                }
                i++;
            }
            fprintf(stderr,"\nTotal de produtos: %d\n",total);
        }
    }
    fprintf(stderr,"\n-------------------Enter para Menu Anterior------------------");
    if (fgets (letter,3,stdin)) return;
}

/*-----------------------------INTERPRETADOR-------------------------------*/
int interpretador (CatClientes ccs, CatProds cps, CatFiliais cfs[], int qtF, CatFaturacao cft) {
    int trigger=0;
    char tr[4];
    do {
        fprintf(stderr,"--------------------------------MENU----------------------------------\n");
        fprintf(stderr,"1 -Apresentar Produtos(Letra/Todos)\n2 -Vendas de um Produto num mês\n3 -Produtos Não Comprados\n4 -Total de Produtos Comprados Pelo Cliente\n5 -Faturação entre Meses\n6 -Clientes que Compraram em Todas as Filiais\n7 -Clientes que Compraram certo Produto numa Filial\n8 -Lista de Produtos Mais Comprados por Cliente num Mês\n9 -Lista de 'N' Produtos Mais Vendidos\n10-Lista de 3 Produtos Mais Comprados por Cliente\n11-Clientes/Produtos que Não Realizaram Compras\n12-Info\n13-Reintroduzir Dados\n0 -Sair\nInput: ");
        if (fgets(tr,4,stdin)) {
            trigger = atoi(tr);
            /*QUERY 2*/
            if (trigger == 1) apresentaProdutos(cps);
            /*QUERY 3*/
            else if (trigger == 2) apresentaVendasProdMes(cft);
            /*QUERY 4*/
            else if (trigger == 3) apresentaProdutosNC(cps,cft);
            /*QUERY 5*/
            else if (trigger == 4) apresentaNmrPComC(cfs,qtF);
            /*QUERY 6*/
            else if (trigger == 5) apresentaFaturacaoEntreMeses(cft,qtF);
            /*QUERY 7*/
            else if (trigger == 6) apresentaCliCompraTodasFiliais(ccs,cfs,qtF);
            /*QUERY 8*/
            else if (trigger == 7) apresentaClientesComPF(cfs);
            /*QUERY 9*/
            else if (trigger == 8) ;
            /*QUERY 10*/
            else if (trigger == 9) ;
            /*QUERY 11*/
            else if (trigger == 10) ;
            /*QUERY 12*/
            else if (trigger == 11) nrProdClientesNUsados(cfs,cps,ccs,qtF);
            /*QUERY 1*/
            else if (trigger == 12) /*info(stack)*/;
            /*QUERY 1.3*/
            else if (trigger == 13) return free_ALL(ccs,cps,cfs,cft,qtF);
            else if (trigger == 0)  fprintf(stderr,"FIM!\n");
            else fprintf(stderr,"Input não definido.\n");
        }
    } while (trigger!=0);
    
    return 0;
}

/*-----------------------------MAIN-------------------------------*/
int main () {
	char *sC, *sP, *sF, *sAux;
    int i, qtF;
    CatClientes catClientes;
    CatProds catProds;
    CatFiliais catFiliais[3];
    CatFaturacao catFat;
    do{
        freopen(NULL, "rb", stdin);
        i=0;
        qtF = 3;
        sC = (char *) calloc(maxbufferPC, sizeof(char));
        sP = (char *) calloc(maxbufferPC, sizeof(char));
        sF= (char *) calloc(maxbufferV, sizeof(char));
        sAux= (char *) calloc(maxbufferV, sizeof(char));
        catClientes = initCatClientes();
        catProds = initCatProds();
        catFat = initCatFaturacao(qtF);
        for (i=0;i<qtF;i++)
            catFiliais[i] = initCatFiliais();
        fprintf(stderr,"Insira o Caminho do Ficheiro de Clientes (0 para default): ");
        if (fgets(sAux,maxbufferPC,stdin)) {
            strcpy(sC,strtok(sAux,"\r\n"));
            if (strcmp(sC,"0")==0)
                strcpy(sC,"Clientes.txt");
            catClientes = lerClientes(catClientes,sC);
        }

        fprintf(stderr,"Insira o Caminho do Ficheiro de Produtos (0 para default): ");
        if (fgets(sAux,maxbufferPC,stdin)) {
            strcpy(sP,strtok(sAux,"\r\n"));
            if (strcmp(sP,"0")==0)
                strcpy(sP,"Produtos.txt");
            catProds = lerProds(catProds,sP);
        }

        fprintf(stderr,"Insira o Caminho do Ficheiro de Vendas (0 para default): ");
        if (fgets(sAux,maxbufferV,stdin)) {
            strcpy(sF,strtok(sAux,"\r\n"));
            if (strcmp(sF,"0")==0)
                strcpy(sF,"Vendas_1M.txt");
            for (i=0;i<qtF;i++)
                catFiliais[i] = lerVendas(sF,catFiliais[i],catProds,catClientes, i+1);
        }
        catFat = organizaFat (catFat,juntaFiliais(catFiliais, qtF),listaProdutos(catProds),totalProdutos(catProds));
        i = interpretador(catClientes,catProds,catFiliais,qtF,catFat);
        if (i==1) {
            free(sAux);
            free(sC);
            free(sP);
            free(sF);
            scanf("%*[^\n]%*[\n]");
        }
    }while(i==1);
	return 0;
}


