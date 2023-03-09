#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct File File;
//=============================
//Быстрая сортировка(1)
void swap(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}
void quickSort1(int *arr, int first, int last){
    if(first < last){
        int l_index = first, r_index = last, middle = arr[(l_index + r_index) / 2];
        do{
            while(arr[l_index] < middle) l_index++;
            while(arr[r_index] > middle) r_index--;
            if(l_index <= r_index){
                swap(&arr[l_index], &arr[r_index]);
                l_index++;
                r_index--;
            }
        }while(l_index < r_index);
        quickSort1(arr, first, r_index);
        quickSort1(arr, l_index, last);
    }
}
//=============================

//=============================
//Быстрая сортировка(2)
void swap(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}
int med (int a, int b, int c)
{
    if (a > b) { // ba ?c
        if (c > a) // bac
            return a;
        return (b > c) ? b : c;
    }
    // ab ? c
    if (c > b) // abc
        return b;
    return (a > c) ? a : c;
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
int partition2(int *arr, int first, int last){
    int v = arr[(first + last) / 2];
    int i = first;
    int j = last;
    while(i <= j){
        while(arr[i] < v){
            i++;
        }
        while(arr[j] >= v){
            j--;
        }
        if(i >= j){
            break;
        }
        swap(&arr[i++], &arr[j--]);
    }
    return j;
}
void quickSort2(int *arr, int first, int last){
    const int M = 10;
    if(last - first <= M){
        InsertSort(arr, last - first);
        return;
    }
    int median = med(arr[first], arr[(first + last) / 2], arr[last]);
    swap(&arr[median], &arr[(first + last) / 2]);
    int i = partition2(arr, first, last);
    quickSort2(arr, first, i);
    quickSort2(arr, i + 1, last);

}
//=============================


//=============================
//Быстрая сортиврока(3)
//int get_rand() {
//    return rand() / RAND_MAX;
//}
//void swap(int *px, int *py){
//    int temp;
//    temp = *px;
//    *px = *py;
//    *py = temp;
//}

int partition3(int *arr, int first, int last) {
    int number = arr[(int)((float) rand() / RAND_MAX * last)];
    int m = first;
    for(int i = first; i < last; i++){
        if(arr[i] < number){
            swap(&arr[i], &arr[m]);
            m++;
        }
    }
    return m;
}
void quickSort3(int *arr, int first, int last) {
    if (last - first <= 1) {
        return;
    }
    int m = partition3(arr, first, last);
    quickSort3(arr, first, m);
    quickSort3(arr, m, last);
}
//=============================

int main() {
    File* f1 = fopen("test_quick_sort1.txt", "w");
    File* f2 = fopen("test_quick_sort2.txt", "w");
    File* f3 = fopen("test_quick_sort3.txt", "w");
    fprintf(f1, "QuickSort1:(ms)\n");
    fprintf(f2, "QuickSort2:(ms)\n");
    fprintf(f3, "QuickSort3:(ms)\n");
    for(int j = 1000; j <= 10000000; j+=100000) {
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
            quickSort1(a, 0, i - 1);
            time_t end = clock();
            average_time1 += end - begin;
            fprintf(f1, "%ld\n", end - begin);


            begin = end;
            quickSort2(b, 0, i);
            end = clock();
            average_time2 += end - begin;
            fprintf(f2, "%ld\n", end - begin);

            begin = end;
            quickSort3(c, 0, i);
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