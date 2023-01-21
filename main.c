#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pessoa.h"
#include "arquivo.h"

#define N 30

// Main
int main()
{
    NoLista *lista;
    iniciaLista(&lista);

    int escolha = -1;
    while (escolha != 0)
    {
        printf("\nEscolha a opcao desejada:\n"
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
            inserirElemento(&lista, registraPessoa());
            salvarArquivo(&lista);
            break;

        case 2:
            imprimeLista(&lista);
            break;

        default:
            printf("Opcao invalida, escolha novamente:\n\n");
            break;
        }
    }

    return 0;
}