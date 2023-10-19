#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20
#define SHA1CircularShift(bits, word) (((word) << (bits)) | ((word) >> (32 - (bits)))

void sha1_transform(uint32_t state[5], const unsigned char block[SHA1_BLOCK_SIZE]);
void sha1_update(uint32_t state[5], uint32_t *bitlen, const unsigned char data[], uint32_t data_len);
void sha1_final(uint32_t state[5], uint32_t *bitlen, unsigned char digest[SHA1_DIGEST_SIZE]);
void sha1(char *message, unsigned char *digest);

int main() {
    char message[] = "Hello, SHA-1!";
    unsigned char digest[SHA1_DIGEST_SIZE];

    sha1(message, digest);

    printf("SHA-1 Hash: ");
    for (int i = 0; i < SHA1_DIGEST_SIZE; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}


