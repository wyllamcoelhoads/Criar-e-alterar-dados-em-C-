#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNO 100
#define MAX_NOTAS 5

FILE *arq;
char nomearq[60];
int  num_students = 0;


void menucadastro(){
	system("cls");
	printf("\t\t|---------CADASTRO DE TURMA---------|\n");
	printf("\t\t|***********************************|\n");
}

void menualterar(){
	system("cls");
	printf("\t\t|---------ALTERAR ALUNO---------|\n");
	printf("\t\t|*******************************|\n");
}

void menulistar(){
	system("cls");
	printf("\t\t|---------LISTAR ALUNO---------|\n");
	printf("\t\t|******************************|\n");
}

void menuconsultar(){
	system("cls");
	printf("\t\t|---------CONSULTAR ALUNO---------|\n");
	printf("\t\t|*********************************|\n");
}

struct lista_aluno 
{
	char nome[50];
	int matricula;
	int id;
	char cpf[12];
	float notas[5];
	float nota_final;
	unsigned int num_faltas;
	char status[50];
}; 

struct lista_aluno aluno;



void imprimir_aluno(FILE *file) {
	//arq = fopen(nomearq,"r");
	arq = fopen(nomearq,"r");
	fread(aluno.nome, sizeof(aluno.nome), 50,arq);
    /*printf("ID: %i\n", &aluno.id);
    printf("Code: %s\n", &aluno.cpf);
    printf("Name: %s\n", aluno.nome);
    printf("Nota: ");
    for (int i = 0; i < 5; i++) {
    printf("%1.f ", &aluno.notas[i]);
    }*/
    //printf("\nNota final: %d\n", &aluno.nota_final);
    //printf("Numero de faltas %i\n", &aluno.num_faltas);
    //printf("Status: %s\n", &aluno.status);
   /* printf("ID	CPF	NOME\n");
   	while (fscanf(arq, "%i %s %s", aluno.id, aluno.nome, aluno.cpf) != EOF) {
        printf("%i %s %s\n", &aluno.id,&aluno.nome, &aluno.cpf);
   		printf("%i\t%s\t%s\n", aluno.id, aluno.cpf, aluno.nome);
   }*/
   
    system("pause");
    
    
     //   lista_aluno aluno;
    printf("\nDI\tCPF\t\tNOME\t\t\t\t\tNOTAS\tAvg\tFALTAS\tStatus\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_students; i++) {
        
        for (int j = 0; j < 5; j++) {
            printf("%.1f ", aluno.notas[j]);
        }
        printf("\t%.1f\t", aluno.nota_final);
        printf("%i\t\t%s\n", aluno.num_faltas, aluno.status);
    }
    fclose(arq);
}

void consulta_aluno(){
	int mat;
	while(1){
	menuconsultar();
	printf("Informe o nome do arquivo da turma (fim para sair): \n");
	scanf("%s", nomearq);
	arq = fopen(nomearq,"r");
	if (strcmp(nomearq, "fim") == 0) {
		system("cls");
		printf("Sistema encerrado...\n");
		system("pause");
		exit(1);
        
	}else if (!arq) {
		system("cls");
		printf("ERRO:: O arquivo %s não existe!! \n", nomearq);
		system("pause");
		consulta_aluno();
	}
	system("cls");
   	printf("Arquivo aberto!!!\n");
   	system("pause");
   	system("cls");
        while (fread(&aluno.id, sizeof(int), 1, arq) == 1) {
            num_students += fread(&aluno.id, sizeof(aluno.id), 1, arq);
        }
        system("cls");
        printf("%i alunos encontrados no arquivo %s.\n", num_students, nomearq);
		system("pause");
   		system("cls");
   		imprimir_aluno(arq);

   	}
   		/*while (1) {
            printf("Digite um valor de chave (ID, código, nome) para pesquisar (ou 'fim' para sair): ");
            char key[50];
            int matricula_get;
            scanf("%s%*c", key);
            if (strcmp(key, "fim") == 0) {
                break;
            }
            matricula_get = fwrite(&aluno.matricula, sizeof(int), 1, arq);
            
            printf("%s", matricula_get);
            system("pause");
            
        }*/
        fclose(arq);
	}   	



