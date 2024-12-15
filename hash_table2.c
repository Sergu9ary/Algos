#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct File File;
typedef struct Node{
    int value;
    struct Node* next;
}Node;

typedef struct HashSet{
    Node** table;
    int size;
}HashSet;

int hash(int value, int size){
    unsigned int hash = 0;
    unsigned int A = 31;
    unsigned int B = 23;
    unsigned int P = 2147483647;
    hash = (hash * A + value + B) % P;
    return hash % size;

}

HashSet* createHashSet(int size){
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->table = (Node**)calloc(size, sizeof(Node*));
    set->size = size;
    return set;
}

int contains(HashSet* set, int value){
    int index = hash(value, set->size);
    Node* node = set->table[index];
    while(node != NULL){
        if(node->value == value){
            return 1;
        }
        node = node->next;
    }
    return 0;
}

void add(HashSet* set, int value){
    if(contains(set, value) == 1){
        return;
    }
    int index = hash(value, set->size);
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = set->table[index];
    set->table[index] = node;
}


void removeValue(HashSet* set, int value){
    if(contains(set, value) == 0){
        return;
    }
    int index = hash(value, set->size);
    Node* node = set->table[index];
    Node* prev = NULL;
    while (node != NULL) {
        if (node->value == value) {
            if (prev == NULL) {
                set->table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }

}

void destroyHashSet(HashSet* set) {
    for (int i = 0; i < set->size; i++) {
        Node* node = set->table[i];
        while (node != NULL) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(set->table);
    free(set);
}


void test(int size) {
    HashSet* set = createHashSet(size);
    int operations[size];
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        operations[i] = rand() % 4;
        int value = rand();
        switch (operations[i]) {
            case 0:
                add(set, value);
                break;
            case 1:
                add(set, value);
                break;
            case 2:
                contains(set, value);
                break;
            case 3:
                removeValue(set, value);
                break;
        }
    }
    destroyHashSet(set);
}



int main() {
    File* f1 = fopen("test_HashSet.txt", "w");
    for (int size = 10000; size <= 1000000; size += 10000) {
        time_t begin = clock();
        test(size);
        time_t end = clock();
        fprintf(f1, "Add time = %ld \n", end - begin);
    }
    return 0;
}
