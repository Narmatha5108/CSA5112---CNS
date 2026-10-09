
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b)
{
    while(b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main()
{
    char text[200], encrypted[200], decrypted[200];
    int a, b, i, x, inv;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter values of a and b: ");
    scanf("%d %d", &a, &b);

    a = (a % 26 + 26) % 26;
    b = (b % 26 + 26) % 26;

    if(gcd(a, 26) != 1)
    {
        printf("Invalid a! Choose a value relatively prime to 26.\n");
        return 0;
    }

    /* Find modular inverse of a */
    for(inv = 1; inv < 26; inv++)
    {
        if((a * inv) % 26 == 1)
            break;
    }

    /* Encryption */
    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha((unsigned char)text[i]))
        {
            if(isupper((unsigned char)text[i]))
                x = text[i] - 'A';
            else
                x = text[i] - 'a';

            x = (a * x + b) % 26;

            if(isupper((unsigned char)text[i]))
                encrypted[i] = x + 'A';
            else
                encrypted[i] = x + 'a';
        }
        else
            encrypted[i] = text[i];
    }
    encrypted[i] = '\0';

    /* Decryption */
    for(i = 0; encrypted[i] != '\0'; i++)
    {
        if(isalpha((unsigned char)encrypted[i]))
        {
            if(isupper((unsigned char)encrypted[i]))
                x = encrypted[i] - 'A';
            else
                x = encrypted[i] - 'a';

            x = (inv * (x - b + 26)) % 26;

            if(isupper((unsigned char)encrypted[i]))
                decrypted[i] = x + 'A';
            else
                decrypted[i] = x + 'a';
        }
        else
            decrypted[i] = encrypted[i];
    }
    decrypted[i] = '\0';

    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
