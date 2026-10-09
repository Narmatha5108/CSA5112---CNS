
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char text[200], key[100];
    char encrypted[200], decrypted[200];
    int i, j = 0, k, keyLen;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    text[strcspn(text, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    keyLen = strlen(key);

    if(keyLen == 0)
    {
        printf("Key cannot be empty.\n");
        return 0;
    }

    for(i = 0; i < keyLen; i++)
    {
        if(!isalpha((unsigned char)key[i]))
        {
            printf("Key must contain letters only.\n");
            return 0;
        }
        key[i] = toupper((unsigned char)key[i]);
    }

    /* Encryption */
    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha((unsigned char)text[i]))
        {
            k = key[j % keyLen] - 'A';

            if(isupper((unsigned char)text[i]))
                encrypted[i] = (text[i] - 'A' + k) % 26 + 'A';
            else
                encrypted[i] = (text[i] - 'a' + k) % 26 + 'a';

            j++;
        }
        else
            encrypted[i] = text[i];
    }
    encrypted[i] = '\0';

    /* Decryption */
    j = 0;

    for(i = 0; encrypted[i] != '\0'; i++)
    {
        if(isalpha((unsigned char)encrypted[i]))
        {
            k = key[j % keyLen] - 'A';

            if(isupper((unsigned char)encrypted[i]))
                decrypted[i] = (encrypted[i] - 'A' - k + 26) % 26 + 'A';
            else
                decrypted[i] = (encrypted[i] - 'a' - k + 26) % 26 + 'a';

            j++;
        }
        else
            decrypted[i] = encrypted[i];
    }
    decrypted[i] = '\0';

    printf("\nEncrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
