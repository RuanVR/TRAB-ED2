#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30

//  STRUCTS

// Estrutura da pessoa
typedef struct pessoa
{
    char nome[128];
    char sexo;
    int idade;
    int musica[5];
} Pessoa;

// No Lista
typedef struct noLista
{
    Pessoa pessoa;
    struct NoLista *prox;
} NoLista;

// Lista dos votos das música
typedef struct musica
{
    int musica;
    int votos;
} Musica;

// Declaração das funções
Pessoa *registraPessoa(Musica *musicaTop, Musica *musicaM_Mais20, Musica *musicaM_Menos20, Musica *musicaF_Mais20, Musica *musicaF_Menos20);
void iniciaLista(NoLista **l);
void inserirElemento(NoLista **l, Pessoa p);
void imprimeLista(NoLista **l);
void imprimeMusica(Musica *m);
void iniciaMusica(Musica *m);
void ordenaMusicas(Musica *musicaTop, Musica *musicaM_Mais20, Musica *musicaM_Menos20, Musica *musicaF_Mais20, Musica *musicaF_Menos20);
void ordenaLista(NoLista **completa, NoLista **l, Musica *m);
void inserirVoto(Musica *m, int id);
void shellSort(Musica *m);
void gravaPesquisa(NoLista **l);
void gravaCategoria(FILE **arq, NoLista **l);
void gravaMusica(FILE **arq, Musica *m);
Pessoa *registraPessoaGravada(NoLista **l);

// Main
int main()
{
    // CRIAÇÃO DE LISTAS DE TODAS AS CATEGORIAS
    NoLista *lista_completa, *listaM_Mais20, *listaM_Menos20, *listaF_Mais20, *listaF_Menos20;
    iniciaLista(&lista_completa);
    iniciaLista(&listaM_Mais20);
    iniciaLista(&listaM_Menos20);
    iniciaLista(&listaF_Mais20);
    iniciaLista(&listaF_Menos20);

    // CRIAÇÃO DAS LISTAS AUXILIARES DE CADA CATEGORIA
    NoLista *M_Mais20, *M_Menos20, *F_Mais20, *F_Menos20;
    iniciaLista(&M_Mais20);
    iniciaLista(&M_Menos20);
    iniciaLista(&F_Mais20);
    iniciaLista(&F_Menos20);

    // CRIAÇÃO DE MUSICAS DE TODAS AS CATEGORIAS
    Musica musicaTop[N], musicaM_Mais20[N], musicaM_Menos20[N], musicaF_Mais20[N], musicaF_Menos20[N];
    iniciaMusica(musicaTop);
    iniciaMusica(musicaM_Mais20);
    iniciaMusica(musicaM_Menos20);
    iniciaMusica(musicaF_Mais20);
    iniciaMusica(musicaF_Menos20);

    // CRIAÇÃO DE FILES PARA LEITURA

    
    registraPessoaGravada(&lista_completa);

    // CRIAÇÃO DOS FILES PARA GRAVAÇÃO
    FILE *M_Mais = fopen("arquivos/homem_mais.txt", "w");
    FILE *M_Menos = fopen("arquivos/homem_menos.txt", "w");
    FILE *F_Mais = fopen("arquivos/mulher_mais.txt", "w");
    FILE *F_Menos = fopen("arquivos/mulher_menos.txt", "w");
    FILE *Top = fopen("arquivos/top.txt", "w");

    int escolha = -1;
    while (escolha != 0)
    {
        printf("\nEscolha a opcao desejada:\n"
               "1 - Inserir nova pessoa\n"
               "2 - Imprimir lista de musicas em ordem de popularidade\n"
               "3 - Imprimir pessoas MENORES ou IGUAL de 20 do sexo M que mencionaram em PRIMEIRO lugar uma das top 3 musicas de sua categoria\n"
               "4 - Imprimir pessoas MAIORES de 20 do sexo M que mencionaram em PRIMEIRO lugar uma das top 3 musicas de sua categoria\n"
               "5 - Imprimir pessoas MENORES ou IGUAL de 20 do sexo F que mencionaram em PRIMEIRO lugar uma das top 3 musicas de sua categoria\n"
               "6 - Imprimir pessoas MAIORES de 20 do sexo F que mencionaram em PRIMEIRO lugar uma das top 3 musicas de sua categoria\n"
               "0 - Sair do programa\n\n");
        scanf("%d", &escolha);
        printf("\n");
        switch (escolha)
        {
        case 0:

            ordenaLista(&M_Menos20, &listaM_Menos20, musicaM_Menos20);
            ordenaLista(&M_Mais20, &listaM_Mais20, musicaM_Mais20);
            ordenaLista(&F_Menos20, &listaF_Menos20, musicaF_Menos20);
            ordenaLista(&F_Mais20, &listaF_Mais20, musicaF_Mais20);

            gravaPesquisa(&lista_completa);
            gravaCategoria(M_Mais, &listaM_Mais20);
            gravaCategoria(M_Menos, &listaM_Menos20);
            gravaCategoria(F_Mais, &listaF_Mais20);
            gravaCategoria(F_Menos, &listaF_Menos20);
            gravaMusica(Top, musicaTop);

            printf("\nPrograma encerrado!");
            break;

        case 1:;
            Pessoa *registro = registraPessoa(musicaTop, musicaM_Mais20, musicaM_Menos20, musicaF_Mais20, musicaF_Menos20);

            if (registro->idade <= 20 && registro->sexo == 'm')
            {
                inserirElemento(&M_Menos20, *registro);
            }

            if (registro->idade > 20 && registro->sexo == 'm')
            {
                inserirElemento(&M_Mais20, *registro);
            }

            if (registro->idade <= 20 && registro->sexo == 'f')
            {
                inserirElemento(&F_Menos20, *registro);
            }

            if (registro->idade > 20 && registro->sexo == 'f')
            {
                inserirElemento(&F_Mais20, *registro);
            }

            ordenaMusicas(musicaTop, musicaM_Mais20, musicaM_Menos20, musicaF_Mais20, musicaF_Menos20);

            inserirElemento(&lista_completa, *registro);

            break;

        case 2:;
            printf("As musicas mais populares entre todas as pesquisas sao: \n\n");
            imprimeMusica(musicaTop);
            break;

        case 3:;

            ordenaLista(&M_Menos20, &listaM_Menos20, musicaM_Menos20);
            imprimeMusica(musicaM_Menos20);
            printf("\nPessoas que selecionaram como 1 alguma musica do top 3 dessa categoria: \n\n");
            imprimeLista(&listaM_Menos20);
            break;

        case 4:;

            ordenaLista(&M_Mais20, &listaM_Mais20, musicaM_Mais20);
            imprimeMusica(musicaM_Mais20);
            printf("\nPessoas que selecionaram como 1 alguma musica do top 3 dessa categoria: \n\n");
            imprimeLista(&listaM_Mais20);
            break;

        case 5:;

            ordenaLista(&F_Menos20, &listaF_Menos20, musicaF_Menos20);
            imprimeMusica(musicaF_Menos20);
            printf("\nPessoas que selecionaram como 1 alguma musica do top 3 dessa categoria: \n\n");
            imprimeLista(&listaF_Menos20);
            break;

        case 6:;

            ordenaLista(&F_Mais20, &listaF_Mais20, musicaF_Mais20);
            imprimeMusica(musicaF_Mais20);
            printf("\nPessoas que selecionaram como 1 alguma musica do top 3 dessa categoria: \n\n");
            imprimeLista(&listaF_Mais20);
            break;

        default:;
            printf("Opcao invalida, escolha novamente:\n\n");
            break;
        }
    }

    return 0;
}

