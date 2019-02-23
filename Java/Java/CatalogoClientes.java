import java.util.Set;
import java.util.TreeSet;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;
public class CatalogoClientes implements Serializable
{
    private Set<Cliente> catClientes;
    /**
     * Construtor do Catalogo de Clientes vazio
     */
    public CatalogoClientes () {
        this.catClientes = new TreeSet<Cliente>(new ClienteComparator());
    }
    /**
     * Construtor do Catalogo de Clientes a partir de outro Catalogo de Clientes
     * @param   c   Catalogo de Clientes já existente
     */
    public CatalogoClientes (CatalogoClientes c) {
        this.catClientes = c.getCatClientes();
    }
    /**
     * Construtor do Catalogo de Clientes(organizado) a partir de uma lista de Clientes
     * @param   catClientes Lista de Clientes já existente
     */
    public CatalogoClientes (List<Cliente> catClientes){
        this.catClientes = new TreeSet<Cliente>(new ClienteComparator());
        this.catClientes.addAll(catClientes);
    }
    /**
     * Devolve o Catalogo de Clientes
     * @return catClientes  Set de Clientes da Class CatalogoClientes
     */
    public Set<Cliente> getCatClientes() {return catClientes;}
    /**
     * Insere um Catalogo de Clientes na Class CatalogoClientes
     * @param   catClientes Set de clientes já existente
     */
    public void setCatClientes(Set<Cliente> catClientes) {this.catClientes=catClientes;}
    /**
     * Verifica se existe determinado cliente dentro do Catalogo
     * @param   cli Cliente a analizar
     */
    public boolean contains (Cliente cli) {return catClientes.contains(cli);}
}
