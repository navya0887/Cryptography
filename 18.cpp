#include <stdio.h>
#include <stdint.h>

// Function to perform a circular left shift on a 28-bit value
uint32_t circularLeftShift(uint32_t value, int shift) {
    return ((value << shift) | (value >> (28 - shift))) & 0x0FFFFFFF;
}

// Function to generate the round keys using the specified method
void generateRoundKeys(uint64_t key, uint64_t roundKeys[16]) {
    // Initial permutation and compression
    uint64_t pc1 = 0;
    uint64_t pc2 = 0;
    for (int i = 0; i < 28; i++) {
        pc1 |= ((key >> (64 - i)) & 1) << (27 - i);
        pc2 |= ((key >> (64 - i)) & 1) << (55 - i);
    }

    for (int round = 0; round < 16; round++) {
        // Splitting into C and D
        uint32_t C = pc1 & 0x0FFFFFFF;
        uint32_t D = pc1 >> 28;

        // Applying circular left shifts
        C = circularLeftShift(C, 1);
        D = circularLeftShift(D, 1);

        // Combining C and D
        pc1 = (((uint64_t)D) << 28) | C;

        // Selecting the specified bits from C and D
        uint32_t selectedBits = 0;
        for (int i = 0; i < 24; i++) {
            selectedBits |= ((pc2 >> (55 - i)) & 1) << i;
        }

        // Combining the selected bits and the rotated half
        roundKeys[round] = (selectedBits << 28) | pc1;
    }
}

int main() {
    // Replace with your 64-bit key
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t roundKeys[16];

    generateRoundKeys(key, roundKeys);

    printf("Round Keys:\n");
    for (int i = 0; i < 16; i++) {
        printf("Round %2d: 0x%012llx\n", i + 1, roundKeys[i]);
    }

    return 0;
}

