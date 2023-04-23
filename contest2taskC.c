#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct Node{
    int key;
    int priority;
    int size;
    struct Node* left;
    struct Node* right;
};



int size(struct Node* root) {
    return root ? root->size : 0;
}

void update_size(struct Node* root) {
    if (root) {
        root->size = size(root->left) + size(root->right) + 1;
    }
}


struct Node* createNode(int key){
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->priority = rand();
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}


struct Node* merge(struct Node *left, struct Node *right){
    if(!left) return right;
    if(!right) return left;

    if(left->priority > right->priority){
        left->right = merge(left->right, right);
        return left;
    }
    else{
        right->left = merge(left, right->left);
        return right;
    }

}

void split(struct Node *node, int key, struct Node **left, struct Node **right){
    if(node == NULL){
        *left = NULL;
        *right = NULL;
        return;
    }
    if(node->key < key){
        *left = node;
        split(node->right, key, &((*left))->right, right);
    }
    else{
        *right = node;
        split(node->left, key, left,  &((*right))->left);
    }
}

struct Node *insert(struct Node *root, int key, int priority) {
    if (!root) {
        struct Node* new_node = (struct node*) malloc(sizeof(struct Node));
        new_node->key = key;
        new_node->priority = priority;
        new_node->size = 1;
        new_node->left = new_node->right = NULL;
        return new_node;
    }
    if (key < root->key) {
        root->left = insert(root->left, key, priority);
        if (root->left->priority > root->priority) {
            struct Node* new_root = root->left;
            root->left = new_root->right;
            new_root->right = root;
            root = new_root;
        }
    } else if (key > root->key) {
        root->right = insert(root->right, key, priority);
        if (root->right->priority > root->priority) {
            struct Node* new_root = root->right;
            root->right = new_root->left;
            new_root->left = root;
            root = new_root;
        }
    }
    update_size(root);
    return root;

}

struct Node *delete(struct Node *root, int key){
    if(root == NULL){
        return root;
    }
            if (key < root->key) {
            root->left = delete(root->left, key);
        } else if (key > root->key) {
            root->right = delete(root->right, key);
        } else {
            if (!root->left || !root->right) {
                struct Node* new_root = root->left ? root->left : root->right;
                free(root);
                root = new_root;
            } else {
                struct Node* node = root->left;
                while (node->right) {
                    node = node->right;
                }
                root->key = node->key;
                root->left = delete(root->left, root->key);
            }
        }
        if (root) {
            if (root->left && root->left->priority > root->priority) {
                struct Node* new_root = root->left;
                root->left = new_root->right;
                new_root->right = root;
                root = new_root;
            } else if (root->right && root->right->priority > root->priority) {
                struct Node* new_root = root->right;
                root->right = new_root->left;
                new_root->left = root;
                root = new_root;
            }
            update_size(root);
        }
        return root;
}
struct Node *search(struct Node *root, int key){
    if(root == NULL){
        return NULL;
    }
    if(root->key == key){
        return root;
    }
    if(root->key < key){
        return search(root->right, key);
    }
    else{
        return search(root->left, key);
    }
}
bool exists(struct Node *root, int key){
    while (root) {
        if (key < root->key) {
            root = root->left;
        } else if (key > root->key) {
            root = root->right;
        } else {
            return true;
        }
    }

    return false;
}

struct Node *next(struct Node* root, int key) {
    struct Node* node = NULL;
    while (root) {
        if (key < root->key) {
            node = root;
            root = root->left;
        } else if (key > root->key) {
            root = root->right;
        } else {
            return root;
        }
    }
    return node;
}

struct Node *prev(struct Node* root, int key) {
    struct Node* node = NULL;
    while (root) {
        if (key < root->key) {
            root = root->left;
        } else if (key > root->key) {
            node = root;
            root = root->right;
        } else {
            return root;
        }
    }
    return node;
}



int kth(struct Node *root, int k){
    if (k < 0 || k >= size(root) || !root) {
        return -1;
    }
    int s = size(root->left);
    if (k == s) {
        return root->key;
    }
    if (k < s) {
        return kth(root->left, k);
    }
    return kth(root->right, k - s - 1);


}


int main() {
    struct node* root = NULL;
    char op[10];
    int x;
    while(scanf("%s %d", op, &x) != EOF){
        if (op[0] == 'i') {
            if (!exists(root, x)) {
                int priority = rand();
                root = insert(root, x, priority);
            }
        } else if (op[0] == 'd') {
            if (exists(root, x)) {
                root = delete(root, x);
            }
        } else if (op[0] == 'e') {
            printf("%s\n", exists(root, x) ? "true" : "false");
        } else if (op[0] == 'n') {
            struct Node* p = next(root, x);
            if (p) {
                printf("%d\n", p->key);
            } else {
                printf("none\n");
            }
        } else if (op[0] == 'p') {
            struct Node* p = prev(root, x);
            if (p) {
                printf("%d\n", p->key);
            } else {
                printf("none\n");
            }
        } else if (op[0] == 'k') {
            int kth_value = kth(root, x);
            if (kth_value >= 0) {
                printf("%d\n", kth_value);
            } else {
                printf("none\n");
            }
        }
    }

    return 0;
}
