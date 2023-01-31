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
// void salvarArquivo(NoLista **l);
void iniciaMusica(Musica *m);
void ordenaMusicas(Musica *musicaTop, Musica *musicaM_Mais20, Musica *musicaM_Menos20, Musica *musicaF_Mais20, Musica *musicaF_Menos20);
void ordenaLista(NoLista **completa, NoLista **l, Musica *m);
void imprimeTop3(Musica *m);
void inserirVoto(Musica *m, int id);

void shellSort(Musica *m);

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

    int escolha = -1;
    while (escolha != 0)
    {
        printf("\nEscolha a opcao desejada:\n"
               "1 - Inserir nova pessoa\n"
               "2 - Imprimir lista de musicas em ordem de popularidade\n"
               "3 - Imprimir as pessoas MENORES ou IGUAL de 20 do sexo M que mencionaram em PRIMEIRO lugar uma das top 3 musicas de sua categoria\n"
               "4 - Imprimir as pessoas MAIORES de 20 do sexo M que mencionaram em PRIMEIRO lugar uma das top 3 musicas de sua categoria\n"
               "5 - Imprimir as pessoas MENORES ou IGUAL de 20 do sexo F que mencionaram em PRIMEIRO lugar uma das top 3 musicas de sua categoria\n"
               "6 - Imprimir as pessoas MAIORES de 20 do sexo F que mencionaram em PRIMEIRO lugar uma das top 3 musicas de sua categoria\n"
               "0 - Sair do programa\n\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            printf("\n\nPrograma encerrado!");
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

            imprimeMusica(musicaTop);
            break;

        case 3:;

            ordenaLista(&M_Menos20, &listaM_Menos20, musicaM_Menos20);
            imprimeTop3(musicaM_Menos20);
            imprimeLista(&listaM_Menos20);
            break;

        case 4:;

            ordenaLista(&M_Mais20, &listaM_Mais20, musicaM_Mais20);
            imprimeTop3(musicaM_Mais20);
            imprimeLista(&listaM_Mais20);
            break;

        case 5:;

            ordenaLista(&F_Menos20, &listaF_Menos20, musicaF_Menos20);
            imprimeTop3(musicaF_Menos20);
            imprimeLista(&listaF_Menos20);
            break;

        case 6:;

            ordenaLista(&F_Menos20, &listaF_Mais20, musicaF_Mais20);
            imprimeTop3(musicaF_Mais20);
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

    //printf("Pessoa registrada\n\n");

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

    //printf("Pessoa inserida\n\n");
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
    else{
        printf("Lista Vazia");
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
            printf("Musica: %d \n", auxiliar[i].musica);
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

void ordenaMusicas(Musica *musicaTop, Musica *musicaM_Mais20, Musica *musicaM_Menos20, Musica *musicaF_Mais20, Musica *musicaF_Menos20){
    shellSort(musicaTop);
    shellSort(musicaM_Mais20);
    shellSort(musicaM_Menos20);
    shellSort(musicaF_Mais20);
    shellSort(musicaF_Menos20);
}

void ordenaLista(NoLista **completa, NoLista **l, Musica *m){
    //Da um free na lista caso ela esteja com elementos
    if (*l != NULL)
    {
        NoLista *temp, *p = l;
        for ( p; p != NULL; p = temp)
        {
            temp = p->prox;
            free(p);
        }
        (*l) = NULL;
        free(temp);
    }
    
    NoLista *temp = *completa;

    for ( temp; temp != NULL; temp = temp->prox)
    {
        if (temp->pessoa.musica[0] == m[0].musica || temp->pessoa.musica[0] == m[1].musica || temp->pessoa.musica[0] == m[2].musica)
        {   
            inserirElemento(l, temp->pessoa);
        } 
    }  
}

void imprimeTop3(Musica *m){
    printf("As top 3 musicas mais populares dessa categoria são:\n");
    printf("1- %d| ", m[1].musica);
    printf("2- %d| ", m[2].musica);
    printf("3- %d| ", m[3].musica);
}

// Salvando elementos no arquivo
/*void salvarArquivo(NoLista**l){
    NoLista *temp = *l;
    FILE *arquivo = fopen("arquivo.txt", "w");
    Pessoa *p = temp->pessoa;

    while (temp != NULL)
    {
        fprint(arquivo, "$s\t%s\t%d\t%d\n", p->nome, p->sexo, p->idade, p->musica);
    }
}*/
