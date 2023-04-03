#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No
{
    char nome[50];
    struct No *proximo;
} No;
typedef struct lista
{
    No *cabeca = NULL;
    No *fim = NULL;
    int tamanho = 0;
} lista;
No *prev(lista *lst, No *referencia)
{
    if (referencia == NULL || referencia == lst->cabeca)
        return NULL;
    No *aux = lst->cabeca;
    while (aux != NULL)
    {
        if (aux->proximo == referencia)
        {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}
void imprimir(lista *lst)
{
    No *inicio = lst->cabeca;
    while (inicio != NULL)
    {
        printf("%s ->  ", inicio->nome);
        inicio = inicio->proximo;
    }
    printf("NULL");
    printf("\n\n");
}
void imprimir_inverso(lista *lst)
{
    No *aux = lst->fim;

    while (aux != NULL)
    {
        printf("%s ->  ", aux->nome);
        aux = prev(lst, aux);
    }
    printf("NULL");
    printf("\n\n");
}
void ler_nome(No *Novo)
{
    fflush(stdin);
    printf("\nDigite um nome: ");
    scanf("%[^\n]s", Novo->nome);
}
No *novo_no()
{
    No *Novo = (No *)malloc(sizeof(No));
    ler_nome(Novo);
    return Novo;
}
void anexar_inicio(lista *lst, lista *anexar)
{
    if ((lst == NULL) || (lst->tamanho == 0))
    {
        return;
    }
    lst->tamanho += anexar->tamanho;
    anexar->fim->proximo = lst->cabeca;
    lst->cabeca = anexar->cabeca;
}
void anexar_fim(lista *lst, lista *anexar)
{
    lst->tamanho += anexar->tamanho;
    lst->fim->proximo = anexar->cabeca;
    lst->fim = anexar->fim;
}
void inserir_fim(lista *lst, No *Novo)
{
    if ((lst == NULL) || (Novo == NULL))
    {
        return;
    }

    if (lst->tamanho == 0)
    {
        lst->cabeca = Novo;
        lst->fim = Novo;
        lst->tamanho = 1;
        Novo->proximo = NULL;
        return;
    }

    Novo->proximo = NULL;
    lst->fim->proximo = Novo;
    lst->fim = Novo;
    lst->tamanho++;
}
void inserir_inicio(lista *lst, No *Novo)
{
    if (lst == NULL)
        return;
    if (lst->tamanho == 0)
    {
        lst->cabeca = Novo;
        lst->fim = Novo;
        lst->tamanho = 1;
        return;
    }
    Novo->proximo = lst->cabeca;
    lst->cabeca = Novo;
    lst->tamanho++;
}
void remover(lista *lst, No *elemento)
{
    if ((lst == NULL) || (elemento == NULL) || (lst->tamanho == 0))
    {
        return;
    }

    if ((lst->cabeca == elemento) && (lst->fim == elemento))
    {
        lst->tamanho = 0;
        lst->cabeca = NULL;
        lst->fim = NULL;
        return;
    }

    lst->tamanho--;

    if (lst->cabeca == elemento)
    {
        lst->cabeca = lst->cabeca->proximo;
        elemento->proximo = NULL;
        return;
    }

    if (lst->fim == elemento)
    {
        lst->fim = prev(lst, lst->fim);
        lst->fim->proximo = NULL;
        return;
    }

    No *antElem = prev(lst, elemento);
    No *proxElem = elemento->proximo;
    antElem->proximo = proxElem;

    elemento->proximo = NULL;
}
lista *merge(lista *lst1, lista *lst2)
{
    if ((lst1 == NULL) && (lst2 == NULL))
    {
        return NULL;
    }

    if ((lst1 != NULL) && (lst2 == NULL))
    {
        return lst1;
    }

    if ((lst1 == NULL) && (lst2 != NULL))
    {
        return lst2;
    }

    lista *nova = new lista;

    while ((lst1->tamanho > 0) && (lst2->tamanho > 0))
    {
        No *nome1 = lst1->cabeca;
        No *nome2 = lst2->cabeca;
        No *elemento;
        if (strcmp(nome2->nome, nome1->nome) > 0)
        {
            elemento = lst1->cabeca;
            remover(lst1, elemento);
        }
        else
        {
            elemento = lst2->cabeca;
            remover(lst2, elemento);
        }
        inserir_fim(nova, elemento);
    }
    if (lst1->tamanho > 0)
    {
        anexar_fim(nova, lst1);
    }

    if (lst2->tamanho > 0)
    {
        anexar_fim(nova, lst2);
    }

    return nova;
}
lista *merge_sort(lista *lst)
{
    if ((lst == NULL) || (lst->tamanho == 0))
    {
        return NULL;
    }

    if (lst->tamanho == 1)
    {
        return lst;
    }

    lista *lista2 = new lista;
    int tam_metade = lst->tamanho / 2;
    No *inicio2 = lst->cabeca;
    for (int i = 0; i < tam_metade; i++)
    {
        inicio2 = inicio2->proximo;
    }

    No *fim1 = prev(lst, inicio2);
    fim1->proximo = NULL;

    lista2->cabeca = inicio2;
    lista2->fim = lst->fim;
    lista2->tamanho = lst->tamanho - tam_metade;

    lst->fim = fim1;
    lst->tamanho = tam_metade;

    lst = merge_sort(lst);

    lista2 = merge_sort(lista2);

    lista *res = merge(lst, lista2);

    return res;
}
void quick_sort(lista *lst)
{
    if ((lst == NULL) || (lst->tamanho <= 1))
    {
        return;
    }
    int metade = lst->tamanho / 2;
    No *pivo = lst->cabeca;
    for (int i = 0; i < metade; i++)
    {
        pivo = pivo->proximo;
    }

    lista menores;
    lista maiores;

    No *aux = lst->cabeca;
    No *elemento = NULL;

    while (aux != NULL)
    {
        elemento = aux;
        aux = aux->proximo;
        if (elemento == pivo)
        {
            continue;
        }
        remover(lst, elemento);
        if (strcmp(pivo->nome, elemento->nome) > 0)
        {
            inserir_inicio(&menores, elemento);
        }
        else
        {
            inserir_inicio(&maiores, elemento);
        }
    }
    quick_sort(&menores);
    anexar_inicio(lst, &menores);
    quick_sort(&maiores);
    anexar_fim(lst, &maiores);
}
void troca_insertion(lista *lst, No *aux, No *troca, No *proximo, No *anterior)
{
    if (troca == lst->fim)
    {
        lst->fim = prev(lst, troca);
    }
    if (aux == lst->cabeca)
    {
        troca->proximo = lst->cabeca;
        lst->cabeca = troca;
        anterior->proximo = proximo;
    }
    else
    {
        troca->proximo = aux;
        anterior->proximo = proximo;
        anterior = prev(lst, aux);
        if (anterior != NULL)
        {
            anterior->proximo = troca;
        }
    }
}
void insertion_sort(lista *lst)
{
    if (lst->cabeca == NULL || lst->cabeca->proximo == NULL)
        return;

    No *troca = lst->cabeca->proximo;
    No *anterior = prev(lst, troca);
    No *aux = lst->cabeca;
    No *proximo = troca->proximo;

    while (troca != NULL)
    {
        while (aux != troca)
        {
            if (strcmp(aux->nome, troca->nome) > 0)
            {
                troca_insertion(lst, aux, troca, proximo, anterior);
                break;
            }
            aux = aux->proximo;
        }
        troca = proximo;
        aux = lst->cabeca;
        anterior = prev(lst, troca);
        if (troca != NULL)
            proximo = troca->proximo;
    }
}
void troca_proximo(lista *lst, No *aux)
{
    No *temp = aux->proximo;
    aux->proximo = temp->proximo;
    temp->proximo = aux;
    if (aux->proximo == lst->fim)
    {
        lst->fim = aux;
    }
    if (aux == lst->cabeca)
    {
        lst->cabeca = temp;
    }
    else
    {
        No *anterior = lst->cabeca;
        while (anterior->proximo != aux)
        {
            anterior = anterior->proximo;
        }
        anterior->proximo = temp;
    }
}
void bubble_sort(lista *lst)
{
    int cont_troca;
    No *aux = NULL;
    No *ultimo = NULL;
    if ((lst->cabeca == NULL) || (lst->cabeca->proximo == NULL))
        return;
    do
    {
        cont_troca = 0;
        aux = lst->cabeca;
        while (aux->proximo != ultimo)
        {
            if (strcmp(aux->nome, aux->proximo->nome) > 0)
            {
                troca_proximo(lst, aux);
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
int length(lista *lst)
{
    No *aux = lst->cabeca;
    int cont = 0;
    while (aux != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    return cont;
}
void swap(lista *lst, No *cel1, No *cel2)
{
    if ((cel1 == NULL) || (cel2 == NULL))
        return;

    No *ant1 = NULL;
    No *ant2 = NULL;

    No *tmp = NULL;
    if (cel1 == lst->fim)
    {
        lst->fim = cel2;
    }
    else if (cel2 == lst->fim)
    {
        lst->fim = cel1;
    }
    if ((lst->cabeca == cel2) || (cel2->proximo == cel1))
    {
        tmp = cel2;
        cel2 = cel1;
        cel1 = tmp;
    }

    if (lst->cabeca != cel1)
    {
        ant1 = prev(lst, cel1);
    }

    ant2 = prev(lst, cel2);

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

        if (lst->cabeca == cel1)
        {
            lst->cabeca = cel2;
        }
    }
}
No *pos(lista *lst, int p)
{
    No *aux = lst->cabeca;
    int cont = 0;
    while (aux != NULL)
    {
        if (cont == p)
        {
            return aux;
        }
        aux = aux->proximo;
        cont++;
    }
    return NULL;
}
void shuffle(lista *lst)
{
    int size = length(lst);
    for (int i = 0; i < size; i++)
    {
        No *cel1 = pos(lst, rand() % size);
        No *cel2 = pos(lst, rand() % size);
        swap(lst, cel1, cel2);
    }
}
void selection_sort(lista *lst)
{
    if ((lst->cabeca == NULL) || (lst->cabeca->proximo == NULL))
        return;

    No *menor, *inserir = lst->cabeca;
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
            swap(lst, inserir, menor);
            inserir = menor;
        }
        inserir = inserir->proximo;
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
    printf("7 - Ordenar por Quick Sort\n");
    printf("8 - Ordenar por Merge Sort\n");
    printf("0 - Sair\n");
}
int main()
{
    lista *lst = new lista;
    int opcao;
    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserir_inicio(lst, novo_no());
            break;
        case 2:
            imprimir(lst);
            break;
        case 3:
            shuffle(lst);
            break;
        case 4:
            bubble_sort(lst);
            break;
        case 5:
            selection_sort(lst);
            break;
        case 6:
            insertion_sort(lst);
            break;
        case 7:
            quick_sort(lst);
            break;
        case 8:
            lst = merge_sort(lst);
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}