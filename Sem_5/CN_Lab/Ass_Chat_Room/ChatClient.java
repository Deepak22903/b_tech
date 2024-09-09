import java.io.*;
import java.net.*;

public class ChatClient {
  private static final String SERVER_ADDRESS = "localhost";
  private static final int SERVER_PORT = 12345;

  public static void main(String[] args) {
    try {
      Socket socket = new Socket(SERVER_ADDRESS, SERVER_PORT);
      BufferedReader in =
          new BufferedReader(new InputStreamReader(socket.getInputStream()));
      PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
      BufferedReader userInput =
          new BufferedReader(new InputStreamReader(System.in));

      new Thread(() -> {
        try {
          String message;
          while ((message = in.readLine()) != null) {
            System.out.println(message);
          }
        } catch (IOException e) {
          System.err.println("Error reading from server: " + e.getMessage());
        }
      }).start();

      String message;
      while ((message = userInput.readLine()) != null) {
        out.println(message);
      }

    } catch (IOException e) {
      System.err.println("Error connecting to the server: " + e.getMessage());
    }
  }
}
