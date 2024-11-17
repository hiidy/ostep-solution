import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class UdpServer {
  private static final int PORT = 7777;
  private DatagramSocket socket;
  private DatagramPacket inPacket;
  private DatagramPacket outPacket;
  private byte[] inMsg = new byte[100];
  private byte[] outMsg;

  public UdpServer() {
    try {
      this.socket = new DatagramSocket(PORT);
      System.out.println("Server started on port" + PORT);
    } catch (SocketException e) {
      throw new RuntimeException(e);
    }
  }

  public void run() throws IOException {
    while (true) {
      inPacket = new DatagramPacket(inMsg, inMsg.length);
      socket.receive(inPacket);

      InetAddress clientAddress = inPacket.getAddress();
      int clientPort = inPacket.getPort();

      String ack = "메시지를 정확히 받았습니다.";
      outMsg = ack.getBytes();

      outPacket = new DatagramPacket(outMsg, outMsg.length, clientAddress, clientPort);
      socket.send(outPacket);

      inMsg = new byte[10];
    }
  }

  public static void main(String[] args) throws IOException {
    UdpServer udpServer = new UdpServer();
    udpServer.run();
  }
}
