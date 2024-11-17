import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class UdpCommunication {
  private InetAddress address;
  private int port;
  private DatagramSocket socket;
  private DatagramPacket inPacket;
  private DatagramPacket outPacket;
  private byte[] inMsg = new byte[100];
  private byte[] outMsg;

  public UdpCommunication(String address, int port) throws UnknownHostException, SocketException {
    this.socket = new DatagramSocket();
    this.address = InetAddress.getByName(address);
    this.port = port;
  }

  public UdpCommunication(int port) throws SocketException {
    this.socket = new DatagramSocket(port);
  }

  public void send(String message) throws IOException {
    outMsg = message.getBytes();
    outPacket = new DatagramPacket(outMsg, outMsg.length, address, port);
    socket.send(outPacket);
  }

  public void sendTo(String message, InetAddress address, int port) throws IOException {
    outMsg = message.getBytes();
    outPacket = new DatagramPacket(outMsg, outMsg.length, address, port);
    socket.send(outPacket);
  }

  public Message receive() throws IOException {
    inPacket = new DatagramPacket(inMsg, inMsg.length);
    socket.receive(inPacket);

    String data = new String(inPacket.getData(), 0, inPacket.getLength());

    return new Message(inPacket.getAddress(), inPacket.getPort(), data);
  }
}
