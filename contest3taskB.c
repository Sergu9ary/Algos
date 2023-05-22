#include <stdio.h>
#include <stdlib.h>
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


int main() {
    int n;
    scanf("%d", &n);
    HashSet* set = createHashSet(n);
    for (int i = 0; i < n; i++) {
        char str;
        int value;
        scanf(" %c %d", &str, &value);
        if (str == '+') {
            add(set, value);
        } else if (str == '-') {
            removeValue(set, value);
        } else if (str == '?') {
            printf("%s\n", contains(set, value) ? "YES" : "NO");
        }
    }
    destroyHashSet(set);
    return 0;
}
