// NÃO FUNCIONA




// #include <stdio.h>
// #include <stdlib.h>
// #include <iostream>
// using namespace std;

// #define T 3

// typedef struct
// {
//   string codigo_barra;
//   string nome;
//   string data;
//   int quant;
//   float preco;
// } medicamento;

// typedef struct page
// {
//   int pos = 0;
//   bool folha = false;
//   string codigos[T - 1];
//   struct page *pai = NULL;
//   medicamento *medicamentos[T - 1];
//   struct page *filhos[T];
//   struct page *prox = NULL;
// } pagina;

// pagina *criar_pagina();
// void inserir_na_folha(pagina **root, medicamento *med);

// void imprimir_medicamento(medicamento *med)
// {
//   cout << "Codigo de barras: " << med->codigo_barra << endl;
//   printf("Nome: %s\n", med->nome);
//   printf("Data do Cadastro: %s\n", med->data);
//   printf("Quantidade: %d\n", med->quant);
//   printf("Preço: %f\n", med->preco);
// }

// void print_medicamentos(pagina *pag)
// {
//   if (pag == NULL)
//     return;

//   if (pag->folha)
//   {
//     for (int i = 0; i < pag->pos; i++)
//     {
//       imprimir_medicamento(pag->medicamentos[i]);
//       printf("\n");
//     }
//     print_medicamentos(pag->prox);
//   }
//   print_medicamentos(pag->filhos[0]);
// }

// void printBPlusTree(pagina *root)
// {
//   if (root != NULL)
//   {
//     printf("[");
//     int i;
//     for (i = 0; i < root->pos; i++)
//     {
//       cout << root->codigos[i] << " ";
//     }
//     printf("]");
//     if (!(root->folha))
//     {
//       cout << "->" << endl;
//       for (i = 0; i < root->pos + 1; i++)
//       {
//         printBPlusTree(root->filhos[i]);
//         if (i < root->pos)
//           cout << root->codigos[i] << " ";
//       }
//     }
//   }
// }

// medicamento *criar_medicamento()
// {
//   medicamento *med = new medicamento;

//   printf("Insira o codigo de barra do medicamento: ");
//   cin >> med->codigo_barra;

//   printf("Insira o nome do medicamento: ");
//   scanf("%s", med->nome);

//   printf("Insira a data do cadastro: ");
//   scanf("%s", med->data);

//   printf("Insira a quantidade do medicamento: ");
//   scanf("%d", &med->quant);

//   printf("Insira o preco do medicamento: ");
//   scanf("%f", &med->preco);

//   return med;
// }

// pagina *dividir_pagina(pagina *esq)
// {

//   int meio = (T - 1) / 2;

//   pagina *pai, *dir;
//   // tratar caso pai!=NULL
//   pai = criar_pagina();
//   dir = criar_pagina();

//   // atribuindo os filhos ao pai
//   pai->filhos[0] = esq;
//   pai->filhos[1] = dir;

//   // encadeando a lista dos vetores das folhas
//   dir->prox = esq->prox;
//   esq->prox = dir;

//   int i;
//   for (i = 0; i < (T - 1) - (meio + 1); i++)
//   {
//     dir->medicamentos[i] = esq->medicamentos[i + (meio + 1)];
//     dir->filhos[i] = esq->filhos[i + (meio + 1)];
//     dir->pos++;

//     esq->medicamentos[i + (meio + 1)] = NULL;
//     esq->filhos[i + (meio + 1)] = NULL;
//     esq->pos--;
//   }

//   dir->filhos[i] = esq->filhos[i + (meio + 1)];
//   esq->filhos[i + (meio + 1)] = NULL;

//   // adicionando o codigo de barra da esq nos codigos do pai
//   pai->codigos[0] = esq->medicamentos[meio]->codigo_barra;
//   pai->pos++;

//   pai->pai = esq->pai;
//   esq->pai = dir->pai = pai;

//   pai->folha = false;
//   if (esq->folha)
//     dir->folha = true;

//   return pai;
// }

// void inserir_pai(pagina **root, pagina *pag, pagina *pai)
// {
//   if ((*root) == NULL)
//   {
//     return;
//   }
//   if (pai == NULL)
//   {
//     *root = pag;
//     return;
//   }

//   if (pai->pos < T - 1)
//   {
//     int i = pai->pos - 1;
//     while (i >= 0 && pag->codigos[0] < pai->codigos[i])
//     {
//       pai->codigos[i + 1] = pai->codigos[i];
//       if (i == pai->pos - 1)
//       {
//         pai->filhos[i + 2] = pai->filhos[i + 1];
//       }
//       pai->filhos[i + 1] = pai->filhos[i];
//       i--;
//     }
//     pai->codigos[i + 1] = pag->codigos[0];
//     pai->filhos[i + 1] = pag->filhos[0];
//     pai->filhos[i + 2] = pag->filhos[1];
//     pai->pos++;
//     return;
//   }
//   else
//   {
//     pagina *new_pai = dividir_pagina(pai);
//     inserir_pai(root, pai, new_pai);
//   }
// }

// pagina *busca_insercao(pagina *root, string codigo_barra)
// {
//   if (root == NULL)
//   {
//     return NULL;
//   }
//   int i = 0;

//   while (i < root->pos && codigo_barra > root->codigos[i])
//     i++;

//   // medicamento ja existe na arvore
//   if (root->folha)
//   {
//     if (codigo_barra == root->codigos[i])
//     {
//       root->medicamentos[i]->quant++;
//       printf("Medicamento já existe. Quantidade incrementada em 1.\n");
//       return NULL;
//     }
//     return root;
//   }
//   return busca_insercao(root->filhos[i], codigo_barra);
// }

