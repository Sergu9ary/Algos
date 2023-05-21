#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct File File;
struct Node{
   int data;
   struct Node* left;
   struct Node* right;
};

struct Node* createNode(int data){
   struct Node* Node;
   Node = (struct Node*)malloc(sizeof(struct Node));
   Node->data = data;
   Node->left = NULL;
   Node->right = NULL;
   return Node;
}

struct Node* search(struct Node* Node, int key){
   if((Node == NULL) || (key == Node->data)){
       return Node;
   }
   if(key < Node->data){
       return search(Node->left, key);
   }
   else{
       return search(Node->right, key);
   }
}

struct Node* insert(struct Node* Node, int key){
   if(Node == NULL){
       return createNode(key);
   }
   else if(key < Node->data){
       Node->left = insert(Node->left, key);
   }
   else if(key > Node->data){
       Node->right = insert(Node->right, key);
   }
   return Node;
}

struct Node* delete(struct Node* Node, int key){
   if(Node == NULL){
       return Node;
   }
   if(key < Node->data){
       Node->left = delete(Node->left, key);
   }
   else if(key > Node->data){
       Node->right = delete(Node->right, key);
   }
   else{
       if(Node->left == NULL){
           struct Node* temp = Node->right;
           free(Node);
           return temp;
       }
       else if(Node->right == NULL){
           struct Node* temp = Node->left;
           free(Node);
           return temp;
       }
       struct Node* temp = Node->right;
       while(temp && temp->left != NULL){
           temp = temp->left;
       }
       Node->data = temp->data;
       Node->right = delete(Node->right, Node->data);
   }
   return Node;
}

void printPreorder(struct Node* root) {
   if (root == NULL) {
       return;
   }
   printPreorder(root->left);
   printf("%d ", root->data);
   printPreorder(root->right);

}
int main() {
   struct Node* root = NULL;
   File* f1 = fopen("test_BST.txt", "w");
   double add_time = 0;
   double delete_time = 0;
   for(int i = 0; i < 5; i++){
       for(int j = 0; j < 100000; j++){
           int data = rand() % 1000000;
           time_t begin = clock();
           root = insert(root, data);
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
