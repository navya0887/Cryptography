#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform Hill cipher encryption
void hillCipherEncrypt(const char *message, const int key[2][2]) {
    int len = strlen(message);
    int encrypted[len];

    for (int i = 0; i < len; i += 2) {
        int p1 = tolower(message[i]) - 'a';
        int p2 = tolower(message[i + 1]) - 'a';

        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;

        encrypted[i] = c1 + 'a';
        encrypted[i + 1] = c2 + 'a';
    }

    printf("Encrypted message: %s\n", encrypted);
}

int main() {
    const char *message = "meet me at the usual place at ten rather than eight oclock";
    const int key[2][2] = {{9, 4}, {5, 7}};

    printf("Original message: %s\n", message);
    hillCipherEncrypt(message, key);

    return 0;
}

