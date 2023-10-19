#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

// Structure to hold letter frequencies
typedef struct {
    char letter;
    int frequency;
} LetterFrequency;

// English letter frequencies (for comparison)
LetterFrequency englishFrequencies[] = {
    {'a', 8167}, {'b', 1492}, {'c', 2782}, {'d', 4253},
    {'e', 12702}, {'f', 2228}, {'g', 2015}, {'h', 6094},
    {'i', 6966}, {'j', 153}, {'k', 772}, {'l', 4025},
    {'m', 2406}, {'n', 6749}, {'o', 7507}, {'p', 1929},
    {'q', 95}, {'r', 5987}, {'s', 6327}, {'t', 9056},
    {'u', 2758}, {'v', 978}, {'w', 2360}, {'x', 150},
    {'y', 1974}, {'z', 74}
};

// Function to calculate letter frequencies in the text
void calculateLetterFrequencies(const char *text, LetterFrequency frequencies[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            frequencies[letter - 'a'].frequency++;
        }
    }
}

// Function to compare frequencies for sorting
int compareFrequencies(const void *a, const void *b) {
    return ((LetterFrequency *)b)->frequency - ((LetterFrequency *)a)->frequency;
}

int main() {
    const char *ciphertext = "Your encrypted text goes here";
    LetterFrequency frequencies[26] = {0};

    // Calculate letter frequencies in the ciphertext
    calculateLetterFrequencies(ciphertext, frequencies);

    // Sort frequencies in descending order
    qsort(frequencies, 26, sizeof(LetterFrequency), compareFrequencies);

    printf("Top 10 possible plaintexts:\n");
    int maxPrint = 10;
    for (int i = 0; i < maxPrint; i++) {
        char shift = 'a' - frequencies[i].letter;
        printf("Shift %d: ", shift);
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            if (isalpha(ciphertext[j])) {
                char decrypted = tolower(ciphertext[j]) - shift;
                if (decrypted < 'a') {
                    decrypted += 26;
                }
                printf("%c", isupper(ciphertext[j]) ? toupper(decrypted) : decrypted);
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n");
    }

    return 0;
}

