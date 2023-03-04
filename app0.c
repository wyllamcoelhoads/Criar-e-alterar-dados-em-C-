#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista_aluno
{
int matricula;
char cpf[12];
char nome;
char nota_prova[5];
float nota_media;
char situacao[50];
} aluno;

void cadastra()
{
    FILE *arq_cad;
    arq_cad = fopen()
    printf("Digite o numero de matricula: \n");

}
int main(){
int op;
printf("1-Cadastra uma turma.\n");
printf("2-Consulta um aluno.\n");
printf("3-Altera dados de um aluno.\n");
printf("4-Lista dados de uma turma.\n");
printf("5-Sair.\n");
scanf("%d", &op);
switch (op){
    case 1 :
        printf("escolheu o 1\n");
        break;
    case 2 :
        printf("escolheu o 2\n");
        break;
    case 3 :
        printf("escolheu o 3\n");
        break;
    case 4 :
        printf("escolheu o 4\n");
        break;
    case 5 :
        printf("escolheu o 5\n");
        system("clear");
        break;
}

main();
}
