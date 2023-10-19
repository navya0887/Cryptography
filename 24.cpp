#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the modular multiplicative inverse using the extended Euclidean algorithm
int modInverse(int e, int phi) {
    int m0 = phi;
    int a = 0, b = 1;
    int q, x, temp;

    if (phi == 1)
        return 0;

    while (e > 1) {
        q = e / phi;
        temp = phi;
        phi = e % phi;
        e = temp;
        temp = a;
        a = b - q * a;
        b = temp;
    }

    if (b < 0)
        b += m0;

    return b;
}

int main() {
    int e = 31;
    int n = 3599;

    // Find the prime factors of n (p and q)
    int p, q;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }

    int phi = (p - 1) * (q - 1);
    int d = modInverse(e, phi);

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    return 0;
}


