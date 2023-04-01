#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No
{
    int valor;
    struct No *proximo;
    struct No *anterior;
} No;

No *cabeca = NULL;
No *fim = NULL;
void menu()
{
    printf("1 - Adicionar um novo elemento\n");
    printf("2 - Imprimir a lista\n");
    printf("3 - Ordenar por Selection Sort\n");
    printf("0 - Sair\n");
}
void imprimir()
{
    No *inicio = cabeca;
    while (inicio != NULL)
    {
        printf("%d ->  ", inicio->valor);
        inicio = inicio->proximo;
    }
    printf("NULL");
    printf("\n\n");
}
void inserir(int valor)
{
    No *Novo = new No;
    if (cabeca == NULL)
    {   
        Novo->proximo = NULL;
        Novo->anterior = NULL;
        Novo->valor = valor;
        cabeca = Novo;
        fim = Novo;
        return;
    }
    Novo->valor = valor;
    Novo->proximo = cabeca;
    Novo->anterior = NULL;
    cabeca->anterior = Novo;
    cabeca = Novo;
}
void imprimir_inverso()
{
    No *aux = fim;
    while (aux != NULL)
    {
        printf("%d ->  ", aux->valor);
        aux = aux->anterior;
    }
    printf("NULL");
    printf("\n\n");
}
void troca(No *elem1, No *elem2)
{
    if (cabeca == NULL || elem1 == NULL || elem2 == NULL)
    {
        return;
    }
    if (elem2 == fim)
        fim = elem1;

    if (cabeca == elem1)
    {
        cabeca = elem2;
    }
    else if (cabeca == elem2)
    {
        cabeca = elem1;
    }

    if (elem1->anterior != NULL)
    {
        elem1->anterior->proximo = elem2;
    }
    else
    {
        cabeca = elem2;
    }

    if (elem2->anterior != NULL)
    {
        elem2->anterior->proximo = elem1;
    }
    else
    {
        cabeca = elem1;
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
            if (menor->valor > aux->valor)
            {
                menor = aux;
            }
            aux = aux->proximo;
        }
        if (menor != inserir)
        {
            troca(inserir, menor);
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
            srand(time(NULL));
            int num;
            for (int i = 0; i < 100; i++)
            {
                num = rand() % 10;
                inserir(num);
            }
            break;
        case 2:
            printf("a partir da cabeca\n");
            imprimir();
            printf("a partir do fim\n");
            imprimir_inverso();
            break;
        case 3:
            selection_sort();
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    return 0;
}
