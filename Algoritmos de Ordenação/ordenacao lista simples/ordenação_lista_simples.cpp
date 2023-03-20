#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No
{
    char nome[30];
    struct No *proximo;
} No;

No *cabeca = NULL;

void imprimir()
{
    No *inicio = cabeca;
    while (inicio != NULL)
    {
        printf("%s ->  ", inicio->nome);
        inicio = inicio->proximo;
    }
    printf("\n\n");
}
void ler_nome(No *Novo)
{
    printf("\nDigite um nome: ");
    scanf("%s", Novo->nome);
}
void inserir()
{
    No *Novo = (No *)malloc(sizeof(No));
    ler_nome(Novo);
    Novo->proximo = cabeca;
    cabeca = Novo;
}
void menu()
{
    printf("1 - Adicionar um novo elemento\n");
    printf("2 - Imprimir a lista\n");
    printf("3 - Embaralhar a lista\n");
    printf("4 - Ordenar por Bubble Sort\n");
    printf("5 - Ordenar por Selection Sort\n");
    printf("6 - Ordenar por Insertion Sort\n");
    printf("0 - Sair\n");
}
No *prev(No *referencia)
{
    if (referencia == NULL || referencia == cabeca)
        return NULL;
    No *aux = cabeca;
    while (aux->proximo != referencia)
    {
        aux = aux->proximo;
    }
    return aux;
}
void selection_sort()
{
    if (cabeca == NULL || cabeca->proximo == NULL)
        return;

    No *menor, *inserir = cabeca;
    No *aux = menor->proximo;

    while (inserir->proximo != NULL)
    {
        menor = inserir;
        aux = inserir->proximo;

        while (aux != NULL)
        {
            if (strcmp(menor->nome, aux->nome) > 0)
            {
                menor = aux;
            }
            aux = aux->proximo;
        }
        if (menor != inserir)
        {
            No *anterior_menor = prev(menor);
            anterior_menor->proximo = menor->proximo;
            if (inserir == cabeca)
            {
                cabeca = menor;
                menor->proximo = inserir;
            }
            else
            {
                No *anterior_inserir = prev(inserir);
                anterior_inserir->proximo = menor;
                menor->proximo = inserir;
            }
            inserir = menor;
        }
        inserir = inserir->proximo;
    }
}
void troca_insertion(No *aux, No *troca, No *proximo, No *anterior)
{
    if (aux == cabeca)
    {
        troca->proximo = cabeca;
        cabeca = troca;
        anterior->proximo = proximo;
    }
    else
    {
        troca->proximo = aux;
        anterior->proximo = proximo;
        anterior = prev(aux);
        if (anterior != NULL)
        {
            anterior->proximo = troca;
        }
    }
}
void insertion_sort()
{
    if (cabeca == NULL || cabeca->proximo == NULL)
        return;

    No *troca = cabeca->proximo;
    No *anterior = prev(troca);
    No *aux = cabeca;
    No *proximo = troca->proximo;

    while (troca != NULL)
    {
        while (aux != troca)
        {
            imprimir();
            if (strcmp(aux->nome, troca->nome) > 0)
            {
                troca_insertion(aux, troca, proximo, anterior);
                break;
            }
            aux = aux->proximo;
        }
        troca = proximo;
        aux = cabeca;
        anterior = prev(troca);
        if (troca != NULL)
            proximo = troca->proximo;
    }
}
void troca_proximo(No *aux)
{
    No *temp = aux->proximo;
    aux->proximo = temp->proximo;
    temp->proximo = aux;

    if (aux == cabeca)
    {
        cabeca = temp;
    }
    else
    {
        No *anterior = cabeca;
        while (anterior->proximo != aux)
        {
            anterior = anterior->proximo;
        }
        anterior->proximo = temp;
    }
}
void bubble_sort()
{
    int cont_troca;
    No *aux = NULL;
    No *ultimo = NULL;
    // ultimo é o ponteiro para o ultimo elemento da lista
    // ele sera sempre atualizado ao final do laço mais exterior para limitar a repetição e não comparar com elementos já ordernados
    if (cabeca == NULL || cabeca->proximo == NULL)
        return;
    do
    {
        cont_troca = 0;
        aux = cabeca;
        while (aux->proximo != ultimo)
        {
            if (strcmp(aux->nome, aux->proximo->nome) > 0)
            {
                // troca os ponteiros dos nós
                troca_proximo(aux);
                cont_troca = 1;
            }
            else
            {
                aux = aux->proximo;
            }
        }
        ultimo = aux;
    } while (cont_troca != 0);
}
int main()
{
    int opcao;
    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserir();
            break;
        case 2:
            imprimir();
            break;
        case 3:
            // embaralhar();
            break;
        case 4:
            bubble_sort();
            break;
        case 5:
            selection_sort();
            break;
        case 6:
            insertion_sort();
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}