#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct File File;

void swap(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

void bubblesort(int* l, int* r){
    int sz = r - l;
    if(sz <= 1) return;
    _Bool b = true;
    while(b){
        b = false;
        for(int* i = l; i + 1 < r; i++){
            if(*i > *(i + 1)){
                swap(i, (i + 1));
                b = true;
            }
        }
        r--;
    }
}


void InsertSort(int *mas, int n){
    int key = 0;
    for(int i = 1; i < n; i++){
        key = mas[i];
        int j = i - 1;
        while(j >= 0 && mas[j] > key){
            mas[j + 1] = mas[j];
            j--;
        }
        mas[j + 1] = key;
    }
}


void SelectionSort(int *mas, int n) {
    for(int i = 0; i < n - 1; i++) {
        int minj = i;
        for(int j = i + 1; j < n; j++){
            if(mas[j] < mas[minj]) {
                minj = j;
            }
        }
        swap(&mas[i], &mas[minj]);
    }
}


int main() {
    File* f1 = fopen("test_bubble_sort.txt", "w");
    File* f2 = fopen("test_selection_sort.txt", "w");
    File* f3 = fopen("test_insert_sort.txt", "w");
    fprintf(f1, "BubbleSort:(ms)\n");
    fprintf(f2, "SelectionSort:(ms)\n");
    fprintf(f3, "InsertSort:(ms)\n");
    for(int j = 1000; j <= 1000000; j+=10000) {
        double average_time1 = 0;
        double average_time2 = 0;
        double average_time3 = 0;
        for(int i = 0; i < 5; i++){
            int *a = (int *) malloc(j * sizeof(int));
            int *b = (int *) malloc(j * sizeof(int));
            int *c = (int *) malloc(j * sizeof(int));

            for(int x = 0; x < j; x++){
                int r = rand() % j;
                a[x] = r;
                b[x] = r;
                c[x] = r;
            }
            time_t begin = clock();
            bubblesort(a, a + i);
            time_t end = clock();
            average_time1 += end - begin;
            fprintf(f1, "%ld\n", end - begin);


            begin = end;
            SelectionSort(a, i);
            end = clock();
            average_time2 += end - begin;
            fprintf(f2, "%ld\n", end - begin);

            begin = end;
            InsertSort(a, i);
            end = clock();
            average_time3 += end - begin;
            fprintf(f3, "%ld\n", end - begin);


            free(a);
            free(b);
            free(c);

        }
        fprintf(f1, "Average time = %g \n", average_time1 / 5);
        fprintf(f2, "Average time = %g \n", average_time2 / 5);
        fprintf(f3, "Average time = %g \n", average_time3 / 5);
    }
    return 0;
}