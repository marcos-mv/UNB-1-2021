#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main()
{
        int b, connfd, sin_size, l, n;
        char operador;
        char buffer[50] = {0};
        int op1, op2, resultado;

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("Falha na criacao do socket");
		exit(EXIT_FAILURE);
	}


        struct sockaddr_in servaddr;
        struct sockaddr_in clientaddr;

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = 6006;

	int rc = bind(sockfd, (const struct sockaddr *)&servaddr, 
		sizeof(servaddr));

	if(rc == -1)
	{
		perror("falhou no  bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

        int volta;
        
        int len = sizeof(clientaddr);

        volta = recvfrom(
                sockfd,
                &operador,
                sizeof(char),
                MSG_WAITALL,
                ( struct sockaddr *)&clientaddr,
                &len
        );


        volta = recvfrom(
                sockfd,
                &op1,
                sizeof(int),
                MSG_WAITALL,
                ( struct sockaddr *)&clientaddr,
                &len
        );

        if ( volta == -1 ) printf("2 zoou\n");

        volta = recvfrom(
                sockfd,
                &op2,
                sizeof(int),
                MSG_WAITALL,
                ( struct sockaddr *)&clientaddr,
                &len
        );

        if ( volta == -1 ) printf("3 zoou\n");

        switch (operador)
        {
        case '+':
                resultado = op1 + op2;
                printf("O Resultado eh: %d + %d = %d\n", op1, op2, resultado);
                break;
        case '-':
                resultado = op1 - op2;
                printf("O Resultado eh: %d - %d = %d\n", op1, op2, resultado);
                break;
        case '*':
                resultado = op1 * op2;
                printf("O Resultado eh: %d * %d = %d\n", op1, op2, resultado);
                break;
        case '/':
                resultado = op1 / op2;
                printf("O Resultado eh: %d / %d = %d\n", op1, op2, resultado);
                break;
        default:
                printf("ERRO: Operacao nao descrita.");
        }

        sendto(
                sockfd, 
                &resultado, 
                sizeof(int), 
                0, 
                (struct sockaddr *)&clientaddr, 
                len
        );

        close(sockfd);
        
        return 0;
}