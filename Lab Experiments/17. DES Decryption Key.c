```c
#include <stdio.h>
#include <stdint.h>

/* DES left-shift schedule */
int shiftSchedule[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

/* Generate reverse-order keys for decryption */
void generateDecryptionKeys(uint64_t keys[16])
{
    uint64_t temp;

    for (int i = 0; i < 16; i++)
        keys[i] = i + 1;  /* Demonstration key labels */

    for (int i = 0; i < 8; i++) {
        temp = keys[i];
        keys[i] = keys[15 - i];
        keys[15 - i] = temp;
    }
}

/* Display the decryption key order */
int main(void)
{
    uint64_t keys[16];

    generateDecryptionKeys(keys);

    printf("DES Decryption Key Schedule\n");
    printf("---------------------------\n");

    for (int i = 0; i < 16; i++)
        printf("Round %2d: K%llu\n",
               i + 1,
               (unsigned long long)keys[i]);

    printf("\nDecryption uses keys in reverse order:\n");
    printf("K16, K15, K14, ..., K2, K1\n");

    printf("\nDES left-shift schedule:\n");
    for (int i = 0; i < 16; i++)
        printf("%d ", shiftSchedule[i]);

    printf("\n");

    return 0;
}
```
