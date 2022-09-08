import java.net.*;
import java.io.*;

public class Server {
	public static void main(String[] args) {
		System.out.println("Server-TCPDemo3");
		ServerSocket server = null;
		Socket client = null;
		DataInputStream dis = null;
		BufferedReader br = null;
		DataOutputStream dos = null;
		
		try{
			server = new ServerSocket(5000);
			// TCP ��ݿ��� ������ ServerSocket�� �����ؾ� �Ѵ�. 5000�� ��Ʈ�� ServerSocket�� �����Ѵ�.
			System.out.println("���� ���� ����");
			
			client = server.accept();
			// ����ϰ� �ִٰ� Ŭ���̾�Ʈ�� �����ϸ�  ���������� ServerSocket Ŭ������ �ν��Ͻ�ȭ �Ѵ�.
			System.out.println("Ŭ���̾�Ʈ ����");
			
			while(true){
				dis = new DataInputStream(client.getInputStream());
				// Ŭ���̾�Ʈ�� ������ �����͸� �б� ���� InputStream�� Ȯ���Ѵ�.
				
				String receiveMessage = dis.readUTF();
				// readUTF�� ���� ���۵Ǿ�� ���ڿ��� �о� String Ŭ������ �ν��Ͻ��� �����Ѵ�.
				System.out.println("Client : " + receiveMessage);
				// ���� ���ڿ��� ����Ѵ�.
				
				if(receiveMessage.equals("exit"))
					break;
					
				String sendMessage = receiveMessage.toUpperCase();
				// ���� ���ڿ��� �빮�ڷ� �ٲ� ��, �ٸ� String ������ �����Ѵ�.
			
				dos = new DataOutputStream(client.getOutputStream());
				// ���ٿ��� String�� ����� ������ ������ ���ؼ� DataOutputStream ��ü�� �����ؾ� �Ѵ�.
				
				dos.writeUTF(sendMessage);
				// writeUTF�� ���� �޼����� ������.
				
				if(sendMessage.equals("exit"))
					break;
			}
		}catch(IOException ioe){
			ioe.printStackTrace();
		}finally{
			try{
				if(dis != null)
					dis.close();
				if(br != null)
					br.close();
				if(dos != null)
					dos.close();
				if(client != null)
					client.close();
				if(server != null)
					server.close();
			}
			catch(IOException ioe){
				ioe.printStackTrace();
			}
		}
	}
}