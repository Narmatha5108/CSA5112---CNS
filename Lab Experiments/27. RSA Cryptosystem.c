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
    int n = 3233, e = 17;
    char message[200];
    int cipher[200], i = 0;
    int found, j;
    printf("Enter any message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    printf("\nEncrypted Message: ");
    while (message[i] != '\0') {
        cipher[i] = power((unsigned char)message[i], e, n);
        printf("%d ", cipher[i]);
        i++;
    }
    printf("\n\nCodebook Attack - Decrypted Message: ");
    for (int k = 0; k < i; k++) {
        found = 0;
        for (j = 0; j <= 255; j++) {
            if (power(j, e, n) == cipher[k]) {
                printf("%c", j);
                found = 1;
                break;
            }
        }
        if (!found)
            printf("?");
    }
    printf("\nCodebook Attack Demonstrated!\n");
    return 0;
}
