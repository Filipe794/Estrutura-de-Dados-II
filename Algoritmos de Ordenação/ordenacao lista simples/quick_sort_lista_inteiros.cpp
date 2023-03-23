#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No
{
    int conteudo;
    struct No *seg;
} No;

No *cabeca = NULL;

No *prev(No *referencia)
{
    if (referencia == NULL || referencia == cabeca)
        return NULL;
    No *aux = cabeca;
    while (aux->seg != referencia)
    {
        aux = aux->seg;
    }
    return aux;
}
void gera_num(No *Novo)
{
    Novo->conteudo = rand() % 11;
    while (Novo->conteudo == 0)
    {
        Novo->conteudo = rand() % 11;
    }
}
void inserir()
{
    No *Novo = (No *)malloc(sizeof(No));
    gera_num(Novo);
    Novo->seg = cabeca;
    cabeca = Novo;
}
void imprimir()
{
    No *aux = cabeca;
    while (aux != NULL)
    {
        printf("%d ->  ", aux->conteudo);
        aux = aux->seg;
    }
    printf("\n\n");
}
// No *ultimo(){
//     No *aux = cabeca;
//     while (aux->seg != NULL)
//     {
//         aux = aux->seg;
//     }
//     return aux;
// }

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        inserir();
    }
    imprimir();
    // quick_sort();
    imprimir();
    return 0;
}