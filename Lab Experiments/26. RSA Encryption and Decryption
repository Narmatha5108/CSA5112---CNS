#include <stdio.h>
#include <string.h>
long long power(long long base, int exp, int mod) {
    long long result = 1;
    while (exp > 0) {
        result = (result * base) % mod;
        exp--;
    }
    return result;
}
int main() {
    int p = 61, q = 53;
    int n = p * q;
    int e = 17, d = 2753;
    char message[200];
    unsigned char ch;
    int cipher;
    printf("Enter any message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    printf("\nEncrypted Message (HEX): ");
    for (int i = 0; message[i] != '\0'; i++) {
        ch = (unsigned char)message[i];
        cipher = power(ch, e, n);
        printf("%04X ", cipher);
    }
    printf("\nDecrypted Message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        ch = (unsigned char)message[i];
        cipher = power(ch, e, n);
        printf("%c", (char)power(cipher, d, n));
    }
    printf("\n");
    printf("RSA Encryption and Decryption Successful!\n");
    return 0;
}
