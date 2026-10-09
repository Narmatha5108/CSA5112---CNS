#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

/* Create 5 x 5 matrix */
void createMatrix(char key[])
{
    char used[26] = {0};
    int r = 0, c = 0, i;
    char ch;

    for(i = 0; key[i] != '\0'; i++)
    {
        ch = toupper(key[i]);

        if(ch == 'J')
            ch = 'I';

        if(ch >= 'A' && ch <= 'Z' && !used[ch - 'A'])
        {
            matrix[r][c++] = ch;
            used[ch - 'A'] = 1;

            if(c == 5)
            {
                c = 0;
                r++;
            }
        }
    }

    for(ch = 'A'; ch <= 'Z'; ch++)
    {
        if(ch == 'J')
            continue;

        if(!used[ch - 'A'])
        {
            matrix[r][c++] = ch;
            used[ch - 'A'] = 1;

            if(c == 5)
            {
                c = 0;
                r++;
            }
        }
    }
}

/* Find position of a character */
void findPosition(char ch, int *r, int *c)
{
    int i, j;

    if(ch == 'J')
        ch = 'I';

    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
            if(matrix[i][j] == ch)
            {
                *r = i;
                *c = j;
                return;
            }
}

/* Encryption / Decryption */
void playfair(char text[], char result[], int decrypt)
{
    int i, r1, c1, r2, c2;
    int shift;

    shift = decrypt ? 4 : 1;

    for(i = 0; text[i] != '\0'; i += 2)
    {
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if(r1 == r2)
        {
            result[i] = matrix[r1][(c1 + shift) % 5];
            result[i + 1] = matrix[r2][(c2 + shift) % 5];
        }
        else if(c1 == c2)
        {
            result[i] = matrix[(r1 + shift) % 5][c1];
            result[i + 1] = matrix[(r2 + shift) % 5][c2];
        }
        else
        {
            result[i] = matrix[r1][c2];
            result[i + 1] = matrix[r2][c1];
        }
    }

    result[i] = '\0';
}

int main()
{
    char key[100], text[100];
    char encrypted[100], decrypted[100];

    printf("Enter key: ");
    scanf("%s", key);

    printf("Enter text (even number of letters): ");
    scanf("%s", text);

    createMatrix(key);

    printf("\nPlayfair Matrix:\n");

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);

        printf("\n");
    }

    playfair(text, encrypted, 0);
    playfair(encrypted, decrypted, 1);

    printf("\nEncrypted text: %s", encrypted);
    printf("\nDecrypted text: %s", decrypted);

    return 0;
}
