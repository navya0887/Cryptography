#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_KEY 26

// Function to generate a random key
void generateKey(int key[], int keyLength) {
    srand(time(NULL));
    for (int i = 0; i < keyLength; i++) {
        key[i] = rand() % MAX_KEY;
    }
}

// Function to encrypt the plaintext using the key
void encryptWithOneTimePadVigenere(char plaintext[], int key[], int keyLength) {
    int textLength = strlen(plaintext);

    for (int i = 0; i < textLength; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int shift = key[i % keyLength];
            char shifted = (plaintext[i] - 'A' + shift) % 26 + 'A';
            printf("%c", shifted);
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int shift = key[i % keyLength];
            char shifted = (plaintext[i] - 'a' + shift) % 26 + 'a';
            printf("%c", shifted);
        } else {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
}

int main() {
    char plaintext[] = "Meet me at the usual place at ten rather than eight o'clock";
    int keyLength = strlen(plaintext);

    int key[keyLength];
    generateKey(key, keyLength);

    printf("Original message: %s\n", plaintext);
    printf("Random key: ");
    for (int i = 0; i < keyLength; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    printf("Encrypted message: ");
    encryptWithOneTimePadVigenere(plaintext, key, keyLength);

    return 0;
}

