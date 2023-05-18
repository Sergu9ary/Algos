#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct File File;
struct kHeap{
    int size;
    int capacity;
    int k; //количество потомков каждого узла
    int *data;
};

void swap(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

int kParent(int i, int k){
    return (i - 1) / k;
}

int kChild(int i, int k, int n){
    return k * i + n;
}

struct kHeap* heapCreate(int k, int capacity){
    struct kHeap* kheap;
    kheap = malloc(sizeof(struct kHeap));
    kheap->data = (int*)malloc(capacity * sizeof(int));
    kheap->size = 0;
    kheap->capacity = capacity;
    kheap->k = k;
    return kheap;
}

void siftUp(struct kHeap* kheap, int index){
    while(index > 0 && kheap->data[index] < kheap->data[kParent(index, kheap->k)]){
        swap(&kheap->data[index], &kheap->data[kParent(index, kheap->k)]);
        index = kParent(index, kheap->k);
    }

}
void siftDown(struct kHeap* kheap, int index){
    int has_child = 1;
    while (has_child) {
        int smallest_child = -1;
        int j;

        // Находим наименьшего потомка
        for (j = 0; j < kheap->k; j++) {
            int child_index = kChild(index, kheap->k, j);
            if (child_index >= kheap->size) {
                break;
            }
            if (smallest_child == -1 || kheap->data[child_index] < kheap->data[smallest_child]) {
                smallest_child = child_index;
            }
        }

        if (smallest_child != -1 && kheap->data[smallest_child] < kheap->data[index]) {
            swap(&kheap->data[smallest_child], &kheap->data[index]);
            index = smallest_child;
        } else {
            has_child = 0;
        }
    }
}

struct kHeap* heapBuild(int* a, int k,  int size, int capacity){
    struct kHeap* heap = heapCreate(k, capacity);
    memcpy(heap->data, a, size * sizeof(int));
    heap->size = size;
    for(int i = size - 1; i >= 0; i--){
        siftDown(heap, i);
    }
    return heap;
}

void insert(struct kHeap* kheap, int x){
    kheap->data[kheap->size] = x;
    kheap->size++;
    siftUp(kheap, kheap->size - 1);
}

int extractMin(struct kHeap* kheap){
    int min = kheap->data[0];
    kheap->size--;
    kheap->data[0] = kheap->data[kheap->size];
    siftDown(kheap, 0);
    return min;
}

void kDestroy(struct kHeap* kheap) {
    free(kheap->data);
    free(kheap);
}

void heapSort(int* a, int k,  int l, int r){
    int len = r - l + 1;
    struct kHeap *heap = heapBuild(a, k,  len, len);
    for(int i = 0; i < len; i++){
        a[i] = extractMin(heap);
    }
//    heapDestroy(heap);
}


int main() {
    File* f1 = fopen("test_k-ary_heap.csv", "w");
    for(int j = 1000; j <= 10000000; j+=100000) {
        double average_time1 = 0;
        for (int i = 0; i < 5; i++) {
            int *a = (int *) malloc(j * sizeof(int));
            for (int x = 0; x < j; x++) {
                int r = rand() % j;
                a[x] = r;
            }
            time_t begin = clock();
            heapSort(a, 3,  0, i - 1);
            time_t end = clock();
            average_time1 += end - begin;
        }
        fprintf(f1, "Average time = %g \n", average_time1 / 5);
    }
    return 0;
}
