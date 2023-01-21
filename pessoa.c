#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Objeto pessoa
typedef struct pessoa
{
    char nome[128];
    char sexo;
    int idade;
    int musica[5];
} Pessoa;

// Nó Lista
typedef struct noLista
{
    struct Pessoa *pessoa;
    struct noLista *prox;
} NoLista;

// Adicionando uma nova pessoa no banco de dados
Pessoa *registraPessoa()
{

    Pessoa *p = (Pessoa*)malloc(sizeof(Pessoa));
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