```c
#include <stdio.h>
#include <string.h>

#define SIZE 256
#define BLOCK 8

/* Demonstration block operation */
void encryptBlock(char in[], char out[])
{
    for (int i = 0; i < BLOCK; i++)
        out[i] = in[i] ^ 0x5A;
}

void decryptBlock(char in[], char out[])
{
    encryptBlock(in, out);
}

/* Padding: append 1 bit, then 0 bits */
int addPadding(char data[], int len)
{
    data[len++] = (char)0x80;

    while (len % BLOCK != 0)
        data[len++] = 0;

    return len;
}

void ECB(char data[], int len)
{
    char out[SIZE];

    for (int i = 0; i < len; i += BLOCK)
        encryptBlock(data + i, out + i);

    printf("ECB Ciphertext: ");
    for (int i = 0; i < len; i++)
        printf("%02X ", (unsigned char)out[i]);

    printf("\n");
}

void CBC(char data[], int len)
{
    char out[SIZE], block[BLOCK];
    char iv[BLOCK] = {0};

    for (int i = 0; i < len; i += BLOCK) {
        for (int j = 0; j < BLOCK; j++)
            block[j] = data[i + j] ^ iv[j];

        encryptBlock(block, out + i);

        for (int j = 0; j < BLOCK; j++)
            iv[j] = out[i + j];
    }

    printf("CBC Ciphertext: ");
    for (int i = 0; i < len; i++)
        printf("%02X ", (unsigned char)out[i]);

    printf("\n");
}

void CFB(char data[], int len)
{
    char out[SIZE], iv[BLOCK] = {0};
    char stream[BLOCK];

    for (int i = 0; i < len; i += BLOCK) {
        encryptBlock(iv, stream);

        for (int j = 0; j < BLOCK; j++)
            out[i + j] = data[i + j] ^ stream[j];

        for (int j = 0; j < BLOCK; j++)
            iv[j] = out[i + j];
    }

    printf("CFB Ciphertext: ");
    for (int i = 0; i < len; i++)
        printf("%02X ", (unsigned char)out[i]);

    printf("\n");
}

int main(void)
{
    char data[SIZE];
    int len;

    printf("Enter plaintext: ");
    if (!fgets(data, sizeof(data), stdin))
        return 1;

    len = strlen(data);
    if (len > 0 && data[len - 1] == '\n')
        len--;

    /* Always add a padding marker */
    len = addPadding(data, len);

    printf("\nPadded length: %d bytes\n", len);

    ECB(data, len);
    CBC(data, len);
    CFB(data, len);

    return 0;
}
```
