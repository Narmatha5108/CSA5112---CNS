#include <stdio.h>
#include <stdint.h>
uint64_t left64(uint64_t x) {
    return x << 1;
}
void generate64(uint64_t L) {
    uint64_t K1, K2;
    K1 = left64(L);
    if (L >> 63)
        K1 ^= 0x1B;
    K2 = left64(K1);
    if (K1 >> 63)
        K2 ^= 0x1B;
    printf("\n64-bit Block:\n");
    printf("K1 = %016llX\n", (unsigned long long)K1);
    printf("K2 = %016llX\n", (unsigned long long)K2);
}
void generate128(unsigned __int128 L) {
    unsigned __int128 K1, K2;
    K1 = L << 1;
    if (L >> 127)
        K1 ^= 0x87;
    K2 = K1 << 1;
    if (K1 >> 127)
        K2 ^= 0x87;
    printf("\n128-bit Block:\n");
    printf("K1 = %016llX%016llX\n",(unsigned long long)(K1 >> 64),(unsigned long long)K1);
    printf("K2 = %016llX%016llX\n",(unsigned long long)(K2 >> 64),(unsigned long long)K2);
}
int main() {
    generate64(0x8000000000000000ULL);
    generate128(((unsigned __int128)1 << 127));
    return 0;
}


a) Required constants:
Block size	Constant
64 bits	     0x1B
128 bits	   0x87

b) How left shift and XOR work:
    1. First, the block cipher encrypts an all-zero block to produce L.
    2. L is shifted left by one bit to generate K1.
    3. If the most significant bit is 1, the corresponding constant is XORed.
    4. The same operation is repeated on K1 to generate K2.
    5. These subkeys are used during CMAC generation.    
