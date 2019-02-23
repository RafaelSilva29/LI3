public class Produto
{
    private String produto;
    /**
     * Construtor de Produto vazio
     */
    public Produto () {
        this.produto = "n/a";
    }
    /**
     * Construtor de Produto a partir de uma string
     * @param   produto     String com o nome do produto
     */
    public Produto (String produto) {
        this.produto = produto;
    }
    /**
     * Construtor de Produto a partir de outro Produto
     * @param   c   Produto já existente
     */
    public Produto (Produto c) {
        this.produto = c.getProduto();
    }
    /**
     * Devolve o Nome do Produto
     * @return  produto String com o nome do Produto
     */
    public String getProduto () {return produto;}
    /**
     * Cria uma copia do Produto
     */
    public Produto clone () {return new Produto(this);}
    /**
     * Compara Produtos
     */
    public boolean equals (Object o) {
        if (this==o)
            return true;
        else if (o==null || !o.getClass().equals(this.getClass())) return false;
        else {
            Produto p = (Produto) o;
            return (p.getProduto().equals(this.produto));
        }
    }
    /**
     * Transforma um Produto numa string
     */
    public String toString () {
        StringBuilder s = new StringBuilder();
        s.append(this.produto+" ");
        return s.toString();
    }
}
