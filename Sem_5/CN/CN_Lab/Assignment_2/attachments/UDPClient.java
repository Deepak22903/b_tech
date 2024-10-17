import java.io.*;
import java.net.*;

public class UDPClient {
  public static void main(String[] args) {
    try {
      BufferedReader inFromUser =
          new BufferedReader(new InputStreamReader(System.in));
      DatagramSocket clientSocket = new DatagramSocket();

      InetAddress IPAddress = InetAddress.getByName("localhost");

      byte[] sendData;
      byte[] receiveData = new byte[1024];

      System.out.print("Enter your name: ");
      String sentence = inFromUser.readLine();
      sendData = sentence.getBytes();

      DatagramPacket sendPacket =
          new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
      clientSocket.send(sendPacket);

      DatagramPacket receivePacket =
          new DatagramPacket(receiveData, receiveData.length);
      clientSocket.receive(receivePacket);

      String modifiedSentence =
          new String(receivePacket.getData(), 0, receivePacket.getLength());
      System.out.println("Hello! " + modifiedSentence);

      clientSocket.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
