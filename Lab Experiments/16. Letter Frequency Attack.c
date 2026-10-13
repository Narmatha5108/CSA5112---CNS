```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2000
#define ALPHABET 26

char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

typedef struct {
    char text[SIZE];
    double score;
} Candidate;

int main() {
    char cipher[SIZE];
    int freq[ALPHABET] = {0};
    int order[ALPHABET];
    int n, i, j, k, temp;
    int top, count = 0;

    Candidate candidates[26];

    printf("Enter encrypted message:\n");
    fgets(cipher, SIZE, stdin);

    printf("Enter number of top plaintexts (1-10): ");
    scanf("%d", &top);

    if (top < 1 || top > 10) {
        printf("Please enter a number between 1 and 10.\n");
        return 0;
    }

    n = strlen(cipher);

    /* Count the frequency of each letter */
    for (i = 0; i < n; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
        }
    }

    /* Sort cipher letters by frequency */
    for (i = 0; i < ALPHABET; i++)
        order[i] = i;

    for (i = 0; i < ALPHABET - 1; i++) {
        for (j = i + 1; j < ALPHABET; j++) {
            if (freq[order[j]] > freq[order[i]]) {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    /*
       Try different frequency mappings.
       Common English letters are:
       E, T, A, O, I, N, S, H, R...
    */
    for (k = 0; k < ALPHABET; k++) {
        char map[ALPHABET];

        for (i = 0; i < ALPHABET; i++) {
            map[order[i]] = english[(i + k) % ALPHABET];
        }

        strcpy(candidates[k].text, cipher);

        /* Decrypt using the estimated mapping */
        for (i = 0; i < n; i++) {
            unsigned char ch = (unsigned char)cipher[i];

            if (isupper(ch))
                candidates[k].text[i] = map[ch - 'A'];
            else if (islower(ch))
                candidates[k].text[i] =
                    tolower((unsigned char)map[ch - 'a']);
        }

        /* Score common English letter pairs */
        candidates[k].score = 0;

        for (i = 0; i < n - 1; i++) {
            char a = toupper(
                (unsigned char)candidates[k].text[i]);
            char b = toupper(
                (unsigned char)candidates[k].text[i + 1]);

            if (a == 'T' && b == 'H') candidates[k].score += 3;
            if (a == 'H' && b == 'E') candidates[k].score += 3;
            if (a == 'I' && b == 'N') candidates[k].score += 2;
            if (a == 'E' && b == 'R') candidates[k].score += 2;
            if (a == 'A' && b == 'N') candidates[k].score += 2;
            if (a == 'R' && b == 'E') candidates[k].score += 2;
            if (a == 'O' && b == 'N') candidates[k].score += 2;
            if (a == 'A' && b == 'T') candidates[k].score += 2;
            if (a == 'N' && b == 'D') candidates[k].score += 2;
            if (a == 'E' && b == 'N') candidates[k].score += 2;
            if (a == 'T' && b == 'E') candidates[k].score += 2;
            if (a == 'E' && b == 'S') candidates[k].score += 2;
        }

        /* Reward common English words */
        {
            char lower[SIZE];
            strcpy(lower, candidates[k].text);

            for (i = 0; lower[i]; i++)
                lower[i] = tolower((unsigned char)lower[i]);

            if (strstr(lower, " the ")) candidates[k].score += 10;
            if (strstr(lower, " and ")) candidates[k].score += 8;
            if (strstr(lower, " is ")) candidates[k].score += 5;
            if (strstr(lower, " of ")) candidates[k].score += 5;
            if (strstr(lower, " to ")) candidates[k].score += 5;
            if (strstr(lower, " in ")) candidates[k].score += 5;
            if (strstr(lower, " that ")) candidates[k].score += 6;
            if (strstr(lower, " you ")) candidates[k].score += 5;
            if (strstr(lower, " for ")) candidates[k].score += 5;
            if (strstr(lower, " this ")) candidates[k].score += 6;
        }
    }

    /* Sort candidates by their English-language scores */
    for (i = 0; i < ALPHABET - 1; i++) {
        for (j = i + 1; j < ALPHABET; j++) {
            if (candidates[j].score > candidates[i].score) {
                Candidate t = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = t;
            }
        }
    }

    /* Display the requested number of candidates */
    printf("\nTop %d possible plaintexts:\n\n", top);

    for (i = 0; i < top; i++) {
        printf("%d. %s", i + 1, candidates[i].text);
        printf("Score: %.0f\n\n", candidates[i].score);
    }

    return 0;
}
```
