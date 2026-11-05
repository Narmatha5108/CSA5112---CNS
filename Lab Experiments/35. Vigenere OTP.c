#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
int main() {
    char message[200], encrypted[200], decrypted[200];
    int key[200], count = 0;
    srand((unsigned)time(NULL));
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    for (int i = 0; message[i] != '\0'; i++) {
        char ch = message[i];
        if (isalpha((unsigned char)ch)) {
            key[i] = rand() % 26;
            count++;
            if (isupper((unsigned char)ch)) {
                encrypted[i] = 'A' +
                    (ch - 'A' + key[i]) % 26;
                decrypted[i] = 'A' +
                    (encrypted[i] - 'A' - key[i] + 26) % 26;
            }
            else {
                encrypted[i] = 'a' +
                    (ch - 'a' + key[i]) % 26;
                decrypted[i] = 'a' +
                    (encrypted[i] - 'a' - key[i] + 26) % 26;
            }
        }
        else {
            key[i] = -1;
            encrypted[i] = ch;
            decrypted[i] = ch;
        }
    }
    int len = strlen(message);
    encrypted[len] = '\0';
    decrypted[len] = '\0';
    printf("\nRandom Key Values: ");
    for (int i = 0; i < len; i++) {
        if (key[i] != -1)
            printf("%d ", key[i]);
        else
            printf("- ");
    }
    printf("\nEncrypted Message: %s", encrypted);
    printf("\nDecrypted Message: %s", decrypted);
    printf("\n\nEncryption and Decryption Successful!\n");
    return 0;
}
