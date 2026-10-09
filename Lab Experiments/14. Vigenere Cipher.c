```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plain[] = "send more money";
    char target[] = "cash not needed";
    char cipher[100], result[100];
    int key[] = {9, 0, 1, 7, 23, 15, 21,
                 14, 11, 11, 2, 8, 9};
    int newkey[100];
    int i, j = 0;

    // Part (a): Encryption
    printf("Part (a): Encryption\n");

    for (i = 0; plain[i] != '\0'; i++) {
        if (isalpha((unsigned char)plain[i])) {
            int p = tolower((unsigned char)plain[i]) - 'a';
            cipher[i] = (p + key[j]) % 26 + 'a';
            j++;
        } else {
            cipher[i] = plain[i];
        }
    }
    cipher[i] = '\0';

    printf("Plaintext: %s\n", plain);
    printf("Ciphertext: %s\n", cipher);

    // Part (b): Find a key for the required plaintext
    printf("\nPart (b): Finding the new key\n");

    j = 0;

    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            int c = cipher[i] - 'a';
            int p = tolower((unsigned char)target[i]) - 'a';

            newkey[j] = (c - p + 26) % 26;
            result[i] = (c - newkey[j] + 26) % 26 + 'a';
            j++;
        } else {
            result[i] = cipher[i];
        }
    }
    result[i] = '\0';

    printf("Required plaintext: %s\n", target);
    printf("New key stream: ");

    for (i = 0; i < j; i++)
        printf("%d ", newkey[i]);

    printf("\nDecrypted text: %s\n", result);

    return 0;
}
```
