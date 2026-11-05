#include <stdio.h>
#include <string.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int inverse(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}
int mod26(int x) {
    return (x % 26 + 26) % 26;
}
int main() {
    char p1[3], p2[3], c1[3], c2[3];
    int P[2][2], C[2][2], K[2][2];
    int det, inv;
    printf("Enter first plaintext pair: ");
    scanf("%2s", p1);
    printf("Enter second plaintext pair: ");
    scanf("%2s", p2);
    printf("Enter first ciphertext pair: ");
    scanf("%2s", c1);
    printf("Enter second ciphertext pair: ");
    scanf("%2s", c2);
    for (int i = 0; i < 2; i++) {
        if (p1[i] < 'A' || p1[i] > 'Z' ||
            p2[i] < 'A' || p2[i] > 'Z' ||
            c1[i] < 'A' || c1[i] > 'Z' ||
            c2[i] < 'A' || c2[i] > 'Z') {
            printf("Enter uppercase letters only.");
            return 0;
        }
    }
    P[0][0] = p1[0] - 'A';
    P[1][0] = p1[1] - 'A';
    P[0][1] = p2[0] - 'A';
    P[1][1] = p2[1] - 'A';
    C[0][0] = c1[0] - 'A';
    C[1][0] = c1[1] - 'A';
    C[0][1] = c2[0] - 'A';
    C[1][1] = c2[1] - 'A';
    det = mod26(P[0][0] * P[1][1] -
                P[0][1] * P[1][0]);
    if (gcd(det, 26) != 1) {
        printf("Plaintext matrix is not invertible.");
        return 0;
    }
    inv = inverse(det);
    int I[2][2];
    I[0][0] = mod26(inv * P[1][1]);
    I[0][1] = mod26(-inv * P[0][1]);
    I[1][0] = mod26(-inv * P[1][0]);
    I[1][1] = mod26(inv * P[0][0]);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            K[i][j] = mod26(
                C[i][0] * I[0][j] +
                C[i][1] * I[1][j]
            );
        }
    }
    printf("\nRecovered Hill Cipher Key:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d ", K[i][j]);
        printf("\n");
    }
    printf("\nKnown Plaintext Attack Successful!\n");
    return 0;
}
