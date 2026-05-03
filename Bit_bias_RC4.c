#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char rc4_second_byte(unsigned char *key, int keylen) {
    unsigned char S[256];
    int i, j = 0;

    for (i = 0; i < 256; i++)
        S[i] = i;

    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % keylen]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = j = 0;

    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    unsigned char temp = S[i];
    S[i] = S[j];
    S[j] = temp;

    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    temp = S[i];
    S[i] = S[j];
    S[j] = temp;
    return S[(S[i] + S[j]) % 256];
}

int main() {
    srand(time(NULL));

    int count = 0;
    int N = 100000;

    unsigned char key[16];

    for (int i = 0; i < N; i++) {

        for (int k = 0; k < 16; k++)
            key[k] = rand() % 256;

        if (rc4_second_byte(key, 16) == 0x00)
            count++;
    }
    printf("Zero count: %d / %d\n", count, N);
    printf("Probability: %f\n", (double)count / N);

    return 0;
}