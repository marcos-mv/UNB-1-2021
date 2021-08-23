//Atividade de criação de comunicação via sockets TCP
//Marcos Vinícius Rodrigues da Conceicao 17/0150747

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

void main()
{
    int b, sockfd, sin_size, con, n, len;
    //char buff[256];
    char operador;
    int op1, op2, resultado;

    //criacao do Socket do cliente
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
        printf("Socket criado com sucesso!\n");
    //printf("%d\n", sockfd);


    //criacao da struct sockaddr_in
    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = 6006;

    sin_size = sizeof(struct sockaddr_in);

    //inicia a conexão com um socket
    if ((con = connect(sockfd, (struct sockaddr *)&servaddr, sin_size)) == 0);

    printf("A conexão com o servidor ocorreu com sucesso!\n");
    printf("Entre com uma operação:\n +:Adicao \n -: Subtracao \n *:Multiplicacao \n /: Divisao \n");
    scanf("%c", &operador);
    printf("Entre com os dois operandos:\n");
    scanf("%d %d", &op1, &op2);

    write(sockfd, &operador, 10);
    write(sockfd, &op1, sizeof(op1));
    write(sockfd, &op2, sizeof(op2));
    read(sockfd, &resultado, sizeof(resultado));
    printf("Resultado da operação recebida do servidor = %d\n", resultado);
    close(sockfd);
}