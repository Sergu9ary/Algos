#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
typedef struct File File;
int getMaxDigit(int *arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    int digit = 0;
    while (max > 0) {
        digit++;
        max /= 10;
    }
    return digit;
}
void LSDSort(int arr[], int n)
{
    int digit = getMaxDigit(arr, n);
    int count[10];
    int *tmp = malloc(n * sizeof(int));

    for (int d = 1; d <= digit; d++) {
        memset(count, 0, sizeof(count));
        
        for (int i = 0; i < n; i++)
            count[(arr[i] / (int)pow(10, d-1)) % 10]++;
        for (int i = 1; i < 10; i++)
            count[i] += count[i-1];
        for (int i = n-1; i >= 0; i--) {
            int index = (arr[i] / (int)pow(10, d-1)) % 10;
            tmp[--count[index]] = arr[i];
        }
        for (int i = 0; i < n; i++)
            arr[i] = tmp[i];
    }

    free(tmp);
}


int main() {
    File* f1 = fopen("lsd_sort.txt", "w");
    fprintf(f1, "QuickSort1:(ms)\n");
    for(int j = 1000; j <= 10000000; j+=100000) {
        double average_time1 = 0;
        for(int i = 0; i < 5; i++){
            int *a = (int *) malloc(j * sizeof(int));

            for(int x = 0; x < j; x++){
                int r = rand() % j;
                a[x] = r;
            }
            time_t begin = clock();
            LSDSort(a, i);
            time_t end = clock();
            average_time1 += end - begin;
            fprintf(f1, "%ld\n", end - begin);

            free(a);

        }
        fprintf(f1, "Average time = %g \n", average_time1 / 5);
    }
    return 0;
}