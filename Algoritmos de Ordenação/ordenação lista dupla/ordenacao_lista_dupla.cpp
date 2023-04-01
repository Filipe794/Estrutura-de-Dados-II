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
    printf("\n\n");
}

// void troca(No *elem1, No *elem2)
// {
//     if ((elem1 == NULL) || (elem2 == NULL))
//         return;
//     if(elem2 == fim) fim = elem1;
//     No *ant_elem1 = elem1->anterior;
//     No *prox_elem1 = elem1->proximo;
//     No *prox_elem2 = elem2->proximo;
//     No *ant_elem2 = elem2->anterior;
//     if (elem1 == cabeca)
//     {
//         ant_elem2->proximo = elem1;
//         prox_elem2->anterior = elem1;
//         elem2->anterior = ant_elem1;
//         elem1->anterior = ant_elem2;
//         elem1->proximo = prox_elem2;
//         elem2->proximo = prox_elem1;
//         prox_elem1->anterior = elem2;
//         cabeca = elem2;
//         return;
//     }
//     if(elem1->proximo == elem2){
//         ant_elem1->proximo = elem2;
//         elem2->anterior = ant_elem1;
//         elem2->proximo = elem1;
//         elem1->anterior = elem2;
//         elem1->proximo = prox_elem2;
//         prox_elem2->anterior = elem1;
//         return;
//     }
//     ant_elem1->proximo = elem2;
//     ant_elem2->proximo = elem1;
//     prox_elem2->anterior = elem1;
//     prox_elem1->anterior = elem2;
//     elem2->proximo = prox_elem1;
//     elem1->proximo = prox_elem2;
//     elem1->anterior = ant_elem2;
//     elem2->anterior = ant_elem1;
// }

void swap(No *cel1, No *cel2)
{
    if ((cel1 == NULL) || (cel2 == NULL))
        return;

    No *ant1 = NULL;
    No *ant2 = NULL;

    No *tmp = NULL;

    if ((cabeca == cel2) || (cel2->proximo == cel1))
    {
        tmp = cel2;
        cel2 = cel1;
        cel1 = tmp;
    }

    if (cabeca != cel1)
    {
        ant1 = cel1->anterior;
    }

    ant2 = cel2->anterior;

    if (cel1 != cel2)
    {
        tmp = cel2->proximo;

        if (ant1 != NULL)
        {
            ant1->proximo = cel2;
        }

        if (cel1 != ant2)
        {
            ant2->proximo = cel1;
            cel2->proximo = cel1->proximo;

            if (cel2->proximo == cel1)
            {
                cel1->proximo = cel2;
            }
            else
            {
                cel1->proximo = tmp;
            }
        }
        else
        {
            cel2->proximo = cel1;
            cel1->proximo = tmp;
        }

        if (cabeca == cel1)
        {
            cabeca = cel2;
        }
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
                troca_insertion(aux, troca, proximo, anterior);
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
            swap(inserir, menor);
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