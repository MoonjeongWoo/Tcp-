#include	<winsock2.h> /*���� ��ſ� �ʿ��� �Լ� ���� ����Ǿ��ִ� ������� */
#include	<stdio.h>
#include <conio.h>

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")	/* ������ ���� �Լ��� ���ǵǾ��ִ�. */
#define BUFFER_SIZE 100  /* 100 ����Ʈ */

char exchange(char *fromClient, char *toClient);
int main(){
	
	printf("[[[ Server ]]]\n");		

	/* WSAStartup �Լ��� �̿��ؼ� ������ ������ ���ǵǾ� �ִ� 
	   WS2_32.DLL ������ �ʱ�ȭ�մϴ�.
	   �ʱ�ȭ�� �����ϸ� 0�� �����մϴ�.
	   WS2_32.dll ������ �޸𸮿� ���ε��Ѵ�.
	  ����:
		int WSAStartup ( WORD wVersionRequested, LPWSADATA lpWSAData);
        WORD ������ ������ ����
        LPWSADATA ������ ������ ������ ���� ������ ������ ������
	*/
	
	WSADATA wsdata;	// ������ ���Ͽ� ���� ������ ����Ǵ� �������̴�.
	//MAKEWORK(2, 2) �� ������ ���� 2.2 ������ ����Ѵٴ� ���̴�.
	if ( WSAStartup( MAKEWORD(2, 2), &wsdata ) != 0 ){
		/*WS_32.DLL �� �ʱ�ȭ �ϴµ� ���� ���� ��� �����޽����� ����ϰ�
		���α׷��� �����մϴ�. */
		printf("WS2_32.DLL �� �ʱ�ȭ �ϴµ� �����߽��ϴ�.\n");
		return 0;
	}
    printf("1. WS2_32.DLL �� �ʱ�ȭ �ϴµ� ���� �߽��ϴ�.\n");

    /*socket �Լ��� �̿��ؼ� serverSocket�� �����մϴ�.
	  serverSocket�� ������ Ŭ���̾�Ʈ�� �����ߴ��� �����ϰ� Ŭ���̾�Ʈ�� 
	  ������ ��쿡 Ŭ���̾�Ʈ�� �����͸� �ְ� �޴� ���� �����ϴ� ��Ʈ��, �� socket�� �����մϴ�.
	  ���� :
	  SOCKET socket (int af, int type, int protocol)
          int ������ �������� ü�踦 �����մϴ�. 
		      ���ͳ� �ּ�ü���� TCP,UDP �� ��� PF_INET ���� �����մϴ�.        
          int ���� Ÿ���� �����մϴ�. TCP�� SOCK_STREAM �̰� UDP�� SOCK_DGRAM�̴�.
          int ������ ���������� �����մϴ�. 0 �� �ü���� �ڵ����� ���� Ÿ�Կ� �´� ���������� �������� 


		  (����) �������� ü��(Protocol Family)  ���� 
			PF_INET   IPv4���ͳ� �������� 
			PF_INET6  IPv6���ͳ� ��������  
			PF_LOCAL  LOCAL ����� ���� UNIX �������� 
			PF_PACKET Low level socket�� ���� �������̽� 
			PF_IPX    IPX �뺧 ��������

	*/
	
	/*������ �ڵ� (���� ��ũ����: ��ü ���� �Ǵ� �ĺ��� ���� ������ �Ǵ� ����)�� serverSocket�� ����*/
	SOCKET serverSocket = socket( PF_INET, SOCK_STREAM, 0 );

    /*ZeroMemory �Լ��� �ش� �޸𸮸� 0���� �ʱ�ȭ�����ִ� �Լ��Դϴ�.
	 serverAddress �迭�� 0���� �ʱ�ȭ ���׽��ϴ�. */
    SOCKADDR_IN serverAddress;
	ZeroMemory( &serverAddress, sizeof( serverAddress ) );
	/*serverAddress �� ���������� �ּ������� �����ϴ� ����ü �Դϴ�. 
	  serverAddress �� �ʿ��� �ּ� ������ �����մϴ�.*/
	serverAddress.sin_family		= AF_INET; /*������ �ּ� ü�踦 �����մϴ�.
										    TCP/IP ���������� ��� ���ͳ� ����̹Ƿ� AF_INET �� �����մϴ�.
		(����)�ּ�ü��(Address Family) ����  
           AF_INET  IPv4���ͳ� �������� 
           AF_INET6  IPv6���ͳ� ��������  
           AF_LOCAL  LOCAL ����� ���� UNIX ��������*/

	serverAddress.sin_port			= htons( 10000 ); /*���� ������ ��Ʈ�� �����մϴ�.  */
    serverAddress.sin_addr.s_addr	= htonl( ADDR_ANY );/*������ IP�� �����մϴ�.*/  
	/*ADDR_ANY�� ������ IP �ּҸ� �ڵ����� ã�Ƽ� �������ִ� �ǹ� (Connection will be accepted on any Internet interface on a server system having multiple IP addresses)*/

	/* htons, htonl
   CPU(����/CISC, Sparc/RISC) ���� �� ����Ʈ �̻��� ���� �����ϴ� ����� �ٸ� 
   16���� �� 0x1234�� ���� ������ ������ 0x34, 0x12 ������ �����ϴ� Little-Endian (����/CISC)�� ����ϴ� �ý����� �ִ°� �ϸ�, 
   �ݴ�� ū ������ ������ 0x12, 0x34������ �����ϴ� Big_Endian(Sparc/RISC)�� ����ϴ� �ý����� ����
   ��Ʈ��ũ ����Ʈ ������ 2 ����Ʈ �̻��� ū ���ڿ� ���� � ����Ʈ���� ���������� ���� ������ ���Ͽ� (��, �򿣵��) 
   ���� �ٸ� �ý��� ���� ȥ�� �߻��� ������. ����, ���� �迭 CPU������ htons, htonl�� �Ἥ ��Ʋ��Ƽ��->�򿣵��, �򿣵��->��Ʋ���������
   ó���� �־�� �� */

    /*bind �Լ��� serverAddress �� ������ ���������� �ּ������� �̿��ؼ� 
	  serverSocket��  IP �� PORT�� �ο��մϴ�.  serverSocket�� IP �� port�� �ο� �ϴµ� 
	�����ϸ� 0��, �����ϸ� SOCKET_ERROR �� �����մϴ�.
	
      ����:
	   bind(SOCKET s, const struct sockaddr FAR* name, int namelen)
	       SOCKET IP�� PORT�� �ο��� ������ �ڵ�
	       struct ������ IP�� PORT�� ���� ������ �����ϰ� �ִ� SOCKADDR_IN ����ü�� ������
		   int    SOCKADDR_IN ����ü�� ����
	*/ 
	if ( bind( serverSocket, (SOCKADDR *)&serverAddress, 
		sizeof( serverAddress ) ) == SOCKET_ERROR )
	{
		printf("serverSocket�� IP �� PORT �� �ο� �ϴµ� �����߽��ϴ�!!!\n" );
		return 0;
	}
   printf("2. serverSocket �� IP �� Port �� �ο� �ϴµ� ���� �߽��ϴ�.\n");

	/*listen �Լ��� Ŭ���̾�Ʈ�� serverSocket�� �ο��� IP �� PORT�� ���� �ߴ����� 
	  ���� �ϴ� �Լ� �Դϴ�. Ŭ���̾�Ʈ�� �����Ҷ����� 
	  �� ���α׷��� ���⼭ Ŭ���̾�Ʈ�� ��ٸ��� �ֽ��ϴ�.
	
	  ����:
	   listen(SOCKET s, int backlog)
	       SOCKET Ŭ���̾�Ʈ�� ������ ��ٸ��� ���� ��ü
	       int ���ÿ� ���Ӱ����� Ŭ���̾�Ʈ�� ��; SOMAXCONN �� ��� ���� ���� ������ Ŭ���̾�Ʈ�� ���� ���������� ���� �߽��ϴ�.
        
	     */
   printf("3. Ŭ���̾�Ʈ�� ������ ��ٸ��ϴ�.\n");
   listen( serverSocket, SOMAXCONN );
    /*Ŭ���̾�Ʈ�� ������ �����ϸ� ���α׷��� �̺κ����� �����ɴϴ�. */
	  
    SOCKET socket;

	/* accept �Լ��� Ŭ���̾�Ʈ�� ������ ����ϰ� Ŭ���̾�Ʈ�� �����͸� �ְ� �޴� ���� �����ϴ�
	  socket�� �����մϴ�.

	  ����:
	   accept(SOCKET s, struct sockaddr FAR* addr, int FAR* addrlen)
	       SOCKET ������ ����� ���� ������ �ڵ�
	       struct Ŭ���̾�Ʈ�� �ּ� ������ ������ SOCKADDR_IN ����ü�� �ּ�; Ŭ���̾�Ʈ�� �ּ� ������ ���� �� �ʿ䰡 ���� ���� NULL�� ����
		   int Ŭ���̾�Ʈ�� �ּ� ������ ������ SOCKADDR_IN ����ü�� ����; Ŭ���̾�Ʈ�� �ּ� ������ ���� �� �ʿ䰡 ���� ���� NULL�� ����
	     */
	if ( ( socket = accept( serverSocket, NULL, NULL ) ) ==	INVALID_SOCKET )
	{
		printf("Ŭ���̾�Ʈ�� �����͸� �ְ� �޴� socket�� ���� �� �� �����ϴ�.");
		return 0;
	}
	printf("!! Ŭ���̾�Ʈ�� �����߽��ϴ�. �޼����� ��ٸ��� ��......\n\n");
	char fromClient[BUFFER_SIZE+1]; //Ŭ���̾�Ʈ�� ���� ���޵� ������ ������ �迭

    /* recv �Լ��� Ŭ���̾�Ʈ���� send �Լ��� �̿��ؼ� ������ ������ �����͸� �о���Դϴ�.

	  ����:
	   recv(SOCKET s, char FAR* addr, int len, int flags)
	       SOCKET Ŭ���̾�Ʈ�� �����͸� �����ؼ� �������� ������ ������ �ڵ�
		   char   Ŭ���̾�Ʈ�� �����͸� ������ �迭
		   int    �о���� �������� ũ��
		   int    �����͸� �о���� ���� �ɼ����� ��κ� 0���� ����   
	     */

	/*Ŭ���̾�Ʈ�� ������ �����͸� �о� �鿩�� fromClient �� �����մϴ�.*/
	recv( socket, fromClient, BUFFER_SIZE, 0 );
	/*fromClient �� ����� ������ ����մϴ�.*/
	printf("Ŭ���̾�Ʈ�� ���� ���� ���� ������: %s\n\n", fromClient );
	char toClient[BUFFER_SIZE]; //Ŭ���̾�Ʈ�� ������ ������ ������ �迭

	char len[1];
	len[0] = exchange(fromClient, toClient); //�ҹ��ڸ� �빮�ڷ� �ٲٴ� �Լ�

	//strcpy(toClient,"Hello Client!!"); //toClient �迭�� Hello Client!! �� �����մϴ�.
	/*toClient �迭�� ����� ������ Ŭ���̾�Ʈ�� �����մϴ�.*/

    /* send �Լ��� Ŭ���̾�Ʈ�� �����͸� �����ϴ� �Լ��Դϴ�.

	  ����:
	   send((SOCKET s, const char FAR* buf, int len, int flags)
	       SOCKET Ŭ���̾�Ʈ�� �����͸� �����ؼ� �������� ������ ������ �ڵ�
		   char   Ŭ���̾�Ʈ�� ���� �����͸� �����ϰ� �ִ� �迭
		   int    ���� �������� ũ��
		   int    �����͸� ���� ���� �ɼ����� ��κ� 0���� ���� )   
	     */
	send(socket, len, sizeof(char), 0 );
	send(socket, toClient, len[0], 0 );
	printf("Ŭ���̾�Ʈ�� ������ �޼��� : %s\n", toClient);
	printf("Ŭ���̾�Ʈ�� ������ �޼��� ���� : %d\n\n", len[0]);

	getch();

    /*Ŭ���̾�Ʈ���� ������ �����մϴ�.*/  
	closesocket(socket);
	printf("Ŭ���̾�Ʈ���� ������ ���� �߽��ϴ�.\n");
	/*WS_32.DLL ����� ���� �մϴ�.*/
	WSACleanup();	// ws2_32.dll ������ �޸𸮿��� �����Ѵ�.
	printf("WS2_32.DLL �� ����� �����մϴ�.\n");
	return 1;
}

char exchange(char *fromClient, char *toClient){
	int i;
	char num=0;
	
	for(i=0; i<100; i++){
		toClient[i] = fromClient[i];
		if(fromClient[i]=='\0')
			break;
		num++;
	}
	for(i=0; i<num ; i++){
		if(fromClient[i]>=97)
			toClient[i] = fromClient[i]-32;	/* �ҹ���'a'= 97, �빮��'A'=65 */
	}
	return num;
} 

