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

void inserir_raiz(No **root, No *novo)
{
  if ((*root) == NULL)
  {
    (*root) = novo;
    novo->cor = preto;
    return;
  }

  inserir_no(*root, novo);
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
      return;
    }
    inserir_no(root->esq, novo);
  }
}

void balanceada(No **root, No *node)
{
  if (node == NULL)
    return;

  balanceada(root, node->dir);

  int altura_esquerda = altura(node->esq);
  int altura_direita = altura(node->dir);

  if (altura_direita > altura_esquerda)
  {
    printf("desbalanceada para a direita\n");
    balancear(root, node->dir);
  }
  else if (altura_direita < altura_esquerda)
  {
    printf("desbalanceada para a esquerda\n");
    balancear(root, node->esq);
  }

  balanceada(root, node->esq);
}

void balancear(No **root, No *novo)
{

  No *tio = NULL;
  No *avo = novo->pai->pai;
  No *pai = novo->pai;

  if (avo->esq == pai)
  {
    tio = avo->dir;
  }
  else if (avo->dir == pai)
  {
    tio = avo->esq;
  }

  int cor_pai = pai->cor;
  int cor_tio = tio->cor;

  if (cor_pai != preto) // CASO O PAI SEJA PRETO, NAO PRECISA ALTERAR NADA
  {
    if (cor_pai == vermelho && cor_tio == vermelho)
    {
      if ((*root) != avo)
      {
        avo->cor = vermelho;
      }
      cor_tio = preto;
      cor_pai = preto;
    }
    if (cor_pai == vermelho && cor_tio == preto)
    {
      // rotação simples a direita
      if (avo->esq == pai && pai->esq == novo)
      {
        pai->cor = preto;
        avo->cor = vermelho;
        tio->cor = vermelho;
        // posso recolorir logo aq, antes de chamar a função de rotação
        rot_simples_dir(root, avo);
      }
      else if (avo->dir == pai && pai->dir == novo)
      {
        // rotação simples a esquerda
        pai->cor = preto;
        avo->cor = vermelho;
        tio->cor = vermelho;
        // posso recolorir logo aq, antes de chamar a função de rotação?
        rot_simples_esq(root, avo);
      }
      else if (avo->esq == pai && pai->dir == novo)
      {
        novo->cor = preto;
        avo->cor = vermelho;
        rot_dupla_dir(root, avo);
      }
      else if (avo->dir == pai && pai->esq == novo)
      {
        novo->cor = preto;
        avo->cor = vermelho;
        rot_dupla_esq(root, avo);
      }
    }
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
  inserir_no(*raiz, criar_no());
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
      balanceada(&root,root);
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