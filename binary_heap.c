#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
typedef struct File File;

void swap(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

struct Heap{
    int* data;
    int size;
    int capacity;
};

struct Heap* heapCreate(int capacity){
    struct Heap* heap;
    heap = malloc(sizeof(struct Heap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}


void siftUp(struct Heap* heap, int index){
    while (index > 0 && heap->data[(index - 1) / 2] > heap->data[index]) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }

}



void siftDown( struct Heap* heap, int index){
    while (index * 2 + 1 < heap->size) {
        int smallerChildIndex = index * 2 + 1;
        if (index * 2 + 2 < heap->size && heap->data[index * 2 + 2] < heap->data[smallerChildIndex]) {
            smallerChildIndex = index * 2 + 2;
        }
        if (heap->data[index] < heap->data[smallerChildIndex]) {
            break;
        } else {
            int temp = heap->data[index];
            heap->data[index] = heap->data[smallerChildIndex];
            heap->data[smallerChildIndex] = temp;
            index = smallerChildIndex;
        }
    }

}

struct Heap* heapBuild(int* a, int size, int capacity){
    struct Heap* heap = heapCreate(capacity);
    memcpy(heap->data, a, size * sizeof(int));
    heap->size = size;
    for(int i = size - 1; i >= 0; i--){
        siftDown(heap, i);
    }
    return heap;
}

int getMin(struct Heap* heap){
    return heap->data[0];
}

void decreaseKey( struct Heap* heap, int v, int delta ){
    heap->data[v] -= delta;
    siftUp(heap, v);
}

void insert(struct Heap* heap, int x){
    heap->data[heap->size] = x;
    heap->size++;
    siftUp(heap, heap->size - 1);
}

int extractMin(struct Heap* heap){
    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->size--;
    siftDown(heap, 0);
    return min;
}
void heapDestroy(struct Heap* heap){
    free(heap->data);
    free(heap);
}

void printHeap(struct Heap* heap) {
    printf("Heap (size = %d): ", heap->size);
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void heapSort(int* a, int l, int r){
    int len = r - l + 1;
    struct Heap *heap = heapBuild(a, len, len);
    for(int i = 0; i < len; i++){
        a[i] = extractMin(heap);
    }
    heapDestroy(heap);
}




int main() {
    File* f1 = fopen("test_binary_heap.csv", "w");
    for(int j = 1000; j <= 10000000; j+=100000) {
        double average_time1 = 0;
        for (int i = 0; i < 5; i++) {
            int *a = (int *) malloc(j * sizeof(int));
            for (int x = 0; x < j; x++) {
                int r = rand() % j;
                a[x] = r;
            }
            time_t begin = clock();
            heapSort(a, 0, i - 1);
            time_t end = clock();
            average_time1 += end - begin;
        }
        fprintf(f1, "Average time = %g \n", average_time1 / 5);
    }
    return 0;
}
