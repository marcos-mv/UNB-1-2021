//Atividade de criação de comunicação via sockets TCP
//Marcos Vinícius Rodrigues da Conceicao 17/0150747

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void main()
{
        int b, sockfd, connfd, sin_size, l, n, len;
        char operador;
        int op1, op2, resultado;

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
                printf("Socket criado com sucesso!\n"); //criacao do socket

        //printf("%d\n", sockfd);                 //print de verificação se houver sucesso retorna 0 caso não -1

        //Montando estrutura sockaddr_in
        struct sockaddr_in servaddr;
        struct sockaddr_in clientaddr;

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = 6006;

        //Bind
        if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == 0)
                printf("bind executado com sucesso\n"); //bind () atribui o endereço especificado por addr para o soquete referido pelo arquivo
                                                        // descritor sockfd. addrlen especifica o tamanho, em bytes, da
                                                        // estrutura de endereço apontada pelo addr. Tradicionalmente, esta operação é
                                                        // chamado de “atribuir um nome a um soquete”.

        //printf("%d\n",b);

        if ((listen(sockfd, 5)) == 0) //listen escuta as conexões do socket
                printf("Servidor esperando por conexoes\n");
        //printf("%d\n",l);

        sin_size = sizeof(struct sockaddr_in);
        if ((connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &sin_size)) > 0)
                ;
        printf("Conexão estabelicida com o cliente.\n");
        //printf("%d\n",connfd);
        read(connfd, &operador, 10);
        read(connfd, &op1, sizeof(op1));
        read(connfd, &op2, sizeof(op2));
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
                printf("O resultado eh: %d / %d = %d\n", op1, op2, resultado);
                break;
        default:
                printf("ERRO: Operacao Nao Suportada");
        }

        write(connfd, &resultado, sizeof(resultado));

        //Depois de enviado o resultado para o cliente o socket é fechado. 
        close(sockfd);
}