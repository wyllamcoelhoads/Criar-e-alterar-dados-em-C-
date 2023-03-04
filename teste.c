#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif
int main(){
FILE *arq;
char tsaida[50];
if((arq = fopen("arquivoteste.txt","r")) == NULL){
    printf("ERRO na abertura do arquivo!!\n");
    exit(1);
}    
fgets(tsaida,50,arq);

printf("foi lida a mensagem: %s\n", tsaida);
fclose(arq);
}
