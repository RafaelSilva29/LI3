import java.lang.*;
public class Venda
{
    private Produto produto;
    private double preco;
    private int qtd;
    private char tipoNP;
    private Cliente cliente;
    private int mes;
    private int filial;
    /**
     * Construtor de Venda vazia
     */
    public Venda () {
        this.produto = null;
        this.preco = 0;
        this.qtd = 0;
        this.tipoNP = ' ';
        this.cliente = null;
        this.mes = 0;
        this.filial = 0;
    }
    /**
     * Contrutor de Venda a partir dos seus dados
     * @param   produto Nome do produto
     * @param   preco   Preço do produto
     * @param   qtd     Quantidade vendida
     * @param   tipoNP  Produto em Promoção ou Normal
     * @param   cliente Cliente que comprou o Produto
     * @param   mes     Mes da compra
     * @param   filial  Filial onde foi realizada a venda
     */
    public Venda (Produto produto, double preco, int qtd, char tipoNP, Cliente cliente, int mes, int filial) {
        this.produto = produto;
        this.preco = preco;
        this.qtd = qtd;
        this.tipoNP = tipoNP;
        this.cliente = cliente;
        this.mes = mes;
        this.filial = filial;
    }
    /**
     * Construtor de Venda a partir de outra venda
     * @param   v   Venda já existente
     */
    public Venda (Venda v) {
        this.produto = v.getProduto();
        this.preco = v.getPreco();
        this.qtd = v.getQtd();
        this.tipoNP = v.getTipoNP();
        this.cliente = v.getCliente();
        this.mes = v.getMes();
        this.filial = v.getFilial();
    }
    /**
     * Devolve o Nome do Produto
     * @return  produto String com o nome do Produto
     */
    public Produto getProduto () {return produto;}
    /**
     * Devolve o Preço da Venda
     * @return  preco   Preco de Produto
     */
    public double getPreco () {return preco;}
    /**
     * Devolve o Quantida da Venda
     * @return  qtd  Quantidade Vendida
     */
    public int getQtd () {return qtd;}
    /**
     * Devolve o Tipo de Venda
     * @return  tipoNP  Tipo de Venda (Promoção ou Normal)
     */
    public char getTipoNP (){return tipoNP;}
    /**
     * Devolve o Nome do Cliente
     * @return  cliente String com o nome do Cliente
     */
    public Cliente getCliente () {return cliente;}
    /**
     * Devolve o Mês da Venda
     * @return  mes     Mês em que foi realizada a venda
     */
    public int getMes () {return mes;}
    /**
     * Devolve a Filial onde foi realizada a Venda
     * @return  filial  Numero da Filial
     */
    public int getFilial () {return filial;}
    /**
     * Cria uma copia da Venda
     */
    public Venda clone () {return new Venda(this);}
    /**
     * Compara Vendas
     */
    public boolean equals (Object o) {
        if (this==o) 
            return true;
        else if (o==null || !o.getClass().equals(this.getClass()))
            return false;
        else {
            Venda v = (Venda) o;
            return (v.getProduto().equals(this.getProduto()) && v.getPreco()==this.getPreco() && 
                    v.getQtd()==this.getQtd() && v.getTipoNP()==this.getTipoNP() && v.getCliente().equals(this.getCliente()) &&
                    v.getMes()==this.getMes() && v.getFilial()==this.getFilial());
        }
    }
    /**
     * Cria um hashCode para a Venda
     */
    public int hashCode() {
        return (produto.getProduto()+preco+qtd+tipoNP+cliente.getCliente()+mes+filial).hashCode();
    }
    /**
     * Transforma uma Venda numa string
     */
    public String toString () {
        StringBuilder s = new StringBuilder();
        s.append(this.produto+" "+this.preco+" "+this.qtd+" "+this.tipoNP+" "+this.cliente+" "+this.mes+" "+this.filial);
        return s.toString();
    }
    
    /**
     * Verifica se uma venda é valida, se cumpre os parametros para ser criada
     * @param   catCli  Catalogo de Clientes 
     * @param   caProd  Catalogo de Produtos
     */
    public boolean vendaValida(CatalogoClientes catCli, CatalogoProdutos caProd) {
        if (!catCli.contains(cliente)) return false;
        if (!caProd.contains(produto)) return false;
        if (preco<0 || preco>=1000) return false;
        if (qtd<1 || qtd>200) return false;
        if (tipoNP!='N' && tipoNP!='P') return false;
        if (mes<1 || mes>12) return false;
        return true;
    }
    /**
     * Veridica se uma venda tem preço 0
     */
    public boolean vendaPreco0 () {
        if (preco==0) return true;
        else return false;
    }
}
