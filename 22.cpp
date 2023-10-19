#include <stdio.h>

// S-DES Key (10 bits)
unsigned short int key = 0b0111111101;
// Binary Initialization Vector (8 bits)
unsigned char iv = 0b10101010;

// S-DES S-Box tables (4 bits to 4 bits)
unsigned char sBox0[] = {0b01, 0b00, 0b11, 0b10, 0b11, 0b10, 0b01, 0b00, 0b00, 0b10, 0b01, 0b11, 0b11, 0b01, 0b11, 0b10};
unsigned char sBox1[] = {0b00, 0b01, 0b10, 0b11, 0b10, 0b00, 0b01, 0b11, 0b11, 0b00, 0b01, 0b11, 0b10, 0b01, 0b00, 0b10};

// Function to perform S-DES round function
unsigned char sDesRound(unsigned char plaintext, unsigned char roundKey) {
    // Expand and permute (EP)
    unsigned char epResult = 0;
    for (int i = 0; i < 4; i++) {
        epResult |= ((plaintext >> (3 - i)) & 1) << (7 - i * 2);
    }

    // XOR with round key
    unsigned char xorResult = epResult ^ roundKey;

    // Apply S-Boxes
    unsigned char s0Input = (xorResult >> 4) & 0x0F;
    unsigned char s1Input = xorResult & 0x0F;
    unsigned char s0Output = sBox0[s0Input];
    unsigned char s1Output = sBox1[s1Input];

    // Combine S-Box outputs
    unsigned char sBoxOutput = (s0Output << 2) | s1Output;

    // Permutation (P4)
    unsigned char p4Result = 0;
    for (int i = 0; i < 4; i++) {
        p4Result |= ((sBoxOutput >> (3 - i)) & 1) << (3 - i);
    }

    // XOR with the left part
    return plaintext ^ p4Result;
}

// Function to perform S-DES encryption
unsigned char sDesEncrypt(unsigned char plaintext, unsigned short int key) {
    // Initial permutation (IP)
    unsigned char ipResult = 0;
    for (int i = 0; i < 8; i++) {
        ipResult |= ((plaintext >> (7 - i)) & 1) << (1 - i % 2 + i / 2 * 4);
    }

    // Split the plaintext into two halves
    unsigned char left = (ipResult >> 4) & 0x0F;
    unsigned char right = ipResult & 0x0F;

    // Perform two rounds with the given key
    for (int round = 0; round < 2; round++) {
        unsigned char roundKey = (key >> (8 - 2 * round)) & 0x3;
        unsigned char temp = right;
        right = left ^ sDesRound(right, roundKey);
        left = temp;
    }

    // Swap the left and right halves and apply final permutation (IP^-1)
    unsigned char finalResult = (right << 4) | left;
    unsigned char ciphertext = 0;
    for (int i = 0; i < 8; i++) {
        ciphertext |= ((finalResult >> (7 - i)) & 1) << (1 - i % 2 + i / 2 * 4);
    }

    return ciphertext;
}

// Function to perform CBC mode encryption
void cbcEncrypt(const char* plaintext, int length, unsigned short int key, unsigned char iv) {
    unsigned char previousCipherblock = iv;

    for (int i = 0; i < length; i++) {
        unsigned char currentBlock = plaintext[i];
        // XOR the current block with the previous ciphertext block
        currentBlock ^= previousCipherblock;

        // Encrypt the result of the XOR operation
        unsigned char ciphertext = sDesEncrypt(currentBlock, key);

        // Print or use the ciphertext
        printf("%02X ", ciphertext);

        previousCipherblock = ciphertext;
    }
    printf("\n");
}

// Function to perform CBC mode decryption
void cbcDecrypt(const char* ciphertext, int length, unsigned short int key, unsigned char iv) {
    unsigned char previousCipherblock = iv;

    for (int i = 0; i < length; i++) {
        unsigned char currentCipherblock = ciphertext[i];

        // Decrypt the ciphertext
        unsigned char decryptedBlock = sDesEncrypt(currentCipherblock, key);

        // XOR the result of the decryption with the previous ciphertext block
        decryptedBlock ^= previousCipherblock;

        // Print or use the decrypted block
        printf("%02X ", decryptedBlock);

        previousCipherblock = currentCipherblock;
    }
    printf("\n");
}

int main() {
    // Binary plaintext: 0000000100100011
    // Binary key: 0111111101
    const char plaintext[] = {0x01, 0x23}; // Hexadecimal representation of the binary plaintext
    const int length = 2;

    printf("Plaintext: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    printf("Encrypted (CBC): ");
    cbcEncrypt(plaintext, length, key, iv);

    printf("Decrypted (CBC): ");
    cbcDecrypt(plaintext, length, key, iv);

    return 0;
}

