#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No
{
    char nome[50];
    char cpf[12];
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
void imprimir_lista(lista *lst)
{
    No *aux = lst->cabeca;
    while (aux != NULL)
    {
        printf("Nome: %s CPF: %s Data do Evento: %s\n", aux->nome, aux->cpf, aux->data);
        aux = aux->proximo;
    }
    printf("\n\n");
}
void ler_info(No *Novo)
{
    fflush(stdin);
    printf("\nDigite o nome: ");
    scanf("%[^\n]s", Novo->nome);
    printf("\nDigite o CPF: ");
    fflush(stdin);
    scanf("%[^\n]s", Novo->cpf);
    printf("\nDigite a data do evento (DD/MM/AAAA): ");
    fflush(stdin);
    scanf("%[^\n]s", Novo->data);
    printf("\n");
}
No *novo_no()
{
    No *Novo = (No *)malloc(sizeof(No));
    ler_info(Novo);
    return Novo;
}
void inserir_inicio(lista *lst, No *Novo)
{
    if ((lst == NULL) || (Novo == NULL))
        return;
    if (lst->tamanho == 0)
    {
        lst->cabeca = Novo;
        lst->fim = Novo;
        lst->tamanho = 1;
        Novo->proximo = NULL;
        return;
    }
    No *aux = lst->cabeca;
    while (aux != NULL)
    {
        if ((strcmp(aux->cpf, Novo->cpf) == 0) && (strcmp(aux->data, Novo->data) == 0))
        {
            printf("Esse cpf ja possui um ingresso pra essa mesma data\n");
            return;
        }
        aux = aux->proximo;
    }
    Novo->proximo = lst->cabeca;
    lst->cabeca = Novo;
    lst->tamanho++;
}
void buscar_ingresso_cpf(lista *lst)
{
    char cpf[20];
    printf("Insira o CPF a ser procurado: ");
    scanf("%s", cpf);
    printf("\n");
    No *aux = lst->cabeca;
    int cont = 0;
    while (aux != NULL)
    {
        if (strcmp(aux->cpf, cpf) == 0)
        {
            printf("Nome: %s CPF: %s Data do Evento: %s\n", aux->nome, aux->cpf, aux->data);
            cont = 1;
        }
        aux = aux->proximo;
    }
    if (cont != 1)
    {
        printf("Nenhum ingresso encontrado para esse CPF\n");
    }
    printf("\n");
}
void buscar_ingresso_data(lista *lst)
{
    char data[20];
    printf("Insira a data a ser procurada: ");
    scanf("%s", data);
    printf("\n");
    No *aux = lst->cabeca;
    int cont = 0;
    while (aux != NULL)
    {
        if (strcmp(aux->data, data) == 0)
        {
            printf("Nome: %s CPF: %s Data do Evento: %s\n", aux->nome, aux->cpf, aux->data);
            cont = 1;
        }
        aux = aux->proximo;
    }
    if (cont != 1)
    {
        printf("Nenhum ingresso encontrado para essa data\n");
    }
    printf("\n");
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
            if (strcmp(aux->cpf, troca->cpf) > 0)
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

typedef struct data
{
    char data[20];
    int cont = 1;
    struct data *proximo;
} data;

typedef struct lista_data
{
    data *inicio = NULL;
    data *fim = NULL;
} lista_data;

void nova_data(lista_data *lst, No *elemento)
{
    data *novo = new data;
    lst->inicio = novo;
    lst->fim = novo;
    novo->proximo = NULL;
    strcpy(novo->data, elemento->data);
}

void procura_data(lista_data *lst, No *elemento)
{
    if (elemento == NULL)
        return;

    data *teste_data = lst->inicio;
    if (lst->inicio == NULL)
    {
        nova_data(lst,elemento);
        return;
    }

    while (teste_data != NULL)
    {
        if (strcmp(elemento->data, teste_data->data) == 0)
        {
            teste_data->cont += 1;
            return;
        }
        teste_data = teste_data->proximo;
    }
    data *novo = new data;
    lst->fim->proximo = novo;
    novo->proximo = NULL;
    lst->fim = novo;
    strcpy(novo->data, elemento->data);
}

void imprime_lista_data(lista_data *lst)
{
    data *aux = lst->inicio;
    while (aux != NULL)
    {
        printf("Para a data %s temos %d ingressos vendidos\n", aux->data, aux->cont);
        aux = aux->proximo;
    }
    printf("\n\n");
}

void encerra_vendas(lista *lst)
{
    lista_data* lista = new lista_data;
    No *comp = lst->cabeca;

    while (comp != NULL)
    {
        procura_data(lista,comp);
        comp = comp->proximo;
    }
    imprime_lista_data(lista);
    printf("\n");
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
    if (antElem != NULL)
        antElem->proximo = proxElem;

    elemento->proximo = NULL;
}
void anexar_inicio(lista *lst, lista *nova)
{
    if ((nova == NULL) || (nova->tamanho == 0) || (lst == NULL))
    {
        return;
    }
    lst->tamanho += nova->tamanho;
    nova->fim->proximo = lst->cabeca;
    lst->cabeca = nova->cabeca;
}
void anexar_fim(lista *lst, lista *nova)
{
    if ((lst == NULL) || (nova == NULL) || (nova->tamanho == 0))
    {
        return;
    }
    lst->tamanho += nova->tamanho;
    lst->fim->proximo = nova->cabeca;
    lst->fim = nova->fim;
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
        if (strcmp(pivo->data, elemento->data) > 0)
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
void menu()
{
    printf("1 - Adicionar novo ingresso\n");
    printf("2 - Procurar ingressos por CPF\n");
    printf("3 - Procurar ingressos para uma determinada data\n");
    printf("4 - Encerrar vendas\n");
    printf("0 - Sair\n");
}
void teste(lista *lst, char nome[50], char cpf[12], char data[20])
{
    No *inserir = new No;
    strcpy(inserir->nome, nome);
    strcpy(inserir->cpf, cpf);
    strcpy(inserir->data, data);
    inserir_inicio(lst, inserir);
}
int main()
{
    lista *lst = new lista;

    teste(lst, "filipe", "123321", "12/12/13");
    teste(lst, "julia", "13524635", "12/12/12");
    teste(lst, "bet", "123321", "12/12/12");
    teste(lst, "will", "135246", "12/12/15");
    teste(lst, "caua", "123321", "12/12/14");
    teste(lst, "werton", "8765", "12/12/17");
    teste(lst, "luis", "123321", "12/12/19");
    teste(lst, "fernando", "87563", "12/12/21");

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
            insertion_sort(lst);
            buscar_ingresso_cpf(lst);
            break;
        case 3:
            insertion_sort(lst);
            buscar_ingresso_data(lst);
            break;
        case 4:
            quick_sort(lst);
            imprimir_lista(lst);
            encerra_vendas(lst);
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}