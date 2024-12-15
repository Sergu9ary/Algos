#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int arr[N];

int BIT[N + 1];

void update(int idx, int val) {
    while (idx <= N) {
        BIT[idx] += val;
        idx += idx & -idx;
    }
}

int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += BIT[idx];
        idx -= idx & -idx;
    }
    return sum;
}

int rand_range(int a, int b) {
    return rand() % (b - a + 1) + a;
}

int main() {
    File* f1 = fopen("test_Fenwick.txt", "w");
    for (int i = 0; i < N; i++) {
        arr[i] = rand_range(1, 100);
        update(i+1, arr[i]);
    }

    for (int i = 0; i < N/10; i++) {
        if (rand()%2 == 0) {
            int pos = rand_range(0, N-1);
            int val = rand_range(1, 100);
            arr[pos] = val;
            update(pos+1, val - (query(pos+1) - query(pos)));
        } else {
            int l = rand_range(0, N-1);
            int r = rand_range(l, N-1);
            time_t begin = clock();
            int sum = query(r+1) - query(l);
            time_t end = clock();
            fprintf(f1, "Query: sum[%d,%d] = %d, time=%ld\n", l, r, sum, end - begin);
        }
    }

    return 0;
}
