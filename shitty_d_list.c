#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertBegin(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!*head) *head = newNode;
    else {
        Node* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void insertBefore(Node** head, int target, int data) {
    if (!*head) return;
    if ((*head)->data == target) {
        insertBegin(head, data);
        return;
    }
    Node *temp = *head, *prev = NULL;
    while (temp && temp->data != target) {
        prev = temp;
        temp = temp->next;
    }
    if (temp) {
        Node* newNode = createNode(data);
        prev->next = newNode;
        newNode->next = temp;
    }
}

void insertAfter(Node** head, int target, int data) {
    Node* temp = *head;
    while (temp && temp->data != target) temp = temp->next;
    if (temp) {
        Node* newNode = createNode(data);
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void insertAtPosition(Node** head, int pos, int data) {
    if (pos == 0) insertBegin(head, data);
    else {
        Node* temp = *head;
        for (int i = 0; temp && i < pos - 1; i++) temp = temp->next;
        if (temp) {
            Node* newNode = createNode(data);
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

// DELETE OPERATIONS
void deleteBegin(Node** head) {
    if (*head) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void deleteEnd(Node** head) {
    if (!*head) return;
    if (!(*head)->next) {
        free(*head);
        *head = NULL;
        return;
    }
    Node *temp = *head, *prev = NULL;
    while (temp->next) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    free(temp);
}

void deleteBefore(Node** head, int target) {
    if (!*head || !(*head)->next) return;
    if ((*head)->next->data == target) {
        deleteBegin(head);
        return;
    }
    Node *temp = *head, *prev = NULL, *prev2 = NULL;
    while (temp && temp->next && temp->next->data != target) {
        prev2 = prev;
        prev = temp;
        temp = temp->next;
    }
    if (temp && temp->next && temp->next->data == target) {
        if (prev2) {
            prev2->next = temp;
            free(prev);
        }
    }
}

void deleteAfter(Node** head, int target) {
    Node* temp = *head;
    while (temp && temp->data != target) temp = temp->next;
    if (temp && temp->next) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        free(toDelete);
    }
}

void deleteAtPosition(Node** head, int pos) {
    if (!*head) return;
    if (pos == 0) deleteBegin(head);
    else {
        Node *temp = *head, *prev = NULL;
        for (int i = 0; temp && i < pos; i++) {
            prev = temp;
            temp = temp->next;
        }
        if (temp) {
            prev->next = temp->next;
            free(temp);
        }
    }
}

Node* search(Node* head, int target) {
    while (head && head->data != target) head = head->next;
    return head;
}


void merge(Node** list1, Node* list2) {
    if (!*list1) *list1 = list2;
    else {
        Node* temp = *list1;
        while (temp->next) temp = temp->next;
        temp->next = list2;
    }
}

int count(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int32_t main(int argc, char *argv[]) {
    struct Node *headNode = (Node*) malloc(sizeof(Node));
    headNode->data = 69;

    insertBegin(&headNode, 420);

    printList(headNode);

    return EXIT_SUCCESS;
}
