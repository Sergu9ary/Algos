
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000000
#define MAX_K 20

int nums[MAX_N];
int sp[MAX_K][MAX_N];

void build_sparse_table(int n) {
    for (int i = 0; i < n; i++) {
        sp[0][i] = nums[i];
    }

    int log_n = log2(n) + 1;
    for (int j = 1; j < log_n; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            sp[j][i] = fmin(sp[j-1][i], sp[j-1][i+(1<<(j-1))]);
        }
    }
}

int query(int l, int r) {
    int j = log2(r - l + 1);
    return fmin(sp[j][l], sp[j][r-(1<<j)+1]);
}

int main() {
    for (int i = 0; i < MAX_N; i++) {
        nums[i] = rand();
    }
    
    build_sparse_table(MAX_N);
    
    int queries[MAX_N][2];
    for (int i = 0; i < MAX_N; i++) {
        int l = rand() % MAX_N;
        int r = rand() % (MAX_N - l) + l;
        queries[i][0] = l;
        queries[i][1] = r;
    }
    
    double sum_time = 0;
    for (int t = 0; t < 5; t++) {
        clock_t start, end;
        double time;
        start = clock();
        for (int i = 0; i < MAX_N; i++) {
            query(queries[i][0], queries[i][1]);
        }
        end = clock();
        time = ((double) (end - start)) ;
        printf("Test: %f ms\n", time);
        sum_time += time;
    }

    double avg_time = sum_time / 5;
    printf("Average time: %f ms\n", avg_time);

    return 0;
}
