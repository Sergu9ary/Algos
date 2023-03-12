
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct File File;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}




int main() {
    File* f1 = fopen("merge_sort.txt", "w");
    fprintf(f1, "MergeSort1:(ms)\n");
    for(int j = 1000; j <= 10000000; j+=100000) {
        double average_time1 = 0;
        for(int i = 0; i < 5; i++){
            int *a = (int *) malloc(j * sizeof(int));

            for(int x = 0; x < j; x++){
                int r = rand() % j;
                a[x] = r;
            }
            time_t begin = clock();
            mergeSort(a, 0, i - 1);
            time_t end = clock();
            average_time1 += end - begin;
            fprintf(f1, "%ld\n", end - begin);

            free(a);

        }
        fprintf(f1, "Average time = %g \n", average_time1 / 5);
    }
    return 0;
}