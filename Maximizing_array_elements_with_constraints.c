#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);


/*
 * Complete the 'maxElement' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER maxSum
 *  3. INTEGER k
 */
bool check(int n, int i, int maxSum, int m) 
{
    for (int d = 1; maxSum >= 0 && d < m && i + d < n; d++)
        maxSum -= m - d;
    for (int d = 1; maxSum >= 0 && d < m && i - d >= 0; d++)
        maxSum -= m - d;
    return maxSum >= 0;
}

int maxElement(int n, int maxSum,int k){
    int l = 0, r = maxSum;
    while (l < r) 
    {
        int m = (l + r + 1) / 2;
        if(check(n, k, maxSum - n - m, m))
            l = m;
        else
            r = m - 1;
    }
    return l + 1;
}
// int maxElement(int n, int maxSum, int k) {
//     // Stores the sum of elements in the left and right of k K
//     int S1 = 0, S2 = 0;
 
//     S1 = k * (k + 1) / 2;
//     S2 = (n - k - 1) * (n - k) / 2;
 
//     // Stores the maximum possible value at k K
//     int X = (maxSum + S1 + S2) / n;

//     return X;
// }

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int maxSum = parse_int(ltrim(rtrim(readline())));

    int k = parse_int(ltrim(rtrim(readline())));

    int result = maxElement(n, maxSum, k);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
