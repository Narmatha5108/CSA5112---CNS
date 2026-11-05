#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char cipher[1000], result[1000];
    char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    char letters[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int freq[26] = {0};
    int order[26];
    int top;
    printf("Enter encrypted message: ");
    fgets(cipher, sizeof(cipher), stdin);
    cipher[strcspn(cipher, "\n")] = '\0';
    printf("Enter number of possible plaintexts: ");
    scanf("%d", &top);
    for (int i = 0; cipher[i]; i++) {
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
    }
    for (int i = 0; i < 26; i++)
        order[i] = i;
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freq[order[j]] > freq[order[i]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    if (top < 1) top = 1;
    if (top > 10) top = 10;
    printf("\nPossible Plaintexts:\n");
    for (int k = 0; k < top; k++) {
        for (int i = 0; cipher[i]; i++) {
            char ch = cipher[i];
            if (isupper((unsigned char)ch)) {
                int pos = ch - 'A';
                result[i] = english[(pos + k) % 26];
            }
            else if (islower((unsigned char)ch)) {
                int pos = ch - 'a';
                result[i] = tolower(english[(pos + k) % 26]);
            }
            else {
                result[i] = ch;
            }
        }
        result[strlen(cipher)] = '\0';
        printf("\nCandidate %d: %s\n", k + 1, result);
    }
    printf("\nFrequency attack completed.\n");
    return 0;
}
