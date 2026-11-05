#include <stdio.h>
#include <stdint.h>
#include <string.h>
uint64_t encrypt(uint64_t x, uint64_t key) {
    return x + key;
}
int main() {
    char message[20];
    uint64_t key = 0x123456789ABCDEF0ULL;
    uint64_t X = 0, T, secondBlock;
    uint64_t first, second;
    printf("Enter message (maximum 8 characters): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    int len = strlen(message);
    if (len == 0 || len > 8) {
        printf("Please enter 1 to 8 characters.");
        return 0;
    }
    for (int i = 0; i < len; i++) {
        X = (X << 8) | (unsigned char)message[i];
    }
    T = encrypt(X, key);
    secondBlock = X ^ T;
    first = encrypt(X, key);
    second = encrypt(secondBlock ^ first, key);
    printf("\nOriginal Message: %s", message);
    printf("\nOriginal MAC: %016llX",(unsigned long long)T);
    printf("\nSecond Block: %016llX",(unsigned long long)secondBlock);
    printf("\nForged MAC: %016llX",(unsigned long long)second);
    if (T == second)
        printf("\nCBC-MAC Forgery Successful!");
    return 0;
}
