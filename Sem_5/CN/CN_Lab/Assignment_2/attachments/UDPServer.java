import java.net.*;
import java.io.*;
public class UDPServer {
    public static void main(String[] args) {
        try {
            DatagramSocket serverSocket = new DatagramSocket(9876);
            byte[] receiveData = new byte[1024];
            byte[] sendData = new byte[1024];

            System.out.println("Server is listening on port 9876...");

            while (true) {
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                serverSocket.receive(receivePacket);

                String clientSentence = new String(receivePacket.getData(), 0, receivePacket.getLength());
                System.out.println("Received: " + clientSentence);

                String capitalizedSentence = clientSentence.toUpperCase();
                sendData = capitalizedSentence.getBytes();

                InetAddress clientIPAddress = receivePacket.getAddress();
                int clientPort = receivePacket.getPort();

                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, clientIPAddress, clientPort);
                serverSocket.send(sendPacket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
