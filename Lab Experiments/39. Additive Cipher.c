#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char cipher[500], result[500];
    int shift[26], count = 0;
    double score[26];
    double english[26] = {
        8.2, 1.5, 2.8, 4.3, 12.7, 2.2,
        2.0, 6.1, 7.0, 0.15, 0.77, 4.0,
        2.4, 6.7, 7.5, 1.9, 0.095, 6.0,
        6.3, 9.1, 2.8, 0.98, 2.4, 0.15,
        2.0, 0.074
    };
    printf("Enter encrypted message: ");
    fgets(cipher, sizeof(cipher), stdin);
    cipher[strcspn(cipher, "\n")] = '\0';
    for (int k = 0; k < 26; k++) {
        int freq[26] = {0};
        int total = 0;
        for (int i = 0; cipher[i]; i++) {
            if (isalpha((unsigned char)cipher[i])) {
                int ch = toupper((unsigned char)cipher[i]);
                freq[(ch - 'A' - k + 26) % 26]++;
                total++;
            }
        }
        score[k] = 0;
        if (total == 0) {
            score[k] = 1000000;
        } else {
            for (int j = 0; j < 26; j++) {
                double expected = english[j] * total / 100.0;
                double diff = freq[j] - expected;
                if (expected > 0)
                    score[k] += diff * diff / expected;
            }
        }
        shift[k] = k;
    }
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (score[shift[j]] < score[shift[i]]) {
                int temp = shift[i];
                shift[i] = shift[j];
                shift[j] = temp;
            }
        }
    }
    printf("\nPossible Plaintexts:\n");
    for (int k = 0; k < 10; k++) {
        int s = shift[k];
        for (int i = 0; cipher[i]; i++) {
            char ch = cipher[i];
            if (isupper((unsigned char)ch))
                result[i] = 'A' + (ch - 'A' - s + 26) % 26;
            else if (islower((unsigned char)ch))
                result[i] = 'a' + (ch - 'a' - s + 26) % 26;
            else
                result[i] = ch;
        }
        result[strlen(cipher)] = '\0';
        printf("\nCandidate %d (Shift %d): %s",
               k + 1, s, result);
    }
    printf("\n\nFrequency Attack Completed!\n");
    return 0;
}
