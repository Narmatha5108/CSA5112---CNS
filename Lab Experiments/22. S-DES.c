```c
#include <stdio.h>
#include <string.h>

int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[]  = {6,3,7,4,8,5,10,9};
int IP[]  = {2,6,3,1,4,8,5,7};
int IPI[] = {4,1,3,5,7,2,8,6};
int EP[]  = {4,1,2,3,2,3,4,1};
int P4[]  = {2,4,3,1};

int S0[4][4] = {
    {1,0,3,2}, {3,2,1,0},
    {0,2,1,3}, {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3}, {2,0,1,3},
    {3,0,1,0}, {2,1,0,3}
};

int permute(int x, int table[], int n, int bits)
{
    int result = 0;

    for (int i = 0; i < n; i++)
        result = (result << 1) |
                 ((x >> (bits - table[i])) & 1);

    return result;
}

int leftShift(int x, int n)
{
    return ((x << n) | (x >> (5 - n))) & 31;
}

void generateKeys(int key, int *k1, int *k2)
{
    int p = permute(key, P10, 10, 10);
    int left = (p >> 5) & 31;
    int right = p & 31;

    left = leftShift(left, 1);
    right = leftShift(right, 1);

    *k1 = permute((left << 5) | right, P8, 8, 10);

    left = leftShift(left, 2);
    right = leftShift(right, 2);

    *k2 = permute((left << 5) | right, P8, 8, 10);
}

int fk(int x, int key)
{
    int left = (x >> 4) & 15;
    int right = x & 15;

    int temp = permute(right, EP, 8, 4) ^ key;

    int a = (temp >> 4) & 15;
    int b = temp & 15;

    int row0 = ((a & 8) >> 2) | (a & 1);
    int col0 = (a >> 1) & 3;

    int row1 = ((b & 8) >> 2) | (b & 1);
    int col1 = (b >> 1) & 3;

    int s = (S0[row0][col0] << 2) |
             S1[row1][col1];

    return ((left ^ permute(s, P4, 4, 4)) << 4) | right;
}

int swapHalves(int x)
{
    return ((x & 15) << 4) | ((x >> 4) & 15);
}

int encryptBlock(int x, int k1, int k2)
{
    x = permute(x, IP, 8, 8);
    x = fk(x, k1);
    x = swapHalves(x);
    x = fk(x, k2);

    return permute(x, IPI, 8, 8);
}

int decryptBlock(int x, int k1, int k2)
{
    x = permute(x, IP, 8, 8);
    x = fk(x, k2);
    x = swapHalves(x);
    x = fk(x, k1);

    return permute(x, IPI, 8, 8);
}

void printBinary(int x)
{
    for (int i = 7; i >= 0; i--)
        printf("%d", (x >> i) & 1);
}

int main(void)
{
    char plaintext[257];
    int P[32], C[32], D[32];
    int key = 0b0111111101;
    int iv = 0b10101010;
    int k1, k2, n;

    printf("Enter binary plaintext (multiple of 8 bits): ");
    scanf("%256s", plaintext);

    n = strlen(plaintext);

    if (n == 0 || n % 8 != 0 || n / 8 > 32) {
        printf("Invalid input! Enter 8, 16, 24... bits (maximum 256).\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (plaintext[i] != '0' && plaintext[i] != '1') {
            printf("Invalid binary input!\n");
            return 1;
        }
    }

    for (int i = 0; i < n / 8; i++) {
        P[i] = 0;

        for (int j = 0; j < 8; j++)
            P[i] = (P[i] << 1) |
                   (plaintext[i * 8 + j] - '0');
    }

    generateKeys(key, &k1, &k2);

    /* CBC Encryption */
    int previous = iv;

    for (int i = 0; i < n / 8; i++) {
        C[i] = encryptBlock(P[i] ^ previous, k1, k2);
        previous = C[i];
    }

    printf("\nCiphertext:\n");
    for (int i = 0; i < n / 8; i++) {
        printBinary(C[i]);
        printf(" ");
    }

    /* CBC Decryption */
    previous = iv;

    for (int i = 0; i < n / 8; i++) {
        D[i] = decryptBlock(C[i], k1, k2) ^ previous;
        previous = C[i];
    }

    printf("\nDecrypted plaintext:\n");
    for (int i = 0; i < n / 8; i++) {
        printBinary(D[i]);
        printf(" ");
    }

    printf("\n");

    return 0;
}
```
