#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct File File;





struct Node {
   int height;
   int key;
   struct Node *left;
   struct Node *right;
};

int height(struct Node *Node) {
   if (Node == NULL)
       return 0;
   return Node->height;
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
   struct Node *Node = (struct Node *)
           malloc(sizeof(struct Node));
   Node->key = key;
   Node->left = NULL;
   Node->right = NULL;
   Node->height = 1;
   return Node;
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


struct Node *insertNode(struct Node *Node, int key) {
   if (Node == NULL)
       return createNode(key);

   if (key < Node->key)
       Node->left = insertNode(Node->left, key);
   else if (key > Node->key)
       Node->right = insertNode(Node->right, key);
   else
       return Node;

   Node->height = max(height(Node->left), height(Node->right)) + 1;

   int balance = getBalance(Node);
   if (balance > 1 && key < Node->left->key)
       return rightRotate(Node);

   if (balance < -1 && key > Node->right->key)
       return leftRotate(Node);

   if (balance > 1 && key > Node->left->key) {
       Node->left = leftRotate(Node->left);
       return rightRotate(Node);
   }

   if (balance < -1 && key < Node->right->key) {
       Node->right = rightRotate(Node->right);
       return leftRotate(Node);
   }

   return Node;
}

struct Node *findMin(struct Node *Node) {
   struct Node *current_Node = Node;

   while (current_Node->left != NULL)
       current_Node = current_Node->left;

   return current_Node;
}

struct Node *delete(struct Node *Node, int key) {
   if (Node == NULL)
       return Node;
   if (key < Node->key)
       Node->left = delete(Node->left, key);
   else if (key > Node->key)
       Node->right = delete(Node->right, key);
   else {
       if ((Node->left == NULL) || (Node->right == NULL)) {
           struct Node *temp_Node = Node->left ? Node->left : Node->right;
           if (temp_Node == NULL) {
               temp_Node = Node;
               Node = NULL;
           } else
               *Node = *temp_Node;
           free(temp_Node);
       } else {
           struct Node *temp_Node = findMin(Node->right);
           Node->key = temp_Node->key;
           Node->right = delete(Node->right, temp_Node->key);
       }
   }
   if (Node == NULL)
       return Node;
   Node->height = 1 + max(height(Node->left), height(Node->right));

   int balance = getBalance(Node);

   if (balance > 1 && getBalance(Node->left) >= 0)
       return rightRotate(Node);

   if (balance > 1 && getBalance(Node->left) < 0) {
       Node->left = leftRotate(Node->left);
       return rightRotate(Node);
   }

   if (balance < -1 && getBalance(Node->right) <= 0)
       return leftRotate(Node);

   if (balance < -1 && getBalance(Node->right) > 0) {
       Node->right = rightRotate(Node->right);
       return leftRotate(Node);
   }

   return Node;
}

int main() {
   struct Node* root = NULL;
   File* f1 = fopen("test_AVL.txt", "w");
   double add_time = 0;
   double delete_time = 0;
   for(int i = 0; i < 5; i++){
       for(int j = 0; j < 100000; j++){
           int data = rand() % 1000000;
           time_t begin = clock();
           root = insertNode(root, data);
           time_t end = clock();
           add_time += end - begin;
       }
       for(int j = 0; j < 50000; j++){
           int data = rand() % 1000000;
           time_t begin = clock();
           root = delete(root, data);
           time_t end = clock();
           delete_time += end - begin;
       }
   }
   fprintf(f1, "Add time(100000) = %g \n", add_time / 5);
   fprintf(f1, "Delete time(50000) = %g \n", delete_time / 5);
   return 0;
}
