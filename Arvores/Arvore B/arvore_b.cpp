#include <stdio.h>
#include <stdlib.h>

#define T 3

// typedef struct {
//   int cpf;
//   int idade;
//   char* teste;
// } registro;

typedef struct page
{
  int pos = 0;
  int chaves[2 * T - 1];
  struct page *filhos[2 * T];
} pagina;

pagina *root = NULL;

bool folha(pagina *pag)
{
  for (int i = 0; i <= pag->pos + 1; i++)
  {
    if (pag->filhos[i] != NULL)
    {
      return false;
    }
  }
  return true;
}

void print(pagina *pag)
{
  if (pag == NULL)
    return;

  for (int i = 0; i < pag->pos; i++)
  {
    // if (!folha(pag)) {
    print(pag->filhos[i]);
    // }
    printf("%d ", pag->chaves[i]);
  }
  print(pag->filhos[pag->pos]);
}

pagina *criar_pagina()
{
  pagina *pag = new pagina;
  for (int i = 0; i < 2 * T - 1; i++)
  {
    pag->chaves[i] = 0;
    pag->filhos[i] = NULL;
  }
  pag->filhos[2 * T - 1] = NULL;

  return pag;
}

pagina *busca(pagina *pag, int num)
{
  if (pag == NULL)
  {
    return NULL;
  }

  for (int i = 0; i < pag->pos; i++)
  {
    if (num < pag->chaves[i])
    {
      return busca(pag->filhos[i], num);
    }
    else
    {
      if (num == pag->chaves[i])
      {
        return pag;
      }
    }
  }
  return busca(pag->filhos[pag->pos], num);
}

pagina *dividir_pagina(pagina *esq)
{
  int meio = (2 * T - 1) / 2;
  pagina *pai, *dir;
  pai = criar_pagina();
  dir = criar_pagina();

  pai->filhos[0] = esq;
  pai->filhos[1] = dir;

  for (int i = 0; i < (2 * T - 1) - (meio + 1); i++)
  { // Maior q meio e coloca na dir
    dir->chaves[i] = esq->chaves[i + (meio + 1)];
    dir->pos++;

    esq->chaves[i + (meio + 1)] = 0;
    esq->pos--;
  }

  pai->chaves[0] = esq->chaves[meio];
  pai->pos++;
  esq->chaves[meio] = 0;
  esq->pos--;

  return pai;
}

void inserir_pagina(pagina **pg, int num)
{
  pagina *pag = *pg;
  if (folha(pag))
  {
    if (pag->pos < 2 * T - 1)
    { // Folha não cheia
      int i = pag->pos - 1;
      while (i >= 0 && pag->chaves[i] > num)
      {
        pag->chaves[i + 1] = pag->chaves[i];
        i--;
      }
      pag->chaves[i + 1] = num;
      pag->pos++;
    }
    else
    { // Folha cheia
      *pg = dividir_pagina(pag);
      inserir_pagina(pg, num);
    }
  }
  else
  {
    for (int i = 0; i < pag->pos; i++)
    {
      if (num == pag->chaves[i])
      {
        return;
      }
      if (num < pag->chaves[i])
      {
        inserir_pagina(&pag->filhos[i], num);
      }
    }
    inserir_pagina(&pag->filhos[pag->pos], num);
  }
}

void inserir(pagina **root, int num)
{
  if (*root == NULL)
  {
    *root = criar_pagina();
    (*root)->chaves[0] = num;
    (*root)->pos++;
  }
  else
  {
    inserir_pagina(root, num);
  }
}

int pos_chave(pagina *pag, int num)
{
  int res = -1;
  for (int i = 0; i < pag->pos; i++)
  { // encontra a posição do elemento a ser removido
    if (pag->chaves[i] == num)
    {
      res = i;
      break;
    }
  }
  return res;
}

void remover_chave_merge(pagina *pag, int num)
{
  int res = pos_chave(pag, num);
  // if ((res == -1) ||
  //     (res = 2 * T - 2)) {  // Aborta se não existe ou última posição
  //   return;
  // }

  pagina *esq = pag->filhos[res];
  pagina *dir = pag->filhos[res + 1];

  for (int i = 0; i < dir->pos; i++)
  {
    esq->chaves[esq->pos] = dir->chaves[i];
    esq->filhos[esq->pos] = dir->filhos[i];
    esq->pos++;
  }
  esq->filhos[esq->pos] = dir->filhos[dir->pos];
  delete dir;

  pag->chaves[res] = pag->chaves[res + 1];
  for (int i = res + 1; i < pag->pos - 1; i++)
  {
    pag->chaves[i] = pag->chaves[i + 1];
    pag->filhos[i] = pag->filhos[i + 1];
  }
  pag->filhos[pag->pos] = NULL;
  pag->pos--;
  pag->chaves[pag->pos] = 0;
}

void remover_chave_folha(pagina *pag, int num)
{
  int res = pos_chave(pag, num);
  // if (res == -1) {  // Aborta se a chave não está na página
  //   return;
  // }

  for (int i = res; i < pag->pos; i++)
  {
    if (pag->chaves[i] >= num)
    {
      pag->chaves[i] = pag->chaves[i + 1];
    }
  }
  pag->pos--;
}

int main(int argc, char const *argv[])
{
  // inserir(&root, 20);
  // inserir(&root, 50);
  // inserir(&root, 30);
  // inserir(&root, 10);
  // inserir(&root, 40);

  // inserir(&root, 35);

  // print(root);
  // printf("\n");

  pagina *pag1, *pag2, *pag3;

  pag1 = criar_pagina();
  pag2 = criar_pagina();
  pag3 = criar_pagina();

  pag1->chaves[0] = 40;
  pag1->pos++;
  pag1->chaves[1] = 100;
  pag1->pos++;
  pag1->chaves[2] = 120;
  pag1->pos++;

  pag2->chaves[0] = 10;
  pag2->pos++;
  pag2->chaves[1] = 20;
  pag2->pos++;

  pag3->chaves[0] = 70;
  pag3->pos++;
  pag3->chaves[1] = 80;
  pag3->pos++;

  pag1->filhos[0] = pag2;
  pag1->filhos[1] = pag3;

  print(pag1);
  printf("\n");
  remover_chave_merge(pag1, 40);

  return 0;
}
