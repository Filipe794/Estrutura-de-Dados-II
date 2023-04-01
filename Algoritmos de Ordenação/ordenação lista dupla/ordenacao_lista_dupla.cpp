#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No
{
    char nome[50];
    struct No *proximo;
    struct No *anterior;
} No;

No *cabeca = NULL;
No *fim = NULL;

void imprimir()
{
    No *inicio = cabeca;
    while (inicio != NULL)
    {
        printf("%s ->  ", inicio->nome);
        inicio = inicio->proximo;
    }
    printf("NULL");
    printf("\n\n");
}
void ler_nome(No *Novo)
{
    printf("\nDigite um nome: ");
    scanf("%s", Novo->nome);
}
void inserir()
{
    No *Novo = new No;
    if (cabeca == NULL)
    {
        ler_nome(Novo);
        cabeca = Novo;
        fim = Novo;
        return;
    }
    ler_nome(Novo);
    Novo->proximo = cabeca;
    Novo->anterior = cabeca->anterior;
    cabeca->anterior = Novo;
    cabeca = Novo;
}
void imprimir_inverso()
{
    No *aux = fim;
    while (aux != NULL)
    {
        printf("%s ->  ", aux->nome);
        aux = aux->anterior;
    }
    printf("NULL");
    printf("\n\n");
}
void troca_posicao(No *elem1, No *elem2)
{
   if (cabeca == NULL || elem1 == NULL || elem2 == NULL) {
        return;
    }

    if(elem2 == fim) fim = elem1;

    if (cabeca == elem1) {
        cabeca = elem2;
    } else if (cabeca == elem2) {
        cabeca = elem1;
    }

    if (elem1->anterior != NULL) {
        elem1->anterior->proximo = elem2;
    }

    if (elem2->anterior != NULL) {
        elem2->anterior->proximo = elem1;
    }

    No* temp = elem1->anterior;
    elem1->anterior = elem2->anterior;
    elem2->anterior = temp;

    temp = elem1->proximo;
    elem1->proximo = elem2->proximo;
    elem2->proximo = temp;

    if (elem1->proximo != NULL) {
        elem1->proximo->anterior = elem1;
    }

    if (elem2->proximo != NULL) {
        elem2->proximo->anterior = elem2;
    }
    
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
        anterior = aux->anterior;
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
    No *anterior = troca->anterior;
    No *aux = cabeca;
    No *proximo = troca->proximo;

    while (troca != NULL)
    {
        while (aux != troca)
        {
            if (strcmp(aux->nome, troca->nome) > 0)
            {
                troca_posicao(aux, troca);
                break;
            }
            aux = aux->proximo;
        }
        troca = proximo;
        aux = cabeca;
        anterior = troca->anterior;
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
                troca_posicao(aux, aux->proximo);
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
            troca_posicao(inserir, menor);
            inserir = menor;
        }
        inserir = inserir->proximo;
    }
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
            printf("a partir da cabeca\n");
            imprimir();
            printf("a partir do fim\n");
            imprimir_inverso();
            break;
        case 3:
            bubble_sort();
            break;
        case 4:
            selection_sort();
            break;
        case 5:
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