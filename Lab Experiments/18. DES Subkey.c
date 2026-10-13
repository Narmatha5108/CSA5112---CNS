
#include <stdio.h>
#include <stdint.h>

/* DES PC-1 permutation: 64 bits to 56 bits */
int PC1[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,10,
    2,59,51,43,35,27,11,
    3,60,52,44,36,63,55,
    47,39,31,23,15,7,62,
    54,46,38,30,22,14,6,
    61,53,45,37,29,21,13,
    5,28,20,12,4,27,19,
    11,3,25,17,9,1,58,
    50,42,34,26,18,10,2
};

/* Correct DES PC-1 table */
int pc1[56] = {
    57,49,41,33,25,17,9,1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,21,13,5,28,20,12,4
};

/* DES PC-2 permutation: 56 bits to 48 bits */
int pc2[48] = {
    14,17,11,24,1,5,3,28,15,6,21,10,
    23,19,12,4,26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,51,45,33,48,
    44,49,39,56,34,53,46,42,50,36,29,32
};

int shifts[16] = {
    1,1,2,2,2,2,2,2,
    1,2,2,2,2,2,2,1
};

void leftShift(int half[28], int n)
{
    while (n--) {
        int first = half[0];

        for (int i = 0; i < 27; i++)
            half[i] = half[i + 1];

        half[27] = first;
    }
}

int main(void)
{
    uint64_t key;
    int key56[56], C[28], D[28];

    printf("Enter 64-bit DES key in hexadecimal: ");
    scanf("%llx", (unsigned long long *)&key);

    /* Apply PC-1 to remove parity bits */
    for (int i = 0; i < 56; i++)
        key56[i] = (key >> (64 - pc1[i])) & 1;

    /* Divide into two disjoint 28-bit halves */
    for (int i = 0; i < 28; i++) {
        C[i] = key56[i];
        D[i] = key56[i + 28];
    }

    printf("\nDES 48-bit round subkeys:\n");

    for (int round = 0; round < 16; round++) {
        int combined[56];
        int subkey[48];

        /* Rotate both halves */
        leftShift(C, shifts[round]);
        leftShift(D, shifts[round]);

        /* Join C and D */
        for (int i = 0; i < 28; i++) {
            combined[i] = C[i];
            combined[i + 28] = D[i];
        }

        /* Apply PC-2 to select 48 bits */
        for (int i = 0; i < 48; i++)
            subkey[i] = combined[pc2[i] - 1];

        printf("K%02d = ", round + 1);

        for (int i = 0; i < 48; i++)
            printf("%d", subkey[i]);

        printf("\n");
    }

    return 0;
}
