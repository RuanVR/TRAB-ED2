#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30

// Objeto pessoa
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
    int escolha = -1;
    Pessoa *p;

    while (escolha != 0)
    {
        printf("Escolha a opcao desejada:\n"
               "1 - Inserir nova pessoa\n"
               "2 - Imprimir lista de musicas em ordem de popularidade\n"
               "0 - Sair do programa\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            printf("\n\nPrograma encerrado!");
            break;

        case 1:
            p = registraPessoa();
            break;

        default:
            printf("Opcao invalida, escolha novamente:\n\n");
            break;
        }
    }

    return 0;
}

// FUNÇÕES

// Adicionando uma nova pessoa no banco de dados
Pessoa *registraPessoa()
{

    Pessoa *p = (Pessoa *)malloc(sizeof(Pessoa));
    int i = 1;

    printf("\nDigite seu nome: ");
    scanf(" %[^\n]", p->nome);

    printf("Digite sua idade: ");
    scanf("%d", &p->idade);

    // Confirma se o sexo é valido
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

    // Insere musicas
    printf("Digite em ordem suas musicas preferidas: \n");
    while (i < 5)
    {
        printf("%d: ", i + 1);
        scanf("%d", &p->musica[i]);

        // Verificando se a musica é valida entre as existentes
        if (p->musica[i] < 1 || p->musica[i] > 30)
        {
            printf("Musica invalida, digite novamente\n\n");
        }
        else
        {
            // Verificando se a musica já está registrada na lista da pessoa
            int sec = 0;
            if (i > 0)
            {
                for (int j = 0; j < i; j++)
                {
                    if (p->musica[i] == p->musica[j])
                    {
                        printf("Musica ja selecionada, informe uma nova\n");
                        sec = 1;
                    }
                }
                
            }   
            if (sec == 0)
            {
                i++; 
            }   
        }
    }

    printf("Pessoa registrada\n\n");

    return p;
}