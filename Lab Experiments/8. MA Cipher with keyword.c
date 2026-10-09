```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char text[500], encrypted[500], decrypted[500];
    char plain[] = "abcdefghijklmnopqrstuvwxyz";
    char cipher[] = "cipherabdfgjklmnoqstuvwxyz";

    int i, j;

    printf("Enter the message: ");
    fgets(text, sizeof(text), stdin);

    // Encryption
    for (i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if (isalpha((unsigned char)ch)) {
            int upper = isupper((unsigned char)ch);
            ch = tolower((unsigned char)ch);

            for (j = 0; j < 26; j++) {
                if (ch == plain[j]) {
                    encrypted[i] = cipher[j];
                    break;
                }
            }

            if (upper)
                encrypted[i] = toupper((unsigned char)encrypted[i]);
        } else {
            encrypted[i] = ch;
        }
    }
    encrypted[i] = '\0';

    // Decryption
    for (i = 0; encrypted[i] != '\0'; i++) {
        char ch = encrypted[i];

        if (isalpha((unsigned char)ch)) {
            int upper = isupper((unsigned char)ch);
            ch = tolower((unsigned char)ch);

            for (j = 0; j < 26; j++) {
                if (ch == cipher[j]) {
                    decrypted[i] = plain[j];
                    break;
                }
            }

            if (upper)
                decrypted[i] = toupper((unsigned char)decrypted[i]);
        } else {
            decrypted[i] = ch;
        }
    }
    decrypted[i] = '\0';

    printf("\nEncrypted message: %s", encrypted);
    printf("\nDecrypted message: %s", decrypted);

    return 0;
}
```
