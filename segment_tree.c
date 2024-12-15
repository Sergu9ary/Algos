#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000000

int tree[MAX_SIZE * 4]; 

void update(int node, int start, int end, int idx, int val)
{
    if (start == end)
    {
        tree[node] = val;
        return;
    }

    int mid = (start + end) / 2;

    if (idx <= mid)
    {
        update(node * 2, start, mid, idx, val);
    }
    else
    {
        update(node * 2 + 1, mid + 1, end, idx, val);
    }

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// Функция для поиска суммы на отрезке [left, right]
int query(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
    {
        return 0;
    }
    if (left <= start && right >= end)
    {
        return tree[node];
    }

    int mid = (start + end) / 2;

    return query(node * 2, start, mid, left, right) +
           query(node * 2 + 1, mid + 1, end, left, right);
}

int main()
{
    File* f1 = fopen("test_segment_tree.txt", "w");
    int n = 1000000;
    int q = 10000000;

    for (int j = 1; j <= 5; j++)
    {
        fprintf(f1, "%d:\n", j);

        int* a = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
        {
            a[i] = rand() % 10 + 1;
        }
        int start = 0;
        int end = n - 1;
        int node = 1;
        for (int i = start; i <= end; i++)
        {
            update(node, start, end, i, a[i]);
        }
        int sum = 0;
        clock_t start_time, end_time, total_time = 0;
        for (int i = 0; i < q; i++)
        {
            int type = rand() % 2;

            if (type == 0)
            {
                int idx = rand() % n;
                int val = rand() % 10 + 1;

                start_time = clock();
                update(node, start, end, idx, val);
                end_time = clock();

                total_time += end_time - start_time;
            }
            else
            {
                int left = rand() % n;
                int right = rand() % n;

                if (left > right)
                {
                    int temp = left;
                    left = right;
                    right = temp;
                }

                start_time = clock();
                sum += query(node, start, end, left, right);
                end_time = clock();

                total_time += end_time - start_time;
            }
        }
        printf(f1, "Среднее время: %ld миллисекунд\n", total_time / q);

        free(a);
    }

    return 0;
}
