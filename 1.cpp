#include <stdio.h>
#include <string.h>
void caesarEncrypt(char message[], int key) {
    for (int i = 0; i < strlen(message); i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = (message[i] - 'A' + key) % 26 + 'A';
        } else if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = (message[i] - 'a' + key) % 26 + 'a';
        }
    }
}

void caesarDecrypt(char message[], int key) {
    caesarEncrypt(message, 26 - key); 
}

int main() {
    char message[100];
    int key;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the Caesar cipher key (an integer): ");
    scanf("%d", &key);

    message[strcspn(message, "\n")] = 0;

    caesarEncrypt(message, key);
    printf("Encoded message: %s\n", message);

    caesarDecrypt(message, key);
    printf("Decoded message: %s\n", message);

    return 0;
}

