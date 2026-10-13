```c
#include <stdio.h>

int main(void)
{
    int P[4] = {10, 20, 30, 40};
    int C[4], R[4], i;
    int IV = 5;

    printf("CBC Mode - Error Propagation\n\n");

    /* Simple demonstration encryption */
    for (i = 0; i < 4; i++) {
        int previous = (i == 0) ? IV : C[i - 1];
        C[i] = P[i] ^ previous;
    }

    printf("Original plaintext: ");
    for (i = 0; i < 4; i++)
        printf("%d ", P[i]);

    printf("\nOriginal ciphertext: ");
    for (i = 0; i < 4; i++)
        printf("%d ", C[i]);

    /* Introduce an error in ciphertext block C1 */
    C[0] ^= 1;

    /* Decrypt the corrupted ciphertext */
    for (i = 0; i < 4; i++) {
        int previous = (i == 0) ? IV : C[i - 1];
        R[i] = C[i] ^ previous;
    }

    printf("\n\nAfter error in C1:");
    printf("\nReceived plaintext: ");
    for (i = 0; i < 4; i++)
        printf("%d ", R[i]);

    printf("\n\nNote: This uses a simplified XOR model,");
    printf("\nnot actual DES or AES encryption.\n");

    return 0;
}
```

(a) Are any blocks beyond P2 affected?
      No. In CBC mode, an error in ciphertext block \(C_1\) corrupts the entire plaintext block \(P_1\) and flips the corresponding bit in \(P_2\). Blocks \(P_3\) and later remain unaffected.
(b) If a bit error occurs in the source version of P1, through how many ciphertext blocks is it propagated?
      In CBC mode, an error in plaintext block \(P_1\) affects all subsequent ciphertext blocks, \(C_1, C_2, C_3,\ldots\), because each ciphertext block depends on the previous ciphertext block.
At the receiver, the corrupted ciphertext generally causes \(P_1\) to be corrupted unpredictably, and subsequent plaintext blocks are also affected.
Result:
      - ECB: A ciphertext block error affects only its corresponding plaintext block.
      - CBC: A ciphertext block error corrupts the corresponding plaintext block and flips the matching bit in the next plaintext block. A plaintext error can propagate through all subsequent ciphertext blocks.
