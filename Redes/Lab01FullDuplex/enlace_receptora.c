#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */
#include <stdlib.h>

#define MAX_MSG 200

int main(int argc, char *argv[]) {
  int sd, rc, n, tam_Cli;
  struct sockaddr_in endCli;   /* Vai conter identificacao do cliente */ 
  struct sockaddr_in endServ;  /* Vai conter identificacao do servidor local */
  char   msg[MAX_MSG];/* Buffer que armazena os dados que chegaram via rede */
  char mensagem[200];

  if (argc<2) {
	  printf("Digite IP e Porta para este servidor\n");
	  exit(1); }
/* Criacao do socket UDP */
  sd=socket(AF_INET, SOCK_DGRAM, 0);
  if(sd<0) {
    printf("%s: nao pode abrir o socket \n",argv[0]);
    exit(1);  }

/* Preenchendo informacoes sobre o servidor */
  endServ.sin_family 	  = AF_INET;
  endServ.sin_addr.s_addr = inet_addr(argv[1]); 
  endServ.sin_port 	  = htons(atoi(argv[2]));

/* Fazendo um bind na porta local do servidor */
  rc = bind (sd, (struct sockaddr *) &endServ,sizeof(endServ));
  if(rc<0) {
    printf("%s: nao pode fazer bind na porta %s \n", argv[0], argv[2]);
    exit(1); }

  printf("Esperando por dados no IP: %s, porta UDP numero: %s\n", argv[1], argv[2]);

/* Este servidor entra num loop infinito esperando dados de clientes */
  while(1) {

    /* inicia o buffer */
    memset(msg,0x0,MAX_MSG);
    tam_Cli = sizeof(endCli);
    /* recebe a mensagem  */
    n = recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *) &endCli, &tam_Cli);
    if(n<0) {
      printf("%s: nao pode receber dados \n",argv[0]);
      continue;} 
      
    /* imprime a mensagem recebida na tela do usuario */
    printf("{UDP, IP_L: %s, Porta_L: %u", inet_ntoa(endServ.sin_addr), ntohs(endServ.sin_port));
    printf(" IP_R: %s, Porta_R: %u} \n=> %s\n",inet_ntoa(endCli.sin_addr), ntohs(endCli.sin_port), msg);

    // printf("Escreva uma mensagem para o IP %s, para a PORT %u \n=> ", inet_ntoa(endCli.sin_addr), ntohs(endCli.sin_port) );
    printf("<= ");
    scanf(" %[^\n]", mensagem);
    putchar('\n');

    rc = sendto(sd, mensagem, strlen(mensagem), MSG_CONFIRM ,(struct sockaddr *) &endCli, sizeof(endCli));
    if(rc<0) {
      printf("%s: nao pode enviar dados \n",argv[0]);
      close(sd);
      exit(1); 
    }
    
  } /* fim do while */
return 0;

} /* fim do programa */
