#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct File File;
struct Node{
    int data;
    int degree;
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
};

struct Node* createNode(int data){
    struct Node* node;
    node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

struct Node* merge(struct Node* node1, struct Node* node2){
    if(node1 == NULL){
        return node2;
    }
    if(node2 == NULL){
        return node1;
    }
    if(node1->data < node2->data){
        node1->sibling = merge(node1->sibling, node2);
        node1->sibling->parent = node1;
        return node1;
    }
    else{
        node2->sibling = merge(node2->sibling, node1);
        node2->sibling->parent = node2;
        return node2;
    }
}

struct Node* unionHeap(struct Node* node1, struct Node* node2){
    struct Node* node = merge(node1, node2);
    if(node == NULL){
        return node;
    }
    struct Node* prev = NULL;
    struct Node* curr = node;
    struct Node* next = curr->sibling;
    while(next != NULL){
        if((curr->degree != next->degree) || ((next->sibling != NULL) && (next->sibling->degree == curr->degree))){
            prev = curr;
            curr = next;
        }
        else{
            if(curr->data <= next->data){
                curr->sibling = next->sibling;
                next->parent = curr;
                next->sibling = curr->child;
                curr->child = next;
                curr->degree++;
            }
            else{
                if(prev == NULL){
                    node= next;
                }
                else{
                    prev->sibling = next;
                }
                curr->parent = next;
                curr->sibling = next->child;
                next->child = curr;
                next->degree++;
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return node;
}

struct Node* insert(struct Node* heap, int data) {
    struct Node* node = createNode(data);
    return unionHeap(heap, node);
}

struct Node* findMin(struct Node* node){
    struct Node* minNode = node;
    struct Node* curr = node;
    while(curr != NULL){
        if(curr->data < minNode->data){
            minNode = curr;
        }
        curr = curr->sibling;
    }
    return minNode;
}

struct Node* deleteMin(struct Node* node){
    struct Node* minNode = findMin(node);
    struct Node* prev = NULL;
    struct Node* curr = node;
    while(curr != minNode){
        prev = curr;
        curr = curr->sibling;
    }
    if(prev == NULL){
        node = minNode->sibling;
    }
    else{
        prev->sibling = minNode->sibling;
    }
    struct Node* child = minNode->child;
    struct Node* newNode = NULL;
    while(child != NULL){
        struct Node* next = child->sibling;
        child->sibling = newNode;
        child->parent = NULL;
        newNode = child;
        child = next;
    }
    return unionHeap(node, newNode);
}

struct Node* addToNode(int* arr, int size){
    struct Node* node = NULL;
    for(int i = 0; i < size; i++){
        node = insert(node, arr[i]);
    }
    return node;
}

void heapSort(int* arr, int size){
    struct Node* node = addToNode(arr, size);
    for(int i = 0; i < size; i++){
        struct Node* minNode = findMin(node);
        arr[i] = minNode->data;
        node = deleteMin(node);
    }
}

int main() {
        File* f1 = fopen("test_binomial_heap.csv", "w");
        for(int j = 1000; j <= 10000000; j+=100000) {
            double average_time1 = 0;
            for (int i = 0; i < 5; i++) {
                int *a = (int *) malloc(j * sizeof(int));
                for (int x = 0; x < j; x++) {
                    int r = rand() % j;
                    a[x] = r;
                }
                int size = sizeof(a) / sizeof(a[0]);
                time_t begin = clock();
                heapSort(a, size);
                time_t end = clock();
                average_time1 += end - begin;
            }
            fprintf(f1, "%lf\n", average_time1 / 5);
        }
    return 0;
}
