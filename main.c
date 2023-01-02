#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30

//Objeto pessoa
typedef struct pessoa
{
    char nome[128]; 
    char sexo;
    int idade;
    int musicas[5];
} Pessoa;




int main()
{  
    int escolha = 1;


    while (escolha = 1)
    {
        printf("Escolha a opcao desejada:\n"
        "1 - Inserir nova pessoa\n"
        "2- Imprimir lista de musicas em ordem de popularidade"
        "3- ");
    }
    
    return 0;
}

//FUNÇÕES

//Adicionando uma nova pessoa no banco de dados
void registraPessoa(){

    Pessoa *p = (Pessoa*) malloc(sizeof(Pessoa));
    int i = 1;

    printf("Digite seu nome: ");
    scanf(" %[^\n]", p->nome);

    printf("Digite sua idade\n");
    scanf("%d", p->idade);

    //Confirma se o sexo é valido
    while (i == 1)
    {
        printf("Digite seu sexo: m - masculino | f - feminino\n");
        scanf(" %[^\n]", p->sexo);

        if (p->sexo == 'm' || p->sexo == 'f')
        {
            i = 0;
        } 
        else
        {
            printf("Sexo invalido, digite novamente\n");
        }     
    }
    
}