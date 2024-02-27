#include <stdio.h>
#include <string.h>

typedef struct{
	char nome[40];
	double consumo, tempo;
}tEletro;

int qtd=0;
//----------------------------
void cadastra(tEletro eletro[]){
	if(qtd!=100){
	   printf("\n*** Cadastro de eletrodomestico *** \n");
	   printf("Eletrodomestico: "); 
	   fflush(stdin); gets(eletro[qtd].nome);
	   printf("Consumo: "); 
	   scanf("%f", &eletro[qtd].consumo);
	   printf("Tempo: "); 
	   scanf("%f", &eletro[qtd].tempo);
	   printf("\nEletrodomestico cadastrado com sucesso!");
	   qtd++;
    } else printf("Limite de eletrodomesticos esgotado!");	
}//fim cadastra
//----------------------------------------
void listaEletro(tEletro eletro[]){
	int i;
	for(i=0; i<qtd; i++){
	 printf("\n *** Dados do eletrodomestico %d ***\n", i+1);
	 printf("Eletrodomestico: %s\n", eletro[i].nome);
	 printf("Consumo: %.2f\n", eletro[i].consumo);
	 printf("Tempo medio de uso diario: %.2f\n", eletro[i].tempo);
	}
}//fim listaEletro
//-----------------------------------------
double consumoEstimado(tEletro eletro[], double valorKWh){
	int i;
	double cons_e, cons_t_d;
	
	for(i=0; i<qtd; i++){
		cons_e+=(eletro[i].consumo*eletro[i].tempo*valorKWh);
		cons_t_d+=cons_e;
		cons_e=0;
	}//fim for
	printf("\nConsumo total diario em Reais: %.2f", cons_t_d);
	printf("\nConsumo total mensal em Reais: %.2f", cons_t_d*30);

}//fim consumoEstimado
//-----------------------------------------------------

void maiorConsumo(tEletro eletro[], double consumo){
	int i;
	
    for(i=0; i<qtd; i++){
       if(eletro[i].consumo > consumo){
          printf("\n%s", eletro[i].nome);
	   }//fim if   
    }//fim for
}//fim maiorConsumo
//----------------------------------------
void salvaArquivo(tEletro eletro[]){
	FILE *arq;
   arq=fopen("eletrodomesticos.dat","wb");
   fwrite(&eletro[0], sizeof(tEletro), qtd, arq);
   printf("\nDados salvos com sucesso!");
   fclose(arq);
}//fim salvaArquivo
//-----------------------------------------
void carrega(tEletro eletro[]){
	   FILE *arq = fopen("eletrodomesticos.dat","rb");
	   while(fread(&eletro[qtd], sizeof(tEletro), 1, arq)>0){
	   	qtd++;
	   }// fim while
	   fclose(arq);
	   printf("\nDados carregados com sucesso!");
}// fim carrega
//-----------------------------------------------------

int menu(){
	int op;
	printf("\t\t*** IFSULDEMINAS - Campus Machado ***\n");
	printf("1 - Cadastrar novo eletrodomestico\n");
	printf("2 - Listar todos eletrodomesticos\n");
	printf("3 - Consumo estimado\n");
	printf("4 - Eletrodomesticos que gastam mais que X\n");
	printf("5 - Salvar eletrodomesticos\n");
	printf("6 - Carregar eletrodomesticos\n");
	printf("0 - Sair\n");
	printf("\nDigite sua opcao: "); 
	scanf("%d",&op);
	return op;
}//fim menu
//-----------------------------
int main(){
	tEletro eletro[100];
	int op;
	float valorKwH, consumo;
    do{
    	op=menu();
    	switch(op){
    		case 1: cadastra(eletro);
    		break;
    		case 2: listaEletro(eletro);
    		break;
    		case 3: printf("\nInforme o valor do kW-h em Reais: ");
    		        scanf("%f", &valorKwH);
			        consumoEstimado(eletro, valorKwH);
			break;	
			case 4: printf("\nInforme um valor de consumo: ");
			        scanf("%f", &consumo);
			        maiorConsumo(eletro, consumo);
			break;
    		case 5: salvaArquivo(eletro);
			break;
			case 6: carrega(eletro);
			break;

			case 0: printf("\nPrograma finalizado com sucesso!");
			break;
			default: printf("\nOpcao invalida");
		}// fim switch
    	getch();
    	system("cls");
	}while(op!=0);
	return 0;
}//fim main
