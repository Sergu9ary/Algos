#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct File File;


struct Node {
   int key;
   struct Node *left;
   struct Node *right;
};


struct Node *rightRotate(struct Node *x) {
   struct Node *y = x->left;
   x->left = y->right;
   y->right = x;
   return y;
}

struct Node *leftRotate(struct Node *x) {
   struct Node *y = x->right;
   x->right = y->left;
   y->left = x;
   return y;
}
struct Node *splay(struct Node *root, int key) {
   if (root == NULL || root->key == key)
       return root;

   if (root->key > key) {
       if (root->left == NULL)
           return root;

       // Zig
       if (root->left->key > key) {
           root->left->left = splay(root->left->left, key);
           root = rightRotate(root);
       }
           // Zag
       else if (root->left->key < key) {
           root->left->right = splay(root->left->right, key);

           if (root->left->right != NULL)
               root->left = leftRotate(root->left);
       }

       return (root->left == NULL) ? root : rightRotate(root);
   }
   else {
       if (root->right == NULL)
           return root;

       // Zag
       if (root->right->key < key) {
           root->right->right = splay(root->right->right, key);
           root = leftRotate(root);
       }
           // Zig
       else if (root->right->key > key) {
           root->right->left = splay(root->right->left, key);

           if (root->right->left != NULL)
               root->right = rightRotate(root->right);
       }

       return (root->right == NULL) ? root : leftRotate(root);
   }
}

struct Node *insert(struct Node *root, int key) {
   if (root == NULL) {
       struct Node *node = (struct Node*)malloc(sizeof(struct Node));
       node->key = key;
       node->left = node->right = NULL;
       return node;
   }

   root = splay(root, key);

   if (root->key == key)
       return root;

   struct Node *node = (struct Node*)malloc(sizeof(struct Node));
   node->key = key;

   if (root->key > key) {
       node->right = root;
       node->left = root->left;
       root->left = NULL;
   }
   else {
       node->left = root;
       node->right = root->right;
       root->right = NULL;
   }

   return node;
}

struct Node *delete(struct Node *root, int key) {
   if (root == NULL)
       return NULL;

   root = splay(root, key);

   if (root->key != key)
       return root;

   struct Node *temp;

   if (root->left == NULL) {
       temp = root;
       root = root->right;
   }
   else {
       temp = root;
       root = splay(root->left, key);
       root->right = temp->right;
   }

   free(temp);
   return root;
}

struct Node *search(struct Node *root, int key) {
   return splay(root, key);
}


int main() {
   File* f1 = fopen("test_Splay.txt", "w");
   double add_time = 0;
   double delete_time = 0;
   for(int i = 100000; i < 1000000; i+=100000){
       struct Node* root = NULL;
       for(int j = 0; j < i; j++){
           time_t begin = clock();
           root = insert(root, rand() % 1000000);
           time_t end = clock();
           add_time += end - begin;
       }
       for(int j = 0; j < 50000; j++){
           time_t begin = clock();
           root = delete(root, rand() % 1000000);
           time_t end = clock();
           delete_time += end - begin;
       }
   }
   fprintf(f1, "Add time(100000) = %g \n", add_time / 10);
   fprintf(f1, "Delete time(50000) = %g \n", delete_time / 10);
   return 0;
}
