import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Scanner;
import java.util.Stack;

public class UdpClient {

  private static final int SERVER_PORT = 7777;
  private static final String SERVER_IP = "127.0.0.1";
  private DatagramSocket clientSocket;
  private DatagramPacket inPacket;
  private DatagramPacket outPacket;
  private Scanner sc = new Scanner(System.in);
  private byte[] inMsg = new byte[100];
  private byte[] outMsg;

  public void start() throws SocketException, IOException {
    String msg = sc.nextLine();
    outMsg = msg.getBytes();

    clientSocket = new DatagramSocket();
    InetAddress address = InetAddress.getByName(SERVER_IP);

    outPacket = new DatagramPacket(outMsg, outMsg.length, address, SERVER_PORT);
    inPacket = new DatagramPacket(inMsg, inMsg.length);

    clientSocket.send(outPacket);
    clientSocket.receive(inPacket);

    String receivedMsg = new String(inPacket.getData(), 0, inPacket.getLength());
    System.out.println(receivedMsg);
  }

  public static void main(String[] args) {
    try {
      new UdpClient().start();
    } catch (IOException e) {
      throw new RuntimeException(e);
    }
  }
}
