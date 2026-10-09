
#include <stdio.h>
#include <string.h>

int main()
{
    char cipher[2000], line[500];
    int i = 0, j = 0;

    printf("Enter ciphertext (press Enter on a blank line to finish):\n");

    while(fgets(line, sizeof(line), stdin))
    {
        if(line[0] == '\n')
            break;

        if(i + strlen(line) < sizeof(cipher))
        {
            strcpy(cipher + i, line);
            i += strlen(line);
        }
    }

    cipher[i] = '\0';

    printf("\nDecrypted text:\n");

    while(cipher[j] != '\0')
    {
        if(strncmp(&cipher[j], "‡", strlen("‡")) == 0)
        {
            printf("o");
            j += strlen("‡");
        }
        else if(strncmp(&cipher[j], "†", strlen("†")) == 0)
        {
            printf("d");
            j += strlen("†");
        }
        else if(strncmp(&cipher[j], "¶", strlen("¶")) == 0)
        {
            printf("v");
            j += strlen("¶");
        }
        else if(strncmp(&cipher[j], "—", strlen("—")) == 0)
        {
            printf("c");
            j += strlen("—");
        }
        else
        {
            switch(cipher[j])
            {
                case '5': printf("a"); break;
                case '3': printf("g"); break;
                case '0': printf("l"); break;
                case ')': printf("s"); break;
                case '6': printf("i"); break;
                case '*': printf("n"); break;
                case ';': printf("t"); break;
                case '4': printf("h"); break;
                case '8': printf("e"); break;
                case '2': printf("b"); break;
                case '.': printf("p"); break;
                case '1': printf("f"); break;
                case '(': printf("r"); break;
                case '?': printf("u"); break;
                case '9': printf("m"); break;
                case ']': printf("w"); break;
                case ':': printf("y"); break;
                case '\n': printf("\n"); break;
                default: printf("%c", cipher[j]);
            }

            j++;
        }
    }

    printf("\n");
    return 0;
}
