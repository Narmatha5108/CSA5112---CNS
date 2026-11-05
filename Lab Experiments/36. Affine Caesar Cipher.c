#include <stdio.h>
#include <string.h>
#include <ctype.h>
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
int inverse(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}
int main() {
    char text[200], encrypted[200], decrypted[200];
    int a, b, inv;
    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    printf("Enter value of a: ");
    scanf("%d", &a);
    printf("Enter value of b: ");
    scanf("%d", &b);
    a = (a % 26 + 26) % 26;
    b = (b % 26 + 26) % 26;
    if (gcd(a, 26) != 1) {
        printf("Invalid key! a must be coprime with 26.\n");
        return 0;
    }
    inv = inverse(a);
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isupper((unsigned char)ch)) {
            encrypted[i] = 'A' +
                (a * (ch - 'A') + b) % 26;
        }
        else if (islower((unsigned char)ch)) {
            encrypted[i] = 'a' +
                (a * (ch - 'a') + b) % 26;
        }
        else {
            encrypted[i] = ch;
        }
    }
    encrypted[strlen(text)] = '\0';
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = encrypted[i];
        if (isupper((unsigned char)ch)) {
            decrypted[i] = 'A' +
                (inv * (ch - 'A' - b + 26 * 2)) % 26;
        }
        else if (islower((unsigned char)ch)) {
            decrypted[i] = 'a' +
                (inv * (ch - 'a' - b + 26 * 2)) % 26;
        }
        else {
            decrypted[i] = ch;
        }
    }
    decrypted[strlen(text)] = '\0';
    printf("\nEncrypted Message: %s", encrypted);
    printf("\nDecrypted Message: %s\n", decrypted);
    return 0;
}
