#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cel
{
  int num;
  cel *prox;
  cel *ant;
} celula;

typedef struct list
{
  celula *inicio = NULL;
  celula *fim = NULL;
  int tamanho = 0;
} lista;

void anexar_inicio(lista *nova, lista *lista){
  nova->tamanho += lista->tamanho;
  nova->inicio->ant = lista->fim;

}

void remover(lista *lst, celula *elemento){
  if((lst == NULL) || (elemento == NULL)|| (lst->tamanho == 0)){
    return;
  }
  lst->tamanho--;
  if((lst->inicio == elemento)&&(lst->fim == elemento)){
    lst->tamanho = 0;
    lst->inicio = NULL;
    lst->fim = NULL;
  }
  if(lst->inicio == elemento){
    lst->inicio = lst->inicio->prox;
    lst->inicio->ant = NULL;
    elemento->prox = NULL;
    return;
  }
  if(lst->inicio == elemento){
    lst->inicio = lst->inicio->prox;
  }
}

void anexar_fim(lista *lst, lista *lst_2)
{
  lst->fim->prox = lst_2->inicio;
  lst_2->inicio->ant = lst->fim;
  lst->fim = lst_2->fim;
  lst->tamanho+=lst_2->tamanho;
}

celula *remover(celula *elemento)
{
}

void quick_sort(lista *lst)
{
  if((lst == NULL) || (lst->tamanho < 2)){
    return;
  }
  int tam_metade = lst->tamanho / 2;
  celula *pivo = lst->inicio;
  for (int i = 0; i < tam_metade; i++)
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
      continue;
    remover(elemento);
  //   if (aux->num < pivo->num)
  //   {
  //     inserir_fim(&menores, elemento);
  //   }
  //   else
  //   {
  //     inserir_fim(&maiores, elemento);
  //   }
  }
  // quick_sort(&menores);
  // anexar_inicio(lst,&menores);
  // quick_sort(&maiores);
  // anexar_fim(lst,maiores);
}

int main(){
  lista lst;
  quick_sort(&lst);
  return 0;
}