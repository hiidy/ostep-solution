import java.net.InetAddress;

public record Message(InetAddress address, int port, String message) {}
