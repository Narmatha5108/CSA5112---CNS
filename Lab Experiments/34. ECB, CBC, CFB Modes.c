#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define BLOCK 8
void encryptBlock(unsigned char in[], unsigned char out[]) {
    for (int i = 0; i < BLOCK; i++)
        out[i] = in[i] ^ 0x5A;
}
void printBlock(unsigned char data[], int len) {
    for (int i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("\n");
}
int main() {
    unsigned char message[200];
    unsigned char padded[208] = {0};
    unsigned char output[208] = {0};
    unsigned char block[8], result[8];
    unsigned char iv[8] = {1,2,3,4,5,6,7,8};
    printf("Enter message: ");
    fgets((char *)message, sizeof(message), stdin);
    int len = strcspn((char *)message, "\n");
    message[len] = '\0';
    if (len == 0 || len > 199) {
        printf("Invalid message length!");
        return 0;
    }
    int total = ((len / BLOCK) + 1) * BLOCK;
    memcpy(padded, message, len);
    padded[len] = 0x80;
    printf("\nPadded Message: ");
    printBlock(padded, total);
    // ECB MODE
    printf("\nECB Mode:\n");
    for (int i = 0; i < total; i += BLOCK) {
        encryptBlock(padded + i, output + i);
    }
    printBlock(output, total);
    // CBC MODE
    printf("\nCBC Mode:\n");
    unsigned char previous[8];
    memcpy(previous, iv, BLOCK);
    for (int i = 0; i < total; i += BLOCK) {
        for (int j = 0; j < BLOCK; j++)
            block[j] = padded[i+j] ^ previous[j];
        encryptBlock(block, result);
        memcpy(output + i, result, BLOCK);
        memcpy(previous, result, BLOCK);
    }
    printBlock(output, total);
    // CFB MODE
    printf("\nCFB Mode:\n");
    memcpy(previous, iv, BLOCK);
    for (int i = 0; i < total; i += BLOCK) {
        encryptBlock(previous, result);
        for (int j = 0; j < BLOCK; j++) {
            output[i+j] = padded[i+j] ^ result[j];
            previous[j] = output[i+j];
        }
    }
    printBlock(output, total);
    printf("\nECB, CBC and CFB modes demonstrated successfully.\n");
    return 0;
}
