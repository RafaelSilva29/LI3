import static java.lang.System.out;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.HashSet;
import java.lang.Exception;
import java.util.stream.Collectors;
import java.io.Serializable;

public class Main implements Serializable
{
    /**
     * Função responsavel pela inicialização do programa.
     */
    public static void main (String[] args) {
        new Main();
    }
    
    public Main() {
         Hipermercado hiper = loadFilesTXT("Clientes.txt","Produtos.txt","Vendas_1M.txt");
          interpretador(hiper);
    }
    
    /**
     * Dado o nome dos ficheiros de leitura, esta devolve a class Hipermercado já incializada.
     * @param   clientes    Nome do ficheiro que contêm os Clientes
     * @param   produtos    Nome do ficheiro que contêm os Produtos
     * @param   vendas      Nome do ficheiro que contêm as Vendas
     * @return              Hipermercado inicializado com os ficheiros
     */
    private static Hipermercado loadFilesTXT (String clientes, String produtos, String vendas) {
        String ficheiroVendas;
        int vendasErradas, totalProds, ncProds, totalClie, vendasP0;
        /**Ler ficheiros para array*/
        ficheiroVendas = vendas;
        ArrayList<Cliente> clientesArr = readClientesWithBuff(clientes);
        totalClie = clientesArr.size();
        ArrayList<Produto> produtosArr = readProdutosWithBuff(produtos);
        totalProds = produtosArr.size();
        ArrayList<Venda> vendasArr = readVendasWithBuff(vendas);
        vendasErradas = vendasArr.size();
        /**Criar Catalogos Cli/Prods*/
        CatalogoClientes catCli = new CatalogoClientes(clientesArr);
        CatalogoProdutos catProds = new CatalogoProdutos(produtosArr);
        /**Vendas preço 0*/
        vendasP0 = (int) vendasArr.stream()
                                  .filter(v -> v.vendaPreco0())
                                  .count();
        /**Validar vendas*/
        vendasArr = (ArrayList<Venda>) vendasArr.stream()
                                                .filter(v -> v.vendaValida(catCli,catProds))
                                                .collect(Collectors.toList());
        vendasErradas -= vendasArr.size();
        /**Criar Faturacao*/
        Faturacao fat = new Faturacao(vendasArr);
        /**Criar Filiais*/
        List<Filial> lstFil = Filial.fromArrVendaToListFil(vendasArr);
        /**Criar Hipermercado*/
        Hipermercado hiper = new Hipermercado(catCli,catProds,fat,lstFil);
        /**Produtos nunca Comprados*/
        List<Produto> arrProdNC = hiper.prodsNC();
        ncProds = arrProdNC.size();
        /**Faturação*/
        
        /**Prints Queries estatisticas*/
        System.out.println("Ficheiro de Vendas: " + ficheiroVendas);
        System.out.println("Vendas Erradas: " + vendasErradas);
        System.out.println("Vendas a Preço: " + vendasP0);
        System.out.println("Total de Produtos: " + totalProds);
        System.out.println("Produtos nunca Comprados: " + ncProds);
        /**Hipermercado criado*/
        return hiper;
    }
    
    /**
     * Dado o nome do ficheiro de clientes, está guarda-os num ArrayList<Cliente>.
     * @param   fich    Nome do ficheiro que contêm os Clientes
     * @return          Lista com todos os clientes do ficheiro
     */
    public static ArrayList<Cliente> readClientesWithBuff(String fich){
        ArrayList<Cliente> ret = new ArrayList<>();
        BufferedReader inStream = null;
        String linha = null;
        try {
            inStream = new BufferedReader(new FileReader(fich));
            while( (linha = inStream.readLine()) != null ) {
                ret.add(new Cliente(linha.trim()));
            }
        } catch(IOException e) {
            out.println(e.getMessage()); return null;
        }
        return ret;  
    }
    
    /**
     * Dado o nome do ficheiro de clientes, está guarda-os num ArrayList<Produto>.
     * @param   fich    Nome do ficheiro que contêm os Produtos
     * @return          Lista com todos os produtos do ficheiro
     */
    public static ArrayList<Produto> readProdutosWithBuff(String fich){
        ArrayList<Produto> ret = new ArrayList<>();
        BufferedReader inStream = null;
        String linha = null;
        try {
            inStream = new BufferedReader(new FileReader(fich));
            while( (linha = inStream.readLine()) != null ) {
                ret.add(new Produto(linha.trim()));
            }
        } catch(IOException e) {
            out.println(e.getMessage()); return null;
        }
        return ret;  
    }
    
