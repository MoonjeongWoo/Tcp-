#include	<winsock2.h> /*���� ��ſ� �ʿ��� �Լ� ���� ����Ǿ��ִ� ������� */
#include	<stdio.h>
#include        <conio.h>

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")	/* ������ ���� �Լ��� ���ǵǾ��ִ�. */

#define		PORT		  55000 /*������ Ŭ���̾�Ʈ���� �����͸� �ְ� ���� ��Ʈ��ȣ*/
#define    BUFFERSIZE    50

int main(){
	
    WSADATA wsdata;
	if ( WSAStartup( MAKEWORD(2, 2), &wsdata ) != 0 ){
		printf("WS2_32.DLL �� �ʱ�ȭ �ϴµ� �����߽��ϴ�.\n\n");
		return 0;
	}
    printf("WS_32.DLL �� �ʱ�ȭ �ϴµ� ���� �߽��ϴ�\n\n");
     /*Ŭ���̾�Ʈ�� �޽����� ������ ������ �ּҸ� ������ ����ü*/
	struct sockaddr_in serverAddress;
	/*Ŭ���̾�Ʈ ������ �����ϰ� ���� ������ ���� ������ -1 �� ����*/
	int clientSocket=socket(PF_INET, SOCK_DGRAM, 0);   
	if(clientSocket == -1){
		printf("Ŭ���̾�Ʈ ������ �����ϴµ� �����߽��ϴ�.\n");
		return 0;
	}
	/*���� ������ �ּ� ������ 0���� �����մϴ�.*/
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;//������ �ּ� ü��
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");//���� ������
	serverAddress.sin_port=htons(PORT);//������ ��Ʈ

	char toServer[BUFFERSIZE]; //������ ������ �޽����� ������ �迭
	char fromServer[BUFFERSIZE];//�������� ������ �޽����� �о� �鿩�� ������ �迭
    sprintf(toServer,"UDP ���� �ȳ�!!!\n");//toServer �� "UDP ���� �ȳ�!!!\n" �޽����� �����մϴ�.
   /*toServer �迭�� ���Ե� �޽����� ������ �����մϴ�.*/
    sendto(clientSocket,toServer,BUFFERSIZE, 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	printf("������ ������ �޽���:%s\n",toServer);
	/*�������� Ŭ���̾�Ʈ�� ������ �޽����� �о� ���Դϴ�.*/
	
	recvfrom(clientSocket,fromServer, BUFFERSIZE, 0, NULL, NULL);	

	printf("�����κ��� ���۵� �޽��� : %s\n",fromServer);
	getch();
	closesocket(clientSocket);
	return 0;
}
