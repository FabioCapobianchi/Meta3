
#include "comuns.h"
#include <signal.h>

int s_fifo_fd;
int c_fifo_fd;
char c_fifo_fname[25];

void trataSig(int i){
fprintf(stderr,"\n%s a terminar!!!!\n"
        "(interrompido via teclado == ^C)\n\n",c_fifo_fname);
         close(c_fifo_fd);
	 unlink(c_fifo_fname);
    exit(EXIT_SUCCESS);
}

int main(){


client cli1;
resposta_t resp;

char pnome[25];
int read_res;

//Cria o FIFO do cliente
 printf("\nDigite o nome de jogador: \n");
 scanf("%s",pnome);

	cli1.pid_cliente = getpid();
	strcpy(cli1.pnome,pnome);
	sprintf(cli1.fname, CLIENT_FIFO, cli1.pnome);
	strcpy(c_fifo_fname,cli1.fname);

if(signal(SIGINT,trataSig) == SIG_ERR){
        perror("\nNao foi possivel configurar o sinal SIGINT\n");
        exit(EXIT_FAILURE);
    }


  if(mkfifo(c_fifo_fname, 0777) == -1){
      perror("\nmkfifo do FIFO cliente deu erro");
     exit(EXIT_FAILURE);
 }

  fprintf(stderr,"\nJogador %s criado\n",pnome);

     s_fifo_fd = open(CHAMP_FIFO, O_WRONLY);
 if(s_fifo_fd == -1){
	 fprintf(stderr, "\nO servidor não esta a correr\n");
	 unlink(c_fifo_fname);
	 exit(EXIT_FAILURE);
}
 
     c_fifo_fd = open(c_fifo_fname, O_RDWR);
 if(c_fifo_fd == -1){
	 perror("\nErro ao abrir o FIFO do cliente");
	 close(c_fifo_fd);
	 unlink(c_fifo_fname);
	 exit(EXIT_FAILURE);
 }
 
 memset(cli1.comando, '\0', TAM_MAX);
 
 while(1){

   printf("\nDigite o comando > ");
   scanf("%s",cli1.comando);
 if(strcasecmp(cli1.comando,"quit")==0){
	write(s_fifo_fd, &cli1, sizeof(cli1));
	close(c_fifo_fd);
	close(s_fifo_fd);
	unlink(c_fifo_fname);
   return 0;
}
// b) Envia a pergunta
  write(s_fifo_fd, &cli1, sizeof(cli1));

// c) Obtem a resposta

    read_res = read(c_fifo_fd, &resp, sizeof(resp));
  if(read_res == sizeof(resp) && strcasecmp(cli1.comando,"mygame")==0){
  
  printf("\nJogo -> %s" , resp.ngame);
  printf("\nPontos -> %d" , resp.points);
  }
 else
  printf("\nSem resposta");  
}

	close(c_fifo_fd);
	close(s_fifo_fd);
	unlink(c_fifo_fname);
 return 0;

}