    /**
     * Dado o nome do ficheiro de clientes, está guarda-os num ArrayList<Venda>.
     * @param   fich    Nome do ficheiro que contêm os Vendas
     * @return          Lista com todos os vendas do ficheiro
     */
    public static ArrayList<Venda> readVendasWithBuff(String fich){
        ArrayList<Venda> ret = new ArrayList<>();
        BufferedReader inStream = null;
        String linha = null;
        try {
            inStream = new BufferedReader(new FileReader(fich));
            while( (linha = inStream.readLine()) != null ) {
                String[] aux = linha.trim().split(" ");
                ret.add(new Venda(new Produto(aux[0]),
                                  Double.parseDouble(aux[1]),
                                  Integer.parseInt(aux[2]),
                                  aux[3].charAt(0),
                                  new Cliente(aux[4]),
                                  Integer.parseInt(aux[5]),
                                  Integer.parseInt(aux[6])));
            }
        } catch(IOException e) {
            out.println(e.getMessage()); return null;
        }
        return ret;  
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    private void interpretador(Hipermercado hiper) {
        int trigger = 0;
        do {
            System.out.println("--------------------------------MENU----------------------------------");
            System.out.println("1 - Produtos Nunca Comprados");
            System.out.println("2 - Vendas e Numero de Clientes num dado Mês");
            System.out.println("3 - Faturação de Cliente por Mês");
            System.out.println("4 - Faturação de Produto");
            System.out.println("5 - Produtos mais Comprados por Cliente");
            System.out.println("6 - 'N' Produtos mais vendidos");
            System.out.println("7 - Três maiores Compradores em cada Filial");
            System.out.println("8 - 'N' Clientes com mais Produtos Distintos");
            System.out.println("9 - 'N' Clientes que mais Compraram certo Produto");
            
            System.out.println("10- Carregar Estado da Aplicação");
            System.out.println("11- Guardar Estado da Aplicação");
            System.out.println("12- Info");
            System.out.println("13-Reintroduzir Dados");
            System.out.println("0 -Sair");
            System.out.print("Input: ");
            trigger = Input.lerInt();
            if (trigger == 1) prodsNC(hiper);
            
            else if (trigger == 2) vendasEClientesNumMes(hiper);
            
            else if (trigger == 3) vendasCliMes(hiper);
            
            else if (trigger == 4) vendasProdMes(hiper);
            
            else if (trigger == 5) prodQtddoCli(hiper);
            
            else if (trigger == 6) prodsMaisVendEClis(hiper);
            
            else if (trigger == 7) ;
            
            else if (trigger == 8) ;
            
            else if (trigger == 9) ;
            
            else if (trigger == 10) hiper = loadDatFile();
            
            else if (trigger == 11) saveDatFile(hiper);
            
            else if (trigger == 12) info(hiper);
            else if (trigger == 13) hiper = reloadData();
            else if (trigger == 0) System.out.println("Exit Program.");
            else System.out.println("Input não definido.\n");
        } while (trigger!=0);
    }
    
    private void prodsNC (Hipermercado hiper) {
        Crono.start();
        List<Produto> arrProdNC = hiper.prodsNC();
        System.out.println(arrProdNC.size()+" produtos nunca comprados");
        double timeF = Crono.stop();
        Iterator it = arrProdNC.iterator();
        int sw=0, z=0, i=0, total = arrProdNC.size();
        while(it.hasNext() && sw!=1){
            if (z==120) {
                System.out.println("   ---------------------Enter para Apresentar Mais-------------------"+i/120+"/"+((total/120)+((total%120)/(total%120))));
                String aux = Input.lerString().trim();
                if (aux.equals("")) {i--;z=0;}
                else {sw=1;}
            }
            else {
                System.out.print("  |  "+it.next());
                if ((i%6)==5) System.out.print("  |\n");
                z++;
            }
            i++;
        }
        if (sw==0) System.out.println("  |");
        Input.lerString();
        System.out.println("Tempo de execução: " + timeF+"s");
    }
    
    private void vendasEClientesNumMes(Hipermercado hiper) {
        System.out.print("Insira o mes: ");
        int mes = Input.lerInt();
        Crono.start();
        int nV = hiper.nmrVendasMes(mes);
        System.out.println(nV+" vendas no mês "+mes);
        List<Cliente> lstCli = hiper.clienteComMes(mes);
        double timeF = Crono.stop();
        Iterator it = lstCli.iterator();
        int sw=0, z=0, i=0, total = lstCli.size();
        while(it.hasNext() && sw!=1){
            if (z==120) {
                System.out.println("   ---------------------Enter para Apresentar Mais-------------------"+i/120+"/"+((total/120)+((total%120)/(total%120))));
                String aux = Input.lerString().trim();
                if (aux.equals("")) {i--;z=0;}
                else {sw=1;}
            }
            else {
                System.out.print("  |  "+it.next());
                if ((i%6)==5) System.out.print("  |\n");
                z++;
            }
            i++;
        }
        if (sw==0) System.out.println("  |");
        Input.lerString();
        System.out.println("Tempo de execução: " + timeF+"s");
    }
    
    private void vendasCliMes (Hipermercado hiper) {
        System.out.print("Insira o Cliente: ");
        Cliente c = new Cliente(Input.lerString().trim());
        Crono.start();
        Map<Integer,List<Venda>> mapVendas = hiper.vendasCliente(c);
        for (int i=1;i<=12;i++){
            double totalGasto=0;
            ArrayList<Produto> lstP = new ArrayList<>();
            if (mapVendas.get(i).size()!=0){
                System.out.println("Mes "+i+":");
                System.out.println(mapVendas.get(i).size()+" vendas");
                for (Venda v : mapVendas.get(i)){
                    lstP.add(v.getProduto());
                    totalGasto+=v.getPreco();
                }
                System.out.println(totalGasto+" gasto");
                Iterator it = lstP.iterator();
                int y=0;
                while(it.hasNext()){
                    System.out.print("  |  "+it.next());
                    if ((y%6)==5 || !it.hasNext()) System.out.print("  |\n");
                    y++;
                }
            }
        }
        double timeF = Crono.stop();
        Input.lerString();
        System.out.println("Tempo de execução: " + timeF+"s");
    }
    
    private void vendasProdMes (Hipermercado hiper) {
        System.out.print("Insira o Produto: ");
        Produto p = new Produto(Input.lerString().trim());
        Crono.start();
        Map<Integer,List<Venda>> mapVendas = hiper.vendasProduto(p);
        for (int i=1;i<=12;i++){
            int faturado = 0;
            int vComp = mapVendas.get(i).stream()
                                        .mapToInt(v -> v.getQtd())
                                        .sum();
            if (vComp!=0){
                ArrayList<Cliente> lstC = new ArrayList<>();
                System.out.println("Mes "+i+":");
                System.out.println(vComp+" compras");
                for (Venda v : mapVendas.get(i)){
                    lstC.add(v.getCliente());
                    faturado+=v.getPreco()*v.getQtd();
                }
                System.out.println(faturado+" faturado");
                Iterator it = lstC.iterator();
                int y=0;
                while(it.hasNext()){
                    System.out.print("  |  "+it.next());
                    if ((y%6)==5 || !it.hasNext()) System.out.print("  |\n");
                    y++;
                }
            }
        }
        double timeF = Crono.stop();
        Input.lerString();
        System.out.println("Tempo de execução: " + timeF+"s");
    }
    
    
    private void prodQtddoCli (Hipermercado hiper) {
        System.out.print("Insira o Cliente: ");
        Cliente c = new Cliente(Input.lerString().trim());
        TreeMap<Produto,Integer> lstPQ = (TreeMap<Produto,Integer>) hiper.prodQtddoCli(c);
        
        Crono.start();
        /**INDICE|Produto*/
        TreeMap<Integer,Produto> lstProd = new TreeMap<>();
        /**qtd|INDICE      qtds organizadas na insereção*/
        TreeMap<Integer,HashSet<Integer>> lstQtd = new TreeMap<>();
        int y=0;
        Iterator itP = lstPQ.keySet().iterator(); 
        Iterator itQ = lstPQ.values().iterator();
        while (itP.hasNext()){
            Produto p = (Produto) itP.next();
            int qt = (int) itQ.next();
            lstProd.put(y,p);
            if (lstQtd.containsKey(qt)) lstQtd.get(qt).add(y);
            else {
                HashSet<Integer> aux = new HashSet<>();
                aux.add(y);
                lstQtd.put(qt,aux);
            }
            y++;
        }
        
        /**Organizar as indices*/
        HashSet<Integer> lstPos = new HashSet<>();
        for(HashSet<Integer> l :lstQtd.values())
            for(int j : l)
                lstPos.add(j);
        
        /**Adcicionar produtos a um Set organizado pelos indices organizados anteriormente*/
        HashSet<Produto> ret = new HashSet<>();
        for(int j:lstPos)
            ret.add(lstProd.get(j));
        double timeF = Crono.stop();
            
        Iterator it = ret.iterator();
        int sw=0, z=0, i=0, total = ret.size();
        while(it.hasNext() && sw!=1){
            if (z==120) {
                System.out.println("   ---------------------Enter para Apresentar Mais-------------------"+i/120+"/"+((total/120)+((total%120)/(total%120))));
                String aux = Input.lerString().trim();
                if (aux.equals("")) {i--;z=0;}
                else {sw=1;}
            }
            else {
                System.out.print("  |  "+it.next());
                if ((i%6)==5 || !it.hasNext()) System.out.print("  |\n");
                z++;
            }
            i++;
        }
        Input.lerString();
        System.out.println("Tempo de execução: " + timeF);
    }
    
    /**Determinar o conjunto dos X produtos mais vendidos em todo o ano (em número de
     * unidades vendidas) indicando o número total de distintos clientes que o
     * compraram (X é um inteiro dado pelo utilizador);*/
    private void prodsMaisVendEClis (Hipermercado hiper) {
        System.out.print("Insira o numero de produtos: ");
        int x = Input.lerInt();
        Map<Produto,Set<Cliente>> map = hiper.prodsMaisVendEClis(x);
        Iterator itP = map.keySet().iterator();
        while(itP.hasNext() && x>0){
            Produto p = (Produto) itP.next();
            Iterator itC = map.get(p).iterator();
            System.out.print("-"+p+"  |  ");
            while(itC.hasNext()) {
                Cliente c = (Cliente) itC.next();
                System.out.print(c+"  |  ");
            }
            System.out.print("\n");
            x--;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    private Hipermercado loadDatFile() {
        System.out.print("Escreva nome do Ficheiro(0-default): ");
        String file = Input.lerString();
        Crono.start();
        if (file.equals("0")) file = "Hipermercado";
        try{
            Hipermercado hiper  = new Hipermercado();
            hiper.loadState(file);
            double timeF = Crono.stop();
            System.out.println("Tempo de execução: " + timeF+"s");
            return hiper;
        } catch (Exception e) {
            return null;
        }
    }
    
    private void saveDatFile (Hipermercado hiper) {
        System.out.print("Escreva nome do Ficheiro(0-default): ");
        String file = Input.lerString();
        Crono.start();
        if (file.equals("0")) file = "Hipermercado";
        try{
            hiper.saveState(file);
            double timeF = Crono.stop();
            System.out.println("Tempo de execução: " + timeF+"s");
        } catch (Exception e) {}
    }
    
    private void info(Hipermercado hiper) {
        int i;
        System.out.println("Vendas por Mês");
        for(i=1;i<=12;i++){
            System.out.println("Mes "+ i +": " + hiper.nmrVendasMes(i));
        }
        double[] fat = hiper.getFaturadoPMes();
        System.out.println("Faturado por Mês");
        for(i=0;i<12;i++) {
            System.out.println("Mes "+ (i+1) +": " + fat[i]);
        }
    }
    
    private Hipermercado reloadData () {
        System.out.print("Escreva nome do Ficheiro de Clientes(0-default): ");
        String fCli = Input.lerString();
        if (fCli.equals("0")) fCli = "Clientes.txt";
        System.out.print("Escreva nome do Ficheiro de Produtos(0-default): ");
        String fProd = Input.lerString();
        if (fProd.equals("0")) fProd = "Produtos.txt";
        System.out.print("Escreva nome do Ficheiro de Vendas(0-default): ");
        String fVenda = Input.lerString();
        if (fVenda.equals("0")) fVenda = "Vendas_1M.txt";
        Crono.start();
        Hipermercado hiper = loadFilesTXT(fCli,fProd,fVenda);
        double timeF = Crono.stop();
        System.out.println("Tempo de execução: " + timeF+"s");
        return hiper;
    }
}