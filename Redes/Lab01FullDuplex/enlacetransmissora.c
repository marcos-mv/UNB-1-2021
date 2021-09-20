#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <stdlib.h>

#define MAX_MSG 200

int main(int argc, char *argv[]) {
  int sd, rc, i, tam_Cli;
  struct sockaddr_in ladoCli;   /* dados do cliente local   */
  struct sockaddr_in ladoServ; 	/* dados do servidor remoto */
  char   msg[MAX_MSG];/* Buffer que armazena os dados que chegaram via rede */
  char mensagem[200] = "";
    
/* confere o numero de argumentos passados para o programa */
  if(argc<2)  {
    printf("uso correto: %s <ip_do_servidor> <porta_do_servidor> \n", argv[0]);
    exit(1);  }

/* Preenchendo as informacoes de identificacao do remoto */
  ladoServ.sin_family 	   = AF_INET;
  ladoServ.sin_addr.s_addr = inet_addr(argv[1]);
  ladoServ.sin_port 	   = htons(atoi(argv[2]));

/* Preenchendo as informacoes de identificacao do cliente */
  ladoCli.sin_family 	 = AF_INET;
  ladoCli.sin_addr.s_addr= htonl(INADDR_ANY);  
  ladoCli.sin_port 	     = htons(0); /* usa porta livre entre (1024-5000)*/

/* Criando um socket. Nesse momento a variavel       */
/* sd contem apenas dados sobre familia e protocolo  */

  sd = socket(AF_INET,SOCK_DGRAM,0);
  if(sd<0) {
    printf("%s: n�o pode abrir o socket \n",argv[0]);
    exit(1); }

/* Relacionando o socket sd com a estrutura ladoCli /*
/* Depois do bind, sd faz referencia a protocolo local, ip local e porta local */
  rc = bind(sd, (struct sockaddr *) &ladoCli, sizeof(ladoCli));
  if(rc<0) {
    printf("%s: n�o pode fazer um bind da porta\n", argv[0]);
    exit(1); }
  printf("{UDP, IP_R: %s, Porta_R: %s}\n", argv[1], argv[2]);

  printf("Escreva uma mensagem para o IP %s, para a PORT %u \n", inet_ntoa(ladoServ.sin_addr), ntohs(ladoServ.sin_port) );

  while(1) {

  /* Enviando um pacote para cada parametro informado */
  printf("<= ");
  scanf(" %[^\n]", mensagem);
  putchar('\n');

  rc = sendto(sd, mensagem, strlen(mensagem), 0,(struct sockaddr *) &ladoServ, sizeof(ladoServ));
  if(rc<0) {
    printf("%s: nao pode enviar dados \n",argv[0]);
    close(sd);
    exit(1); }

  /* inicia o buffer */
  memset(msg,0x0,MAX_MSG);
  tam_Cli = sizeof(ladoServ);
  /* recebe a mensagem  */
  rc = recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *) &ladoServ, &tam_Cli);
  if(rc<0) {
    printf("%s: nao pode receber dados \n",argv[0]);
    continue;
  } 
    
  /* imprime a mensagem recebida na tela do usuario */
  printf("{UDP, IP_L: %s, Porta_L: %u", inet_ntoa(ladoCli.sin_addr), ntohs(ladoCli.sin_port));
  printf(" IP_R: %s, Porta_R: %u} \n=> %s\n",inet_ntoa(ladoServ.sin_addr), ntohs(ladoServ.sin_port), msg);


  }

  return 1;
} /* fim do programa */
