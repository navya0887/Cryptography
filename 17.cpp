#include <stdio.h>
#include <stdint.h>
static const int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

static const int PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

uint64_t initialPermutation(uint64_t data) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result |= ((data >> (64 - IP[i])) & 1) << (63 - i);
    }
    return result;
}
void generateRoundKeys(uint64_t key, uint64_t roundKeys[16]) {
   
}

int main() {
    uint64_t cipherText = 0x0123456789ABCDEF; 
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t roundKeys[16];

    generateRoundKeys(key, roundKeys);

    uint64_t permutedCipher = initialPermutation(cipherText);

    return 0;
}

