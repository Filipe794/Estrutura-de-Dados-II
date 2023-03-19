#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int i = 15; // variavel global pra facilitar mudar o tamanho do vetor (15,127,32.767)

int loc() //gerador do numero aleatorio
{
    return rand() % (i + 1);//i+1 pra deixar o valor na base 2
}

int main()
{
    int array[i]; // vetor
    int j; // contador pro for
    for (j = 0; j < i; j++)
    {
        array[j] = loc(); // preenchendo o vetor
    }

    for (int j = 0; j < i; j++)
    {
        printf("array %d: %d\n", j, array[j]); // imprimindo a posição do vetor e o valor dela
    }

    int search = loc(); // gerando o valor q vai ser procurado

    printf("search: %d\n", search); // imprimindo o valor

    int cont = 0; // criando o contador

    j = 0; // zerando o contador q tinha usado no for, agr vou usar no while

    do
    {
        cont++; // adiciona um no contador de comparações
        if (array[j] == search)
        {
            printf("comparações: %d", cont);
            return 0;
        }
        j++; // passando pra proxima posição do vetor
    } while ((j < i) || (array[j] == search));

    printf("numero nao encontrado\n");
    printf("comparacoes: %d", cont);

    return 0;
}