import java.io.IOException;
import java.util.Scanner;

public class UdpClient {

  private static final int SERVER_PORT = 7777;
  private static final String SERVER_IP = "127.0.0.1";
  private Scanner sc = new Scanner(System.in);
  private UdpCommunication udpCommunication;

  public void start() throws IOException {
    udpCommunication = new UdpCommunication(SERVER_IP, SERVER_PORT);
    String msg = sc.nextLine();
    udpCommunication.send(msg);
    Message receivedMsg = udpCommunication.receive();
    System.out.println("해당 메시지를 받았습니다. --->" + receivedMsg.message());
  }

  public static void main(String[] args) {
    try {
      new UdpClient().start();
    } catch (IOException e) {
      throw new RuntimeException(e);
    }
  }
}
