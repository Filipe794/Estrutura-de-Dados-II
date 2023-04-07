#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No
{
    char nome[50];
    char cpf[30];
    char data[20];
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
    if ((referencia == NULL) || (referencia == lst->cabeca) || (lst == NULL))
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
    No *aux = lst->cabeca;
    while (aux != NULL)
    {
        printf("Nome: %s CPF: %s Data do Evento: %s\n", aux->nome, aux->cpf, aux->data);
        aux = aux->proximo;
    }
    printf("\n\n");
}
