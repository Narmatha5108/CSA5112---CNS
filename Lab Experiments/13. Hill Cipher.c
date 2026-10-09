```c
#include <stdio.h>

int main() {
    int p[2][2] = {{2, 4}, {3, 5}};
    int c[2][2] = {{8, 18}, {15, 23}};
    int inv[2][2];
    int key[2][2];
    int det, i, j;

    // Find determinant of plaintext matrix
    det = (p[0][0] * p[1][1] -
           p[0][1] * p[1][0]) % 26;

    if (det < 0)
        det += 26;

    // Find modular inverse of determinant
    int d;
    for (d = 1; d < 26; d++) {
        if ((det * d) % 26 == 1)
            break;
    }

    if (d == 26) {
        printf("Plaintext matrix has no inverse modulo 26.\n");
        return 0;
    }

    // Inverse of plaintext matrix modulo 26
    inv[0][0] = (p[1][1] * d) % 26;
    inv[0][1] = (-p[0][1] * d) % 26;
    inv[1][0] = (-p[1][0] * d) % 26;
    inv[1][1] = (p[0][0] * d) % 26;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            if (inv[i][j] < 0)
                inv[i][j] += 26;

    // Calculate key = ciphertext * inverse(plaintext)
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            key[i][j] = 0;

            for (int k = 0; k < 2; k++)
                key[i][j] += c[i][k] * inv[k][j];

            key[i][j] %= 26;
        }
    }

    printf("Recovered Hill Cipher Key:\n");

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            printf("%d ", key[i][j]);

        printf("\n");
    }

    return 0;
}
```
