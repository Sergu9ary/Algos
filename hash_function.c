#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <zlib.h>

#define N 1000000

void int_mod() {
    int hash_table[1000] = {0};
    int key;
    for (int i = 0; i < N; i++) {
        key = rand();
        hash_table[key % 1000]++;
    }
    printf("Collision:\n");
    for (int i = 0; i < 1000; i++) {
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}


void int_multiplicative() {
    int hash_table[1000] = {0};
    int key;
    double A = (sqrt(5.0) - 1.0) / 2.0;
    for (int i = 0; i < N; i++) {
        key = rand();
        hash_table[(int)(floor(1000 * fmod(key * A, 1.0)))]++;
    }
    printf("Collision:\n");
    for (int i = 0; i < 1000; i++) {
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}

void float_sum() {
    int hash_table[1000] = {0};
    float key;
    for (int i = 0; i < N; i++) {
        key = (float)rand() / RAND_MAX;
        hash_table[(int)(floor(1000 * fmod(key, 1.0)))]++;
    }
    printf("Collision:\n");
    for (int i = 0; i < 1000; i++) {
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}

unsigned int string_hash(const char* str) {
    unsigned int hash = 5381;
    while (*str != '\0') {
        hash = ((hash << 5) + hash) + (*str);
        ++str;
    }
    return hash;
}

void string_length() {
    int hash_table[1000] = {0};
    char key[6];
    for (int i = 0; i < N; i++) {
        sprintf(key, "%05d", rand() % 100000);
        hash_table[string_hash(key) % 1000]++;
    }
    printf("Collision:\n");
    for (int i = 0; i < 1000; i++) {
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}

void string_sum() {
    int hash_table[1000] = {0};
    char key[6];
    for (int i = 0; i < N; i++) {
        sprintf(key, "%05d", rand() % 100000);
        unsigned int hash = 0;
        for (int j = 0; j < strlen(key); j++) {
            hash += key[j];
        }
        hash_table[hash % 1000]++;
    }
    printf("Collision:\n");
    for (int i = 0; i < 1000; i++) {
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}

void string_polynomial() {
    int hash_table[1000] = {0};
    char key[6];
    for (int i = 0; i < N; i++) {
        sprintf(key, "%05d", rand() % 100000);
        unsigned int hash = 0;
        for (int j = 0; j < strlen(key); j++) {
            hash = hash * 33 + key[j];
        }
        hash_table[hash % 1000]++;
    }
    printf("Collision:\n");
    for (int i = 0; i < 1000; i++) {
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}

void string_crc32() {
    uint32_t histogram[1000] = {0};
    uint8_t key[16];

    for (int i = 0; i < 1000000; i++) {
        // Генерация случайного ключа
        for (int j = 0; j < 16; j++) {
            key[j] = rand() % 256;
        }

        // Вычисление crc32 хеша
        uint32_t hash = crc32(0, key, 16);

        // Добавление хеша в гистограмму
        histogram[hash % 1000]++;
    }

    // Построение столбчатой диаграммы коллизий
    printf("Collision:\n");
    for (int i = 0; i < 1000; i++) {
        printf("%d: %d\n", i, histogram[i]);
    }
}



int main() {
    int_mod();
    int_multiplicative();
    float_sum();
    string_length();
    string_sum();
    string_polynomial();
    string_crc32();
    return 0;
}
