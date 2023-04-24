#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node
{
  int num;
  struct node *esquerda;
  struct node *direita;
} No;

int gera_num()
{
  int num = rand() % 100; // gerando um localizador aleatorio
  while (num == 0)        // evitando q o localizador seja 0
  {
    num = rand() % 100;
  }
  return num;
}

No *criar_no(No *raiz)
{

  No *node = (No *)malloc(sizeof(No));

  node->num = gera_num();

  node->esquerda = NULL;
  node->direita = NULL;

  return node;
}

void inserir_no(No *node, No *novo)
{
  if (node == NULL)
  {
    printf("Erro\n");
    return;
  }

  if (node->num < novo->num)
  { // caso o num do nó a ser inserido seja maior que o num do nó que está na raiz
    // o nó a ser inserido irá para a direita da raiz

    if (node->direita == NULL) // testando se o nó da direita está nulo
    {                          // caso esteja, o nó novo sera inserido aqui
      node->direita = novo;
      return;
    }
    inserir_no(node->direita, novo); // caso nao esteja nulo, chamará recursivamente a função de inserir nó
                                     // para continuar procurando onde inserir o nó
  }
  else
  { // caso o num do nó a ser inserido seja menor que o num do nó que está na raiz
    // o nó a ser inserido irá para a esquerda da raiz
    if (node->esquerda == NULL)
    {
      node->esquerda = novo;
      return;
    }
    inserir_no(node->esquerda, novo);
  }
}

No *preencher_no()
{
  No *node = (No *)malloc(sizeof(No));
  node->num = gera_num();

  node->esquerda = NULL;
  node->direita = NULL;

  return node;
}
// funcao inserir para os testes serem mais rápidos
void inserir_teste(No **raiz)
{

  if ((*raiz) == NULL)
  {
    *raiz = preencher_no();
    return;
  }

  No *novo = preencher_no();
  inserir_no(*raiz, novo);
}

No *buscar_pai(No *node, int num)
{
  if (node == NULL)
    return NULL;

  if ((node->esquerda != NULL) && (node->esquerda->num == num))
  {
    return node;
  }

  if ((node->direita != NULL) && (node->direita->num == num))
  {
    return node;
  }

  if (node->num < num)
  {
    return buscar_pai(node->direita, num);
  }
  else
  {
    return buscar_pai(node->esquerda, num);
  }
}

bool um_filho(No *node)
{
  // return (node->esquerda == NULL) && (node->direita == NULL);
  if ((node->esquerda == NULL) && (node->direita != NULL))
  {
    return true;
  }

  if ((node->esquerda != NULL) && (node->direita == NULL))
  {
    return true;
  }

  return false;
}

bool eh_folha(No *node)
{
  // return (node->esquerda == NULL) && (node->direita == NULL);
  if ((node->esquerda == NULL) && (node->direita == NULL))
  {
    return true;
  }
  else
  {
    return false;
  }
}

No *remover(No *node, int num);

void substituir(No *pai, No *removido)
{
  if (um_filho(removido))
  {
    if (removido->esquerda != NULL)
    {
      pai->esquerda = removido->esquerda;
    }
    else
    {
      pai->direita = removido->direita;
    }
  }
  else
  {
    No *substituto = maior(removido->esquerda);
    remover(pai, substituto->num);
    substituto->esquerda = removido->esquerda;
    substituto->direita = removido->direita;
    if (pai->num < substituto->num)
    {
      pai->direita = substituto;
    }
    else
    {
      pai->esquerda = substituto;
    }
    removido->direita = NULL;
    removido->esquerda = NULL;
  }
}

No *remover(No *node, int num)
{
  No *pai = buscar_pai(node, num);
  if (pai == NULL)
  {
    printf("Numero não encontrado");
    return NULL;
  }
  else
  {
    // printf("Pai: %d\n", pai->num);
    No *removido = NULL;
    if (pai->num < num)
    {
      removido = pai->direita;
      if (eh_folha(removido))
      {
        pai->direita = NULL;
      }
      else
      {
        substituir(pai, removido);
      }
    }
    else
    {
      removido = pai->esquerda;
      if (eh_folha(removido))
      {
        pai->esquerda = NULL;
      }
      else
      {
        substituir(pai, removido);
      }
    }
    // printf("Removido: %d\n", removido->num);
    return removido;
  }
}

No *remover_raiz(No **raiz)
{
  if (*raiz == NULL)
  {
    printf("Árvore vazia\n");
    return NULL;
  }

  int num = (*raiz)->num;
  No *removido = *raiz;
  if ((removido)->num == num)
  {
    if (eh_folha(removido))
    {
      *raiz = NULL;
      return removido;
    }

    if (um_filho(removido))
    {
      if ((*raiz)->esquerda != NULL)
      {
        *raiz = (*raiz)->esquerda;
        removido->esquerda = NULL;
      }
      else
      {
        *raiz = (*raiz)->direita;
        removido->direita = NULL;
      }
      return removido;
    }
    else
    {
      No *substituto = maior((*raiz)->esquerda);

      remover(*raiz, substituto->num);

      substituto->esquerda = (*raiz)->esquerda;
      substituto->direita = (*raiz)->direita;

      (*raiz)->esquerda = NULL;
      (*raiz)->direita = NULL;

      removido = *raiz;
      *raiz = substituto;

      return removido;
    }
  }
}

