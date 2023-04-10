#include <stdio.h>
#include "funcoes.h"

int main()
{
    lista *lst = new lista;
    int opcao;

    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserir_inicio(lst, novo_no());
            break;
        case 2:
            if (lst->cabeca == NULL)
            {
                printf("Nao ha ingressos vendidos\n");
                break;
            }
            insertion_sort(lst);
            buscar_ingresso_cpf(lst);
            break;
        case 3:
            if (lst->cabeca == NULL)
            {
                printf("Nao ha ingressos vendidos\n");
                break;
            }
            insertion_sort(lst);
            buscar_ingresso_data(lst);
            break;
        case 4:
            if (lst->cabeca == NULL)
            {
                printf("Nao ha ingressos vendidos\n");
                break;
            }
            imprimir_lista(lst);
            break;
        case 5:
            if (lst->cabeca == NULL)
            {
                printf("Nao ha ingressos vendidos\n");
                break;
            }
            quick_sort(lst);
            encerra_vendas(lst);
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}