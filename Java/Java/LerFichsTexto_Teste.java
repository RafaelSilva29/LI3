import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.stream.Collectors;
import static java.lang.System.out;

public class LerFichsTexto_Teste
{
    public static void main(String [] args) {
        Hipermercado hiper = new Hipermercado();
        
        System.out.println("\nBufferedReader e ArrayList<Venda>");
        double tempo = 0;
        Crono.start();
        ArrayList<String> wBuff = readLinesWithBuff(args[0]);
        Crono.stop();
        tempo += Double.parseDouble(Crono.print());
        System.out.println("Ficheiro "+args[0]+" lido usando BufferedReader!\nLidas e guardadas "+wBuff.size()+" linhas.\nTempo de leitura para ArrayList<Strings>: "+tempo);
        
        System.out.println("\nScanner/FileReader e ArrayList<Venda>");
        tempo = 0;
        Crono.start();
        ArrayList<String> wOutBuff = readLinesArrayWithScanner(args[0]);
        Crono.stop();
        System.out.println("Ficheiro "+args[0]+" lido usando Scanner e FileReader!\nLidas e guardadas "+wOutBuff.size()+" linhas.\nTempo: "+Crono.print());
        
        System.out.println("\nCom Parsing e ArrayList<Venda>");
        tempo = 0;
        Crono.start();
        ArrayList<Venda> arrV1 = parseAllLinhas(wBuff);
        Crono.stop();
        tempo += Double.parseDouble(Crono.print());
        System.out.println("Tempo com parsing para ArrayList<Venda>:"+tempo);
        
        System.out.println("\nCom Parsing e HashSet<Venda>");
        tempo = 0;
        Crono.start();
        HashSet<Venda> arrV2 = parseAllLinhasToSet(wBuff);
        Crono.stop();
        tempo += Double.parseDouble(Crono.print());
        System.out.println("Tempo com parsing para HashSet<Venda>:"+tempo);
        System.out.println((wBuff.size()-arrV2.size())+" linhas duplicadas");
        
    }
    
    public static ArrayList<String> readLinesWithBuff(String fich) {
        ArrayList<String> linhas = new ArrayList<>();
        BufferedReader inStream = null;
        String linha = null;
        try {
            inStream = new BufferedReader(new FileReader(fich));
            while( (linha = inStream.readLine()) != null )
                linhas.add(linha);
        } catch(IOException e) {
            out.println(e.getMessage()); return null;
        }
        return linhas;  
    }
    
    public static ArrayList<String> readLinesArrayWithScanner(String ficheiro) {
        ArrayList<String> linhas = new ArrayList<>();
        Scanner scanFile = null;
        try {
            scanFile = new Scanner(new FileReader(ficheiro));
            scanFile.useDelimiter("\n\r");
            while(scanFile.hasNext()) 
                linhas.add(scanFile.nextLine());
        }
        catch(IOException ioExc)
             { out.println(ioExc.getMessage()); return null; }
        finally { if(scanFile != null) scanFile.close(); }
        return linhas;
     }
     
    public static Venda parseLinhaVenda(String linha) {
        String[] aux = linha.trim().split(" ");
        Produto produto = new Produto(aux[0]);
        double preco = Double.parseDouble(aux[1]);
        int qtd = Integer.parseInt(aux[2]);
        char tipoNP = aux[3].charAt(0);
        Cliente cliente = new Cliente(aux[4]);
        int mes = Integer.parseInt(aux[5]);
        int filial = Integer.parseInt(aux[6]);
        return new Venda(produto,preco,qtd,tipoNP,cliente,mes,filial);
    }
    public static ArrayList<Venda> parseAllLinhas(ArrayList<String> linhas) {
        ArrayList<Venda> ret = new ArrayList<>();
        for (String s: linhas)
            ret.add(parseLinhaVenda(s));
        return ret;
    }
    public static HashSet<Venda> parseAllLinhasToSet(ArrayList<String> linhas) {
        HashSet<Venda> ret = new HashSet<Venda>();
        for (String s: linhas)
            ret.add(parseLinhaVenda(s));
        return ret;
    }
    
}