// FUNÇÕES DE CRIAÇÃO/ ARMAZENAMENTO NA LISTA/ SALVAMENTO NO ARQUIVO

// Iniciador da lista
void iniciaLista(NoLista **l)
{
    *l = NULL;
}

void iniciaMusica(Musica *m)
{
    for (int i = 0; i < N; i++)
    {
        m[i].musica = i + 1;
        m[i].votos = 0;
    }
}

// Adicionando uma nova pessoa no banco de dados
Pessoa *registraPessoa(Musica *musicaTop, Musica *musicaM_Mais20, Musica *musicaM_Menos20, Musica *musicaF_Mais20, Musica *musicaF_Menos20)
{

    Pessoa *p = (Pessoa *)malloc(sizeof(Pessoa));
    int i = 1;

    printf("Digite seu nome: ");
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

                // ADICIONANDO VOTOS AS MÚSICAS

                inserirVoto(musicaTop, p->musica[i]);

                if (p->idade <= 20 && p->sexo == 'm')
                {
                    inserirVoto(musicaM_Menos20, p->musica[i]);
                }

                if (p->idade > 20 && p->sexo == 'm')
                {
                    inserirVoto(musicaM_Mais20, p->musica[i]);
                }

                if (p->idade <= 20 && p->sexo == 'f')
                {
                    inserirVoto(musicaF_Menos20, p->musica[i]);
                }

                if (p->idade > 20 && p->sexo == 'f')
                {
                    inserirVoto(musicaF_Mais20, p->musica[i]);
                }

                i++;
            }
        }
    }

    return p;
}

