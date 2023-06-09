#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define size 50
#define qnt_pessoas_sorteadas 10

// a distribuição fica melhor usando os tres numeros primos mais proximos de 50: 41,43,47
#define mod_hash_0 41
#define mod_hash_1 43

int hash_0(int chave)
{
    return chave % mod_hash_0;
}
int hash_1(int chave)
{
    return chave % mod_hash_1;
}
int hash(int chave, int k)
{
    return (hash_0(chave) + (k * hash_1(chave))) % size;
}

typedef struct pessoa
{
    int chave;
    char nome[20];
    char emprego[20];
    float renda_mensal;

} participante;

typedef struct hash
{
    int pos = 0;
    participante *participantes[size];

} hash_table;

hash_table *init_hash_table()
{
    hash_table *table = new hash_table;
    for (int i = 0; i < size; i++)
    {
        table->participantes[i] = NULL;
    }
    return table;
}
int gera_chave(char *nome)
{
    int chave = 0;

    for (int i = 0; nome[i] != '\0'; i++)
    {
        chave += int(nome[i]);
    }
    return chave;
}

participante *init_participante()
{
    participante *new_p = new participante;

    printf("Insira o nome do participante: ");
    scanf("%s", new_p->nome);
    fflush(stdin);

    printf("Insira o emprego do participante: ");
    scanf("%s", new_p->emprego);
    fflush(stdin);

    printf("Insira a renda mensal do participante: ");
    scanf("%f", &new_p->renda_mensal);

    new_p->chave = gera_chave(new_p->nome);

    return new_p;
}

void insertion(hash_table *root, participante *participante, int k = 0)
{
    int index = hash(participante->chave, k);
    // printf("Index: %d\n",index);

    if (root->participantes[index] == NULL)
    { // nao ocorre colisão, posso inserir
        root->pos++;
        root->participantes[index] = participante;
        return;
    }
    else if (strcmp(root->participantes[index]->nome, participante->nome) == 0)
    {
        printf("Participante já cadastrado!\n");
        return;
    }
    else if (k < size) // numero arbitrario para as tentativas
    {
        k++;
        return insertion(root, participante, k);
    }
    printf("Erro na inserção: Tabela cheia ou todos os index gerados estão ocupados.\n");
    return;
}

participante *busca(hash_table *root, char *nome, int k = 0)
{
    if (root == NULL)
    {
        printf("Tabela Hash vazia.\n");
        return NULL;
    }
    int chave = gera_chave(nome);
    int index = hash(chave, k);

    if (root->participantes[index] == NULL)
    {
        printf("Participante não encontrado.\n");
        return NULL;
    }
    else if (strcmp(root->participantes[index]->nome, nome) == 0)
    {
        return root->participantes[index];
    }
    else if (k < size)
    {
        // deu colisão, incremento o k e tento buscar dnv
        k++;
        return busca(root, nome, k);
    }
    return NULL;
}

int sorteia_index()
{
    return rand() % size;
}

void imprimir_tabela(hash_table *root)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (root->participantes[i] == NULL)
        {
            printf("\n participante %d : NULL ", i);
        }
        else
        {
            printf("\n participante %d key: %d Nome: %s \t", i, root->participantes[i]->chave, root->participantes[i]->nome);
        }
    }
}

void imprimir_participante(participante *p)
{
    if (p == NULL)
    {
        return;
    }
    printf("Nome: %s ", p->nome);
    printf("Emprego: %s ", p->emprego);
    printf("Renda Mensal: %.2f\n", p->renda_mensal);
}

bool numero_repetido(int num, int *sorteados, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (num == sorteados[i])
        {
            return true;
        }
    }
    return false;
}

