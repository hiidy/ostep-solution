import java.io.IOException;

public class UdpServer {
  private static final int SERVER_PORT = 7777;
  private UdpCommunication server;

  public void run() throws IOException {
    server = new UdpCommunication(SERVER_PORT);
    while (true) {

      Message receivedMsg = server.receive();
      System.out.println("클라이언트로 다음 메시지를 받았습니다." + receivedMsg.message());

      String ack = "메시지를 성공적으로 받았습니다.";
      server.sendTo(ack, receivedMsg.address(), receivedMsg.port());
    }
  }

  public static void main(String[] args) throws IOException {
    UdpServer udpServer = new UdpServer();
    udpServer.run();
  }
}
