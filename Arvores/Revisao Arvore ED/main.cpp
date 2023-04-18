#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes_arvore.h"

int main()
{
    srand(time(NULL)); // semente do random

    int opc = 1;
    char destiNo[50];

    while (opc != 0)
    {
        menu();
        scanf("%d", &opc);
        fflush(stdin);
        switch (opc)
        {
        case 1:
            inserir_raiz(&root_br);
            break;

        case 2:
            inserir_raiz(&root_ar);
            break;

        case 3:
            printf("Digite o destiNo a ser procurado: ");
            scanf("%50[^\n]s", destiNo);
            buscar_destino(root_br, destiNo);
            break;

        case 4:
            printf("Digite o destiNo a ser procurado: ");
            scanf("%50[^\n]s", destiNo);
            buscar_destino(root_ar, destiNo);
            break;

        case 5:
            imprimir(root_br);
            break;

        case 6:
            imprimir(root_ar);
            break;

        case 7:
            faturamento(root_br);
            printf("Faturamento: %f\n", fatura.valor);
            printf("Quantidade de passagens Vendidas: %d\n", fatura.qtde);
            arrecadacao = 0;  // zerando o contador de arrecadação para nao acumular
            qnt_passagens = 0; // zerando o contador de passagens para nao acumular
            break;

        case 8:
            faturamento(root_ar);
            printf("Faturamento: %f\n", fatura.valor);
            printf("Quantidade de passagens Vendidas: %d\n", fatura.qtde);
            arrecadacao = 0;
            qnt_passagens = 0;
            break;

        case 9:
            faturamento_global();
            arrecadacao = 0;
            qnt_passagens = 0;
            break;

        case 10:
            consolidar(&root_br);
            consolidar(&root_ar);
            printf("Arvores Consolidadas\n");
            break;

        case 11:
            imprimir(root_consolidada);
            break;

        case 12:
            faturamento(root_consolidada);
            printf("Faturamento: %f\n", fatura.valor);
            printf("Quantidade de passagens Vendidas: %d\n", fatura.qtde);
            arrecadacao = 0;
            qnt_passagens = 0;
            break;

        case 13:
            preencher();
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