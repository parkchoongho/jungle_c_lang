#include <stdio.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} node_t;

void insert(node_t **ptr_root, int val);
void inorder_tree_walk(node_t *node);
node_t* search(node_t *node, int val);
void delete_tree(node_t *node);
node_t* minimum(node_t *node);
node_t* maximum(node_t *node);

int main() {
    node_t *root = NULL;

    insert(&root, 5);
    insert(&root, 2);
    insert(&root, 7);
    insert(&root, 1);
    insert(&root, 3);
    insert(&root, 6);
    insert(&root, 8);

    printf("찾은 값: %d\n", search(root, 8)->val);
    printf("찾은 값: %d\n", minimum(root)->val);
    printf("찾은 값: %d\n", maximum(root)->val);

    inorder_tree_walk(root);
    delete_tree(root);
}

void insert(node_t **ptr_root, int val) {
    if (*ptr_root == NULL) {
        *ptr_root = (node_t *)malloc(sizeof(node_t));

        (*ptr_root)->val = val;
        (*ptr_root)->left = NULL;
        (*ptr_root)->right = NULL;
        return;
    }

    node_t *current = *ptr_root;

    while (1) {
        if (current->val < val){
            if (current->right == NULL) {
                current->right = (node_t *)malloc(sizeof(node_t));
                current->right->val = val;
                current->right->left = NULL;
                current->right->right = NULL;
                break;
            } else {
                current = current->right;
            }
        }
        else{
            if (current->left == NULL){
                current->left = (node_t *)malloc(sizeof(node_t));
                current->left->val = val;
                current->left->left = NULL;
                current->left->right = NULL;
                break;
            } else {
                current = current->left;
            }
        }
    }
}

void inorder_tree_walk(node_t *node) {
    node_t *current = node;
    if (current == NULL)
        return;
    else {
        inorder_tree_walk(current->left);
        printf("{ %d }\n", current->val);
        inorder_tree_walk(current->right);
    }
}

node_t* search(node_t *node, int val) {
    node_t *current = node;
    while (current != NULL && current->val != val){
        if (val > current->val)
            current = current->right;
        else
            current = current->left;
    }

    return current;
}

void delete_tree(node_t *node) {
    node_t *current = node;
    if (current == NULL)
        return;
    else {
        node_t *left_node = current->left;
        node_t *right_node = current->right;
        free(current);
        delete_tree(left_node);
        delete_tree(right_node);
    }
}

node_t* minimum(node_t *node){
    node_t *current = node;
    if (current == NULL)
        return current;
    while (current->left != NULL)
        current = current->left;
    return current;
}

node_t* maximum(node_t *node){
    node_t *current = node;
    if (current == NULL)
        return current;
    while (current->right != NULL)
        current = current->right;
    return current;
}