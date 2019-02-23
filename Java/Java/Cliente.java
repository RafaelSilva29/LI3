public class Cliente {
    private String cliente;
    /**
     * Construtor de Cliente vazio
     */
    public Cliente () {
        this.cliente = "n/a";
    }
    /**
     * Construtor de Cliente a partir de uma string
     * @param   cliente     String com o nome do cliente
     */
    public Cliente (String cliente) {
        this.cliente = cliente;
    }
    /**
     * Construtor de Cliente a partir de outro Cliente
     * @param   c   Cliente já existente
     */
    public Cliente (Cliente c) {
        this.cliente = c.getCliente();
    }
    /**
     * Devolve o Nome do Cliente
     * @return  cliente String com o nome do Cliente
     */
    public String getCliente () {return cliente;}
    /**
     * Cria uma copia do Cliente
     */
    public Cliente clone () {return new Cliente(this);}
    /**
     * Compara clientes
     */
    public boolean equals (Object o) {
        if (this==o) 
            return true;
        else if (o==null || !o.getClass().equals(this.getClass()))
            return false;
        else {
            Cliente v = (Cliente) o;
            return (v.getCliente().equals(this.cliente));
        }
    }
    /**
     * Transforma um cliente numa string
     */
    public String toString () {
        StringBuilder s = new StringBuilder();
        s.append(this.cliente+" ");
        return s.toString();
    }
}
