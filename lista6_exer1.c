#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct{
	char nome[40];
	char genero[40];
	int integrantes, ranking;
}tBanda;

int qtd=0;
//-----------------------------
void cadastrarBanda(tBanda banda[]){
	if(qtd!=10){
	   printf("\n*** Cadastro de Bandas *** \n");
	   printf("Nome da banda: "); 
	   fflush(stdin); gets(banda[qtd].nome);
	   printf("Gênero: "); 
	   fflush(stdin); gets(banda[qtd].genero);
	   printf("Quantidade de integrantes: "); 
	   scanf("%d", &banda[qtd].integrantes);
	   printf("Posição em seu ranking: "); 
	   scanf("%d", &banda[qtd].ranking);
	   printf("\nBanda cadastrada com sucesso!");
	   qtd++;
    } else printf("Limite de bandas esgotado!");
}//fim cadastrarBanda
//-----------------------------
void deletarBanda(tBanda banda[], int num_banda){
	char op_e;
	if(num_banda > qtd) printf("\nBanda não encontrada!");
	else{
		printf("\n*** Dados da banda %d ***\n", num_banda);
		num_banda=num_banda-1;
		printf("Nome da banda: %s\n", banda[num_banda].nome);
		printf("Gênero: %s\n", banda[num_banda].genero);
		printf("Quantidade de integrandes: %d\n", banda[num_banda].integrantes);
		printf("Posição em seu ranking: %d\n", banda[num_banda].ranking);
		printf("Tem certeza que deseja deletar? [s/n]: ");
		scanf(" %c", &op_e);
		if(op_e == 's'){
			banda[num_banda] = banda[qtd-1];
	        printf("\nBanda excluída com sucesso!");
	        qtd--;
		} else if(op_e == 'n') printf("\nOperação cancelada!");	
    }//fim else 	
}//fim deletarBanda
//-----------------------------
void alterarBanda(tBanda banda[], int num_banda){
	char op_e;
	if(num_banda > qtd) printf("\nBanda não encontrada!");
	else{
		printf("\n*** Dados da banda %d ***\n", num_banda);
		num_banda=num_banda-1;
		printf("Nome da banda: %s\n", banda[num_banda].nome);
		printf("Gênero: %s\n", banda[num_banda].genero);
		printf("Quantidade de integrandes: %d\n", banda[num_banda].integrantes);
		printf("Posição em seu ranking: %d\n", banda[num_banda].ranking);
		printf("Tem certeza que deseja alterar? [s/n]: ");
		scanf(" %c", &op_e);
		if(op_e == 's'){
			printf("\n*** Alterar Banda *** \n");
	        printf("Nome da banda: "); 
	        fflush(stdin); gets(banda[num_banda].nome);
	        printf("Gênero: "); 
	        fflush(stdin); gets(banda[num_banda].genero);
	        printf("Quantidade de integrantes: "); 
	        scanf("%d", &banda[num_banda].integrantes);
	        printf("Posição em seu ranking: "); 
	        scanf("%d", &banda[num_banda].ranking);
	        printf("\nBanda editada com sucesso!");
		} else if(op_e == 'n') printf("\nOperação cancelada!");	
    }//fim else 	
}//fim alterarBanda
//-----------------------------
void listarBanda(tBanda banda[]){
	int i;
	if(qtd == 0) printf("\nNenhuma banda cadastrada!");
	else
	   for(i=0; i<qtd; i++){
		   printf("\n*** Dados da banda %d ***\n", i+1);
		   printf("Nome da banda: %s\n", banda[i].nome);
		   printf("Gênero: %s\n", banda[i].genero);
		   printf("Quantidade de integrandes: %d\n", banda[i].integrantes);
		   printf("Posição em seu ranking: %d\n", banda[i].ranking);
	   }//fim for
}//fim listarBanda
//-----------------------------
void  salvaArquivoTexto(tBanda banda[]){
	FILE *arq;
	int i;
	if(qtd==0) printf("\nNenhuma banda cadastrada!");
	else{
	arq = fopen("bandas.txt", "w");
	for(i=0; i<qtd; i++){
		fprintf(arq, "%s\n", banda[i].nome);
		fprintf(arq, "%s\n", banda[i].genero);
		fprintf(arq, "%d\n", banda[i].integrantes);
		fprintf(arq, "%d", banda[i].ranking);
		if(i<qtd-1) //se nao estiver no ultimo registro
	       fprintf(arq, "\n");
	}//fim for
	printf("\nBandas salvas com sucesso!");	
	fclose(arq);
	}//fim else
}//fim salvaArquivoTexto
//-----------------------------
void salvaArquivoBinario(tBanda banda[]){
	FILE *arq;
	int i;
	if(qtd==0) printf("\Nenhuma banda cadastrada!");
	else{
	arq=fopen("bandas.dat", "wb");
	for(i=0; i<qtd; i++) fwrite(&banda[i], sizeof(tBanda), 1, arq);  
	printf("\nBandas salvas com sucesso!");	
	fclose(arq);
    }//fim else
}//fim salvaArquivoBinario
//-----------------------------
void carregaArquivoBinario(tBanda banda[]){
	FILE *arq;
	arq=fopen("bandas.dat", "rb");
	if(arq==NULL) //arquivo nao existe
	   printf("\nArquivo não encontrado!");
	else{
	while(fread(&banda[qtd], sizeof(tBanda), 1, arq) > 0)
	   qtd++;
	printf("\nBandas carregadas com sucesso!"); 
	fclose(arq);
	}//fim else   
}//fim carregaArquivoBinario
//-----------------------------
void carregaArquivoTexto(tBanda banda[]){
	FILE *arq;
	arq=fopen("bandas.txt", "r");
	if(arq==NULL) //arquivo nao existe
	   printf("\nArquivo não encontrado!");
	else{
	while(!feof(arq)){
		fscanf(arq, "%s", &banda[qtd].nome);
		fscanf(arq, "%s", &banda[qtd].genero);
		fscanf(arq, "%d", &banda[qtd].integrantes);
		fscanf(arq, "%d", &banda[qtd].ranking);
		qtd++;                                                                                                                                                                                                                                                                                             
	}//fim while
	fclose(arq);
	printf("\nBandas carregadas com sucesso!");
    }//fim else
}//fim caregaArquivoTexto
//-----------------------------
int buscaNome(tBanda banda[], char nome[]){
	int i;
	for(i=0; i<qtd; i++){
		if(strcmp(nome, banda[i].nome) == 0){
		   printf("\n*** Dados da banda %d ***\n", i+1);
		   printf("Nome da banda: %s\n", banda[i].nome);
		   printf("Gênero: %s\n", banda[i].genero);
		   printf("Quantidade de integrandes: %d\n", banda[i].integrantes);
		   printf("Posição em seu ranking: %d\n", banda[i].ranking);
		   if(banda[i].ranking <= 3) printf("\nEstá entre as bandas favoritas!");
		   return 1;
		}//fim if
	}//fim for
	return 0;
}//fim buscaNome
//-----------------------------
int buscaGenero(tBanda banda[], char genero[]){
	int i, c=0;
	  for(i=0; i<qtd; i++){
	  	if(strcmp(genero,banda[i].genero)==0){
	  		 printf("\n*** Dados da banda %d ***\n",i+1);
		     printf("Nome da banda: %s\n",banda[i].nome);
		     printf("Gênero: %s\n",banda[i].genero);
		     printf("Quantidade de integrantes: %d\n",banda[i].integrantes);
		     printf("Posição em seu ranking: %d\n",banda[i].ranking);
		     c++;
		  }// fim if
	  }// fim for
	  return c;
}//fim buscaGenero
//-----------------------------
int menu(){
	int op;
	printf("\t\t**** IFSULDEMINAS - Campus Machado ****\n");
	printf("1- Cadastrar nova banda\n");
	printf("2- Listar todas bandas\n");
	printf("3- Salvar bandas\n");
	printf("4- Carregar bandas\n");
	printf("5- Buscar banda por nome\n");
	printf("6- Buscar banda por gênero\n");
	printf("7- Deletar banda\n");
	printf("8- Alterar banda\n");
	printf("0- Sair\n");
	printf("\nDigite sua opção: ");
	scanf("%d", &op);
	return op;
}//fim menu
//-----------------------------
int main(){
	setlocale(LC_ALL, "Portuguese");
	tBanda banda[10];
	char nome[40], genero[40];
	int op, num_banda, op_a;
	do{
		op = menu();
		switch(op){
			case 1: cadastrarBanda(banda);
			 break;
			case 2: listarBanda(banda);
			 break;
			case 3: printf("\n1- Salvar em arquivo .txt");
			        printf("\n2- Salvar em arquivo .dat");
			        printf("\nDigite sua opção: ");
			        scanf("%d", &op_a);
			        if(op_a == 1) salvaArquivoTexto(banda);
			        else if(op_a == 2) salvaArquivoBinario(banda); 
			 break;
			case 4: printf("\n1- Carregar arquivo .txt");
			        printf("\n2- Carregar arquivo .dat");
			        printf("\nDigite sua opção: ");
			        scanf("%d", &op_a);
			        if(op_a == 1) carregaArquivoTexto(banda);
			        else if(op_a == 2) carregaArquivoBinario(banda);
			 break; 
			case 5: printf("\nNome da banda para busca: ");
			        fflush(stdin); gets(nome);
			        if(buscaNome(banda, nome) == 0) printf("\nBanda não encontrada!");
			 break; 
			case 6: printf("\nNome do gênero para busca: ");
			        fflush(stdin); gets(genero);
                    if(buscaGenero(banda, genero) == 0) printf("\nBanda não encontrada!");
             break;      
            case 7: printf("\nDigite o número da banda a ser deletada: ");
					scanf("%d", &num_banda);    
					deletarBanda(banda, num_banda);
			 break;  
			case 8: printf("\nDigite o número da banda a ser alterada: ");
					scanf("%d", &num_banda);    
					alterarBanda(banda, num_banda);
			 break;   
			case 0: printf("\nPrograma finalizado com sucesso!");
			 break;
			default: printf("\nOpcão inválida!");
		}//fim switch
		getch(); //pausa
		system("cls"); //limpatela
	}while(op != 0);
}//fim main
