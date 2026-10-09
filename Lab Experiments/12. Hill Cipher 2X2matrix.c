```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char message[] =
        "meet me at the usual place at ten rather than eight oclock";
    char plain[200], cipher[200], decrypted[200];
    int i, j, n = 0;

    int key[2][2] = {{9, 4}, {5, 7}};
    int inverse[2][2] = {{5, 12}, {15, 25}};

    // Remove spaces and keep only letters
    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i]))
            plain[n++] = toupper((unsigned char)message[i]);
    }

    // Add X if the number of letters is odd
    if (n % 2 != 0)
        plain[n++] = 'X';

    plain[n] = '\0';

    // Encryption
    for (i = 0; i < n; i += 2) {
        int a = plain[i] - 'A';
        int b = plain[i + 1] - 'A';

        cipher[i] = (key[0][0] * a +
                     key[0][1] * b) % 26 + 'A';

        cipher[i + 1] = (key[1][0] * a +
                         key[1][1] * b) % 26 + 'A';
    }
    cipher[n] = '\0';

    // Decryption
    for (i = 0; i < n; i += 2) {
        int a = cipher[i] - 'A';
        int b = cipher[i + 1] - 'A';

        decrypted[i] = (inverse[0][0] * a +
                        inverse[0][1] * b) % 26 + 'A';

        decrypted[i + 1] = (inverse[1][0] * a +
                            inverse[1][1] * b) % 26 + 'A';
    }
    decrypted[n] = '\0';

    printf("Plaintext: %s\n", plain);
    printf("Ciphertext: %s\n", cipher);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
```
