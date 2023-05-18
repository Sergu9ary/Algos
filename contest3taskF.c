#include <stdio.h>
#include <stdlib.h>


#define MAXN 100000
#define N 17

int minimum(int a, int b) {
    return a < b ? a : b;
}

int log2(int x) {
    int result = 0;
    while (x >>= 1) {
        result++;
    }
    return result;

}
int arr[MAXN];
int arr1[MAXN][N];
int arr2[MAXN][N];

void build(int n) {
    for (int i = 0; i < n; i++) {
        arr1[i][0] = arr[i];
        arr2[i][0] = 1e9+1;
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            arr1[i][j] = minimum(arr1[i][j-1], arr1[i+(1<<(j-1))][j-1]);
            if (arr1[i][j-1] < arr1[i+(1<<(j-1))][j-1]) {
                arr2[i][j] = minimum(arr2[i][j-1], arr1[i+(1<<(j-1))][j-1]);
            } else if (arr1[i][j-1] > arr1[i+(1<<(j-1))][j-1]) {
                arr2[i][j] = minimum(arr2[i+(1<<(j-1))][j-1], arr1[i][j-1]);
            } else {
                arr2[i][j] = minimum(arr2[i][j-1], arr2[i+(1<<(j-1))][j-1]);
            }
        }
    }
}

int query(int l, int r) {
    int j = log2(r - l + 1);
    int min1 = arr1[l][j];
    int min2 = arr1[r-(1<<j)+1][j];
    int res;
    if (min1 < min2) {
        res = arr2[l][j];
        if (min2 < arr2[l][j]) {
            res = minimum(res, min2);
        }
    } else if (min1 > min2) {
        res = arr2[r-(1<<j)+1][j];
        if (min1 < arr2[r-(1<<j)+1][j]) {
            res = minimum(res, min1);
        }
    } else {
        res = minimum(arr2[l][j], arr2[r-(1<<j)+1][j]);
    }
    return res;
}

int main() {
    int n, m, l, r;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    build(n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &l, &r);
        printf("%d\n", query(l-1, r-1));
    }
    return 0;
}
