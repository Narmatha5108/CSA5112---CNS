#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
int main() {
    DES_cblock key = {
        0x13, 0x34, 0x57, 0x79,
        0x9B, 0xBC, 0xDF, 0xF1
    };
    DES_key_schedule schedule;
    DES_set_key_unchecked(&key, &schedule);
    char message[100];
    unsigned char input[8], encrypted[8], decrypted[8];
    printf("Enter message (maximum 8 characters): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    int len = strlen(message);
    if (len == 0 || len > 8) {
        printf("Enter 1 to 8 characters only.");
        return 0;
    }
    memset(input, 0, 8);
    memcpy(input, message, len);
    DES_ecb_encrypt(
        (const_DES_cblock *)input,
        (DES_cblock *)encrypted,
        &schedule,
        DES_ENCRYPT
    );
    DES_ecb_encrypt(
        (const_DES_cblock *)encrypted,
        (DES_cblock *)decrypted,
        &schedule,
        DES_DECRYPT
    );
    printf("\nEncrypted Message: ");
    for (int i = 0; i < 8; i++)
        printf("%02X", encrypted[i]);
    decrypted[len] = '\0';
    printf("\nDecrypted Message: %s\n", decrypted);
    printf("DES Encryption and Decryption Successful!\n");
    return 0;
}
