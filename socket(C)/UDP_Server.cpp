#include	<winsock2.h> /*���� ��ſ� �ʿ��� �Լ� ���� ����Ǿ��ִ� ������� */
#include	<stdio.h>
#include        <conio.h>

#define		PORT		  55000 /*������ Ŭ���̾�Ʈ���� �����͸� �ְ� ���� ��Ʈ��ȣ*/
#define    BUFFERSIZE    50

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")	/* ������ ���� �Լ��� ���ǵǾ��ִ�. */

int main(){
	
    WSADATA wsdata;
	if ( WSAStartup( MAKEWORD(2, 2), &wsdata ) != 0 ){
		printf("WS2_32.DLL �� �ʱ�ȭ �ϴµ� �����߽��ϴ�.\n\n");
		return 0;
	}
    printf("WS_32.DLL �� �ʱ�ȭ �ϴµ� ���� �߽��ϴ�\n\n");
	
	struct sockaddr_in serverAddress; //������ �ּ� ������ ������ ����ü
	//UDP ���������� �������� ����
	int serverSocket=socket(PF_INET, SOCK_DGRAM, 0);
	//������ �ּҸ� ������ serverAddress �� 0���� �ʱ�ȭ ��Ŵ
	memset(&serverAddress, 0, sizeof(serverAddress));
	//serverAddress �� �ּ� ü�� ����
	serverAddress.sin_family=AF_INET;
	//serverAddress �� ���� IP ����
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	//serverAddress �� ��Ʈ ����
	serverAddress.sin_port=htons(PORT);
	//serverSocket �� ������ �ּ� ���� ����
	bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)	);
	printf("Ŭ���̾�Ʈ���� �����͸� �������⸦ ��ٸ��� �ֽ��ϴ�.\n");
    //Ŭ���̾�Ʈ�� ������ �޽����� ������ �迭
	char fromClient[BUFFERSIZE];
	//Ŭ���̾�Ʈ�� ������ �޽����� ������ �迭
	char toClient[BUFFERSIZE];
	//Ŭ���̾�Ʈ�� �ּ� ������ ������ ����ü
    struct sockaddr_in clientAddress;
	//Ŭ���̾�Ʈ�� �ּ� ������ ������ ����ü�� ũ�⸦ ������ ����
	int clientAddress_size;

	while(1) {
		//Ŭ���̾�Ʈ�� �ּ� ������ ������ clientAddress ����ü�� ũ�⸦ ����
		clientAddress_size=sizeof(clientAddress);
		//Ŭ���̾�Ʈ�� ������ �޽����� �о� �鿩�� fromClient �迭�� �����ϰ� 
		//�޽����� ���� Ŭ���̾�Ʈ�� �ּ� ������ clientAddress �� ������


       /* recvfrom �Լ��� Ŭ���̾�Ʈ�κ��� �����͸� �����ϴ� �Լ��Դϴ�.
          �����͸� �о���̴� �� �����ϸ� �о���� �������� ����Ʈ ���� �����ϰ�, �����ϸ� -1�� �����Ѵ�.
	  ����:
	   recvfrom(int sock, const void *msg, int len, unsigned flags, const struct sockaddr * addr, int addrlen)
	       int    �����͸� ���۹��� ������ ���� �ڵ�
		   void   �о���� �����͸� ������ �迭 ����
		   int    �о���� �����͸� ������ �迭�� ũ��
		   unsigned UDP ������ �ɼ��� �����ϴµ� ���� 0���� ����
		   sockaddr �����͸� ���� �� (addr ����ü)�� ������ ����
		   int    addr �����Ͱ� ����Ű�� ����ü�� ũ�� ����   
	     */

		recvfrom(serverSocket, fromClient, BUFFERSIZE, 0, (struct sockaddr*)&clientAddress, &clientAddress_size);
		printf("��!! Ŭ���̾�Ʈ�� �޽����� �����߽��ϴ�.\n");
		printf("Ŭ���̾�Ʈ�� ���� ���޵� �޽���:%s\n",fromClient);
        //toClient �迭�� "UDP Ŭ���̾�Ʈ �ݰ���!!!\n" �޽����� ����
		sprintf(toClient,"UDP Ŭ���̾�Ʈ �ݰ���!!\n");
        //Ŭ���̾�Ʈ�� toClient �迭�� �޽����� ������

		       /* sendto �Լ��� Ŭ���̾�Ʈ�� �����͸� �����ϴ� �Լ��Դϴ�.
                �����͸� �����ϴ� �� �����ϸ� ������ �������� ����Ʈ ���� �����ϰ�, �����ϸ� -1�� �����Ѵ�.
	  ����:
	  int sendto( int sock, const void *msg, int len, unsigned flags, const struct sockaddr * addr, int addrlen)
	       int   �����͸� ������ ������ ���� �ڵ�
		   void   ������ �����͸� ������ �迭 ����
		   int    ������ �����͸� ������ �迭�� ũ��
		   unsigned UDP ������ �ɼ��� �����ϴµ� ���� 0���� ����
		   sockaddr ������ �ϰ��� �ϴ� ������(addr ����ü)�� ������  ����
		   int    addr �����Ͱ� ����Ű�� ����ü�� ũ�� ����  
	     */
		sendto(serverSocket, toClient, BUFFERSIZE, 0, (struct sockaddr*)&clientAddress, sizeof(clientAddress));
		printf("Ŭ���̾�Ʈ�� ������ �޽���:%s\n",toClient);
	}
	getch();
	closesocket(serverSocket);
	return 0;
	}


      
