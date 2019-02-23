import java.util.Map;
import java.util.HashMap;
import java.util.HashSet;
import java.util.TreeSet;
import java.util.Set;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
public class Faturacao
{
    private Map<Integer,Map<Produto,List<Venda>>> faturacao;
    /**
     * Construtor da Faturacao vazio
     */
    public Faturacao() {
        this.faturacao = new TreeMap<Integer,Map<Produto,List<Venda>>>();
    }
    /**
     * Construtor da Faturacao a parte de outra Faturacao
     * @param   fat Faturacao já existente
     */
    public Faturacao(Faturacao fat) {
        List<Venda> lstV = fat.getFaturacao();
        this.faturacao = new TreeMap<Integer,Map<Produto,List<Venda>>>();
        for (Venda v : lstV) {
            int z = v.getFilial();
            Produto p = v.getProduto();
            if (faturacao.containsKey(z)) {
                if(faturacao.get(z).containsKey(p)) this.faturacao.get(z).get(p).add(v);
                else {
                    ArrayList<Venda> aux = new ArrayList<>();
                    aux.add(v);
                    this.faturacao.get(z).put(p,aux);
                }
            }
            else {
                ArrayList<Venda> aux1 = new ArrayList<>();
                aux1.add(v);
                TreeMap<Produto,List<Venda>> aux2 = new TreeMap<>(new ProdutoComparator());
                aux2.put(p,aux1);
                this.faturacao.put(z,aux2);
            }
        }
    }
    /**
     * Construtor da Faturacao a parte de uma Lista de Vendas
     * @param   catVendas   Lista de Vendas já existente
     */
    public Faturacao(List<Venda> catVendas) {
        this.faturacao = new TreeMap<Integer,Map<Produto,List<Venda>>>();
        for (Venda v : catVendas) {
            int z = v.getFilial();
            Produto p = v.getProduto();
            if (faturacao.containsKey(z)) {
                if(faturacao.get(z).containsKey(p)) this.faturacao.get(z).get(p).add(v);
                else {
                    ArrayList<Venda> aux = new ArrayList<>();
                    aux.add(v);
                    this.faturacao.get(z).put(p,aux);
                }
            }
            else {
                ArrayList<Venda> aux1 = new ArrayList<>();
                aux1.add(v);
                TreeMap<Produto,List<Venda>> aux2 = new TreeMap<>(new ProdutoComparator());
                aux2.put(p,aux1);
                this.faturacao.put(z,aux2);
            }
        }
    }
    /**
     * Devolve uma lista de Vendas
     * @return  aux Lista de Vendas da Class Faturacao
     */
    public List<Venda> getFaturacao() {
        ArrayList<Venda> aux = new ArrayList<>();
        for (Map<Produto,List<Venda>> map : faturacao.values())
            for (List<Venda> lstV : map.values())
                aux.addAll(lstV);
        return aux;
    }
    /**
     * Insere uma Lista de Vendas na Class Faturacao
     * @param   fat     Lista de Vendas já existente
     */
    public void setFaturacao (List<Venda> fat) {
        this.faturacao = new TreeMap<Integer,Map<Produto,List<Venda>>>();
        for (Venda v : fat) {
            int z = v.getFilial();
            Produto p = v.getProduto();
            if (faturacao.containsKey(z)) {
                if(faturacao.get(z).containsKey(p)) this.faturacao.get(z).get(p).add(v);
                else {
                    ArrayList<Venda> aux = new ArrayList<>();
                    aux.add(v);
                    this.faturacao.get(z).put(p,aux);
                }
            }
            else {
                ArrayList<Venda> aux1 = new ArrayList<>();
                aux1.add(v);
                TreeMap<Produto,List<Venda>> aux2 = new TreeMap<>(new ProdutoComparator());
                aux2.put(p,aux1);
                this.faturacao.put(z,aux2);
            }
        }
    }
    
    /**
     * Devolve as compras efectuadas a certo Produto (Query 4)
     * @param   prod    Produto a analisar
     * @return  mapVenda    Map de Mes e Vendas onde são guardadas as vendas de um determinado produto, todos os meses
     */
    public Map<Integer,List<Venda>> vendasProduto (Produto prod) {
        Map<Integer,List<Venda>> mapRet = new TreeMap<>();
        int i;
        for (i=1;i<=12;i++){
            List<Venda> lstV = new ArrayList<>();
            mapRet.put(i,lstV);
        }
        for(Map<Produto,List<Venda>> mapFat: faturacao.values()){
            List<Venda> aux = mapFat.get(prod);
            if (aux!=null) {
                for (Venda v : aux)
                    mapRet.get(v.getMes()).add(v);
            }
        }
        return mapRet;
    }
    
    public double[] getFaturadoPMes (){
        double[] fat = new double[12];
        for (int i=0;i<12;i++)
            fat[i] = 0;
        for(Map<Produto,List<Venda>> map : faturacao.values())
            for (List<Venda> lstV : map.values())
                for (Venda v : lstV)
                    fat[v.getMes()-1] += v.getQtd()*v.getPreco();
        return fat;
    }
    
    public Map<Produto,Set<Cliente>> prodsMaisVendEClis (int x){
        List<Venda> lstV = this.getFaturacao();
        Map<Produto,Integer> mapPI = new TreeMap<>(new ProdutoComparator());
        for(Venda v : lstV){
            Produto p = v.getProduto();
            int qt = v.getQtd();
            if (mapPI.containsKey(p)) mapPI.put(p,mapPI.get(p)+qt);
            else mapPI.put(p,qt);
        }
        
        /************/
        /**INDICE|Produto*/
        TreeMap<Integer,Produto> lstProd = new TreeMap<>();
        /**qtd|INDICE      qtds organizadas na insereção*/
        TreeMap<Integer,HashSet<Integer>> lstQtd = new TreeMap<>();
        int y=0;
        Iterator itP = mapPI.keySet().iterator(); 
        Iterator itQ = mapPI.values().iterator();
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
        HashSet<Produto> lstProdutos = new HashSet<>();
        for(int j:lstPos)
            lstProdutos.add(lstProd.get(j));
        /************/
        
        
        
        Map<Produto,Set<Cliente>> ret = new HashMap<>();
        for(Produto p : lstProdutos){
            TreeSet<Cliente> aux = new TreeSet<>(new ClienteComparator());
            ret.put(p,aux);
        }
        for(Venda v : lstV){
            Produto p = v.getProduto();
            if(ret.containsKey(p)) ret.get(p).add(v.getCliente());
        }
        return ret;
    }
}