void cadastro_aluno(){
	unsigned int id;
	menucadastro();
	printf("Informe o nome do arquivo da turma: \n");
	scanf("%s", nomearq);
 	arq = fopen(nomearq,"w");
	if (!arq) 
	{
	        printf("ERRO:: Falha ao criar o arquivo: %s\n", nomearq);
	        return ;
   }
   fclose(arq);
    int num_aluno= 0;
    while (num_aluno < MAX_ALUNO){
    if(num_aluno > 0 ){
    	menucadastro();
	}
    printf("Informe o matricula do Aluno (0 para sair): \n");
    scanf("%i", &aluno.matricula);
       if (aluno.matricula == 0) {
        	system("cls");
            printf("sistema encerrado...\n");
			exit(1);
    	}else{
    
	//lista_aluno aluno;
    aluno.id += id;
    arq = fopen(nomearq,"a");
	if (!arq) 
	{
	        printf("ERRO:: Falha ao abrir o arquivo; %s\n", nomearq);
	        return ;
   }
    printf("Informe o cpf do Aluno (12 caracteres): \n");
    fflush(stdin);
    scanf("%s", aluno.cpf);
    
    printf("Informe o nome do Aluno: \n");
    fflush(stdin);
    scanf(" %[^\n]s", aluno.nome);
    printf("Informe as 5 notas do aluno (dé enter entre elas): \n");
    for (int i = 0; i < 5; i++) {
    		fflush(stdin);
            scanf("%f", &aluno.notas[i]);
            aluno.nota_final += aluno.notas[i];
    }
    aluno.nota_final /= 5;
    printf("Informe o numero de faltas do aluno: \n");
    fflush(stdin);
    scanf("%u", &aluno.num_faltas);
    
    
    	if (aluno.num_faltas <= (128*0.25) && aluno.nota_final >= 6.0) {
            strcpy(aluno.status, "Aprovado");
        } else if (aluno.num_faltas > (128*0.25) && aluno.nota_final >= 6.0) {
            strcpy(aluno.status, "Reprovado por faltas");
        } else if (aluno.num_faltas <= (128*0.25) && aluno.nota_final < 6.0) {
            strcpy(aluno.status, "Reprovado por notas");
        } else {
            strcpy(aluno.status, "Reprovado por faltas e por nota");
    }
    
      //  print_student(&aluno);
       // fwrite(&aluno, sizeof(lista_aluno), 1, arq);
      /* fread(&aluno.nome, sizeof(char), 100,arq);
       fread(&aluno.cpf, sizeof(char), 100,arq);
       fread(&aluno.nota_final, sizeof(float), 100,arq);
       fread(&aluno.num_faltas, sizeof(unsigned int), 100,arq);*/
       
    fprintf(arq, "%i\t", aluno.matricula);
	fprintf(arq, "%s\t", aluno.nome);
    fprintf(arq, "%s\t", aluno.cpf);
    fprintf(arq, "%f\t", aluno.nota_final);
    fprintf(arq, "%u\t", aluno.num_faltas);
    fprintf(arq, "%s\t\n", aluno.status);	
    
        num_aluno++;
    
    fclose(arq);
    system("cls");
    printf("Aluno salvo com sucesso...\n\n\n\n");
    system("pause");
    system("cls");
	}	    
}

}

int main(){
	int op;
	char cnum[] = {0};
	printf("\t\t|-----------MENU PRINCIPAL-------|\n");
	printf("\t\t| 1 - Cadastrar uma turma.       |\n");
	printf("\t\t| 2 - Consultar um Aluno.        |\n");
	printf("\t\t| 3 - Alterar dados de um aluno. |\n");
	printf("\t\t| 4 - Listar dados de uma turma. |\n");
	printf("\t\t| 5 - Sair.                      |\n");
	printf("\t\t|********************************|\n");
	scanf("%s%*c", cnum);
	op = strtol(cnum, NULL, 10);
	while (op != 6 )
	{
		switch (op){
			case 1:
				system("cls");
				cadastro_aluno();
			break;
			case 2:
				system("cls");
				consulta_aluno();
			break;
			case 3:
				system("cls");
				menualterar();				
			break;
			case 4:
				system("cls");
				menulistar();
			break;
			case 5:
				printf("Sistema encerrado...\n");
				system("pause");
				return 0;	
			break;
			default:
				system("cls");
				printf("\tERRO:: Escolha outra alternativa...\n");
				system("\n");
				system("\n");
				system("pause");
				system("cls");
				main();
				fflush(stdin);
				
		}
			
	}		
}
