#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No
{
    int conteudo;
    struct No *proximo;
} No;

No *cabeca = NULL;

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
    Novo->proximo = cabeca;
    cabeca = Novo;
}
void imprimir()
{
    No *aux = cabeca;
    while (aux != NULL)
    {
        printf("%d ->  ", aux->conteudo);
        aux = aux->proximo;
    }
    printf("\n\n");
}
No *ultimo(){
    No *aux = cabeca;
    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }
    return aux;
}

void quick_sort(){
    //escolher o pivo:
    //  primeiro elemento, elemento do meio ou um aleatorio?
    // separar a lista a partir desse pivo
    //      if(cabeca!=pivo){
    //          aux = cabeca;
    //      }else{
    //          
    //      }
    //      percorrer de:
    //          aux ate prev(anterior)
    //          pivo->proximo ate ultimo(cabeca)
    // recursividade passando as duas partes da lista
}

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