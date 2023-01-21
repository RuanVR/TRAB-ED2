#include <stdio.h>
#include <stdlib.h>

#include "pessoa.h"

// FUNÇÕES DE CRIAÇÃO/ ARMAZENAMENTO NA LISTA/ SALVAMENTO NO ARQUIVO

// Iniciador da lista
void iniciaLista(NoLista **l)
{
    *l = NULL;
}

// Inserindo elementos na lista
void inserirElemento(NoLista **l, Pessoa *p)
{

    NoLista *novo = (NoLista*) malloc(sizeof(NoLista));
    novo->pessoa = p;

    //Inserindo elemento na pilha
    novo->prox = *l;
    *l = novo;

    printf("Pessoa inserida\n\n");
}

// Imprimindo lista
void imprimeLista(NoLista **l)
{
    NoLista *a = *l;

    for (a; a != NULL; a = a->prox)
    {
        Pessoa *imp = a->pessoa;
        printf("%s\n", imp->nome);
    }
}

//Salvando elementos no arquivo 
void salvarArquivo(NoLista**l){
    NoLista *temp = *l;
    FILE *arquivo = fopen("arquivo.txt", "w");
    Pessoa *p = temp->pessoa;

    while (temp != NULL)
    {
        fprint(arquivo, "$s\t%s\t%d\t%d\n", p->nome, p->sexo, p->idade, p->musica);
    }
    
}