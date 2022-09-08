import java.net.*;
import java.io.*;

public class Client {
	public static void main(String[] args) {
		System.out.println("Client-TCPDemo3");
		Socket client = null;
		DataOutputStream dos = null;
		BufferedReader br = null;
		DataInputStream dis = null;
		
		try{
			client = new Socket("localhost", 5000);
			// 5000�� ��Ʈ�� ���� ����
			System.out.println("���� ���� ����");
			
			while(true){
				System.out.print("Client : ");
				br = new BufferedReader(new InputStreamReader(System.in));
				// Ű����� ���ڿ��� �Է� �޾� ������ ������ ���� BufferedReader Ŭ������ �ν��Ͻ��� �����Ѵ�.
				
				String sendMessage = br.readLine();
				// Ű����κ��� �Էµ� �� ������ �о� String �� �����Ѵ�.
				
				dos = new DataOutputStream(client.getOutputStream());
				// ���ٿ��� String�� ����� ������ ������ ���ؼ� DataOutputStream ��ü�� �����ؾ� �Ѵ�.
				
				dos.writeUTF(sendMessage);
				// writeUTF�� ���� �޼����� ������.
				
				dos.flush();
				// ������ ������ ��� �۽��϶�� ��ɾ��̴�.
				// �����͸� �����ϸ� �ٷ� �۽̵Ǵ� ���� �ƴ϶� �ϴ� �������� ���� ���Ŀ� ������ �Ǵµ�
				// flush() ��ɾ�� ��� ���� �� �ִ�.
				
				if(sendMessage.equals("exit"))
					break;
				
				dis = new DataInputStream(client.getInputStream());
				// ������ ������ �����͸� �б� ���� InputStream�� Ȯ���Ѵ�. 
				
				String receiveMessage =  dis.readUTF();
				// readUTF�� ���� ���۵Ǿ�� ���ڿ��� �о� String Ŭ������ �ν��Ͻ��� �����Ѵ�.
				System.out.println("Server : " + receiveMessage);
				
				if(receiveMessage.equals("exit"))
					break;
			}
		}catch(IOException ioe){
			ioe.printStackTrace();
		}finally{
			try{
				if(br != null)
					br.close();
				if(dos != null)
					dos.close();
				if(client != null)
					client.close();
			}catch(IOException ioe){
				ioe.printStackTrace();
			}
		}
	}
}