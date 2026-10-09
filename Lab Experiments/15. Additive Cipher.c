```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char cipher[1000], plain[1000];
    int shift, i, top;

    printf("Enter ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    printf("How many possible plaintexts? ");
    scanf("%d", &top);

    if (top < 1) top = 1;
    if (top > 26) top = 26;

    double freq[26] = {
        8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0,
        6.1, 7.0, 0.15, 0.77, 4.0, 2.4, 6.7,
        7.5, 1.9, 0.095, 6.0, 6.3, 9.1, 2.8,
        0.98, 2.4, 0.15, 2.0, 0.074
    };

    double score[26];
    char results[26][1000];

    // Try every possible shift
    for (shift = 0; shift < 26; shift++) {
        score[shift] = 0;

        for (i = 0; cipher[i] != '\0'; i++) {
            char ch = cipher[i];

            if (isalpha((unsigned char)ch)) {
                int c = tolower((unsigned char)ch) - 'a';
                int p = (c - shift + 26) % 26;

                plain[i] = isupper((unsigned char)ch)
                           ? p + 'A' : p + 'a';

                score[shift] += freq[p];
            } else {
                plain[i] = ch;
            }
        }

        plain[i] = '\0';
        strcpy(results[shift], plain);
    }

    // Sort shifts by frequency score
    for (i = 0; i < 26; i++) {
        int j;
        for (j = i + 1; j < 26; j++) {
            if (score[j] > score[i]) {
                double temp = score[i];
                score[i] = score[j];
                score[j] = temp;

                char tempText[1000];
                strcpy(tempText, results[i]);
                strcpy(results[i], results[j]);
                strcpy(results[j], tempText);
            }
        }
    }

    printf("\nTop %d possible plaintexts:\n", top);

    for (i = 0; i < top; i++) {
        printf("%d. %s", i + 1, results[i]);
    }

    return 0;
}
```
