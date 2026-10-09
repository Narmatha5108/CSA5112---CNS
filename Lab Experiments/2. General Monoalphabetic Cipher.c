#include <stdio.h>
#include <string.h>

int main()
{
    char text[100], encrypted[100], decrypted[100];
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i, j;

    printf("Enter the text: ");
    scanf("%s", text);

    /* Encryption */
    for(i = 0; text[i] != '\0'; i++)
    {
        for(j = 0; j < 26; j++)
        {
            if(text[i] == alphabet[j])
            {
                encrypted[i] = key[j];
                break;
            }
        }
    }
    encrypted[i] = '\0';

    /* Decryption */
    for(i = 0; encrypted[i] != '\0'; i++)
    {
        for(j = 0; j < 26; j++)
        {
            if(encrypted[i] == key[j])
            {
                decrypted[i] = alphabet[j];
                break;
            }
        }
    }
    decrypted[i] = '\0';

    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
