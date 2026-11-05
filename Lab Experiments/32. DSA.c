#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int power(int a, int b, int mod) {
    int result = 1;
    while (b > 0) {
        result = (result * a) % mod;
        b--;
    }
    return result;
}
int inverse(int a, int mod) {
    for (int i = 1; i < mod; i++) {
        if ((a * i) % mod == 1)
            return i;
    }
    return -1;
}
int main() {
    char message[200];
    int p = 23, q = 11, g = 4;
    int x = 3;
    int h = 0, r, s, k;
    int publicKey = power(g, x, p);
    srand((unsigned)time(NULL));
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    for (int i = 0; message[i] != '\0'; i++)
        h = (h + (unsigned char)message[i]) % q;
    printf("\nDSA Signatures:\n");
    for (int j = 1; j <= 2; j++) {
        do {
            k = 1 + rand() % (q - 1);
            r = power(g, k, p) % q;
            s = (inverse(k, q) * (h + x * r)) % q;
        } while (r == 0 || s == 0);
        printf("\nSignature %d: (%d, %d)", j, r, s);
        printf("\nRandom k = %d\n", k);
    }
    printf("\nPublic Key = %d", publicKey);
    printf("\nSame message can have different signatures.\n");
    return 0;
}
