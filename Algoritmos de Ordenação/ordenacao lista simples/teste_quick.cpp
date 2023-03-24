#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* getTail(Node* node) {
    while (node != NULL && node->next != NULL) {
        node = node->next;
    }
    return node;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = NULL, *atual = head, *fim = pivot;
    while (atual != pivot) {
        if (atual->value < pivot->value) {
            if (*newHead == NULL) {
                *newHead = atual;
            }
            prev = atual;
            atual = atual->next;
        } else {
            if (prev != NULL) {
                prev->next = atual->next;
            }
            Node* tmp = atual->next;
            atual->next = NULL;
            fim->next = atual;
            fim = atual;
            atual = tmp;
        }
    }
    if (*newHead == NULL) {
        *newHead = pivot;
    }
    *newEnd = fim;
    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) {// cabeca == NULL
        return head;
    }
    
    Node* newHead = NULL, *newEnd = NULL;
    Node* pivot = partition(head, end, &newHead, &newEnd);
    if (newHead != pivot) {
        Node* tmp = newHead;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = NULL;
        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

void quickSort(Node** headRef) {
    *headRef = quickSortRecur(*headRef, getTail(*headRef));
}

void insertNode(Node** headRef, int value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = *headRef;
    *headRef = newNode;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;

    // Insere alguns elementos na lista
    for(int i=0;i<8;i++){
        int n;
        printf("insira um numero: ");
        scanf("%d",&n);
        insertNode(&head, n);
    }
    insertNode(&head, 10);
    insertNode(&head, 7);
    insertNode(&head, 8);
    insertNode(&head, 9);
    insertNode(&head, 1);
    insertNode(&head, 5);

    printf("Lista original: \n");
    printList(head);

    quickSort(&head);

    printf("Lista ordenada: \n");
    printList(head);

    return 0;
}
