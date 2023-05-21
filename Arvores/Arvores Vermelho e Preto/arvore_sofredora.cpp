#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 1 = preto
// 0 = vermelho

enum Cor
{
  vermelho,
  preto
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

void rot_simples_esq(No **raiz, No *no, bool dupla = false)
{
  No *filho = no->dir;
  if (filho == NULL)
  {
    printf("Rotação errada\n");
    return;
  }

  No *esq_filho = filho->esq;
  no->dir = esq_filho;
  filho->esq = no;

  No *pai = no->pai;
  if (pai == NULL)
  {
    *raiz = filho;
  }
  else
  {
    if (dupla == true)
    {
      pai->esq = filho;
    }
    else
    {
      pai->dir = filho;
    }
  }
}

void rot_simples_dir(No **raiz, No *no, bool dupla = false)
{
  No *filho = no->esq;
  if (filho == NULL)
  {
    printf("Rotação errada\n");
    return;
  }

  No *dir_filho = filho->dir;
  no->esq = dir_filho;
  filho->dir = no;

  No *pai = no->pai;
  if (pai == NULL)
  {
    *raiz = filho;
  }
  else
  {
    if (dupla == true)
    {
      pai->dir = filho;
    }
    else
    {
      pai->esq = filho;
    }
  }
}

void rot_dupla_dir(No **raiz, No *no)
{
  No *filho = no->esq;
  if (filho == NULL)
  {
    printf("Rotação errada\n");
    return;
  }
  rot_simples_esq(raiz, filho, true);
  rot_simples_dir(raiz, no);
}

void rot_dupla_esq(No **raiz, No *no)
{
  No *filho = no->dir;
  if (filho == NULL)
  {
    printf("Rotação errada\n");
    return;
  }
  rot_simples_dir(raiz, filho, true);
  rot_simples_esq(raiz, no);
}

void inserir_no(No *root, No *novo)
{
  if (root == NULL)
  {
    printf("Erro\n");
    return;
  }

  if (root->num == novo->num)
  {
    printf("Número já existe\n");
    return;
  }

  // inserir nó
  if (root->num < novo->num)
  {
    if (root->dir == NULL)
    {
      root->dir = novo;
      novo->pai = root;
      if(novo->pai->cor == vermelho && novo->cor  == vermelho){
        novo->cor = preto;        
      }
      return;
    }
    inserir_no(root->dir, novo);
  }
  else
  {
    if (root->esq == NULL)
    {
      root->esq = novo;
      novo->pai = root;
      if(novo->pai->cor == vermelho && novo->cor  == vermelho){
        novo->cor = preto;        
      }
      return;
    }
    inserir_no(root->esq, novo);
  }
}

void inserir_raiz(No **raiz, No *node)
{
  if (*raiz == NULL)
  {
    *raiz = node;
    (*raiz)->cor = preto;
    (*raiz)->pai = NULL;
    return;
  }
  inserir_no(*raiz, node);
}

void balancear(No **root, No *novo)
{
  printf("entrou\n\n");
  if (novo == (*root) || novo == NULL)
    return;

  No *tio = new No;
  No *pai = novo->pai;
  No *avo = NULL;

  printf("passou 1\n\n");
  if (pai != NULL)
  {
    avo = pai->pai;
  }
  printf("passou 2\n\n");
  if (avo)
  {
    if (avo->esq == pai)
    {
      if (avo->dir == NULL)
      {
        tio->cor = preto;
      }
      else
      {
        tio = avo->dir;
      }
    }
    else if (avo->dir == pai)
    {
      if (avo->esq == NULL)
      {
        tio->cor = preto;
      }
      else
      {
        tio = avo->esq;
      }
    }
  }
  printf("passou 3\n\n");
  if (pai->cor != preto) // CASO O PAI SEJA PRETO, NAO PRECISA ALTERAR NADA
  {
    printf("passou 4\n\n");
    if (pai->cor == vermelho && tio->cor == vermelho)
    {
      printf("passou 5\n\n");
      if ((*root) != avo)
      {
        printf("passou 6\n\n");
        if (avo)
        {
          avo->cor = vermelho;
        }
      }
      printf("passou 7\n\n");
      tio->cor = preto;
      pai->cor = preto;
      printf("passou 8\n\n");
      return;
    }
    if (pai->cor == vermelho && tio->cor == preto)
    {
      printf("passou 10\n\n");
      if (avo)
      { // rotação simples a direita
        printf("passou 11\n\n");
        if (avo->esq == pai && pai->esq == novo)
        {
          printf("passou 12\n\n");
          pai->cor = preto;
          avo->cor = vermelho;
          tio->cor = vermelho;
          printf("passou 13\n\n");
          // posso recolorir logo aq, antes de chamar a função de rotação
          rot_simples_dir(root, avo);
          printf("passou 14\n\n");
          return;
        }
        else if (avo->dir == pai && pai->dir == novo)
        {
          printf("passou 15\n\n");
          // rotação simples a esquerda
          pai->cor = preto;
          avo->cor = vermelho;
          tio->cor = vermelho;
          printf("passou 16\n\n");
          // posso recolorir logo aq, antes de chamar a função de rotação?
          rot_simples_esq(root, avo);
          printf("passou 17\n\n");
          return;
        }
        else if (avo->esq == pai && pai->dir == novo)
        {
          printf("passou 18\n\n");
          novo->cor = preto;
          avo->cor = vermelho;
          rot_dupla_dir(root, avo);
          printf("passou 19\n\n");
          return;
        }
        else if (avo->dir == pai && pai->esq == novo)
        {
          novo->cor = preto;
          avo->cor = vermelho;
          rot_dupla_esq(root, avo);
          printf("passou 20\n\n");
          return;
        }
      }
    }
  }
}

void balanceada(No **root, No *node)
{
  if (node == NULL)
    return;
  printf("testou\n\n\n");
  int altura_esquerda = altura(node->esq);
  int altura_direita = altura(node->dir);

  if (altura_direita != altura_esquerda)
  {
    balancear(root, node);
  }
  balanceada(root, node->pai);
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
      node = criar_no();
      inserir_raiz(&root, node);
      balanceada(&root, node);
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
    case 0:
      break;
    default:
      printf("Opção inválida\n");
      break;
    }
  }
  return 0;
}