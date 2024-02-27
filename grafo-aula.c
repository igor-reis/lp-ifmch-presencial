#include <stdio.h>
#include <locale.h> 

#define maxVertices 10

//-----------------------------------------
typedef struct{
	int mat[maxVertices][maxVertices];
	int aresta;
}tGrafo;

//-----------------------------------------
void inicializa(tGrafo *grafo){
	int i, j;
	for(i=0; i<maxVertices; i++)
	   for(j=0; j<maxVertices; j++)
	      grafo->mat[i][j] = 0;
	grafo->aresta = 0;      
}//fim inicializa
//-------------------------------------------
void insereAresta(tGrafo *grafo, int ori, int dest){
	grafo->mat[ori][dest] = 1;
	grafo->aresta++;
	printf("\nAresta inserida com sucesso!");
}//fim insereAresta
//-------------------------------------------
void removeAresta(tGrafo *grafo, int ori, int dest){
	grafo->mat[ori][dest] = 0;
	grafo->aresta--;
	printf("\nAresta removida com sucesso!");
}//fim removeAresta
//-------------------------------------------
void imprimeGrafo(tGrafo grafo){
  int i, j;
  
  printf("   ");
  for(i=0; i<maxVertices; i++)
     printf("%3d", i);
  printf("\n");
  
  for(i=0; i<maxVertices; i++){
     printf("%3d", i);
     for(j=0; j<maxVertices; j++)
        printf("%3d", grafo.mat[i][j]);
  printf("\n");
  }//fim for
}//fim imprimeGrafo 
//-----------------------------------------
void verificaProp(tGrafo grafo){
	int i, j, r=0, s=0;
	
	printf("\n*** Matriz adjacência R ***:\n\n");
	imprimeGrafo(grafo);
	printf("\n\n");
	printf("Propriedades do Grafo: \n\n");
	
	for(i=0; i<maxVertices; i++){
	   if(grafo.mat[i][i] == 1) r++;
	   else{
	      printf("- Não é reflexivo, pois o vértice (%d %d) é 0.\n", i, i);
	      i=maxVertices;
		  j=maxVertices;	
	   }//fim else 
    }//fim for
    if(r == maxVertices) printf("- É reflexivo.\n");
    
    int c1=0;
	for(i=0; i<maxVertices; i++)
	   for(j=0; j<maxVertices; j++){
	      if(grafo.mat[i][j] == 1){
	         c1++; 
			 if(grafo.mat[i][j] == grafo.mat[j][i]) s++; 
			 else{
			    printf("- Não e simétrico, pois o vértice (%d %d) é diferente de (%d %d).", i, j, j, i);
	            i=maxVertices;
	            j=maxVertices;
			}//fim else 	
		  }//fim if
	    }//fim for
	if(c1 == s) printf("- É simétrico.");    
	   
}//fim verificaProp
//-----------------------------------------
void verificaTran(tGrafo grafo){
	int i, j, k, c1=0, t=0;
	tGrafo R2;
	
	printf("\n*** Matriz adjacência R ***:\n\n");
	imprimeGrafo(grafo);
	printf("\n");
	
	inicializa(&R2);
	
	for(i=0; i<maxVertices; i++) 
       for(j=0; j<maxVertices; j++) 
          for(k=0; k<maxVertices; k++){
          	R2.mat[i][j]+=((grafo.mat[i][k] * grafo.mat[k][j]));
          	if(R2.mat[i][j] >= 1) R2.mat[i][j] = 1; else R2.mat[i][j] = 0;
		  }//fim for k
    printf("\n*** Matriz adjacência R2 *** :\n\n");     
    imprimeGrafo(R2);      
    
    for(i=0; i<maxVertices; i++) 
       for(j=0; j<maxVertices; j++) 
          if(R2.mat[i][j] == 1){
          	 c1++;
             if((R2.mat[i][j] == grafo.mat[i][j])) t++;
             else{
          	   printf("\n- Não é transitivo, pois o vértice (%d %d) não está contido na Matriz adjacencia R.", i, j);
	           i=maxVertices;
		       j=maxVertices;
		     }//fim else
		  }//fim if
     
	if(c1 == t) printf("\n- É transitivo."); 
	        
}//fim verificaTran
//-----------------------------------------
void verificaRInf(tGrafo grafo){
	int i, j, k, c=0, r=2;
	tGrafo ant, atual, somaG;
	inicializa(&ant);
	inicializa(&atual);
	inicializa(&somaG);
	somaG=grafo; ant=grafo;
	
	do{
	   for(i=0; i<maxVertices; i++) 
          for(j=0; j<maxVertices; j++) 
             for(k=0; k<maxVertices; k++){
          	   atual.mat[i][j]+=((grafo.mat[i][k] * ant.mat[k][j]));
          	   if(atual.mat[i][j] >= 1) atual.mat[i][j] = 1; else atual.mat[i][j] = 0;
		     }//fim for k
		     
		for(i=0; i<maxVertices; i++) 
           for(j=0; j<maxVertices; j++)
		      if(atual.mat[i][j] != ant.mat[i][j]){ 
		         for(i=0; i<maxVertices; i++)
                    for(j=0; j<maxVertices; j++){
                       somaG.mat[i][j]+=atual.mat[i][j];
		               ant.mat[i][j]=atual.mat[i][j];
			        }//fim for j
		         printf("\n*** Matriz adjacência R%d ***:\n\n", r);
		         imprimeGrafo(atual);
		         getch();
		         c=1;
		         r++;
		      }else c=0; 
	}while(c==1);
	printf("\n*** Matriz adjacência RInfinito ***:\n\n", r);
	imprimeGrafo(atual);
            
}//fim verificaRInf
//-----------------------------------------
void salvaGrafo(tGrafo *grafo, char nome[]){
	FILE *arq;
	int i;
	arq=fopen(nome, "wb");
	fwrite(grafo, sizeof(tGrafo), 1, arq);
	printf("\nDados salvos com sucesso!");
	fclose(arq);
}//fim salvaGrafo
//-----------------------------
void carregaGrafo(tGrafo *grafo, char nome[]){
	FILE *arq;
	arq=fopen(nome, "rb");
	if(arq==NULL)
	  printf("\nArquivo não encontrado!");
	else{
         fread(grafo, sizeof(tGrafo), 1, arq);
	 printf("\nDados carregados com sucesso!");
	}//fim else
	fclose(arq);
}//fim carregaGrafo
//----------------------------------------
int menu(){
	int op;
	printf("*********** Trabalho extra classe ***********\n");
	printf("       *********** Grafos ***********\n\n");
	printf("1- Inserir Aresta\n");
	printf("2- Remover Aresta\n");
	printf("3- Imprimir Matriz adjacência\n");
	printf("4- Remover Matriz adjacência\n");
	printf("5- Verificar Propriedades\n");
	printf("6- Verificar Transitividade\n");
	printf("7- Verificar Conexividade\n");
	printf("8- Salvar Grafo\n");
    printf("9- Carregar Grafo\n");
	printf("0- Encerrar\n\n");
	printf("Digite sua opção: ");
	scanf("%d",&op);
	return op;
}//fim menu
//------------------------------------
int main(){
	setlocale(LC_ALL, "Portuguese");
	int v1,v2,op,i;
    tGrafo grafo;
    char nome[10];
    inicializa(&grafo);
    
	do{
	    op=menu();
		switch(op){
			case 1: printf("\nEntre com os vértices (i j): ");
			        scanf("%d %d",&v1,&v2);
			        insereAresta(&grafo, v1, v2);
			break;
			case 2: printf("\nEntre com os vértices (i j): ");
			        scanf("%d %d",&v1,&v2);
			        removeAresta(&grafo, v1, v2);
			break;
			case 3: printf("\n*** Matriz adjacência R do Grafo ***: \n\n");
			        imprimeGrafo(grafo);
			break;
			case 4: inicializa(&grafo);
			        printf("\nMatriz adjacência removida com sucesso!");
			break;
			case 5: verificaProp(grafo);
			break;
			case 6: verificaTran(grafo);
			break;
			case 7: verificaRInf(grafo);
			break;
			case 8: printf("\nDigite um nome para o Grafo: ");
			        scanf("%s", &nome);
			        salvaGrafo(&grafo, nome);
		    break; 
		    case 9: printf("\nDigite o nome do Grafo: ");
			        scanf("%s", &nome);
			        carregaGrafo(&grafo, nome);
		    break;         
			case 0: printf("\nEncerrado com sucesso!");
			break;       
		}//fim switch
		getch();
		system("cls");
	}while(op!=0);
}//fim main


