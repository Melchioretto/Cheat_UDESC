import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Servidor {
    public static void main(String[] args) throws IOException{
        // criando o socket na porta do parâmetro
        DatagramSocket server = new DatagramSocket(25555);
        InetAddress add = InetAddress.getByName("ens1");


        // especifica o tamanho máximo que pode ser recebido em uma mensagem
        int sizeBuffer = 65507;
        byte[] buf = new byte[sizeBuffer];

        // cria um pacote com cabeçalhos e recebe ele na segunda linha
        String official = "";
        while (true) {
            DatagramPacket pack = new DatagramPacket(buf, buf.length);
            server.receive(pack);
            String response = new String(pack.getData());

            official = official.concat(response);
            if (response.contains("###;")) {
                break;
            }
        }

        String aux = official.substring(13,official.indexOf("##Clientes##;"));
        String wordList[] = aux.split(";");

        List<String> nowords = new ArrayList<String>();

        for (int i = 0; i < wordList.length; i++){
            nowords.add(wordList[i]);
        }

        List<String> words = nowords.stream().sorted().collect(Collectors.toList()); 

        int init = official.indexOf("##Clientes##") + "##Clientes##".length();
        int end = official.indexOf("###;");

        String find = official.substring(init, end).concat(";");

        buf = new byte[sizeBuffer];
        init = 0;
        byte[] aux_ = "##RELATORIO##;\n".getBytes();
        for (int i = 0; i < aux_.length; i++) {
            buf[init] = aux_[i];
            init++;
        }
        for(int i = 0; i < words.size(); i++) {
            String[] trash = find.split(words.get(i));
            aux_ = (words.get(i).concat("=".concat(Integer.toString(trash.length - 1))).concat(";")).concat("\n").getBytes();
            
            if (init + aux_.length < sizeBuffer) {
                for (int j = 0; j < aux_.length; j++) {
                    buf[init] = aux_[j];
                    init++;
                }
            } else {
                DatagramPacket pack = new DatagramPacket(buf, buf.length, add, 17777);
                server.send(pack);
                buf = new byte[sizeBuffer];
                init = 0;

                for (int j = 0; j < aux_.length; j++) {
                    buf[init] = aux_[j];
                    init++;
                }
            }
        }

        DatagramPacket pack = new DatagramPacket(buf, buf.length, add, 17777);
        server.send(pack);

        buf = new byte[sizeBuffer];
        aux_ = "###;".getBytes();
        for (int j = 0; j < aux_.length; j++) {
            buf[init] = aux_[j];
            init++;
        }
        pack = new DatagramPacket(buf, buf.length, add, 17777);
        server.send(pack);
        
        // fecha o socket criado
        server.close();
    }

   
}