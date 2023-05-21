#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct File File;



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
   struct Node *Node = (struct Node*)malloc(sizeof(struct Node));
   Node->key = key;
   Node->priority = rand();
   Node->size = 1;
   Node->left = NULL;
   Node->right = NULL;
   return Node;
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

void split(struct Node *Node, int key, struct Node **left, struct Node **right){
   if(Node == NULL){
       *left = NULL;
       *right = NULL;
       return;
   }
   if(Node->key < key){
       *left = Node;
       split(Node->right, key, &((*left))->right, right);
   }
   else{
       *right = Node;
       split(Node->left, key, left,  &((*right))->left);
   }
}

struct Node *insert(struct Node *root, int key, int priority) {
   if (!root) {
       struct Node* new_Node = (struct Node*) malloc(sizeof(struct Node));
       new_Node->key = key;
       new_Node->priority = priority;
       new_Node->size = 1;
       new_Node->left = new_Node->right = NULL;
       return new_Node;
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
           struct Node* Node = root->left;
           while (Node->right) {
               Node = Node->right;
           }
           root->key = Node->key;
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
   struct Node* Node = NULL;
   while (root) {
       if (key < root->key) {
           Node = root;
           root = root->left;
       } else if (key > root->key) {
           root = root->right;
       } else {
           return root;
       }
   }
   return Node;
}

struct Node *prev(struct Node* root, int key) {
   struct Node* Node = NULL;
   while (root) {
       if (key < root->key) {
           root = root->left;
       } else if (key > root->key) {
           Node = root;
           root = root->right;
       } else {
           return root;
       }
   }
   return Node;
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
   File* f1 = fopen("test_CT.txt", "w");
   double add_time = 0;
   double delete_time = 0;
   for(int i = 100000; i < 1000000; i+=100000){
       struct Node* root = NULL;
       for(int j = 0; j < i; j++){
           time_t begin = clock();
           root = insert(root, rand() % 1000000, rand());
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
