#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node_t;

void delete_list(node_t **ptr_head);
void print_list(node_t *head);
void append(node_t **ptr_head, int val);
void unshift(node_t **ptr_head, int val);
int shift(node_t **ptr_head);
int pop(node_t **ptr_head);
int remove_by_index(node_t **ptr_head, int index);

int main() {
    node_t *head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    unshift(&head, 4);
    unshift(&head, 5);

    printf("나온 숫자: %d\n", shift(&head));
    printf("나온 숫자: %d\n", remove_by_index(&head, 0));
    printf("나온 숫자: %d\n", remove_by_index(&head, 1));
    print_list(head);
    printf("나온 숫자: %d\n", pop(&head));
    
    print_list(head);

    delete_list(&head);
}

void delete_list(node_t **ptr_head) {
    node_t *current = *ptr_head;
    *ptr_head = NULL;

    while (current != NULL) {
        free(current);
        current = current->next;
    }
}

void print_list(node_t *head) {
    node_t *current = head;

    while (current != NULL) {
        printf("{%d} -> ", current->val);
        current = current->next;
    }
    printf("NULL");
    printf("\n");
}

void append(node_t **ptr_head, int val) {
    if (*ptr_head == NULL){
        *ptr_head = (node_t *)malloc(sizeof(node_t));
        (*ptr_head)->val = val;
        (*ptr_head)->next = NULL;
        return;
    }

    node_t *current = *ptr_head;
    while (current->next != NULL)
        current = current->next;

    current->next = (node_t *)malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

void unshift(node_t **ptr_head, int val){
    node_t *new_node;
    new_node = (node_t *)malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *ptr_head;
    *ptr_head = new_node;
}

int shift(node_t **ptr_head) {
    node_t *current = *ptr_head;
    if (current == NULL)
        return -1;
    *ptr_head = current->next;
    int retval = current->val;
    free(current);
    return retval;
}

int pop(node_t **ptr_head) {
    if (*ptr_head == NULL)
        return -1;
    node_t *current = *ptr_head;
    if (current->next == NULL) {
        *ptr_head = NULL;
        int retval = current->val;
        free(current);
        return retval;
    }
    node_t *before = *ptr_head;
    current = current->next;
    while (current->next != NULL){
        before = before->next;
        current = current->next;
    }
    before->next = NULL;
    int retval = current->val;
    free(current);
    return retval;
}

int remove_by_index(node_t **ptr_head, int index) {
    if (*ptr_head == NULL)
        return -1;

    if (index == 0)
        return shift(ptr_head);
    
    node_t *current = *ptr_head;
    node_t *before = *ptr_head;

    current = current->next;

    if (current == NULL)
        return -1;

    for (int i = 1; i < index; i++){
        current = current->next;
        before = before->next;
        if (current == NULL)
            return -1;
    }
    before->next = current->next;
    int retval = current->val;
    free(current);
    return retval;
}