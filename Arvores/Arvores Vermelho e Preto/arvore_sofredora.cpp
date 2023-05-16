// ponteiro pro pai?
// impletar rotações
// campos para as cores serem booleanos ou inteiros (1 ou 0)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    int num;
    struct node *esq;
    struct node *dir;
    bool red;
} No;

No *criar_no(int num = -1)
{
    No *node = (No *)malloc(sizeof(No));

    if (num == -1)
    {
        node->num = rand() % 100;
        printf("%d, ", node->num);
    }
    else
    {
        node->num = num;
    }

    node->esq = NULL;
    node->dir = NULL;
    node->red = true;

    return node;
}

void inserir_no(No *node, No *novo)
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

    if (node->num < novo->num)
    {
        if (node->dir == NULL)
        {
            node->dir = novo;
            if (node->red == true)
            {
                novo->red = false;
            }
            return;
        }
        inserir_no(node->dir, novo);
    }
    else
    {
        if (node->esq == NULL)
        {
            node->esq = novo;
            if (node->red == true)
            {
                novo->red = false;
            }
            return;
        }
        inserir_no(node->esq, novo);
    }
}

void inserir_raiz(No **raiz)
{
    if (*raiz == NULL)
    {
        *raiz = criar_no();
        (*raiz)->red = false;
        return;
    }

    inserir_no(*raiz, criar_no());
}

No *buscar_pai(No *node, No *filho) {
  if (node == NULL) return NULL;

  if ((node->esq != NULL) && (node->esq == filho)) {
    return node;
  }

  if ((node->dir != NULL) && (node->dir == filho)) {
    return node;
  }

  if (node->num < filho->num) {
    return buscar_pai(node->dir, filho);
  } else {
    return buscar_pai(node->esq, filho);
  }
}

bool um_filho(No *node) {
  // return (node->esq == NULL) && (node->dir == NULL);
  if ((node->esq == NULL) && (node->dir != NULL)) {
    return true;
  }

  if ((node->esq != NULL) && (node->dir == NULL)) {
    return true;
  }

  return false;
}

bool eh_folha(No *node) {
  // return (node->esq == NULL) && (node->dir == NULL);
  if ((node->esq == NULL) && (node->dir == NULL)) {
    return true;
  } else {
    return false;
  }
}

No *maior(No *node) {
  if (node == NULL) return NULL;
  if (node->dir == NULL) return node;
  return maior(node->dir);
}

No *menor(No *node) {
  if (node == NULL) return NULL;
  if (node->esq == NULL) return node;
  return menor(node->esq);
}

int altura(No *node) {
  if (node == NULL || node->red == true) return 0;

  return 1 + fmax(altura(node->esq), altura(node->dir)); // precisa do 1+?
}

void arvore_aleatoria(No **root) {
  for (int i = 0; i < 10; i++) {
    inserir_raiz(root);
  }
}

void imprimir(No *node, int tab = 0) {
  if (node == NULL) return;

  imprimir(node->dir, tab + 1);
  for (int i = 0; i < tab; i++) {
    printf("\t");
  }
  printf("%d\n", node->num);
  imprimir(node->esq, tab + 1);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  No *no = criar_no(5);
  No *root = no;

  no = criar_no(6);
  inserir_no(root, no);
  No *no4 = criar_no(4);
  inserir_no(root, no4);
  no = criar_no(2);
  inserir_no(root, no);
  no = criar_no(1);
  inserir_no(root, no);
  // no = criar_no(3);
  // inserir_no(root, no);

  imprimir(root);
  printf("================\n");
//   balancear(&root, root);
  imprimir(root);

  // int opc = 1;
  // while (opc != 0) {
  //   menu();
  //   scanf("%d", &opc);
  //   switch (opc) {
  //     case 1:
  //       inserir_raiz(&root);
  //       break;
  //     case 2:
  //       buscar_raiz(root);
  //       break;
  //     case 3:
  //       imprimir(root);
  //       balancear(&root, no4);
  //       imprimir(root);
  //       break;
  //     case 4:
  //       remover_raiz(&root);
  //       break;
  //     case 5:
  //       arvore_aleatoria(&root);
  //       break;
  //     case 6:
  //       printf("Maior:%d, Menor:%d, Média:%.2f\n", maior(root)->num,
  //              menor(root)->num, media(root));
  //       break;
  //     case 7:
  //       printf("Altura: %d\n", altura(root));
  //       break;
  //     case 8:
  //       altura_no(root);
  //       break;
  //     case 9:
  //       fb_raiz(root);
  //       break;
  //     case 10:
  //       imprimir_fb(root);
  //       break;
  //     case 0:
  //       break;
  //     default:
  //       printf("Opção inválida\n");
  //       break;
  //   }
  // }

  return 0;
}