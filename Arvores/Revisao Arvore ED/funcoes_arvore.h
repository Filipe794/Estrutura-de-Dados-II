#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
  int localizador;
  char data[10];
  float preco;
  char destino[50];
} passagem;

typedef struct node
{
  passagem passagem;
  struct node *esquerda;
  struct node *direita;
} No;

typedef struct // struct para armazenar os valores do relatorio, para nao encher de variaveiz globais
{
  float valor; // valor total das passagens de cada pais
  int qtde;    // quantidade total de passagens de cada pais
} relatorio;

// raizes pras arvores
No *root_br = NULL;
No *root_ar = NULL;
No *root_consolidada = NULL;

// contadores para arrecadacao de cada arvores
// vou usar na funcao faturamento
float arrecadacao = 0;
int qnt_passagens = 0;

// struct para armazenar do faturamento de cada arvore
relatorio fatura;

int loc()
{
  int loc = rand() % 100; // gerando um localizador aleatorio
  while (loc == 0)        // evitando q o localizador seja 0
  {
    loc = rand() % 100;
  }
  return loc;
}

int buscar_localizador(No *node, int localizador)
{

  if (node == NULL) // caso o nó seja nulo, não há oq testar
  {
    return 0;
  }

  if (node->passagem.localizador == localizador)
  {
    return 1; // caso o localizador ja exista, retorna 1
  }

  // recursividade para procurar nas subarvores
  buscar_localizador(node->direita, localizador);
  buscar_localizador(node->esquerda, localizador);

  return 0;
}

int gerar_localizador()
{
  int localizador = loc(); // recebe o valor gerado pela função loc
  while ((buscar_localizador(root_br, localizador) == 1 || buscar_localizador(root_ar, localizador) == 1))
  { // equanto a função busca_localizador retornar 1 para qualquer uma das arvores será gerado um novo localizador
    localizador = loc();
  }
  return localizador;
}

No *criar_no()
{

  No *node = (No *)malloc(sizeof(No));

  printf("Insira a data da viagem (use o formato DD/MM/AAAA): ");
  scanf("%s", node->passagem.data);
  fflush(stdin);
  printf("Insira o preço da passagem: ");
  scanf("%f", &node->passagem.preco);
  fflush(stdin);
  printf("Insira o destino: ");
  scanf("%50[^\n]s", node->passagem.destino);
  fflush(stdin);

  node->passagem.localizador = gerar_localizador(); // o campo localizador do nó recebe o valor retornado pela função gerar_localizador

  node->esquerda = NULL;
  node->direita = NULL;

  return node;
}

void imprimir_folha(No *node) // função para imprimir apenas uma folha da arvore (usada na busca por destino)
{
  printf("Destino: %s -> ", node->passagem.destino);
  printf("Preço: %.2f reais -> ", node->passagem.preco);
  printf("Data: %s -> ", node->passagem.data);
  printf("Localizador: %d\n", node->passagem.localizador);
}

