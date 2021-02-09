
#include "comuns.h"

void initRandom()
	{
	    srand(time(NULL));
	}

int randomNum(int a, int b)
	{
	    return a + rand()%(b-a+1);
	}

pcli criaCliente(pcli c1, client copia)
   {
	   pcli novo;
	   novo=malloc(sizeof(client));
 
 if(novo==NULL)
	 {
	  return NULL;
	 }else{
		   novo->pid_cliente = copia.pid_cliente;
		   strcpy(novo->pnome, copia.pnome);
		   strcpy(novo->fname, copia.fname);
		   novo->next= NULL;
   
    if(c1==NULL)
        c1 = novo;
    else
	{  
             novo->next = c1;
             c1 = novo;
		     }                           
   }
	   if(c1!=NULL)
	   fprintf(stderr,"\nCliente %s gravado\n", novo->pnome);
   
   return c1;
}

int Verifica_player(pcli c1, char cname[])
{
      pcli aux;
      aux=c1;
     
     if(aux == NULL){
     return 1;
     }
    while(aux != NULL)
    {  
        if(strcmp(aux->pnome,cname)==0)
        { 
            return 0;
        }
        aux = aux->next;
    }
    
    return 1;
}


client* devolve_player(client *c1, int a)
{
      client *aux;
      aux=c1;
       int x=0;
  
    while(aux != NULL)
    {  
      if(x == a){
        printf("\n Aqui i =  %s \n",aux->pnome);
      return aux;
      }
        aux = aux->next;
         x++;
    }
    
    return c1;
}


void mostra_player(pcli c1)
{
    pcli aux;
    aux=c1;
    
     if(aux == NULL){
        fprintf(stderr,"\nAinda nao existem jogadores\n");
      return;
     }
    while(aux != NULL)
    {  
       fprintf(stderr,"Player: %s\n", aux->pnome);
        aux = aux->next;
    }
    
    return ;
}

void mostra_jogos(int tam,char *fga[4][1]){
  int i;

   for(i=0;i<tam;i++){
     printf("Jogo: %s\n", fga[i][0]);
   } 
   return;
 }

char *retorna_jogo(int tam,char *fga[4][1]){
    int i;

  i = max(1,tam);

  return fga[i][0];

}


void*func1(void *arg){
   
  int n = 1; 
  //n = randomNum(1,4);
  client *p = (client *)arg;

  printf("nome %s comando %ld\n",p->pnome, p->tid);
  fflush(stdout);
  if(n==1)
  n = jogo1(); 


  return p;
}

   int jogo1(){

     int n,res=0,pontos=0;
	  printf("\n\nBem vindo ao AdvinhaNum!!!\n\n");
	while(1){
	    n = randomNum(1,5);
	    
	  printf("\nFoi escolhido um numero entre 1 e 5 \\escolha \"0\"  para terminar!!!\n");
	  printf("\nTente acertar o numero \n");
	  scanf("%d",&res);
	  if(res == 0){
	   printf("\nPontuacao final: %d pontos.\n",pontos);
	  break;  
	    }
	  if(res == n){
	  printf("\nAcertou!!!\n");
	  pontos+=1;
	}else{
	  printf("\n--Errou--\n");
	    }
	}
	return pontos;
}

int max(int a, int b){

return (a > b) ? a : b;

}
