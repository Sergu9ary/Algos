#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct File File;

typedef struct Node {
    int value;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    int color; 
} Node;

Node *newNode(int value) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->color = 1;
    return node;
}

void rotateLeft(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(Node **root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void fixViolation(Node **root, Node *z) {
    while (z != *root && z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotateRight(root, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 0;
}

void insert(Node **root, int value) {
    Node *node = newNode(value);
    Node *y = NULL;
    Node *x = *root;
    while (x != NULL) {
        y = x;
        if (node->value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;
    if (y == NULL)
        *root = node;
    else if (node->value < y->value)
        y->left = node;
    else
        y->right = node;
    fixViolation(root, node);
}


int main() {
    File* f1 = fopen("test_RedBlack.txt", "w");
    double add_time = 0;
    double delete_time = 0;
    for(int i = 100000; i < 1000000; i+=100000){
        struct Node* root = NULL;
        for(int j = 0; j < i; j++){
            time_t begin = clock();
            insert(&root, rand() % 1000000);
            time_t end = clock();
            add_time += end - begin;
        }
//        for(int j = 0; j < 50000; j++){
//            time_t begin = clock();
//            root = delete(root, rand() % 1000000);
//            time_t end = clock();
//            delete_time += end - begin;
//        }
    }
    fprintf(f1, "Add time(100000) = %g \n", add_time / 10);
//    fprintf(f1, "Delete time(50000) = %g \n", delete_time / 10);
    return 0;
}