void inserir_no(No *node, No *novo)
{
  if (node == NULL)
  {
    printf("Erro\n");
    return;
  }

  if (node->passagem.localizador < novo->passagem.localizador)
  { // caso o localizador do nó a ser inserido seja maior que o localizador do nó que está na raiz
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
  { // caso o localizador do nó a ser inserido seja menor que o localizador do nó que está na raiz
    // o nó a ser inserido irá para a esquerda da raiz
    if (node->esquerda == NULL)
    {
      node->esquerda = novo;
      return;
    }
    inserir_no(node->esquerda, novo);
  }
}

// funcao pra preencher a arvore sem precisar digitar
No *preencher_arvore(char *data, float preco, char *destino)
{
  No *node = (No *)malloc(sizeof(No));

  strcpy(node->passagem.data, data);
  fflush(stdin);

  node->passagem.preco = preco;
  fflush(stdin);

  strcpy(node->passagem.destino, destino);
  fflush(stdin);

  node->passagem.localizador = gerar_localizador();

  node->esquerda = NULL;
  node->direita = NULL;

  return node;
}
// funcao inserir para os testes serem mais rápidos
void inserir_teste(No **raiz, char *data, float preco, char *destino)
{

  if ((*raiz) == NULL)
  {
    // chama a funcao preencher_arvore passando as strings e o valor do preco a serem inseridos
    *raiz = preencher_arvore(data, preco, destino);
    return;
  }

  No *novo = preencher_arvore(data, preco, destino);
  inserir_no(*raiz, novo);
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

void inserir_raiz(No **raiz) // metodo para inserir uma folha na arvore
{

  if ((*raiz) == NULL) // se a raiz for nula, ja insere a nova folha na raiz e encerra a função
  {
    *raiz = criar_no();
    return;
  }
  // caso a raiz nao seja nula, irá criar um novo nó e chamar a função inserir nó;
  No *novo = criar_no();
  inserir_no(*raiz, novo);
}

void buscar_destino(No *node, char *destino)
{

  if (node == NULL) // caso o nó seja nulo, retorna
  {
    return;
  }

  // pra imprimir ordenado é só passar pelo nó à esqeurda primeiro
  buscar_destino(node->esquerda, destino);

  if (strcmp(node->passagem.destino, destino) == 0) // se encontrar o destino inserido pelo usuario irá imprimir e continuar procurando
  {
    imprimir_folha(node);
  }
  
  buscar_destino(node->direita, destino);

  return;
}

void faturamento(No *node)
{
  if (node == NULL)
  {
    return;
  }

  arrecadacao += node->passagem.preco; // adiciona o preco da passagem de determinado nó
                                       // ao contador global "arrecadacao"
  qnt_passagens++;                     // adiciona 1 ao contador global "qnt_passagens"

  faturamento(node->direita);
  faturamento(node->esquerda);

  // armazenando localizadora struct (também global) depois de percorrer toda a arvore, para na função imprimir_global
  // poder imprimir o valor arrecadado em ambos os paises
  fatura.valor = arrecadacao;
  fatura.qtde = qnt_passagens;
}

void faturamento_global()
{
  int qtde_br;    // irá armazenar a quantidade de passagens que existem no brasil
  float valor_br; // ira armazenar a arrecadacao total das passagens no brasil

  faturamento(root_br); // ira fzr o faturamento no brasil

  valor_br = fatura.valor; // recebe o valor que esta armazenado na struct
  qtde_br = fatura.qtde;   // pois na proxima vez q chamar a funcao faturamento esses valores serao substituidos

  // zerando os contadores para não acumularem
  arrecadacao = 0;
  qnt_passagens = 0;

  faturamento(root_ar); // realizando o faturamento na argentina

  // zerando os contadores para não acumularem
  arrecadacao = 0;
  qnt_passagens = 0;

  // imprimindo o valor arrecadado que está armazenado na struct, referente à argentina somado com as variaveis
  // que armazenaram o do brasil
  printf("Faturamento Global: %f\n", fatura.valor + valor_br);
  printf("Quantidade Global de passagens Vendidas: %d\n", fatura.qtde + qtde_br);
}

void menu()
{
  printf("\n------MENU-----\n");
  printf("1-Inserir Passagem para Brasil\n");
  printf("2-Inserir Passagem para Argentina\n");
  printf("3-Buscar Passagem para Brasil\n");
  printf("4-Buscar Passagem para Argentina\n");
  printf("5-Imprimir Arvore Brasil\n");
  printf("6-Imprimir Arvore Argentina\n");
  printf("7-Faturamento Brasil\n");
  printf("8-Faturamento Argentina\n");
  printf("9-Faturamento Global\n");
  printf("10-Consolidar Vendas\n");
  printf("11-Imprimir Arvore Consolidada\n");
  printf("12-Faturamento Arvore Consolidada\n");
  printf("13-Preencher Arvores\n");
  printf("0-Sair\n");
}

void inserir_consolidada(No **root, No *node)
{
  // metodo de inserir para a arvore consolidada, o teste da raiz nula está aqui dentro desse metodo
  if (*root == NULL)
  {
    *root = node;
    return;
  }

  if ((*root)->passagem.localizador < node->passagem.localizador)
  {
    if ((*root)->direita == NULL)
    {
      (*root)->direita = node;
      return;
    }
    inserir_consolidada(&(*root)->direita, node);
  }
  else
  {
    if ((*root)->esquerda == NULL)
    {
      (*root)->esquerda = node;
      return;
    }
    inserir_consolidada(&(*root)->esquerda, node);
  }
}

No *buscar_pai(No *node, int num)
{
  if (node == NULL)
    return NULL;

  if ((node->esquerda != NULL) && (node->esquerda->passagem.localizador == num))
  {
    return node;
  }

  if ((node->direita != NULL) && (node->direita->passagem.localizador == num))
  {
    return node;
  }

  if (node->passagem.localizador < num)
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

No *maior(No *node)
{
  if (node == NULL)
    return NULL;
  if (node->direita == NULL)
    return node;
  return maior(node->direita);
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
    remover(pai, substituto->passagem.localizador);
    substituto->esquerda = removido->esquerda;
    substituto->direita = removido->direita;
    if (pai->passagem.localizador < substituto->passagem.localizador)
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
    if (pai->passagem.localizador < num)
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

  int num = (*raiz)->passagem.localizador;
  No *removido = *raiz;
  if ((removido)->passagem.localizador == num)
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

      remover(*raiz, substituto->passagem.localizador);

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

void consolidar(No **root)
{
  while ((*root) != NULL)
  {
    inserir_consolidada(&root_consolidada, remover_raiz(root));
  }
  // No *inserir =  remover_raiz(root);
  // while ((*root) != NULL)
  // {
  //   inserir_consolidada(&root_consolidada,inserir);
  // }
}

void preencher()
{
  // eliminando a parte de precisar inserir para agilizar os testes
  inserir_teste(&root_br, "12/1/2012", 1400, "sao paulo");

  inserir_teste(&root_br, "17/2/2013", 2400, "sao paulo");

  inserir_teste(&root_br, "16/3/2014", 3400, "sao paulo");

  inserir_teste(&root_br, "15/4/2015", 4400, "fortaleza");

  inserir_teste(&root_br, "14/5/2016", 5400, "rio de janeiro");

  inserir_teste(&root_br, "13/6/2017", 6400, "florianopolis");

  inserir_teste(&root_ar, "12/7/2018", 7400, "buenos aires");

  inserir_teste(&root_ar, "15/8/2019", 8400, "buenos aires");

  inserir_teste(&root_ar, "17/8/2020", 9400, "mendonza");

  inserir_teste(&root_ar, "15/9/2021", 10400, "bariloche");

  inserir_teste(&root_ar, "19/10/2022", 11400, "salta");

  inserir_teste(&root_ar, "11/09/2023", 12400, "cordova");
}