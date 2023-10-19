#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to calculate the frequency of each letter in the text
void calculateLetterFrequencies(const char *text, int frequencies[26]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            frequencies[letter - 'a']++;
        }
    }
}

// Function to decrypt the text using a given shift value
void decryptWithShift(const char *text, int shift, char decrypted[]) {
    int textLength = strlen(text);
    for (int i = 0; i < textLength; i++) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            char decryptedLetter = ((letter - 'a' - shift + 26) % 26) + 'a';
            decrypted[i] = isupper(text[i]) ? toupper(decryptedLetter) : decryptedLetter;
        } else {
            decrypted[i] = text[i];
        }
    }
    decrypted[textLength] = '\0';
}

// Function to find the shift value for a given letter frequency
int findShift(int letterFrequency) {
    return (letterFrequency + 22) % 26;
}

int main() {
    const char *cipherText = "Uifsf jt b tfdsfu fbgqftu ofxtjuz. Vq jhiu ivn ob nj zxfi. Uifsf jt b tfdsfu fbgqftu ofxtjuz. Uj jhiu ivn ob nj zxfi.";

    int letterFrequencies[26] = {0};
    calculateLetterFrequencies(cipherText, letterFrequencies);

    char decryptedText[200];
    bool possible[26] = {false};
    int maxShifts = 10; // Display the top 10 possible plaintexts

    printf("Top %d possible plaintexts:\n", maxShifts);
    for (int count = 0; count < maxShifts; count++) {
        int maxFrequency = -1;
        int maxIndex = -1;

        for (int i = 0; i < 26; i++) {
            if (!possible[i] && letterFrequencies[i] > maxFrequency) {
                maxFrequency = letterFrequencies[i];
                maxIndex = i;
            }
        }

        if (maxFrequency == -1) {
            break; // No more possible shifts
        }

        possible[maxIndex] = true;
        int shift = findShift(maxIndex);
        decryptWithShift(cipherText, shift, decryptedText);

        printf("Shift: %d - %s\n", shift, decryptedText);
    }

    return 0;
}

