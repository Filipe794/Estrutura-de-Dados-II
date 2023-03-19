#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

// função para criar um novo nó com o valor informado
Node* createNode(char* value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = (char*) malloc(strlen(value) + 1);
    strcpy(newNode->value, value);
    newNode->next = NULL;
    return newNode;
}

// função para inserir um novo nó na lista
void insert(Node** head, char* value) {
    Node* newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

// função para imprimir a lista
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%s ", current->value);
        current = current->next;
    }
    printf("\n");
}

// função para ordenar a lista com Bubble Sort
void bubbleSort(Node* head) {
    int cont_troca;
    Node *aux, *ultimo = NULL;
    // lprt é o ponteiro para o ultimo elemento da lista
    // ele sera sempre atualizado ao final do laço mais exterior para limitar a repetição e não comparar com elementos já ordernados

    /* Checking for empty list */
    if (head == NULL)
        return;

    do {
        cont_troca = 0;
        aux = head;

        while (aux->next != ultimo) {
            if (strcmp(aux->value, aux->next->value) > 0) {
                // troca os ponteiros dos nós
                Node* temp = aux->next;
                aux->next = temp->next;
                temp->next = aux;
                if (aux == head) {
                    head = temp;
                }
                else {
                    Node* prev = head;
                    while (prev->next != aux) {
                        prev = prev->next;
                    }
                    prev->next = temp;
                }
                cont_troca = 1;
            }
            else {
                aux = aux->next;
            }
        }
        ultimo = aux;
    } while (cont_troca);
}

int main() {
    Node* head = NULL;

    insert(&head, "banana");
    insert(&head, "abacate");
    insert(&head, "laranja");
    insert(&head, "uva");
    insert(&head, "manga");

    printf("Lista antes da ordenação: ");
    printList(head);

    bubbleSort(head);

    printf("Lista depois da ordenação: ");
    printList(head);

    return 0;
}