// bool verifica_irmao_espaco(pagina *pag)
// {
//   if (pag->prox = NULL)
//   {
//     return false;
//   }

//   if ((pag->prox->pos < T - 1) && (pag->prox->pai == pag->pai))
//   {
//     return true;
//   }
//   return false;
// }

// int pai_index_filho(pagina *pai, pagina *filho)
// {
//   int i;
//   for (i = 0; i < pai->pos + 1; i++)
//   {
//     if (pai->filhos[i] == filho)
//     {
//       return i;
//     }
//   }
//   return -1;
// }

// void inserir_na_folha(pagina **root, medicamento *med)
// {
//   if (*root == NULL)
//   {
//     return;
//   }
//   // retorna uma folha pra realizar uma inserção
//   pagina *pag = busca_insercao(*root, med->codigo_barra);
//   // verifica se a pagina retornada nao é nula
//   if (pag == NULL)
//   {
//     return;
//   }
//   // verifica se o medicamento ja existe na folha
//   int i = pag->pos - 1; // começa do ultimo elemento do vetor
//   while (i >= 0 && pag->medicamentos[i]->codigo_barra > med->codigo_barra)
//   {
//     if (med->codigo_barra == pag->medicamentos[i]->codigo_barra)
//     {
//       pag->medicamentos[i]->quant++;
//       printf("Medicamento já existe. Quantidade incrementada em 1.\n");
//       return;
//     }
//     i--;
//   }
//   // se tem espaço para inserir
//   if (pag->pos < T - 1)
//   {
//     int i = pag->pos - 1;
//     while (i >= 0 && pag->medicamentos[i]->codigo_barra > med->codigo_barra)
//     {
//       pag->medicamentos[i + 1] = pag->medicamentos[i];
//       i--;
//     }
//     pag->medicamentos[i + 1] = med;
//     pag->pos++;
//     return;
//   }
//   else // n tem espaço
//   {
//     // verificar se o prox tem espaço e é do msm pai
//     // fazer uma outra função de inserção que verifica se o pai tem espaço
//     // se n tiver, divide e insere no pai do pai e por ai vai
//     // caso irmao com espaço e possui o mesmo pai
//     if (verifica_irmao_espaco(pag))
//     {
//       int index = pai_index_filho(pag->pai, pag);
//       if (pag->medicamentos[pag->pos - 1]->codigo_barra < med->codigo_barra)
//       {
//         // jogar a ultima posição pra pai
//         pag->pai->codigos[index] = pag->medicamentos[pag->pos - 1]->codigo_barra;
//         inserir_na_folha(root, med);
//         return;
//       }
//       else
//       {
//         medicamento *aux = pag->medicamentos[pag->pos - 1];
//         pag->pos--;
//         inserir_na_folha(root, med);
//         pag->pai->codigos[index] = pag->medicamentos[pag->pos - 1]->codigo_barra;
//         inserir_na_folha(root, aux);
//         return;
//       }
//     }
//     else
//     {
//       pagina *pai = dividir_pagina(pag);
//       inserir_na_folha(&pai, med);
//       inserir_pai(root, pai, pai->pai);
//     }
//   }
// }

// pagina *criar_pagina()
// {
//   pagina *pag = new pagina;
//   for (int i = 0; i < 2 * T - 1; i++)
//   {
//     pag->codigos[i] = '\0';
//     pag->medicamentos[i] = NULL;
//     pag->filhos[i] = NULL;
//   }
//   pag->filhos[2 * T] = NULL;
//   return pag;
// }

// void inserir(pagina **root, medicamento *med)
// {
//   if (*root == NULL)
//   {
//     (*root) = criar_pagina();
//     (*root)->codigos[0] = med->codigo_barra;
//     (*root)->medicamentos[0] = med;
//     (*root)->pos++;
//     (*root)->folha = true;
//   }
//   else
//   {
//     inserir_na_folha(root, med);
//   }
// }

// pagina *busca(pagina *pag, string codigo_barra)
// {
//   if (pag == NULL)
//   {
//     return NULL;
//   }
//   if (pag->folha)
//   {
//     for (int i = 0; i < pag->pos; i++)
//     {
//       if (codigo_barra == pag->medicamentos[i]->codigo_barra)
//       {
//         return pag;
//       }
//     }
//     return NULL;
//   }
//   for (int i = 0; i < pag->pos; i++)
//   {
//     if (codigo_barra <= pag->codigos[i])
//     {
//       return busca(pag->filhos[i], codigo_barra);
//     }
//   }
//   busca(pag->filhos[pag->pos], codigo_barra);
//   return NULL;
// }

// void menu()
// {
//   printf("\nMENU\n");
//   printf("1- Cadastrar Participante\n");
//   printf("2- Buscar Participante\n");
//   printf("3- Sortear\n");
//   printf("4- Imprimir Participantes\n");
//   printf("0-Sair\n");
// }

// int main()
// {
//   pagina *root = NULL;
//   medicamento *med = criar_medicamento();
//   inserir(&root, med);
//   printBPlusTree(root);
//   // med = criar_medicamento();
//   // inserir(&root, med);
//   // med = criar_medicamento();
//   // inserir(&root, med);
//   // imprimir_medicamento(med);
//   // printf("\n");
//   // printf("\n");
//   print_medicamentos(root);

//   int opc = -1;
//   while (opc != 0)
//   {
//     menu();
//     scanf("%d", &opc);
//     switch (opc)
//     {
//     case 1:
//       break;
//     case 2:
//       break;
//     case 3:
//       break;
//     case 4:
//       break;
//     case 0:
//       break;
//     default:
//       printf("Opção inválida\n");
//       break;
//     }
//   }

//   return 0;
// }