void imprimir(No *node) // função para imprimir a arvore
{
  if (node == NULL)
  {
    return;
  }
  imprimir_folha(node);
  printf("\n");
  imprimir(node->direita);
  imprimir(node->esquerda);
}

void imprimir_folha(No *node)
{
  printf("Numero: %d\n", node->num);
}

No *maior(No *node)
{
  if (node == NULL)
    return NULL;
  if (node->direita == NULL)
    return node;
  return maior(node->direita);
}

No *menor(No *node)
{
  if (node == NULL)
    return NULL;
  if (node->esquerda == NULL)
    return node;
  return menor(node->esquerda);
}

int altura(No *raiz)
{
  if (raiz == NULL)
  {
    return -1;
  }
  else
  {
    int esquerda = altura(raiz->esquerda);
    int direita = altura(raiz->direita);
    if (esquerda > direita)
    {
      return esquerda++;
    }
    else
    {
      return direita++;
    }
  }
}

int soma = 0;

int soma_elementos(No *node)
{
  if (node == NULL)
    return;
  soma_elementos(node->esquerda);
  soma += node->num;
  soma_elementos(node->direita);
}

int qnt_elementos = 0;

int num_elementos(No *node)
{
  if (node == NULL)
    return;
  qnt_elementos++;
  num_elementos(node->direita);
  num_elementos(node->esquerda);
}

// fzr busca e retornar nós pra trocas
No *busca(No *raiz, int num)
{
  if (raiz == NULL)
    return NULL;

  if (raiz->num == num)
    return raiz;

  if (raiz->num < num)
  {
    busca(raiz->esquerda, num);
  }
  else
  {
    busca(raiz->direita, num);
  }
}

int posicao_filho(No *pai, No* filho)
{
  if(pai == NULL || filho == NULL) return -1;

  if (pai->esquerda == filho)
  {
    return 0;
  }else if(pai->direita == filho){
    return 1;
  }
}
void troca(No **raiz, No *node_1, No *node_2)
{

  if (node_1->num == node_2->num)
    return;

  No *pai_node_1 = buscar_pai((*raiz), node_1->num);
  No *pai_node_2 = buscar_pai((*raiz), node_2->num);

  if (node_1 == (*raiz))
  {
    if(posicao_filho(pai_node_2,node_2) == 0){ // filho esta na esquerda
      // reorganizar filho do no 1
      pai_node_2->esquerda = node_1;
    }else if(posicao_filho(pai_node_2,node_2) == 1){// filho esta na direita

    }
    if (node_2 == node_1->esquerda)
    {
      // se for troca com pai e filho na esquerda do pai
    }else if(node_2 == node_1->direita){
      // se for troca com pai e filho na direita do pai
    }
    (*raiz) = node_2;
    return;
  }

  if (node_2 == (*raiz))
  {
    if(posicao_filho(pai_node_1,node_1) == 0){ // filho esta na esquerda
      // reorganizar filho do no 1
      pai_node_1->esquerda = node_2;
    }else if(posicao_filho(pai_node_1,node_1) == 1){// filho esta na direita

    }
    if (node_1 == node_2->esquerda)
    {
      // se for troca com pai e filho na esquerda do pai
    }else if(node_1 == node_2->direita){
      // se for troca com pai e filho na direita do pai
    }
    (*raiz) = node_1;
    return;
  }

  if (node_2 == node_1->esquerda || node_2 == node_1->direita)
  {
    // se for troca com pai e filho
  }
  if (node_1 == node_2->esquerda || node_1 == node_2->direita)
  {
    // se for troca com pai e filho
  }
  // if(posicao_filho() == 1){
  //   // filho na direita
  // }else if(posicao_filho() == 0){
  //   // filho na esquerda
  // }
}
// verificar se os numeros sao iguais, nao fzr nada
// verificar se a troca é pai com filho
// troca na raiz

int main()
{
  No *raiz = new No;
  printf("Maior: %d", maior(raiz)->num);
  printf("Menor: %d", menor(raiz)->num);
  float media = soma / qnt_elementos;
  printf("Media: %f", media);
  int num;
  printf("Insira o numero do no: ");
  scanf("%d", num);
  printf("A altura do no é %d", altura(busca(raiz, num)));
  int num, num_2;
  printf("Insira o numero do no 1 para a troca: ");
  scanf("%d", num);
  printf("Insira o numero do no 2 para a troca: ");
  scanf("%d", num_2);
  troca(&raiz, busca(raiz, num), busca(raiz, num_2));
  return 0;
}