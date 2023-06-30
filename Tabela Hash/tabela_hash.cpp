#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define size 50
#define qnt_pessoas_sorteadas 10
#define mod_hash_0 7
#define mod_hash_1 11

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

    int chave = int(new_p->nome[0]);
    printf("Chave Participante: %d\n", chave);
    new_p->chave = chave;

    return new_p;
}

int insertion(hash_table *root, participante *participante, int k = 0)
{
    int index = hash(participante->chave, k);

    if (root->participantes[index] == NULL)
    { // nao ocorre colisão, posso inserir
        root->participantes[index] = participante;
        return 1;
    }
    else if (strcmp(root->participantes[index]->nome, participante->nome) == 0)
    {
        printf("Participante já cadastrado!\n");
        return 1;
    }
    else
    {
        if (k < 3000) // numero arbitrario para as tentativas
        {
            k++;
            return insertion(root, participante, k);
        }
    }
    return 0;
}

participante *busca(hash_table *root, char *nome, int k = 0)
{
    if (root == NULL)
    {
        printf("Tabela Hash vazia.\n");
        return NULL;
    }
    int chave = int(nome[0]);
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
    // como alguns index ficam vazios, o sorteio acabara nao imprimindo exatatemente 10
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
    }else{
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
//     int chave = int(p->nome[0]);
//     printf("Chave Participante: %d\n", chave);
//     p->chave = chave;
//     return p;
// }
// void preencher_tabela(hash_table *root)
// {
//     participante *p1 = cria_participante("Filipe", "Astronauta");
//     insertion(root, p1);
//     p1 = cria_participante("Joana", "Engenheira");
//     insertion(root, p1);
//     p1 = cria_participante("Pedro", "Médico");
//     insertion(root, p1);
//     p1 = cria_participante("Laura", "Advogada");
//     insertion(root, p1);
//     p1 = cria_participante("Ricardo", "Professor");
//     insertion(root, p1);
//     p1 = cria_participante("Mariana", "Arquiteta");
//     insertion(root, p1);
//     p1 = cria_participante("Antonio", "Policial");
//     insertion(root, p1);
//     p1 = cria_participante("Camila", "Bombeira");
//     insertion(root, p1);
//     p1 = cria_participante("Gustavo", "Empresário");
//     insertion(root, p1);
//     p1 = cria_participante("Ana", "Psicóloga");
//     insertion(root, p1);
//     p1 = cria_participante("Lucas", "Estudante");
//     insertion(root, p1);
//     p1 = cria_participante("Juliana", "Atleta");
//     insertion(root, p1);
//     p1 = cria_participante("Henrique", "Cientista");
//     insertion(root, p1);
//     p1 = cria_participante("Isabela", "Artista");
//     insertion(root, p1);
//     p1 = cria_participante("Eduardo", "Músico");
//     insertion(root, p1);
//     p1 = cria_participante("Amanda", "Jornalista");
//     insertion(root, p1);
//     p1 = cria_participante("Felipe", "Programador");
//     insertion(root, p1);
//     p1 = cria_participante("Carolina", "Piloto");
//     insertion(root, p1);
//     p1 = cria_participante("Vitor", "Enfermeiro");
//     insertion(root, p1);
//     p1 = cria_participante("Renata", "Chef");
//     insertion(root, p1);
//     p1 = cria_participante("Fernando", "Fotógrafo");
//     insertion(root, p1);
//     p1 = cria_participante("Larissa", "Estilista");
//     insertion(root, p1);
//     p1 = cria_participante("Bruno", "Vendedor");
//     insertion(root, p1);
//     p1 = cria_participante("Marina", "Pesquisadora");
//     insertion(root, p1);
//     p1 = cria_participante("Roberto", "Cineasta");
//     insertion(root, p1);
//     p1 = cria_participante("Paula", "Engenheira Civil");
//     insertion(root, p1);
//     p1 = cria_participante("Rafael", "Escritor");
//     insertion(root, p1);
//     p1 = cria_participante("Mariano", "Pintor");
//     insertion(root, p1);
//     p1 = cria_participante("Sofia", "Psiquiatra");
//     insertion(root, p1);
//     p1 = cria_participante("Thiago", "Empreendedor");
//     insertion(root, p1);
//     p1 = cria_participante("Natalia", "Bailarina");
//     insertion(root, p1);
//     p1 = cria_participante("Gabriel", "Cantor");
//     insertion(root, p1);
//     p1 = cria_participante("Beatriz", "Bióloga");
//     insertion(root, p1);
//     p1 = cria_participante("Vinicius", "Motorista");
//     insertion(root, p1);
//     p1 = cria_participante("Letícia", "Designer");
//     insertion(root, p1);
//     p1 = cria_participante("Rodrigo", "Político");
//     insertion(root, p1);
//     p1 = cria_participante("Cristina", "Veterinária");
//     insertion(root, p1);
//     p1 = cria_participante("Leonardo", "Engenheiro de Software");
//     insertion(root, p1);
//     p1 = cria_participante("Tatiana", "Farmacêutica");
//     insertion(root, p1);
//     p1 = cria_participante("Alexandre", "Empresário");
//     insertion(root, p1);
//     p1 = cria_participante("Patrícia", "Psicóloga");
//     insertion(root, p1);
//     p1 = cria_participante("Guilherme", "Advogado");
//     insertion(root, p1);
//     p1 = cria_participante("Carla", "Arquiteta");
//     insertion(root, p1);
//     p1 = cria_participante("Daniel", "Professor");
//     insertion(root, p1);
//     p1 = cria_participante("Renata", "Pesquisadora");
//     insertion(root, p1);
//     p1 = cria_participante("Marcelo", "Engenheiro Elétrico");
//     insertion(root, p1);
//     p1 = cria_participante("Gisele", "Atleta");
//     insertion(root, p1);
//     p1 = cria_participante("Luciano", "Artista Plástico");
//     insertion(root, p1);
//     p1 = cria_participante("Mariana", "Médica");
//     insertion(root, p1);
//     p1 = cria_participante("André", "Músico");
//     insertion(root, p1);
//     p1 = cria_participante("Carolina", "Estudante de Direito");
// }

int main()
{
    srand(time(NULL));
    hash_table *root = init_hash_table();
    char nome[20];
    int status = 1;
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
            status = insertion(root, p);
            if (status == 0)
            {
                printf("Erro na inserção: Tabela cheia ou todos os index gerados estão ocupados.\n");
            }
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