#include <stdio.h>
#include <stdlib.h>

#define T 5

typedef struct
{
  int codigo_barra;
  char nome[15];
  char data[10];
  int quant;
  float preco;
} medicamento;

typedef struct page
{
  int pos = 0;
  bool folha = false;
  int codigos[(2 * T) - 1];
  struct page *pai = NULL;
  medicamento *medicamentos[(2 * T) - 1];
  struct page *filhos[2 * T];
  struct page *prox = NULL;
} pagina;

pagina *root = NULL;

pagina *criar_pagina();

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

void imprimir_medicamento(medicamento *med)
{
  printf("Codigo de barras: %d\n", med->codigo_barra);
  printf("Nome: %s\n", med->nome);
  printf("Data do Cadastro: %s\n", med->data);
  printf("Quantidade: %d\n", med->quant);
  printf("Preço: %f\n", med->preco);
}

void print(pagina *pag)
{
  if (pag == NULL)
    return;

  for (int i = 0; i < pag->pos; i++)
  {
    if (!folha(pag))
    {
      print(pag->filhos[i]);
    }
    imprimir_medicamento(pag->medicamentos[i]);
  }
  print(pag->filhos[pag->pos]);
}

medicamento *criar_medicamento()
{
  medicamento *med = new medicamento;

  printf("Insira o codigo de barra do medicamento: ");
  scanf("%d", &med->codigo_barra);

  printf("Insira o nome do medicamento: ");
  scanf("%s", med->nome);

  printf("Insira a data do cadastro: ");
  scanf("%s", med->data);

  printf("Insira a quantidade do medicamento: ");
  scanf("%d", &med->quant);

  printf("Insira o preco do medicamento: ");
  scanf("%f", &med->preco);

  return med;
}

pagina *dividir_pagina(pagina *esq)
{
  int meio = ((2 * T) - 1) / 2;

  pagina *pai, *dir;

  pai = criar_pagina();
  dir = criar_pagina();

  // atribuindo os filhos ao pai
  pai->filhos[0] = esq;
  pai->filhos[1] = dir;

  // encadeando a lista dos vetores das folhas
  dir->prox = esq->prox;
  esq->prox = dir;

  for (int i = 0; i < (2 * T - 1) - (meio + 1); i++)
  {
    dir->medicamentos[i] = esq->medicamentos[i + (meio + 1)];
    dir->pos++;

    esq->medicamentos[i + (meio + 1)] = NULL;
    esq->pos--;
  }

  // adicionando o codigo de barra da esq nos codigos do pai
  pai->codigos[0] = esq->medicamentos[meio]->codigo_barra;
  pai->pos++;

  esq->medicamentos[meio] = NULL;
  esq->pos--;

  esq->pai = pai;
  dir->pai = pai;

  return pai;
}

void inserir_pagina(pagina **pg, medicamento *med)
{
  pagina *pag = busca_insercao(root, med->codigo_barra);

  if (folha(pag))
  {
    if (pag->pos < (2 * T) - 1)
    {
      int i = pag->pos - 1;
      while (i >= 0 && pag->medicamentos[i]->codigo_barra > med->codigo_barra)
      {
        if (med->codigo_barra == pag->medicamentos[i]->codigo_barra)
        {
          pag->medicamentos[i]->quant++;
          printf("Medicamento já existe. Quantidade incrementada em 1.\n");
          return;
        }
        pag->medicamentos[i + 1] = pag->medicamentos[i];
        i--;
      }
      pag->medicamentos[i + 1] = med;
      pag->pos++;
    }
    else
    {
      *pg = dividir_pagina(pag);
      inserir_pagina(pg, med);
    }
  }
  else
  {
    int i = 0;
    
    for (int i = 0; i < pag->pos; i++)
    {
      if (med->codigo_barra == pag->medicamentos[i]->codigo_barra)
      {
        pag->medicamentos[i]->quant++;
        return;
      }
      if (med->codigo_barra < pag->medicamentos[i]->codigo_barra)
      {
        inserir_pagina(&pag->filhos[i], med);
      }
    }
    inserir_pagina(&pag->filhos[pag->pos], med);
  }
}

pagina *criar_pagina()
{
  pagina *pag = new pagina;
  for (int i = 0; i < 2 * T - 1; i++)
  {
    pag->codigos[i] = 0;
    pag->medicamentos[i] = NULL;
    pag->filhos[i] = NULL;
  }
  pag->filhos[2 * T] = NULL;
  return pag;
}

pagina *inserir_folha(pagina *folha, medicamento *med)
{
  int i, inserir;

  inserir = 0;
  while (inserir < folha->pos && folha->medicamentos[inserir]->codigo_barra < med->codigo_barra)
    inserir++;

  for (i = folha->pos; i > inserir; i--)
  {
    folha->medicamentos[i] = folha->medicamentos[i - 1];
    folha->filhos[i] = folha->filhos[i - 1];
  }
  folha->medicamentos[inserir] = med;
  folha->pos++;
  return folha;
}

void inserir(pagina **root, medicamento *med)
{
  if (*root == NULL)
  {
    (*root) = criar_pagina();
    (*root)->codigos[0] = med->codigo_barra;
    (*root)->medicamentos[0] = med;
    (*root)->pos++;
    (*root)->folha = true;
  }
  else
  {
    inserir_pagina(root, med);
  }
}

pagina *busca_insercao(pagina *root, int codigo_barra)
{
  if (root == NULL)
  {
    return NULL;
  }
  int i = 0;

  while (i < root->pos && codigo_barra > root->codigos[i])
    i++;

  if (i < root->pos && codigo_barra == root->codigos[i])
  {
    // medicamento ja existe na arvore
    root->medicamentos[i]->quant++;
    printf("Medicamento já existe. Quantidade incrementada em 1.\n");
    return NULL;
  }

  if (root->folha)
  {
    return root;
  }

  return busca_insercao(root->filhos[i], codigo_barra);
}

pagina *busca(pagina *pag, int codigo_barra)
{
  if (pag == NULL)
  {
    return NULL;
  }

  if (folha(pag))
  {
    for (int i = 0; i < pag->pos; i++)
    {
      if (codigo_barra == pag->medicamentos[i]->codigo_barra)
      {
        return pag;
      }
    }
    return NULL;
  }

  for (int i = 0; i < pag->pos; i++)
  {
    if (codigo_barra <= pag->codigos[i])
    {
      return busca(pag->filhos[i], codigo_barra);
    }
  }
  busca(pag->filhos[pag->pos], codigo_barra);
  return NULL;
}

int main()
{
  medicamento *med = criar_medicamento();
  imprimir_medicamento(med);
  printf("\n");
  inserir(&root, med);
  printf("\n");
  print(root);
  return 0;
}