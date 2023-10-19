#include <stdio.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>

int main() {
    DSA *dsa = DSA_new();
    if (DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL) != 1) {
        fprintf(stderr, "Error generating DSA parameters.\n");
        return 1;
    }

    if (DSA_generate_key(dsa) != 1) {
        fprintf(stderr, "Error generating DSA key pair.\n");
        return 1;
    }
    const char *message = "This is a message to be signed.";
    unsigned char signature[DSA_size(dsa)];
    unsigned int signature_length;

    if (DSA_sign(0, (unsigned char *)message, strlen(message), signature, &signature_length, dsa) != 1) {
        fprintf(stderr, "Error signing the message.\n");
        return 1;
    }
    if (DSA_verify(0, (unsigned char *)message, strlen(message), signature, signature_length, dsa) != 1) {
        fprintf(stderr, "Signature verification failed.\n");
        return 1;
    }

    printf("Message: %s\n", message);
    printf("Signature verified successfully.\n");
    DSA_free(dsa);

    return 0;
}

