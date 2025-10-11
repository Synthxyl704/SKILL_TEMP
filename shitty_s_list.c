#include <stdio.h>
#include <stdlib.h>

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
    Node *temp = *head;
    while (temp->next && temp->next->data != target) temp = temp->next;
    if (temp->next) {
        Node* newNode = createNode(data);
        newNode->next = temp->next;
        temp->next = newNode;
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
    Node* temp = *head;
    while (temp->next->next) temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}

void deleteBefore(Node** head, int target) {
    if (!*head || !(*head)->next) return;
    if ((*head)->next->data == target) {
        deleteBegin(head);
        return;
    }
    Node *temp = *head;
    while (temp->next->next && temp->next->next->data != target) temp = temp->next;
    if (temp->next->next) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        free(toDelete);
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
        Node *temp = *head;
        for (int i = 0; temp && i < pos - 1; i++) temp = temp->next;
        if (temp && temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            free(toDelete);
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
    int c = 0;
    while (head) {
        c++;
        head = head->next;
    }
    return c;
}

void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    
    insertEnd(&head, 1);
    insertEnd(&head, 3);
    insertBegin(&head, 0);
    insertBefore(&head, 3, 2);
    insertAfter(&head, 1, 9);
    
    printf("List: ");
    printList(head);
    printf("Count: %d\n", count(head));
    
    return 0;
}