// Inserindo elementos na lista
void inserirElemento(NoLista **l, Pessoa p)
{

    NoLista *novo = malloc(sizeof(NoLista));
    novo->pessoa = p;

    // Inserindo elemento na lista
    novo->prox = (*l);
    (*l) = novo;
}

// INSERI VOTO NA MUSICA SELECIONADA
void inserirVoto(Musica *m, int id)
{
    for (int i = 0; i < N; i++)
    {
        if (m[i].musica == id)
        {
            m[i].votos++;
        }
    }
}

// IMPRIMINDO LISTAS DE PESSOAS
void imprimeLista(NoLista **l)
{
    NoLista *a = *l;
    if (*l != NULL)
    {
        for (a; a != NULL; a = a->prox)
        {
            printf("%s\n", a->pessoa.nome);
        }
    }
    else
    {
        printf("Lista Vazia\n");
    }
}

// IMPRIMINDO LISTA DE MUSICAS

void imprimeMusica(Musica *m)
{

    Musica *auxiliar = m;

    for (int i = 0; i < N; i++)
    {
        if (auxiliar[i].votos > 0)
        {
            printf("Musica: %d  ", auxiliar[i].musica);
            printf("Votos: %d \n\n", auxiliar[i].votos);
        }
    }
}

void shellSort(Musica *m)
{
    int h = 1, i, j;
    Musica temp;

    while (h < N)
    {
        h = h * 3 + 1;
    }

    while (h > 1)
    {
        h = (h - 1) / 3;
        for (int i = h; i < N; i++)
        {
            temp = m[i];
            j = i - h;
            while (j >= 0 && temp.votos > m[j].votos)
            {
                m[j + h] = m[j];
                j -= h;
            }
            if (j != (i - h))
            {
                m[j + h] = temp;
            }
        }
    }
}

void ordenaMusicas(Musica *musicaTop, Musica *musicaM_Mais20, Musica *musicaM_Menos20, Musica *musicaF_Mais20, Musica *musicaF_Menos20)
{
    shellSort(musicaTop);
    shellSort(musicaM_Mais20);
    shellSort(musicaM_Menos20);
    shellSort(musicaF_Mais20);
    shellSort(musicaF_Menos20);
}

void ordenaLista(NoLista **completa, NoLista **l, Musica *m)
{
    // Da um free na lista caso ela esteja com elementos
    if (*l != NULL)
    {
        NoLista *temp, *p = *l;
        for (p; p != NULL; p = temp)
        {
            temp = p->prox;
            free(p);
        }
        (*l) = NULL;
        free(temp);
    }

    NoLista *temp = *completa;

    for (temp; temp != NULL; temp = temp->prox)
    {
        if (temp->pessoa.musica[0] == m[0].musica || temp->pessoa.musica[0] == m[1].musica || temp->pessoa.musica[0] == m[2].musica)
        {
            inserirElemento(l, temp->pessoa);
        }
    }
}

// ARQUIVOS

// Grava pesquisa completa
void gravaPesquisa(NoLista **l)
{

    NoLista *temp = *l;

    FILE *pesquisa_completa = fopen("arquivos/pesquisa_completa.txt", "w");
    for (temp; temp != NULL; temp = temp->prox)
    {
        fprintf(pesquisa_completa, "%s\t%c\t%d\t%d %d %d %d %d\n", temp->pessoa.nome, temp->pessoa.sexo, temp->pessoa.idade, temp->pessoa.musica[0], temp->pessoa.musica[1], temp->pessoa.musica[2], temp->pessoa.musica[3], temp->pessoa.musica[4]);
    }
}

// Grava cada categoria

void gravaCategoria(FILE **arq, NoLista **l)
{
    NoLista *temp = *l;

    for (temp; temp != NULL; temp = temp->prox)
    {
        fprintf(arq, "%s\n", temp->pessoa.nome);
    }
}

// Grava top musica

void gravaMusica(FILE **arq, Musica *m)
{
    for (int i = 0; i < N; i++)
    {
        if (m[i].votos > 0)
        {
            fprintf(arq, "%d\t%d\n", m[i].musica, m[i].votos);
        }
    }
}

// Le pessoa grava e adiciona
Pessoa *registraPessoaGravada(NoLista **l)
{

    Pessoa *p = (Pessoa *)malloc(sizeof(Pessoa));
    int i = 1;
    FILE *pessoaGravada = fopen("arquivo/pesquisa_completa.txt", "r");

    while (fscanf(pessoaGravada, "%[^\n]\t%c\t%d\t%d %d %d %d %d\n", p->nome, &p->sexo, &p->idade, &p->musica[0], &p->musica[1], &p->musica[2], &p->musica[3], &p->musica[4]) != EOF)
    {
       inserirElemento(&l, *p);
    }

    fclose(pessoaGravada);
}