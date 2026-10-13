```c
#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

int main(void)
{
    DES_cblock key1, key2, key3, iv;
    DES_key_schedule ks1, ks2, ks3;

    char plaintext[1024];
    unsigned char ciphertext[2048];
    unsigned char block[8];
    int len, padded_len, i;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    len = strlen(plaintext);
    if (len > 0 && plaintext[len - 1] == '\n')
        plaintext[--len] = '\0';

    /* Example keys and initialization vector */
    DES_cblock k1 = {1,2,3,4,5,6,7,8};
    DES_cblock k2 = {9,10,11,12,13,14,15,16};
    DES_cblock k3 = {17,18,19,20,21,22,23,24};
    DES_cblock v  = {0,1,2,3,4,5,6,7};

    memcpy(key1, k1, 8);
    memcpy(key2, k2, 8);
    memcpy(key3, k3, 8);
    memcpy(iv, v, 8);

    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    /* PKCS#7 padding */
    padded_len = ((len / 8) + 1) * 8;

    for (i = 0; i < padded_len; i++) {
        if (i < len)
            block[i % 8] = plaintext[i];

        if (i % 8 == 7 || i == padded_len - 1) {
            int start = i - (i % 8);

            for (int j = 0; j < 8; j++) {
                int pos = start + j;
                if (pos >= len)
                    block[j] = padded_len - len;
            }

            /* CBC: XOR with previous ciphertext or IV */
            for (int j = 0; j < 8; j++)
                block[j] ^= iv[j];

            /* 3DES EDE: Encrypt, Decrypt, Encrypt */
            DES_ecb3_encrypt((const_DES_cblock *)block,
                             (DES_cblock *)(ciphertext + start),
                             &ks1, &ks2, &ks3, DES_ENCRYPT);

            memcpy(iv, ciphertext + start, 8);
        }
    }

    printf("\nCiphertext (hexadecimal):\n");
    for (i = 0; i < padded_len; i++)
        printf("%02X", ciphertext[i]);

    printf("\n");
    return 0;
}
```
