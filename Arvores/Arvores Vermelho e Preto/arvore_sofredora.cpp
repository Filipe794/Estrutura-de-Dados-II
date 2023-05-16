#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 1 = preto
// 0 = vermelho

enum Cor
{
  vermelho = 0,
  preto = 1
};

typedef struct node
{
  int num;
  struct node *esq = NULL;
  struct node *dir = NULL;
  struct node *pai = NULL;
  Cor cor = vermelho;
} No;

No *criar_no()
{
  No *node = new No;
  printf("Insira o valor do no: ");
  scanf("%d", &node->num);
  return node;
}

int posicao_filho(No *pai, No *filho)
{
  if (pai == NULL || filho == NULL)
    return -1;

  if (pai->esq == filho)
  {
    return 0;
  }
  else if (pai->dir == filho)
  {
    return 1;
  }
}

void inserir_no(No **root, No *node, No *novo)
{
  if (node == NULL)
  {
    printf("Erro\n");
    return;
  }

  if (node->num == novo->num)
  {
    printf("Número já existe\n");
    return;
  }

  if (node->cor == preto)
  {
    if (node->num < novo->num)
    {
      if (node->dir == NULL)
      {
        node->dir = novo;
        novo->pai = node;
        return;
      }
      inserir_no(root,node->dir, novo);
    }
    else if (node->esq == NULL)
    {
      node->esq = novo;
      novo->pai = node;
      return;
    }
    inserir_no(root,node->esq, novo);
  }

  // procurar tio
  No *tio = NULL;
  No *avo = node->pai->pai;
  No *pai = node->pai;

  int filho_posicao = posicao_filho(node->pai, node);

  if (filho_posicao == 0)
  {
    tio = node->pai->dir;
  }
  else if (filho_posicao == 1)
  {
    tio = node->pai->esq;
  }
  
  //comparar cores tio e pai
  if(pai->cor == vermelho && tio->cor == vermelho){
    //recolorir pai tio e avo
    if(avo != (*root)){
      avo->cor = vermelho;
    }
    pai->cor = preto;
    tio->cor = vermelho;
    
    // inserir nó

  }




  if (node->num < novo->num)
  {
    if (node->dir == NULL)
    {
      node->dir = novo;
      if (node->cor == vermelho)
      {
        novo->cor = preto;
      }
      novo->pai = node;
      return;
    }
    inserir_no(root,node->dir, novo);
  }
  else
  {
    if (node->esq == NULL)
    {
      node->esq = novo;
      if (node->cor == vermelho)
      {
        novo->cor = preto;
      }
      novo->pai = node;
      return;
    }
    inserir_no(root,node->esq, novo);
  }
}

void inserir_raiz(No **raiz)
{
  if (*raiz == NULL)
  {
    *raiz = criar_no();
    (*raiz)->cor = preto;
    (*raiz)->pai = NULL;
    return;
  }
  inserir_no(raiz, *raiz, criar_no());
}

bool um_filho(No *node)
{
  // return (node->esq == NULL) && (node->dir == NULL);
  if ((node->esq == NULL) && (node->dir != NULL))
  {
    return true;
  }

  if ((node->esq != NULL) && (node->dir == NULL))
  {
    return true;
  }

  return false;
}

bool eh_folha(No *node)
{
  // return (node->esq == NULL) && (node->dir == NULL);
  if ((node->esq == NULL) && (node->dir == NULL))
  {
    return true;
  }
  else
  {
    return false;
  }
}

No *maior(No *node)
{
  if (node == NULL)
    return NULL;
  if (node->dir == NULL)
    return node;
  return maior(node->dir);
}

No *menor(No *node)
{
  if (node == NULL)
    return NULL;
  if (node->esq == NULL)
    return node;
  return menor(node->esq);
}

int altura(No *node)
{
  if (node == NULL)
    return 0;
  if (node->cor == vermelho)
  {
    return fmax(altura(node->esq), altura(node->dir));
  }
  return 1 + fmax(altura(node->esq), altura(node->dir));
}

int balanceada(No *root)
{
  int altura_esquerda = altura(root->esq);
  int altura_direita = altura(root->dir);

  if (altura_direita > altura_esquerda)
  {
    return 1;
  }
  else if (altura_direita < altura_esquerda)
  {
    return -1;
  }
  return 0;
}

void imprimir(No *node, int tab = 0)
{
  if (node == NULL)
    return;

  imprimir(node->dir, tab + 1);
  for (int i = 0; i < tab; i++)
  {
    printf("\t");
  }
  printf("%d - %d\n", node->num, node->cor);
  imprimir(node->esq, tab + 1);
}

No *buscar_no(No *node, int num)
{
  if (node == NULL)
  {
    printf("Número não encontrado\n");
    return NULL;
  }

  if (node->num == num)
  {
    return node;
  }

  if (node->num < num)
  {
    return buscar_no(node->dir, num);
  }
  else
  {
    return buscar_no(node->esq, num);
  }
}

void menu()
{
  printf("MENU\n");
  printf("1-Inserir\n");
  printf("2-Imprimir Árvore\n");
  printf("3-Remover\n");
  printf("4-Altura arvore\n");
  printf("5-Altura nó\n");
  printf("0-Sair\n");
}

int main()
{
  srand(time(NULL));

  No *root = NULL;
  No *node = new No;
  int num;
  int opc = 1;
  while (opc != 0)
  {
    menu();
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
      inserir_raiz(&root);
      break;
    case 2:
      imprimir(root);
      break;
    case 3:
      // remover();
      break;
    case 4:
      altura(root);
      break;
    case 5:
      printf("Insira o valor do no a ser procurado: ");
      scanf("%d", &num);
      node = buscar_no(root, num);
      altura(node);
      break;
    case 6:
      num = balanceada(root);
      if (num != 0)
      {
        if (num == 1)
        { // desbalanceada pra direita
          printf("desbalanceada\n");
        }
        if (num == -1)
        { // desbalanceada pra esquerda
          printf("desbalanceada\n");
        }
      }
      else
      {
        printf("Arvore esta balanceada\n");
      }
      break;
    case 0:
      break;
    default:
      printf("Opção inválida\n");
      break;
    }
  }
  return 0;
}