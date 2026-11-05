#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char cipher[1000], result[1000];
    char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    int freq[26] = {0};
    int order[26];
    char mapping[26];
    printf("Enter encrypted message: ");
    fgets(cipher, sizeof(cipher), stdin);
    cipher[strcspn(cipher, "\n")] = '\0';
    for (int i = 0; cipher[i]; i++) {
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
    }
    for (int i = 0; i < 26; i++)
        order[i] = i;
    // Sort letters by frequency
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freq[order[j]] > freq[order[i]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    printf("\nTop 10 Possible Plaintexts:\n");
    for (int k = 0; k < 10; k++) {
        // Generate frequency mapping
        for (int i = 0; i < 26; i++)
            mapping[order[i]] = english[(i + k) % 26];
        // Decrypt message
        for (int i = 0; cipher[i]; i++) {
            char ch = cipher[i];
            if (isupper((unsigned char)ch))
                result[i] = mapping[ch - 'A'];
            else if (islower((unsigned char)ch))
                result[i] = tolower(mapping[ch - 'a']);
            else
                result[i] = ch;
        }
        result[strlen(cipher)] = '\0';
        printf("\nCandidate %d: %s\n", k + 1, result);
    }
    printf("\nFrequency Analysis Completed!\n");
    return 0;
}
