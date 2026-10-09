```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char key[100];
char matrix[5][5];
int used[26] = {0};

void createMatrix() {
    int i, j, k = 0;
    char ch;

    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper((unsigned char)key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            k++;
        }
    }
}

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

void decryptPair(char a, char b) {
    int r1, c1, r2, c2;

    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);

    if (r1 == r2) {
        putchar(matrix[r1][(c1 + 4) % 5]);
        putchar(matrix[r2][(c2 + 4) % 5]);
    } else if (c1 == c2) {
        putchar(matrix[(r1 + 4) % 5][c1]);
        putchar(matrix[(r2 + 4) % 5][c2]);
    } else {
        putchar(matrix[r1][c2]);
        putchar(matrix[r2][c1]);
    }
}

int main() {
    char message[] =
        "KXJEY UREBE ZWEHE WRYTU HEYFS "
        "KREHE GOYFI WTTTU OLKSY CAJPO "
        "BOTEI ZONTX BYBNT GONEY CUZWR "
        "GDSON SXBOU YWRHE BAAHY USEDQ";

    int i, count = 0;
    char clean[500];

    printf("Enter Playfair keyword: ");
    fgets(key, sizeof(key), stdin);

    createMatrix();

    printf("\n5 x 5 Key Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i])) {
            clean[count++] = toupper((unsigned char)message[i]);
        }
    }

    clean[count] = '\0';

    printf("\nEncrypted message:\n%s\n", message);
    printf("\nDecrypted message:\n");

    for (i = 0; i + 1 < count; i += 2) {
        decryptPair(clean[i], clean[i + 1]);
    }

    printf("\n");
    return 0;
}
```
