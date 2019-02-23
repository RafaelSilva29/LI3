import java.util.Comparator;
import java.io.Serializable;
public class ProdutoComparator implements Comparator<Produto>, Serializable
{
    /**
     * Comparador de Produto (alfabeticamente)
     * @param   c1  Primeiro Produto a comparar
     * @param   c2  Segundo Produto a comparar 
     */
    public int compare(Produto c1,Produto c2){
        return c1.getProduto().compareTo(c2.getProduto());
    }
}
