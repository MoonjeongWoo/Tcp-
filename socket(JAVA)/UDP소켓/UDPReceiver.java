import java.net.*;
import java.io.*;

public class UDPReceiver {
	public static void main(String[] args) {
		DatagramSocket ds = null;
		DatagramPacket sendDatagramPacket = null;
		DatagramPacket receiveDatagramPacket = null;
		
		try{
			ds = new DatagramSocket(5000);
			// ��Ʈ 5000���� ������ �����Ͽ���.
			System.out.println("UDPReceiver �����ͱ׷����� ����");
			
			byte[] receiveByte = new byte[512];
			// DatagramSocket�� ���� �о���� �����ʹ� byte�迭�̴�. 
			
			receiveDatagramPacket = new DatagramPacket(receiveByte, receiveByte.length);
			// �����ϴµ� ����� DatagramSocket Ŭ������ �ν��Ͻ��� �����Ѵ�.(byte�迭�� �ּҰ�, �迭�� ����)
			
			ds.receive(receiveDatagramPacket);
			// DatagramSocket Ŭ������ receive �޼ҵ��̴�. �����Ͱ� ������ �޾Ƶ鿩 �Ű����ڿ� �����Ѵ�.
			
			String receiveMessage = new String(receiveDatagramPacket.getData(), 0, receiveDatagramPacket.getLength());
			// ���ٿ��� ����� �����͸� �ַܼ� ����ϱ� ���� byte�迭�� String Ŭ������ �ν��Ͻ��� �����Ѵ�. (byte�迭���� ����, byte�迭���� �����͸� ������ ��ġ, ������ ����)
			
			System.out.println("���� �޼���: " + receiveMessage);
			// Ŭ���̾�Ʈ�� �������� ���� �޼����� ����Ѵ�.
			
			String sendMessage = "�� ����� Sender~��� ������^^";
			// ������ Ŭ���̾�Ʈ���� �޼����� ������.
			
			byte[] sendByte = sendMessage.getBytes();
			// �޼����� �������� byte�迭�� ������ �ϱ� ������ String���� byte�迭�� ��ȯ�Ѵ�.
			
			InetAddress destinationIA = InetAddress.getByName("127.0.0.1");
			// DatagramSocket�� ���뵵�ΰ� ���� ������ ���������� �������� IP�� ������ �ش�.
			
			sendDatagramPacket = new DatagramPacket(sendByte, sendByte.length, destinationIA, 4000);
			// �۽��ϴµ� ����� DatagramSocket Ŭ������ �ν��Ͻ��� �����Ѵ�. (byte�迭�� �ּҰ�, �迭�� ����, �������� IP, �������� Port)  
			
			ds.send(sendDatagramPacket);
			// ���ٿ��� ������� '�۽ſ� DatagramSocket Ŭ������ �ν��Ͻ�' �� ������.
			
			System.out.println("�޽��� ���� �Ϸ�");			
		}catch(SocketException se){
			
		}catch(UnknownHostException uhe){
			
		}catch(IOException ioe){
			
		}finally{
			if(ds != null)
				ds.close();
		}
	}
}