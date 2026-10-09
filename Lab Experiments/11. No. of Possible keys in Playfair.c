```c
#include <stdio.h>
#include <math.h>

int main() {
    double keys, uniqueKeys;

    // 25 letters in the Playfair matrix
    keys = 1;
    for (int i = 1; i <= 25; i++)
        keys *= i;

    // Approximate effective unique keys
    uniqueKeys = keys / (25 * 24);

    printf("Total possible keys = 25! = %.0e\n", keys);
    printf("Approximate power of 2 = 2^%.2f\n",
           log(keys) / log(2));

    printf("Effectively unique keys = 25! / (25 x 24)\n");
    printf("Approximate unique keys = %.0e\n", uniqueKeys);
    printf("Unique keys as power of 2 = 2^%.2f\n",
           log(uniqueKeys) / log(2));

    return 0;
}
```
