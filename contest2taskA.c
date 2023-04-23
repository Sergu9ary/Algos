#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct Node {
    int height;
    int key;
    struct Node *left;
    struct Node *right;
};

int height(struct Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}


int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node *createNode(int key) {
    struct Node *node = (struct Node *)
            malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T = x->right;

    x->right = y;
    y->left = T;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


struct Node *insertNode(struct Node *node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int findMin(struct Node *node, int key){
    int min = 1e9;
    while(node){
        if(node->key < key){
            node = node->right;
        }
        else{
            if(node->key < min){
                min = node->key;
            }
            node = node->left;
        }
    }
    if(min == 1e9){
        return -1;
    }
    return min;
}


int main() {
        int n, x = 0, result = 0;
        char str = '+', prev_str = '+', str_end = '\0';
        scanf("%d%c", &n, &str_end);
        scanf("%c %d%c", &str, &x, &str_end);
        struct Node *root = createNode(x);
        while(n-- > 1){
            if(scanf("%c %d%c", &str, &x, &str_end)){};
            if(str == '?'){
                result = findMin(root, x);
                printf("%d\n", result);
            }
            else{
                if(prev_str != '+'){
                    root = insertNode(root, (x + result) % 1000000000);
                }
                else{
                    root = insertNode(root, x);
                }
            }
            prev_str = str;
        }
        return 0;
}