void imprimir_sorteados(hash_table *root)
{
    if (root->pos < 10)
    {
        printf("Nao ha cadastros suficientes para realizar o sorteio");
        return;
    }
    int sorteados[qnt_pessoas_sorteadas];

    for (int i = 0; i < qnt_pessoas_sorteadas; i++)
    {
        int index;
        do
        {
            index = sorteia_index();
        } while (numero_repetido(index, sorteados, i));
        sorteados[i] = index;
    }
    // como alguns index podem ficar vazios, o sorteio acabara nao imprimindo exatamente 10
    // pra resolver isso, dps de sortear os numeros verificando se eles estão repetidos
    // vou verificar se algum index gerado leva pra um campo nulo na tabela
    // caso isso aconteça, chamo a função recursivamente
    // ate que nenhum index gerado leve para um campo nulo
    // a variavel chama_outra resolverá isso
    int chama_outra = 0;

    for (int i = 0; i < qnt_pessoas_sorteadas; i++)
    {
        if (root->participantes[sorteados[i]] == NULL)
        {
            chama_outra = 1;
        }
    }

    if (chama_outra == 0)
    {
        for (int i = 0; i < qnt_pessoas_sorteadas; i++)
        {
            printf("%d: ", i + 1);
            imprimir_participante(root->participantes[sorteados[i]]);
            printf("\n");
        }
    }
    else
    {
        imprimir_sorteados(root);
    }
}

void menu()
{
    printf("\nMENU\n");
    printf("1- Cadastrar Participante\n");
    printf("2- Buscar Participante\n");
    printf("3- Sortear\n");
    printf("4- Imprimir Participantes\n");
    printf("0-Sair\n");
}

// participante *cria_participante(char *nome, char *emprego)
// {
//     participante *p = new participante;
//     strcpy(p->nome, nome);
//     strcpy(p->emprego, emprego);
//     p->renda_mensal = (rand() % 10000) / 100.0; // Renda mensal aleatória entre 0 e 10000
//     int chave = gera_chave(p->nome);
//     printf("Chave Participante: %d\n", chave);
//     p->chave = chave;
//     return p;
// }
// void preencher_tabela(hash_table *root)
// {
//     participante *p1 = cria_participante("Filipe", "Astronauta");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Joana", "Engenheira");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Pedro", "Médico");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Laura", "Advogada");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Ricardo", "Professor");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Mariana", "Arquiteta");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Antonio", "Policial");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Camila", "Bombeira");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Gustavo", "Empresário");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Ana", "Psicóloga");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Lucas", "Estudante");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Juliana", "Atleta");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Henrique", "Cientista");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Isabela", "Artista");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Eduardo", "Músico");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Amanda", "Jornalista");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Felipe", "Programador");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Carolina", "Piloto");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Vitor", "Enfermeiro");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Renata", "Chef");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Fernando", "Fotógrafo");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Larissa", "Estilista");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Bruno", "Vendedor");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Marina", "Pesquisadora");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Roberto", "Cineasta");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Paula", "Engenheira Civil");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Rafael", "Escritor");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Mariano", "Pintor");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Sofia", "Psiquiatra");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Thiago", "Empreendedor");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Natalia", "Bailarina");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Gabriel", "Cantor");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Beatriz", "Bióloga");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Vinicius", "Motorista");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Letícia", "Designer");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Rodrigo", "Político");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Cristina", "Veterinária");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Leonardo", "Engenheiro de Software");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Tatiana", "Farmacêutica");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Alexandre", "Empresário");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Patrícia", "Psicóloga");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Guilherme", "Advogado");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Carla", "Arquiteta");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Daniel", "Professor");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("François", "Pesquisadora");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Marcelo", "Engenheiro Elétrico");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Gisele", "Atleta");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Luciano", "Artista Plástico");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Mariana", "Médica");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("André", "Músico");
//     printf("%s: \n", p1->nome);
//     insertion(root, p1);
//     p1 = cria_participante("Carolina", "Estudante de Direito");
//     printf("%s: \n", p1->nome);
// }

int main()
{
    srand(time(NULL));
    hash_table *root = init_hash_table();
    char nome[20];
    int opc = -1;
    participante *p;

        // função pra teste
    // preencher_tabela(root);

    while (opc != 0)
    {
        menu();
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            p = init_participante();
            insertion(root, p);
            break;
        case 2:
            printf("Insira o nome a ser procurado: ");
            scanf("%s", nome);
            p = busca(root, nome);
            imprimir_participante(p);
            break;
        case 3:
            imprimir_sorteados(root);
            break;
        case 4:
            imprimir_tabela(root);
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