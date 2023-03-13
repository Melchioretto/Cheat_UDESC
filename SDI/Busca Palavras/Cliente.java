import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Cliente {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) throws IOException{
        // cria um socket e abre em qualquer porta disponível
        DatagramSocket client = new DatagramSocket(17777);

        // pega o endereço IP da máquina
        InetAddress add = InetAddress.getByName("ens1");

        int sizeBuffer = 65507;
        byte[] buffer = new byte[sizeBuffer];
        int init = 0;

        while(true) {
            if (!sc.hasNextLine()) {
                break;
            }
            String currentLine = sc.nextLine();
            byte[] aux = currentLine.getBytes();
            

            if (init + aux.length < sizeBuffer) {
                for (int i = 0; i < aux.length; i++) {
                    buffer[init] = aux[i];
                    init++;
                }
                
            } else {
                DatagramPacket pack = new DatagramPacket(buffer, sizeBuffer, add, 25555);
                client.send(pack);
                buffer = new byte[sizeBuffer];
                init = 0;

                int modDivision = aux.length % sizeBuffer;
                int numberPacks = modDivision > 0 ? aux.length/sizeBuffer + 1 : aux.length/sizeBuffer;
                

                // para cada pacote
                int sum = 0, j;
                for (int i = 0; i < numberPacks; i++){
                    // para cada posição da linha lida adiciona ao buffer
                    for (j = 0; j < sizeBuffer; j++){
                        if (j + sum == aux.length) {
                            break;
                        }
                        buffer[j] = aux[j + sum];
                    }
                    sum += sizeBuffer;
                    init = 0;
                    pack = new DatagramPacket(buffer, sizeBuffer, add, 25555);
                    client.send(pack);
                    buffer = new byte[sizeBuffer];
                }
            }
          
        }
        
        DatagramPacket pack = new DatagramPacket(buffer, sizeBuffer, add, 25555);
        client.send(pack);
        buffer = new byte[sizeBuffer];
        
        String official = "";
        while (true) {
            DatagramPacket packag = new DatagramPacket(buffer, sizeBuffer);
            client.receive(packag);
            String response = new String(packag.getData());
            official = official.concat(response);
            
            if (official.contains("###;")) {
                break;
            }
        }

        System.out.println(official);
        // fecha o socket aberto anteriormente
        client.close();
        sc.close();
    }

}
