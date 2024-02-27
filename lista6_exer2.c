#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct{
	char nome[40];
	int matricula;
	float n1, n2, n3;
}tAluno;

int qtd=0;
//-----------------------------
void cadastrarAluno(tAluno aluno[]){
	if(qtd!=30){
	   printf("\n*** Cadastro de Alunos *** \n");
	   printf("Nome do aluno: "); 
	   fflush(stdin); gets(aluno[qtd].nome);
	   printf("Matrícula: "); 
	   scanf("%d", &aluno[qtd].matricula);
	   printf("Nota 1: "); 
	   scanf("%f", &aluno[qtd].n1);
	   printf("Nota 2: "); 
	   scanf("%f", &aluno[qtd].n2);
	   printf("Nota 3: "); 
	   scanf("%f", &aluno[qtd].n3);
	   printf("\nAluno cadastrado com sucesso!");
	   qtd++;
    } else printf("Limite de alunos esgotado!");
}//fim cadastrarAluno
//-----------------------------
void listarAluno(tAluno aluno[]){
	int i;
	if(qtd == 0) printf("\nNenhum aluno cadastrado!");
	else
	   for(i=0; i<qtd; i++){
		   printf("\n*** Dados do %dº aluno ***\n", i+1);
		   printf("Nome do aluno: %s\n", aluno[i].nome);
		   printf("Matrícula: %d\n", aluno[i].matricula);
		   printf("Nota 1: %.1f\n", aluno[i].n1);
		   printf("Nota 2: %.1f\n", aluno[i].n2);
		   printf("Nota 3: %.1f\n", aluno[i].n3);
		   mediaAluno(aluno, i);
	   }//fim for
}//fim listarAluno
//-----------------------------
void salvaArquivoBinario(tAluno aluno[]){
	FILE *arq;
	int i;
	if(qtd==0) printf("\nNenhuma banda cadastrada!");
	else{
	arq=fopen("alunos.dat", "wb");
	   for(i=0; i<qtd; i++) fwrite(&aluno[i], sizeof(tAluno), 1, arq);  
	   printf("\nAlunos salvos com sucesso!");	
	   fclose(arq);
	}//fim else
}//fim salvaArquivoBinario
//-----------------------------
void carregaArquivoBinario(tAluno aluno[]){
	FILE *arq;
	arq=fopen("alunos.dat", "rb");
	if(arq==NULL) //arquivo nao existe
	   printf("\nArquivo não encontrado!");
	else{
	while(fread(&aluno[qtd], sizeof(tAluno), 1, arq) > 0)
	   qtd++;
	printf("\nAlunos carregados com sucesso!"); 
	fclose(arq);
	}//fim else   
}//fim carregaArquivoBinario
//-----------------------------
int buscaNome(tAluno aluno[], char nome[]){
	int i;
	float media;
	for(i=0; i<qtd; i++){
		if(strcmp(nome, aluno[i].nome) == 0){
		   printf("\n*** Dados do %dº aluno ***\n", i+1);
		   printf("Nome do aluno: %s\n", aluno[i].nome);
		   printf("Matrícula: %d\n", aluno[i].matricula);
		   printf("Nota 1: %.1f\n", aluno[i].n1);
		   printf("Nota 2: %.1f\n", aluno[i].n2);
		   printf("Nota 3: %.1f\n", aluno[i].n3);
		   mediaAluno(aluno, i);
		   return 1;
		}//fim if
	}//fim for
	return 0;
}//fim buscaNome
//-----------------------------
int buscaMatricula(tAluno aluno[], int matricula){
	int i, c=0;
	  for(i=0; i<qtd; i++){
	  	if(matricula == aluno[i].matricula){
	  	   printf("\n*** Dados do %dº aluno ***\n", i+1);
		   printf("Nome do aluno: %s\n", aluno[i].nome);
		   printf("Matrícula: %d\n", aluno[i].matricula);
		   printf("Nota 1: %.1f\n", aluno[i].n1);
		   printf("Nota 2: %.1f\n", aluno[i].n2);
		   printf("Nota 3: %.1f\n", aluno[i].n3);
		   mediaAluno(aluno, i);
		   c++;
		  }// fim if
	  }// fim for
	  return c;
}//fim buscaMatricula
//-----------------------------
void mediaAluno(tAluno aluno[], int n){
	float media;
	media=((aluno[n].n1+aluno[n].n2+aluno[n].n3)/3);
	if(media >= 6) printf("Situação: Aprovado\n");
	else printf("Situação: Reprovado\n");
}//fim mediaAluno
//-----------------------------
void maiorMedia(tAluno aluno[]){
	int i, c=0;
	float media, maior_media;
	if(qtd==0) printf("\nNenhum aluno cadastrado!");
	else{
	for(i=0; i<qtd; i++){
	   if(i==0) maior_media=((aluno[i].n1+aluno[i].n2+aluno[i].n3)/3);
	   media=((aluno[i].n1+aluno[i].n2+aluno[i].n3)/3);
	   if(media > maior_media){
	      maior_media=media;
	      c=i;
	   }//fim if
	   media=0;
	}//fim for
	printf("\n*** Dados do aluno ***\n");
	printf("Nome do aluno: %s\n", aluno[c].nome);
	printf("Matrícula: %d\n", aluno[c].matricula);
	printf("Nota 1: %.1f\n", aluno[c].n1);
	printf("Nota 2: %.1f\n", aluno[c].n2);
	printf("Nota 3: %.1f\n", aluno[c].n3);
	printf("Média: %.1f\n", maior_media);
	mediaAluno(aluno, c);
	}//fim else
}//fim mediaAluno
//-----------------------------
int menu(){
	int op;
	printf("\t\t**** IFSULDEMINAS - Campus Machado ****\n");
	printf("1- Cadastrar novo aluno\n");
	printf("2- Listar todos alunos\n");
	printf("3- Salvar alunos\n");
	printf("4- Carregar alunos\n");
	printf("5- Buscar aluno por nome\n");
	printf("6- Buscar aluno por matricula\n");
	printf("7- Aluno com maior média geral\n");
	printf("0- Sair\n");
	printf("\nDigite sua opção: ");
	scanf("%d", &op);
	return op;
}//fim menu
//-----------------------------
int main(){
	setlocale(LC_ALL, "Portuguese");
	tAluno aluno[30];
	char nome[40];
	int op, matricula;
	do{
		op = menu();
		switch(op){
			case 1: cadastrarAluno(aluno);
			 break;
			case 2: listarAluno(aluno);
			 break;
			case 3: salvaArquivoBinario(aluno); 
			 break;
			case 4: carregaArquivoBinario(aluno);
			 break; 
			case 5: printf("\nNome do aluno para busca: ");
			        fflush(stdin); gets(nome);
			        if(buscaNome(aluno, nome) == 0) printf("\nAluno não encontrado!");
			 break; 
			case 6: printf("\nMatricula do aluno para busca: ");
			        scanf("%d", &matricula);
                    if(buscaMatricula(aluno, matricula) == 0) printf("\nAluno não encontrado!");
             break;  
			case 7: maiorMedia(aluno);
             break;           
			case 0: printf("\nPrograma finalizado com sucesso!");
			 break;
			default: printf("\nOpcão inválida!");
		}//fim switch
		getch(); //pausa
		system("cls"); //limpatela
	}while(op != 0);
}//fim main
