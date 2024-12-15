#include <stdio.h>
#include <string.h>
#define d 256
#define q 101

int hash(char* str, int m) {
    int h = 0;
    for (int i = 0; i < m; i++) {
        h = (d * h + str[i]) % q;
    }
    return h;
}

void RabinKarp(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }
    int p = hash(pattern, m);
    int t = hash(text, m);
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m) {
                printf("%d\n", i);
            }
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
}

int main() {
    char* str1 = (char*)malloc(5 * 10000 + 5 * sizeof(char));
    char* str2 = (char*)malloc(5 * 10000 + 5 * sizeof(char));

    scanf("%s", str1);
    scanf("%s", str2);
    if(strlen(str1) < strlen(str2)){
        return 0;
    }
    RabinKarp(str1, str2);
    free(str1);
    free(str2);
    return 0;
}
