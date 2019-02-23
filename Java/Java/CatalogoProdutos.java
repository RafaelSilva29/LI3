import java.util.Set;
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeMap;
import java.io.Serializable;
public class CatalogoProdutos implements Serializable
{
    private Set<Produto> catProds;
    /**
     * Construtor do Catalogo de Produtos vazio
     */
    public CatalogoProdutos() {
        this.catProds = new TreeSet<Produto>(new ProdutoComparator());
    }
    /**
     * Construtor do Catalogo de Produtos a partir de outro Catalogo de Produtos
     * @param   c   Catalogo de Produtos já existente
     */
    public CatalogoProdutos (CatalogoProdutos c) {
        this.catProds = c.getCatProds();
    }
    /**
     * Construtor do Catalogo de Produtos(organizado) a partir de uma lista de Produtos
     * @param   catProds    Lista de Produtos já existente
     */
    public CatalogoProdutos (List<Produto> catProds){
        this.catProds = new TreeSet<Produto>(new ProdutoComparator());
        this.catProds.addAll(catProds);
    }
    /**
     * Devolve o Catalogo de Produtos
     * @return catProds Set de Produtos da Class CatalogoProdutos
     */
    public Set<Produto> getCatProds() {return catProds;}
    /**
     * Insere um Catalogo de Produtos na Class CatalogoProdutos
     * @param   catProds    Set de Produtos já existente
     */
    public void setCatProds(Set<Produto> catProds) {this.catProds=catProds;}
    /**
     * Verifica se existe determinado Produto dentro do Catalogo
     * @param   prod    Produto a analizar
     */
    public boolean contains (Produto prod) {return catProds.contains(prod);}
    
    /**
     * Devolve uma lista de Produtos Nunca Comprados (Query 1)
     * @param   vendas  Losta de vendas a analisar
     * @return  ret    Lista de Produtos Nunca Comprados
     */
    public List<Produto> prodsNC (List<Venda> vendas) {
        TreeMap<Produto,Integer> aux = new TreeMap<>(new ProdutoComparator());
        for (Produto p : catProds)
            aux.put(p,0);
        for (Venda v : vendas) {
            int x = aux.get(v.getProduto());
            x += v.getQtd();
            aux.put(v.getProduto(),x);
        }
        ArrayList<Produto> ret = new ArrayList<>();
        for (Produto p : aux.keySet())
            if (aux.get(p)==0) ret.add(p.clone());
        return ret;
    }
}
