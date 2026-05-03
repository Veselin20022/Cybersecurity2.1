#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void rc4_crypt(unsigned char *key, int keylen,
               unsigned char *data, int datalen,
               unsigned char *output) {

    unsigned char S[256];
    int i, j = 0, t;
    for (i = 0; i < 256; i++)
        S[i] = i;

    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % keylen]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = j = 0;
    for (int k = 0; k < datalen; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        t = (S[i] + S[j]) % 256;
        output[k] = data[k] ^ S[t];
    }
}

int main() {

    unsigned char encrypted[] = {
        0x95, 0x56, 0x93, 0x54, 0x1B, 0x22, 0xCF, 0x6E,
        0xC5, 0x8C, 0x52, 0x34, 0xCC, 0x86, 0x3A
    };
    int len = sizeof(encrypted);
    unsigned char buffer[100];
    char key[20];

    time_t now = time(NULL);

    printf("Starting timestamp brute-force...\n");

    for (int i = 0; i < 86400; i++) {
        time_t guess = now - i;

        sprintf(key, "%ld", guess);

        rc4_crypt((unsigned char*)key, strlen(key),
                  encrypted, len, buffer);

        buffer[len] = '\0';

        if (strstr((char*)buffer, "Secret") != NULL ||
            strstr((char*)buffer, "Data") != NULL) {

            printf("\n[SUCCESS]\n");
            printf("Timestamp key: %s\n", key);
            printf("Decrypted: %s\n", buffer);
            printf("Readable time: %s", ctime(&guess));
            break;
        }
    }
    return 0;
}