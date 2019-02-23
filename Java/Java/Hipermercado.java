import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Collections;
import java.io.IOException;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
/**
 * Hipermercado
 *
 * "Hipermercado" é um programa, cujo principal objectivo é "Gestão das Vendas de uma Cadeia de Distribuição com 3 Filiais"
 * Nesta versão são gerados dois catálogos, o de produtos e o de clientes, assim como os controladores responsaveis pela gestão do Programa.
 *
 *@author Alexandre Teixeira -- a73547
 *@author Bruno Sousa -- a74330
 *@author Rafael Silva -- a74264
 *
 */
public class Hipermercado
{
    private CatalogoClientes catalogoClientes;
    private CatalogoProdutos catalogoProdutos;
    private Faturacao faturacao;
    private List<Filial> filiais;
    /**
     * Construtor Hipermercado vazio.
     */
    public Hipermercado() {
        this.catalogoClientes = new CatalogoClientes();
        this.catalogoProdutos = new CatalogoProdutos();
        this.faturacao = new Faturacao();
    }
    /**
     * Construtor Hipermercado a partir de outro Hipermercado
     * @param   h   Hipermercado já existente
     */
    public Hipermercado(Hipermercado h) {
        this.catalogoClientes = h.getCatalogoClientes();
        this.catalogoProdutos = h.getcatalogoProdutos();
        this.faturacao = h.getFaturacao();
        this.filiais = h.getFiliais();
    }
    /**
     * Construtor Hipermercado a partir dos seus catalogos, faturações e filiais.
     * @param   catalogoClientes Catalogo de Clientes já existente
     * @param   catalogoProdutos Catalogo de Clientes já existente
     * @param   faturacao Faturação já existente
     * @param   filiais Lista de filiais já existente
     */
    public Hipermercado(CatalogoClientes catalogoClientes, CatalogoProdutos catalogoProdutos, Faturacao faturacao,List<Filial> filiais) {
        this.catalogoClientes=catalogoClientes;
        this.catalogoProdutos=catalogoProdutos;
        this.faturacao = faturacao;
        this.filiais = filiais;
    }
    /**
     * Devolve o Catalogo de Clientes
     * @return  catalogoClientes    Catalogo de Clientes da Class Hipermercado
     */
    public CatalogoClientes getCatalogoClientes () {return catalogoClientes;}
    /**
     * Devolve o Catalogo de Produtos
     * @return  catalogoProdutos    Catalogo de Produtos da Class Hipermercado
     */
    public CatalogoProdutos getcatalogoProdutos () {return catalogoProdutos;}
    /**
     * Devolve a Faturação
     * @return  faturacao   Faturação da Class Hipermercado
     */
    public Faturacao getFaturacao () {return faturacao;}
    /**
     * Devolve a Lista de Filiais
     * @return  filiais    Lista de Filiais da Class Hipermercado
     */
    public List<Filial> getFiliais () {return filiais;}
    /**
     * Insere um Catalogo de Clientes na Class Hipermercado
     * @param  catalogoClientes    Catalogo de Clientes já existente
     */
    public void setCatalogoClientes (CatalogoClientes catalogoClientes) {this.catalogoClientes=catalogoClientes;}
    /**
     * Insere um Catalogo de Produtos na Class Hipermercado
     * @param  catalogoProdutos    Catalogo de Produtos já existente
     */
    public void setcatalogoProdutos (CatalogoProdutos catalogoProdutos) {this.catalogoProdutos=catalogoProdutos;}
    /**
     * Insere uma Faturação na Class Hipermercado
     * @param  faturacao    Faturação já existente
     */
    public void setFaturacao (Faturacao faturacao) {this.faturacao=faturacao;}
    /**
     * Insere uma Lista de Filiais na Class Hipermercado
     * @param  filiais    Lista de Filiais já existente
     */
    public void setFiliais (List<Filial> filiais) {this.filiais=filiais;}
    /**
     * Guarda o estado da Aplicação (.dat)
     * @param   nomeFicheiro    Nome do Ficheiro a ser guardado
     */
    public void saveState (String nomeFicheiro) throws IOException{
        FileOutputStream file = new FileOutputStream(nomeFicheiro+".dat");
        ObjectOutputStream oss = new ObjectOutputStream(file);
        oss.writeObject(this);
        oss.flush();
        oss.close();
    }
    /**
     * Abre um estado da Aplicação (.dat)
     * @param   nomeFicheiro    Nome do Ficheiro a ser lido
     * @return  hiper   Hipermercado onde é guardado o estado lido
     */
    public static Hipermercado loadState(String nomeFicheiro) throws IOException, ClassNotFoundException{
        FileInputStream file = new FileInputStream(nomeFicheiro+".dat");
        ObjectInputStream ois = new ObjectInputStream(file);
        Hipermercado hiper = (Hipermercado) ois.readObject();
        ois.close();
        return hiper;
    }
    /**
     * Devolve uma lista de Produtos Nunca Comprados (Query 1)
     * @return  lstP    Lista de Produtos Nunca Comprados
     */
    public List<Produto> prodsNC () {
        List<Produto> lstP = catalogoProdutos.prodsNC(faturacao.getFaturacao());
        return lstP;
    }
    /**
     * Devolve o numero de Vendas efectuadas num dado mês (Query 2)
     * @param mes Mês a consultar
     * @return total Total de vendas efectuadas
     */
    public int nmrVendasMes (int mes) {
        int total=0;
        for (Filial f : filiais)
            total += f.getNmrVendasMes(mes);
        return total;
    }
    /**
     * Devolve a Lista de Clientes que efectuaram compra num dado mês (Query 2)
     * @param mes Mês a consultar
     * @return lstCli Lista de Clientes com compras
     */
    public List<Cliente> clienteComMes (int mes) {
        List<Cliente> lstCli = new ArrayList<>();
        for (Filial f : filiais)
            lstCli.addAll(f.clienteComMes(mes));
        Collections.sort(lstCli, new ClienteComparator());
        return lstCli;
    } 
    /**
     * Devolve as compras efectuadas por certo Cliente (Query 3)
     * @param cli Cliente a analisar
     * @return mapVenda Map de Mes e Vendas onde são guardadas as vendas de um determinado cliente, todos os meses
     */
    public Map<Integer,List<Venda>> vendasCliente (Cliente cli) {
        Map<Integer,List<Venda>> mapVenda = new TreeMap<>();
        for (int i=1;i<=12;i++) {
            List<Venda> lstV = new ArrayList<>();
            mapVenda.put(i,lstV);
            for (Filial f : filiais){
                List<Venda> aux = f.vendasdoCliMes(cli,i);
                if (aux!=null)
                    mapVenda.get(i).addAll(aux);
            }
        }
        return mapVenda;
    }
    /**
     * Devolve as compras efectuadas a certo Produto (Query 4)
     * @param prod Produto a analisar
     * @return mapVenda Map< Mes,Vendas > onde são guardadas as vendas de um determinado produto, todos os meses
     */
    public Map<Integer,List<Venda>> vendasProduto (Produto prod) {
        return faturacao.vendasProduto(prod);
    }
    
    public Map<Produto,Integer> prodQtddoCli (Cliente cli) {
        Map<Produto,Integer> lstPQ = new TreeMap<>(new ProdutoComparator());
        for (Filial f : filiais){
            Map<Produto,Integer> map = f.prodQtddoCli(cli);
            Iterator prod = map.keySet().iterator();
            Iterator qtd = map.values().iterator();
            while(prod.hasNext()) {
                Produto p = (Produto) prod.next();
                int qt = (int) qtd.next();
                if (lstPQ.containsKey(p)) {
                    int x = lstPQ.get(p) + qt;
                    lstPQ.put(p,x);
                }
                else lstPQ.put(p,qt);
            }
        }
        return lstPQ;
    }
    
    public Map<Produto,Set<Cliente>> prodsMaisVendEClis (int x){
        return faturacao.prodsMaisVendEClis(x);
    }
    
    public double[] getFaturadoPMes (){
        return faturacao.getFaturadoPMes();
    }
}

