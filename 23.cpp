#include <stdio.h>
#include <stdint.h>

// S-DES Key (10 bits)
uint16_t key = 0b0111111101;

// S-DES S-Box tables (4 bits to 4 bits)
uint8_t sBox0[] = {0b01, 0b00, 0b11, 0b10, 0b11, 0b10, 0b01, 0b00, 0b00, 0b10, 0b01, 0b11, 0b11, 0b01, 0b11, 0b10};
uint8_t sBox1[] = {0b00, 0b01, 0b10, 0b11, 0b10, 0b00, 0b01, 0b11, 0b11, 0b00, 0b01, 0b11, 0b10, 0b01, 0b00, 0b10};

// Function to perform S-DES round function
uint8_t sDesRound(uint8_t plaintext, uint8_t roundKey) {
    // Expand and permute (EP)
    uint8_t epResult = 0;
    for (int i = 0; i < 4; i++) {
        epResult |= ((plaintext >> (3 - i)) & 1) << (7 - i * 2);
    }

    // XOR with round key
    uint8_t xorResult = epResult ^ roundKey;

    // Apply S-Boxes
    uint8_t s0Input = (xorResult >> 4) & 0x0F;
    uint8_t s1Input = xorResult & 0x0F;
    uint8_t s0Output = sBox0[s0Input];
    uint8_t s1Output = sBox1[s1Input];

    // Combine S-Box outputs
    uint8_t sBoxOutput = (s0Output << 2) | s1Output;

    // Permutation (P4)
    uint8_t p4Result = 0;
    for (int i = 0; i < 4; i++) {
        p4Result |= ((sBoxOutput >> (3 - i)) & 1) << (3 - i);
    }

    // XOR with the left part
    return plaintext ^ p4Result;
}

// Function to perform S-DES encryption
uint8_t sDesEncrypt(uint8_t plaintext, uint16_t key) {
    uint8_t roundKeys[2];

    // Generate round keys
    roundKeys[0] = (uint8_t)((key >> 5) & 0x1F);
    roundKeys[1] = (uint8_t)(key & 0x1F);

    // Initial permutation (IP)
    uint8_t ipResult = 0;
    for (int i = 0; i < 8; i++) {
        ipResult |= ((plaintext >> (7 - i)) & 1) << (1 - i % 2 + i / 2 * 4);
    }

    // Split the plaintext into two halves
    uint8_t left = (ipResult >> 4) & 0x0F;
    uint8_t right = ipResult & 0x0F;

    // Perform two rounds with the given key
    for (int round = 0; round < 2; round++) {
        uint8_t roundKey = roundKeys[round];
        uint8_t temp = right;
        right = left ^ sDesRound(right, roundKey);
        left = temp;
    }

    // Swap the left and right halves and apply final permutation (IP^-1)
    uint8_t finalResult = (right << 4) | left;
    uint8_t ciphertext = 0;
    for (int i = 0; i < 8; i++) {
        ciphertext |= ((finalResult >> (7 - i)) & 1) << (1 - i % 2 + i / 2 * 4);
    }

    return ciphertext;
}

// Function to perform CTR mode encryption
void ctrEncrypt(const uint8_t* plaintext, int length, uint16_t key, uint8_t initialCounter) {
    uint8_t counter = initialCounter;

    for (int i = 0; i < length; i++) {
        uint8_t currentBlock = plaintext[i];

        // Encrypt the counter using S-DES to produce a pseudorandom keystream
        uint8_t keystream = sDesEncrypt(counter, key);

        // XOR the current block with the keystream to produce the ciphertext
        uint8_t ciphertext = currentBlock ^ keystream;

        // Print or use the ciphertext
        printf("%02X ", ciphertext);

        // Increment the counter
        counter++;

        // Reset the counter to 0 when it reaches 256 (8 bits)
        if (counter == 0) {
            counter = initialCounter;
        }
    }
    printf("\n");
}

// Function to perform CTR mode decryption (same as encryption)
void ctrDecrypt(const uint8_t* ciphertext, int length, uint16_t key, uint8_t initialCounter) {
    ctrEncrypt(ciphertext, length, key, initialCounter);
}

int main() {
    // Binary plaintext: 000000010000001000000100
    // Binary key: 0111111101
    const uint8_t plaintext[] = {0x01, 0x02, 0x04}; // Hexadecimal representation of the binary plaintext
    const int length = 3;

    printf("Plaintext: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    printf("Encrypted (CTR): ");
    ctrEncrypt(plaintext, length, key, 0);

    printf("Decrypted (CTR): ");
    ctrDecrypt(plaintext, length, key, 0);

    return 0;
}

