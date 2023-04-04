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
typedef struct list
{
    No *cabeca = NULL;
    No *fim = NULL;
    int tamanho = 0;
} lista;

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
void ler_nome(No *Novo)
{
    fflush(stdin);
    printf("\nDigite um nome: ");
    scanf("%[^\n]s", Novo->nome);
}
No *cria_elemento()
{
    No *elemento = new No;
    elemento->anterior = NULL;
    elemento->proximo = NULL;
    fflush(stdin);
    printf("\nDigite um nome: ");
    scanf("%[^\n]s", elemento->nome);
    return elemento;
}
void inserir_inicio(lista *lst, No *elemento)
{
    if ((lst == NULL) || (elemento == NULL))
    {
        return;
    }

    if (lst->tamanho == 0)
    {
        lst->cabeca = elemento;
        lst->fim = elemento;
        lst->tamanho = 1;
        elemento->anterior = NULL;
        elemento->proximo = NULL;
        return;
    }

    elemento->anterior = NULL;
    elemento->proximo = lst->cabeca;
    lst->cabeca->anterior = elemento;
    lst->cabeca = elemento;
    lst->tamanho++;
}
void imprimir_inverso(lista *lst)
{
    No *aux = lst->fim;
    while (aux != NULL)
    {
        printf("%s ->  ", aux->nome);
        aux = aux->anterior;
    }
    printf("NULL");
    printf("\n\n");
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
        lst->cabeca->anterior = NULL;
        elemento->proximo = NULL;
        return;
    }

    if (lst->fim == elemento)
    {
        lst->fim = lst->fim->anterior;
        lst->fim->proximo = NULL;
        elemento->anterior = NULL;
        return;
    }

    No *antElem = elemento->anterior;
    No *proxElem = elemento->proximo;
    antElem->proximo = proxElem;
    proxElem->anterior = antElem;

    elemento->anterior = NULL;
    elemento->proximo = NULL;
}
void inserir_fim(lista *lst, No *elemento)
{
    if ((lst == NULL) || (elemento == NULL))
    {
        return;
    }

    if (lst->tamanho == 0)
    {
        lst->cabeca = elemento;
        lst->fim = elemento;
        lst->tamanho = 1;
        elemento->anterior = NULL;
        elemento->proximo = NULL;
        return;
    }

    elemento->proximo = NULL;
    elemento->anterior = lst->fim;
    lst->fim->proximo = elemento;
    lst->fim = elemento;
    lst->tamanho++;
}
void troca_posicao(lista *lst, No *elem1, No *elem2)
{
    if ((lst->cabeca == NULL) || (elem1 == NULL) || (elem2 == NULL))
    {
        return;
    }

    if (elem2 == lst->fim)
        lst->fim = elem1;

    if (lst->cabeca == elem1)
    {
        lst->cabeca = elem2;
    }
    else if (lst->cabeca == elem2)
    {
        lst->cabeca = elem1;
    }

    if (elem1->anterior != NULL)
    {
        elem1->anterior->proximo = elem2;
    }

    if (elem2->anterior != NULL)
    {
        elem2->anterior->proximo = elem1;
    }

    No *temp = elem1->anterior;
    elem1->anterior = elem2->anterior;
    elem2->anterior = temp;

    temp = elem1->proximo;
    elem1->proximo = elem2->proximo;
    elem2->proximo = temp;

    if (elem1->proximo != NULL)
    {
        elem1->proximo->anterior = elem1;
    }

    if (elem2->proximo != NULL)
    {
        elem2->proximo->anterior = elem2;
    }
}
void menu()
{
    printf("1 - Adicionar um novo elemento\n");
    printf("2 - Imprimir a lista\n");
    printf("3 - Ordenar por Bubble Sort\n");
    printf("4 - Ordenar por Selection Sort\n");
    printf("5 - Ordenar por Insertion Sort\n");
    printf("6 - Ordenar por Quick Sort\n");
    printf("7 - Ordenar por Merge Sort\n");
    printf("0 - Sair\n");
}
void troca_insertion(lista *lst, No *aux, No *troca)
{
    No *prox_troca = troca->proximo;
    No *ant_troca = troca->anterior;
    No *prox_aux = aux->proximo;
    No *ant_aux = aux->anterior;

    if (troca == lst->fim)
        lst->fim = troca->anterior;

    // atualizando ponteiros dos nós aux e troca
    if (aux == lst->cabeca)
    {
        troca->anterior = NULL;
        troca->proximo = aux;
        aux->anterior = troca;
        lst->cabeca = troca;
    }
    else
    {
        troca->anterior = aux->anterior;
        troca->proximo = aux;
        ant_aux->proximo = troca;
        aux->anterior = troca;
    }
    // atualizando os nós adjacentes à aux e troca
    if (prox_troca != NULL)
    {
        prox_troca->anterior = ant_troca;
    }
    if (ant_troca != NULL)
    {
        ant_troca->proximo = prox_troca;
    }
}
void insertion_sort(lista *lst)
{
    if ((lst->cabeca == NULL) || (lst->cabeca->proximo == NULL))
        return;

    No *troca = lst->cabeca->proximo;
    No *aux = lst->cabeca;
    No *proximo = troca->proximo;

    while (troca != NULL)
    {
        while (aux != troca)
        {
            if (strcmp(aux->nome, troca->nome) > 0)
            {
                troca_insertion(lst, aux, troca);
                break;
            }
            aux = aux->proximo;
        }
        troca = proximo;
        aux = lst->cabeca;
        if (troca != NULL)
            proximo = troca->proximo;
    }
}
void troca_proximo(lista *lst, No *aux)
{
    No *temp = aux->proximo;
    aux->proximo = temp->proximo;
    temp->proximo = aux;

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
                troca_posicao(lst, aux, aux->proximo);
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
            troca_posicao(lst, inserir, menor);
            inserir = menor;
        }
        inserir = inserir->proximo;
    }
}
void anexar_fim(lista *nova, lista *lista)
{
    nova->tamanho += lista->tamanho;
    nova->fim->proximo = lista->cabeca;
    lista->cabeca->anterior = nova->fim;
    nova->fim = lista->fim;
}
lista *merge(lista *lista1, lista *lista2)
{
    if ((lista1 == NULL) && (lista2 == NULL))
    {
        return NULL;
    }

    if ((lista1 != NULL) && (lista2 == NULL))
    {
        return lista1;
    }

    if ((lista1 == NULL) && (lista2 != NULL))
    {
        return lista2;
    }

    lista *nova = new lista;

    while ((lista1->tamanho > 0) && (lista2->tamanho > 0))
    {
        No *nome1 = lista1->cabeca;
        No *nome2 = lista2->cabeca;
        No *elemento;
        if (strcmp(nome2->nome, nome1->nome) > 0)
        {
            elemento = lista1->cabeca;
            remover(lista1, elemento);
        }
        else
        {
            elemento = lista2->cabeca;
            remover(lista2, elemento);
        }
        inserir_fim(nova, elemento);
    }
    if (lista1->tamanho > 0)
    {
        anexar_fim(nova, lista1);
    }

    if (lista2->tamanho > 0)
    {
        anexar_fim(nova, lista2);
    }

    return nova;
}
lista *merge_sort(lista *lista1)
{
    if ((lista1 == NULL) || (lista1->tamanho == 0))
    {
        return NULL;
    }

    if (lista1->tamanho == 1)
    {
        return lista1;
    }

    lista *lista2 = new lista;
    int tam_metade = lista1->tamanho / 2;
    No *inicio2 = lista1->cabeca;
    for (int i = 0; i < tam_metade; i++)
    {
        inicio2 = inicio2->proximo;
    }

    No *fim1 = inicio2->anterior;
    fim1->proximo = NULL;
    inicio2->anterior = NULL;

    lista2->cabeca = inicio2;
    lista2->fim = lista1->fim;
    lista2->tamanho = lista1->tamanho - tam_metade;

    lista1->fim = fim1;
    lista1->tamanho = tam_metade;

    lista1 = merge_sort(lista1);

    lista2 = merge_sort(lista2);

    lista *res = merge(lista1, lista2);

    return res;
}
void anexar_inicio(lista *nova, lista *lista)
{
    if ((lista == NULL) || (lista->tamanho == 0))
    {
        return;
    }
    nova->tamanho += lista->tamanho;
    nova->cabeca->anterior = lista->fim;
    lista->fim->proximo = nova->cabeca;
    nova->cabeca = lista->cabeca;
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
            inserir_inicio(lst, cria_elemento());
            break;
        case 2:
            printf("a partir da cabeca\n");
            imprimir(lst);
            printf("a partir do fim\n");
            imprimir_inverso(lst);
            break;
        case 3:
            bubble_sort(lst);
            break;
        case 4:
            selection_sort(lst);
            break;
        case 5:
            insertion_sort(lst);
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}