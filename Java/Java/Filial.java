import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.List;
import java.util.Collections;
import java.io.Serializable;
public class Filial implements Serializable
{
    private int filial;
    private List<Map<Cliente,List<Venda>>> catVendas;
    /**
     * Construtor da Filial vazio
     */
    public Filial() {
        this.filial=-1;
        this.catVendas = new ArrayList<>();
        for (int i=0;i<12;i++){
            this.catVendas.add(new TreeMap<>(new ClienteComparator()));
        }
    }
    /**
     * Construtor da Filial a parte de outra Filial
     * @param   f   Filial já existente
     */
    public Filial(Filial f) {
        this.filial = f.filial;
        List<Venda> lstV =  f.getVendas();
        this.catVendas = new ArrayList<>();
        for (int i=0;i<12;i++){
            this.catVendas.add(new TreeMap<>(new ClienteComparator()));
        }
        for (Venda v : lstV){
            int mes = v.getMes();
            Cliente c = v.getCliente();
            if(this.catVendas.get(mes-1).containsKey(c)){this.catVendas.get(mes-1).get(c).add(v);}
            else {
                ArrayList<Venda> aux = new ArrayList<>();
                aux.add(v);
                this.catVendas.get(mes-1).put(c,aux);
            }
        }
    }
    /**
     * Construtor da Filial a parte de uma Lista de Vendas e a identificação da filial
     * @param   catVendas   Lista de Vendas já existente
     * @param   fil     Identificação da filial
     */
    public Filial(List<Venda> catVendas, int fil) {
        this.filial = fil;
        this.catVendas = new ArrayList<>();
        for (int i=0;i<12;i++){
            this.catVendas.add(new TreeMap<>(new ClienteComparator()));
        }
        for (Venda v : catVendas){
            if (v.getFilial()==fil){
                int mes = v.getMes();
                Cliente c = v.getCliente();
                if(this.catVendas.get(mes-1).containsKey(c)){this.catVendas.get(mes-1).get(c).add(v);}
                else {
                    ArrayList<Venda> aux = new ArrayList<>();
                    aux.add(v);
                    this.catVendas.get(mes-1).put(c,aux);
                }
            }
        }
    }
    /**
     * Devolve uma lista de Vendas
     * @return  ret     Lista de Vendas da Filial
     */
    public List<Venda> getVendas () {
        ArrayList<Venda> ret = new ArrayList<>();
        for (Map<Cliente,List<Venda>> map : catVendas)
            for (List<Venda> lstV : map.values())
                ret.addAll(lstV);
        return ret;
    }
    /**
     * Insere uma Lista de Vendas na Class Filial
     * @param   fat     Lista de Vendas já existente
     */
    public void setFaturacao (List<Venda> fat) {
        this.catVendas = new ArrayList<>();
        for (int i=0;i<12;i++){
            this.catVendas.add(new TreeMap<>(new ClienteComparator()));
        }
        for (Venda v : fat){
            int mes = v.getMes();
            Cliente c = v.getCliente();
            if(this.catVendas.get(mes-1).containsKey(c)){this.catVendas.get(mes-1).get(c).add(v);}
            else {
                ArrayList<Venda> aux = new ArrayList<>();
                aux.add(v);
                this.catVendas.get(mes-1).put(c,aux);
            }
        }
    }
    /**
     * Transforma uma Lista de Vendas numa Lista de Filiais
     * @param   lstV    Lista de Vendas já existente
     * @return  ret     Lista de Vendas transformada para Lista de Filiais
     */
    public static List<Filial> fromArrVendaToListFil (List<Venda> lstV) {
        TreeMap<Integer,Filial> map = new TreeMap<>();
        int x=0;
        for (Venda v : lstV){
            int z = v.getFilial();
            if (map.containsKey(z)) map.get(z).addVenda(v);
            else {
                Filial f = new Filial();
                f.filial=z;
                map.put(z,f);
            }
        }
        ArrayList<Filial> ret = new ArrayList<>();
        ret.addAll(map.values());
        return ret;
    }
    private void addVenda (Venda v) {
        Cliente c = v.getCliente();
        if (this.catVendas.get(v.getMes()-1).containsKey(c)) this.catVendas.get(v.getMes()-1).get(c).add(v);
        else {
            ArrayList<Venda> aux = new ArrayList<>();
            aux.add(v);
            this.catVendas.get(v.getMes()-1).put(c,aux);
        }
    }
    
    /**
     * Devolve o numero de Vendas efectuadas num dado mês (Query 2)
     * @param   mes     Mês a consultar
     * @return  total   Total de vendas efectuadas
     */
    public int getNmrVendasMes (int mes) {
        int total = 0;
        for (List<Venda> lstV : catVendas.get(mes-1).values())
            total += lstV.size();
        return total;
    }
    /**
     * Devolve a Lista de Clientes que efectuaram compra num dado mês (Query 2)
     * @param   mes     Mês a consultar
     * @return  lstCli  Lista de Clientes com compras
     */
    public List<Cliente> clienteComMes (int mes) {
        List<Cliente> lstCli = new ArrayList<>();
        lstCli.addAll(catVendas.get(mes-1).keySet());
        return lstCli;
    }
    /**
     * Devolve as compras efectuadas por certo Cliente (Query 3)
     * @param   cli     Cliente a analisar
     * @param   mes     Mês a consultar
     * @return  mapVenda    Map de Mes e Vendas onde são guardadas as vendas de um determinado cliente, todos os meses
     */
    public List<Venda> vendasdoCliMes (Cliente cli,int mes) {
        return this.catVendas.get(mes-1).get(cli);
    }
    public Map<Produto,Integer> prodQtddoCli(Cliente cli) {
        Map<Produto,Integer> ret = new TreeMap<>(new ProdutoComparator());
        List<Venda> lstV = new ArrayList<>();
        for (Map<Cliente,List<Venda>> map : catVendas)
            if (map.get(cli)!=null) 
                lstV.addAll(map.get(cli));
        for(Venda v : lstV)
            ret.put(v.getProduto(),v.getQtd());
        return ret;
    }
    
}
