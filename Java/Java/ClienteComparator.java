import java.util.Comparator;
import java.io.Serializable;
public class ClienteComparator implements Comparator<Cliente>, Serializable
{
    /**
     * Comparador de Clientes (alfabeticamente)
     * @param   c1  Primeiro Cliente a comparar
     * @param   c2  Segundo Cliente a comparar 
     */
    public int compare(Cliente c1,Cliente c2){
        return c1.getCliente().compareTo(c2.getCliente());
    }
}
