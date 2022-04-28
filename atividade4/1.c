#include<stdio.h>
#include<stdlib.h>

typedef struct{
    char *nome;
    int idade;
    char sexo;
}pessoa;

void mostraStruct1(void *arg);

int main(void){
    pessoa *ptrPessoa;
    ptrPessoa = malloc(sizeof(pessoa));
    ptrPessoa->nome = "Leonardo Amaral";
    ptrPessoa->idade = 44;
    ptrPessoa->sexo = 'M';
    mostraStruct1(ptrPessoa);
}

void mostraStruct1(void *arg){
    pessoa *ptr;
    ptr = (pessoa*) arg; //Typecastin de void para o tipo pessoa
    printf("%s - %d - %c\n", ptr->nome, ptr->idade, ptr->sexo);
}
