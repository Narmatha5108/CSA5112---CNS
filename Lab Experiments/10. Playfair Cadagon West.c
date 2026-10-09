```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void findPosition(char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

int main() {
    char message[] =
        "Must see you over Cadogan West. Coming at once.";
    char text[500], encrypted[500];
    int i, j, r1, c1, r2, c2, k = 0;

    // Remove spaces and punctuation
    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i])) {
            char ch = toupper((unsigned char)message[i]);
            if (ch == 'J')
                ch = 'I';
            text[k++] = ch;
        }
    }
    text[k] = '\0';

    // Add X if the number of letters is odd
    if (k % 2 != 0) {
        text[k++] = 'X';
        text[k] = '\0';
    }

    // Encrypt pairs of letters
    printf("Encrypted message:\n");

    for (i = 0; i < k; i += 2) {
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2) {
            encrypted[i] = matrix[r1][(c1 + 1) % 5];
            encrypted[i + 1] = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            encrypted[i] = matrix[(r1 + 1) % 5][c1];
            encrypted[i + 1] = matrix[(r2 + 1) % 5][c2];
        } else {
            encrypted[i] = matrix[r1][c2];
            encrypted[i + 1] = matrix[r2][c1];
        }
    }

    encrypted[k] = '\0';

    // Display encrypted pairs
    for (i = 0; i < k; i++) {
        printf("%c", encrypted[i]);
        if ((i + 1) % 5 == 0)
            printf(" ");
    }

    printf("\n");
    return 0;
}
```
