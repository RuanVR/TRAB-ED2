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
    int musica[5];
} Pessoa;

Pessoa *registraPessoa();


int main()
{  
    int escolha = 1;
    Pessoa *p;

    while (escolha = 1)
    {
        printf("Escolha a opcao desejada:\n"
        "1 - Inserir nova pessoa\n"
        "2- Imprimir lista de musicas em ordem de popularidade"
        "3- \n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            printf("teste");
            p = registraPessoa();
            break;
        
        default:
            printf("Opcao invalida, escolha novamente:\n\n");
            break;
        }
    }
    
    return 0;
}

//FUNÇÕES

//Adicionando uma nova pessoa no banco de dados
Pessoa *registraPessoa(){

    Pessoa *p = (Pessoa*) malloc(sizeof(Pessoa));
    int i = 1;

    printf("Digite seu nome: ");
    scanf(" %[^\n]\n", p->nome);

    printf("Digite sua idade: ");
    scanf("%d\n", &p->idade);

    //Confirma se o sexo é valido
    while (i == 1)
    {
        printf("Digite seu sexo: m - masculino | f - feminino\n");
        scanf(" %c", &p->sexo);

        if (p->sexo == 'm' || p->sexo == 'f')
        {
            i = 0;
        } 
        else
        {
            printf("Sexo invalido, digite novamente\n\n");
        }     
    }

    //Inserer musicas
    printf("Digite em ordem suas musicas preferidas: \n");
    while (i<5)
    {
        printf("%d: ", i+1);
        scanf("%d", &p->musica[i]);

        //Verificando se a musica é valida entre as existentes
        if(p->musica[i] < 1 || p->musica[i] > 30){
            printf("Musica invalida, digite novamente\n\n");
        }
        else
        {
            i++;
        }  

        //Verificando se a musica já está registrada na lista
    }
    
    printf("Pessoa registrada\n\n");

    return p;
}