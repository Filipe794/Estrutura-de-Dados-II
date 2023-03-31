#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include <stdio.h>

typedef struct cel {
  int num;
  cel *ant;
  cel *prox;
} celula;

typedef struct list {
  celula *inicio;
  celula *fim;
  int tamanho;
} lista;

void anexar_fim(lista *nova, lista *lista) {
  nova->tamanho += lista->tamanho;
  nova->fim->prox = lista->inicio;
  lista->inicio->ant = nova->fim;
  nova->fim = lista->fim;
  delete lista;
}

void divide(lista *lista1, lista *lista2) {
  int tam_metade = lista1->tamanho / 2;
  celula *inicio2 = lista1->inicio;
  for (int i = 0; i < tam_metade; i++) {
    inicio2 = inicio2->prox;
  }

  celula *fim1 = inicio2->ant;
  fim1->prox = NULL;
  inicio2->ant = NULL;

  lista2->inicio = inicio2;
  lista2->fim = lista1->fim;
  lista2->tamanho = lista1->tamanho - tam_metade;

  lista1->fim = fim1;
  lista1->tamanho = tam_metade;
}

void inserir_fim(lista *lista, celula *elemento)
{
  lista->fim->prox = elemento;
  elemento->ant = lista->fim;
  lista->fim = elemento;
}

celula* remover_inicio(lista *lista){
  celula *elemento = lista->inicio;
  elemento->prox = NULL;
  lista->inicio = lista->inicio->prox;
  lista->inicio->ant = NULL;
  return elemento;
}

lista *merge(lista *lista1, lista *lista2) {
  lista *nova = new lista;

  while ((lista1->tamanho > 0) && (lista2->tamanho > 0)) {
    int num1 = lista1->inicio->num;
    int num2 = lista2->inicio->num;
    celula *elemento;
    if (num1 < num2) {
      elemento = remover_inicio(lista1);
    } else {
      elemento = remover_inicio(lista2);
    }
    inserir_fim(nova, elemento);
  }
  if (lista1->tamanho > 0) {
    anexar_fim(nova, lista1);
  }

  if (lista2->tamanho > 0) {
    anexar_fim(nova, lista2);
  }

  return nova;
}

void menu()
{
    printf("1 - Inserir elemento\n");
    printf("2 - Imprimir a lista\n");
    printf("3 - Ordenar lista\n");
    printf("0 - Sair\n");
}

// Carro *aux = *cabeca;
//     if (strcmp(carro->nome, aux->nome) < 0)  // Inserindo inicio
//       carro->prox = aux;
//       carro->ant = aux->ant;
//       aux->ant = carro;
//       *cabeca = carro;

// void inserir_inicio(lista* lista,celula *elemento){
//     lista* aux = lista;
//     //   carro->prox = aux;
//     //   carro->ant = aux->ant;
//     //   aux->ant = carro;
//     //   *cabeca = carro;
// }
int main()
{   

    int opcao;
    lista *lista_1 = NULL;
    lista *lista_2 = NULL;
    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserir_fim();
            break;
        case 2:
            imprimir();
            break;
        case 3:
            merge();
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}