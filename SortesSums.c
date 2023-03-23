// Sorted Sums
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
 * Complete the 'sortedSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */
//#include <stdio.h>

#define A_LIMIT 1000000
#define M 1000000007

// FWT data structure
typedef struct FWT {
    int n;
    int* a;
} FWT;

// FWT initialization function
FWT* FWT_init(int n) {
    FWT* fwt = (FWT*)malloc(sizeof(FWT));
    fwt->n = n;
    fwt->a = (int*)calloc(n, sizeof(int));
    return fwt;
}

// FWT rank update function
void FWT_add(FWT* fwt, int x, int k) {
    for (int i = x; i <= fwt->n; i += i & -i) {
        fwt->a[i] = (fwt->a[i] + k) % M;
    }
}

// FWT rank query function
int FWT_rank(FWT* fwt, int x) {
    int res = 0;
    for (int i = x; i > 0; i -= i & -i) {
        res = (res + fwt->a[i]) % M;
    }
    return res;
}

// sortedSum function
int sortedSum(int a_count, int* a) {
    // pre.rank(x) := How many digits are before x.
    FWT* pre = FWT_init(A_LIMIT + 1);
    // post.rank(x) := How much of the total sum is after x.
    FWT* post = FWT_init(A_LIMIT + 1);
    int cur_fn = 0, ans = 0, total = 0;
    for (int i = 0; i < a_count; i++) {
        int pos = FWT_rank(pre, a[i]) + 1;
        // The part of f(n) which will also be added because
        // it gets shifted one to the right.
        int greater = (total - FWT_rank(post, a[i])) % M;
        if (greater < 0) greater += M;
        cur_fn = (cur_fn + 1LL * pos * a[i] % M + greater) % M;
        ans = (ans + cur_fn) % M;
        FWT_add(pre, a[i], 1);
        FWT_add(post, a[i], a[i]);
        total = (total + a[i]) % M;
    }
    free(pre->a);
    free(pre);
    free(post->a);
    free(post);
    return ans;
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int a_count = parse_int(ltrim(rtrim(readline())));

    int* a = malloc(a_count * sizeof(int));

    for (int i = 0; i < a_count; i++) {
        int a_item = parse_int(ltrim(rtrim(readline())));

        *(a + i) = a_item;
    }

    int result = sortedSum(a_count, a);

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
