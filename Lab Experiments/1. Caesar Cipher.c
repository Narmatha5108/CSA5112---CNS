#include <stdio.h>
#include <string.h>

int main()
{
    char text[100], encrypted[100], decrypted[100];
    int key, i;

    printf("Enter the text: ");
    scanf("%s", text);

    printf("Enter the key: ");
    scanf("%d", &key);

    // Encryption
    for(i = 0; text[i] != '\0'; i++)
        encrypted[i] = (text[i] - 'A' + key) % 26 + 'A';

    encrypted[i] = '\0';

    // Decryption
    for(i = 0; encrypted[i] != '\0'; i++)
        decrypted[i] = (encrypted[i] - 'A' - key + 26) % 26 + 'A';

    decrypted[i] = '\0';

    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
