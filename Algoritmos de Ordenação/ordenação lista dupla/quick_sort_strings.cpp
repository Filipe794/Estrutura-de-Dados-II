#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cel
{
    char nome[30];
    cel *ant = NULL;
    cel *prox = NULL;
} celula;

typedef struct list
{
    celula *inicio = NULL;
    celula *fim = NULL;
    int tamanho = 0;
} lista;

void anexar_inicio(lista *nova, lista *lista)
{
    if ((lista == NULL) || (lista->tamanho == 0))
    {
        return;
    }
    nova->tamanho += lista->tamanho;
    nova->inicio->ant = lista->fim;
    lista->fim->prox = nova->inicio;
    nova->inicio = lista->inicio;
}
void anexar_fim(lista *nova, lista *lista)
{
    if ((lista == NULL) || (lista->tamanho == 0))
    {
        return;
    }
    nova->tamanho += lista->tamanho;
    nova->fim->prox = lista->inicio;
    lista->inicio->ant = nova->fim;
    nova->fim = lista->fim;
}
void remover(lista *lst, celula *elemento)
{
    if ((lst == NULL) || (elemento == NULL) || (lst->tamanho == 0))
    {
        return;
    }

    if ((lst->inicio == elemento) && (lst->fim == elemento))
    {
        lst->tamanho = 0;
        lst->inicio = NULL;
        lst->fim = NULL;
    }

    lst->tamanho--;

    if (lst->inicio == elemento)
    {
        lst->inicio = lst->inicio->prox;
        lst->inicio->ant = NULL;
        elemento->prox = NULL;
        return;
    }

    if (lst->fim == elemento)
    {
        lst->fim = lst->fim->ant;
        lst->fim->prox = NULL;
        elemento->ant = NULL;
        return;
    }

    celula *antElem = elemento->ant;
    celula *proxElem = elemento->prox;
    antElem->prox = proxElem;
    proxElem->ant = antElem;

    elemento->ant = NULL;
    elemento->prox = NULL;
}
void inserir_inicio(lista *lst, celula *elemento)
{
    if ((lst == NULL) || (elemento == NULL))
    {
        return;
    }

    if (lst->tamanho == 0)
    {
        lst->inicio = elemento;
        lst->fim = elemento;
        lst->tamanho = 1;
        elemento->ant = NULL;
        elemento->prox = NULL;
        return;
    }

    elemento->ant = NULL;
    elemento->prox = lst->inicio;
    lst->inicio->ant = elemento;
    lst->inicio = elemento;
    lst->tamanho++;
}
void inserir_fim(lista *lst, celula *elemento)
{
    if ((lst == NULL) || (elemento == NULL))
    {
        return;
    }

    if (lst->tamanho == 0)
    {
        lst->inicio = elemento;
        lst->fim = elemento;
        lst->tamanho = 1;
        elemento->ant = NULL;
        elemento->prox = NULL;
        return;
    }

    elemento->prox = NULL;
    elemento->ant = lst->fim;
    lst->fim->prox = elemento;
    lst->fim = elemento;
    lst->tamanho++;
}
void quick_sort(lista *lst)
{
    if ((lst == NULL) || (lst->tamanho <= 1))
    {
        return;
    }
    int metade = lst->tamanho / 2;
    celula *pivo = lst->inicio;
    for (int i = 0; i < metade; i++)
    {
        pivo = pivo->prox;
    }

    lista menores;
    lista maiores;

    celula *aux = lst->inicio;
    celula *elemento = NULL;

    while (aux != NULL)
    {
        elemento = aux;
        aux = aux->prox;
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
void imprimir(lista *lst)
{
    celula *aux = lst->inicio;
    while (aux != NULL)
    {
        printf("%s -> ", aux->nome);
        aux = aux->prox;
    }
    printf("NULL\n");
}
void imprimir_inverso(lista *lst)
{
    if (lst == NULL)
    {
        return;
    }
    celula *aux = lst->fim;
    while (aux != NULL)
    {
        printf("%s -> ", aux->nome);
        aux = aux->ant;
    }
    printf("NULL\n");
}
void menu()
{
    printf("1 - Adicionar um novo elemento\n");
    printf("2 - Imprimir a lista\n");
    printf("3 - Ordenar Lista\n");
    printf("0 - Sair\n");
}
celula *cria_elemento()
{
    celula *elemento = new celula;
    elemento->ant = NULL;
    elemento->prox = NULL;
    fflush(stdin);
    printf("\nDigite um nome: ");
    scanf("%[^\n]s", elemento->nome);
    return elemento;
}
int main()
{
    int opcao;
    lista *lst = new lista;
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
            quick_sort(lst);
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}