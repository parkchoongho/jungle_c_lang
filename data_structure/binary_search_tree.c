#include <stdio.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node * parent;
    struct node *left;
    struct node *right;
} node_t;

void insert(node_t **ptr_root, int val);
void inorder_tree_walk(node_t *node);
node_t* search(node_t *node, int val);
void delete_tree(node_t *node);
node_t* minimum(node_t *node);
node_t* maximum(node_t *node);
node_t* successor(node_t *node);
node_t* predecessor(node_t * node);
void delete(node_t **ptr_root, node_t *node);
void transplant(node_t **ptr_root, node_t *replaced_node, node_t *replacing_node);


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
    printf("최소 값: %d\n", minimum(root)->val);
    printf("최대 값: %d\n", maximum(root)->val);

    printf("%d 바로 뒤에 값: %d\n", search(root, 3)->val, successor(search(root, 3))->val);
    printf("%d 바로 앞에 값: %d\n", search(root, 5)->val, predecessor(search(root, 5))->val);

    delete(&root, search(root, 5));
    delete(&root, search(root, 6));
    delete(&root, search(root, 2));
    delete(&root, search(root, 7));
    delete(&root, search(root, 8));

    printf("root 값: %d\n", root->val);

    inorder_tree_walk(root);
    delete_tree(root);
}

