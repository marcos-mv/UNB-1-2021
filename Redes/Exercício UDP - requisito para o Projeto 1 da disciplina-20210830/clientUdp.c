#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

//#define buffsize  150
int main()
{
    int b, sin_size, con, n, len;
    //char buff[256];
    char operador;
    int op1, op2, resultado;

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("falha na criacao do socket");
		return(-1);
	}

    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = 6006;

    printf("Entre com uma operação:\n +:Adicao \n -: Subtracao \n *:Multiplicacao \n /: Divisao \n");
    scanf("%c", &operador);
    printf("Entre com os dois operandos:\n");
    scanf("%d %d", &op1, &op2);

    sendto(
        sockfd, 
        &operador, 
        sizeof(char), 
        MSG_CONFIRM, 
        (const struct sockaddr *)&servaddr, 
        sizeof(servaddr)
    );

    sendto(
        sockfd, 
        &op1, 
        sizeof(int), 
        MSG_CONFIRM, 
        (const struct sockaddr *)&servaddr, 
        sizeof(servaddr)
    );

    sendto(
        sockfd, 
        &op2, 
        sizeof(int), 
        MSG_CONFIRM, 
        (const struct sockaddr *)&servaddr, 
        sizeof(servaddr)
    );

    recvfrom(
        sockfd,
        &resultado,
        sizeof(int),
        MSG_WAITALL,
        (const struct sockaddr *)&servaddr,
        sizeof(servaddr)
    );

    printf("resultado da operacao recebido do servidor =%d\n", resultado);
    close(sockfd);
    return 0;
}