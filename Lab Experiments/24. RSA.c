```c
#include <stdio.h>

int main(void)
{
    int n = 3599, e = 31;
    int p, q, phi;
    int d = 1;

    /* Find p and q using trial and error */
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    /* Calculate Euler's totient */
    phi = (p - 1) * (q - 1);

    /* Find the modular inverse of e */
    while ((e * d) % phi != 1)
        d++;

    printf("RSA Private Key Calculation\n");
    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("n = %d\n", n);
    printf("Phi(n) = %d\n", phi);
    printf("Public key (e, n) = (%d, %d)\n", e, n);
    printf("Private key (d, n) = (%d, %d)\n", d, n);

    return 0;
}
```
