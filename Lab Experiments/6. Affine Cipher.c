#include <stdio.h>

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
    char text[100], encrypted[100], decrypted[100];
    int a, b, i, x, inv;

    printf("Enter the text: ");
    scanf("%s", text);

    printf("Enter a and b: ");
    scanf("%d %d", &a, &b);

    if(gcd(a, 26) != 1)
    {
        printf("Invalid value of a");
        return 0;
    }

    /* Find inverse of a */
    for(inv = 1; inv < 26; inv++)
    {
        if((a * inv) % 26 == 1)
            break;
    }

    /* Encryption: E(x) = (ax + b) mod 26 */
    for(i = 0; text[i] != '\0'; i++)
    {
        x = text[i] - 'A';
        encrypted[i] = (a * x + b) % 26 + 'A';
    }
    encrypted[i] = '\0';

    /* Decryption: D(x) = a^-1(x - b) mod 26 */
    for(i = 0; encrypted[i] != '\0'; i++)
    {
        x = encrypted[i] - 'A';
        decrypted[i] = (inv * (x - b + 26)) % 26 + 'A';
    }
    decrypted[i] = '\0';

    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
