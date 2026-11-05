#include <stdio.h>
long long power(long long a, int b, int q) {
    long long result = 1;
    while (b > 0) {
        result = (result * a) % q;
        b--;
    }
    return result;
}
int main() {
    int q = 23, a = 5;
    int x, y;
    long long A, B, keyAlice, keyBob;
    printf("Enter Alice's secret number (1-21): ");
    scanf("%d", &x);
    printf("Enter Bob's secret number (1-21): ");
    scanf("%d", &y);
    if (x < 1 || x > 21 || y < 1 || y > 21) {
        printf("Invalid secret numbers!");
        return 0;
    }
    A = power(a, x, q);
    B = power(a, y, q);
    keyAlice = power(B, x, q);
    keyBob = power(A, y, q);
    printf("\nPublic Number q = %d", q);
    printf("\nPublic Number a = %d", a);
    printf("\nAlice Public Value = %lld", A);
    printf("\nBob Public Value = %lld", B);
    printf("\nAlice Shared Key = %lld", keyAlice);
    printf("\nBob Shared Key = %lld", keyBob);
    if (keyAlice == keyBob)
        printf("\nShared Key Established Successfully!");
    return 0;
}
