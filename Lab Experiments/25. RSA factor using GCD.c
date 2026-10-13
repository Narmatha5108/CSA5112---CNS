```c
#include <stdio.h>

/* Find GCD using Euclidean algorithm */
int gcd(int a, int b)
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void)
{
    int n, e, m, g, p, q, phi, d;

    printf("Enter RSA modulus n: ");
    scanf("%d", &n);

    printf("Enter public key e: ");
    scanf("%d", &e);

    printf("Enter known plaintext block m: ");
    scanf("%d", &m);

    g = gcd(m, n);

    printf("\nGCD(m, n) = %d\n", g);

    if (g > 1 && g < n) {
        p = g;
        q = n / p;

        printf("Factor p = %d\n", p);
        printf("Factor q = %d\n", q);

        phi = (p - 1) * (q - 1);

        /* Find private exponent using a simple search */
        for (d = 1; d < phi; d++) {
            if (((long long)e * d) % phi == 1)
                break;
        }

        if (d < phi)
            printf("Private key d = %d\n", d);
        else
            printf("Private key not found.\n");
    }
    else {
        printf("This block does not reveal a non-trivial factor.\n");
    }

    return 0;
}
```
