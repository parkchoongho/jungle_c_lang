#include <stdio.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} node_t;

void insert(node_t **ptr_root, int val);
void bfs(node_t *node);
void delete_tree(node_t *node);

int main() {
    node_t *root = NULL;

    insert(&root, 5);
    insert(&root, 2);
    insert(&root, 7);
    insert(&root, 1);
    insert(&root, 3);
    insert(&root, 6);
    insert(&root, 8);

    bfs(root);
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

void bfs(node_t *node) {
    if (node == NULL)
        return;
    else {
        bfs(node->left);
        printf("{ %d }\n", node->val);
        bfs(node->right);
    }
}

void delete_tree(node_t *node) {
    if (node == NULL)
        return;
    else {
        node_t *left_node = node->left;
        node_t *right_node = node->right;
        free(node);
        delete_tree(left_node);
        delete_tree(right_node);
    }
}