void insert(node_t **ptr_root, int val) {
    if (*ptr_root == NULL) {
        *ptr_root = (node_t *)malloc(sizeof(node_t));

        (*ptr_root)->val = val;
        (*ptr_root)->parent = NULL;
        (*ptr_root)->left = NULL;
        (*ptr_root)->right = NULL;
        return;
    }

    node_t *current = *ptr_root;

    while (1) {
        if (current->val < val) {
            if (current->right == NULL) {
                current->right = (node_t *)malloc(sizeof(node_t));
                current->right->val = val;
                current->right->parent = current;
                current->right->left = NULL;
                current->right->right = NULL;
                break;
            } else {
                current = current->right;
            }
        }
        else {
            if (current->left == NULL) {
                current->left = (node_t *)malloc(sizeof(node_t));
                current->left->val = val;
                current->left->parent = current;
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
    while (current != NULL && current->val != val) {
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

node_t* minimum(node_t *node) {
    node_t *current = node;
    if (current == NULL)
        return current;
    while (current->left != NULL)
        current = current->left;
    return current;
}

node_t* maximum(node_t *node) {
    node_t *current = node;
    if (current == NULL)
        return current;
    while (current->right != NULL)
        current = current->right;
    return current;
}

node_t* successor(node_t *node) {
    node_t *current = node;

    if (current->right != NULL)
        return minimum(current->right);
    node_t *parent_node = current->parent;

    while (parent_node != NULL && parent_node->right == current) {
        current = parent_node;
        parent_node = parent_node->parent;
    }

    return parent_node;
}

node_t* predecessor(node_t *node) {
    node_t *current = node;

    if (current-> left != NULL)
        return maximum(current->left);
    node_t *parent_node = current->parent;

    while (parent_node != NULL && parent_node->left == current) {
        current = parent_node;
        parent_node = parent_node->parent;
    }

    return parent_node;
}

void transplant(node_t **ptr_root, node_t *replaced_node, node_t *replacing_node) {
    if (replaced_node->parent == NULL)
        (*ptr_root) = replacing_node;
    else if (replaced_node == replaced_node->parent->left)
        replaced_node->parent->left = replacing_node;
    else
        replaced_node->parent->right = replacing_node;
    
    if (replacing_node != NULL)
        replacing_node->parent = replaced_node->parent;
}

void delete(node_t **ptr_root, node_t *node) {
    if (node->left == NULL)
        transplant(ptr_root, node, node->right);
    else if (node->right == NULL)
        transplant(ptr_root, node, node->left);
    else {
        node_t *replacing_node = minimum(node->right);
        if (replacing_node->parent != node) {
            transplant(ptr_root, replacing_node, replacing_node->right);
            replacing_node->right = node->right;
            replacing_node->right->parent = replacing_node;
        }
        transplant(ptr_root, node, replacing_node);
        replacing_node->left = node->left;
        replacing_node->left->parent = replacing_node;
    }
    free(node);
}


// void delete(node_t **ptr_root, node_t *node) {
//     // 1. 삭제할 자식이 왼쪽 오른쪽 둘 다 없을때
//     if (node->left == NULL && node->right == NULL) {
//         // 1) 삭제할 노드가 root일때
//         if (node->parent == NULL) {
//             *ptr_root = NULL;
//             free(node);
//         // 2) 삭제할 노드가 자신 부모 왼쪽일때
//         } else if (node == node->parent->left) {
//             node->parent->left = NULL;
//             free(node);
//         // 3) 삭제할 노드가 자신 부모 오른쪽일때
//         } else if (node == node->parent->right) {
//             node->parent->right = NULL;
//             free(node);
//         }
//         return; 
//     }

//     // 2. 삭제할 노드가 왼쪽만 없을 때
//     if (node->left == NULL) {
//         // 1) 삭제할 노드가 root일 때
//         if (node->parent == NULL) {
//             *ptr_root = node->right;
//             free((*ptr_root)->parent);
//             (*ptr_root)->parent = NULL;
//         // 2) 삭제할 노드가 자신 부모 왼쪽일때
//         } else if(node == node->parent->left) {
//             node->parent->left = node->right;
//             node->right->parent = node->parent;
//             free(node);
//         // 3) 삭제할 노드가 자신 부모 오른쪽일때
//         } else if (node == node->parent->right) {
//             node->parent->right = node->right;
//             node->right->parent = node->parent;
//             free(node);;
//         }
//     // 3. 삭제할 노드가 오른쪽만 없을때
//     } else if (node->right == NULL) {
//         // 1) 삭제할 노드가 root일 때
//         if (node->parent == NULL) {
//             *ptr_root = node->left;
//             free((*ptr_root)->parent);
//             (*ptr_root)->parent = NULL;
//         // 2) 삭제할 노드가 자신 부모 왼쪽일때
//         } else if (node == node->parent->left) {
//             node->parent->left = node->left;
//             node->left->parent = node->parent;
//             free(node);
//         // 3) 삭제할 노드가 자신 부모 오른쪽일때
//         } else if (node == node->parent->right) {
//             node->parent->right = node->left;
//             node->left->parent = node->parent;
//             free(node);
//         }
//     // 4. 삭제할 노드가 왼쪽 오른쪽 자식 모두 있을 때
//     } else {
//         node_t *next_node = minimum(node->right);
//         // 1. 바로 다음 노드가 노드 자식일때
//         if (next_node->parent == node) {
//             // 1) 삭제할 노드가 root일때
//             if (node->parent == NULL) {
//                 *ptr_root = next_node;
//                 next_node->parent = NULL;
//                 next_node->left = node->left;
//                 free(node);
//             // 2) 삭제할 노드가 자신 부모 왼쪽일때
//             } else if (node == node->parent->left) {
//                 printf("다음 노드값: %d\n", next_node->val);
//                 node->parent->left = next_node;
//                 next_node->parent = node->parent;
//                 next_node->left = node->left;
//                 node->left->parent = next_node;
//                 free(node);
//             // 3) 삭제할 노드가 자신 부모 오른쪽일때
//             } else if (node == node->parent->right) {
//                 node->parent->right = next_node;
//                 next_node->parent = node->parent;
//                 next_node->left = node->left;
//                 node->left->parent = next_node;
//                 free(node);
//             }
//         // 1. 바로 다음 노드가 노드 자식이 아닐때
//         } else {
//             node->val = next_node->val;
//             if (next_node->right != NULL) {
//                 next_node->parent->left = next_node->right;
//                 next_node->right->parent = next_node->parent;
//             } else {
//                 next_node->parent->left = NULL;
//             }
//             free(next_node);
//         }
//     }
// }