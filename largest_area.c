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
 * Complete the 'getMaxArea' function below.
 *
 * The function is expected to return a LONG_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER w
 *  2. INTEGER h
 *  3. BOOLEAN_ARRAY isVertical
 *  4. INTEGER_ARRAY distance
 */

/*
 * To return the long integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * long* return_long_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static long a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * long* return_long_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     long *a = malloc(5 * sizeof(long));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */

typedef struct Node {
    struct Node* parent;
    int l, r;
    struct Node* lc;
    struct Node* rc;
    int val;
    int (*op)(int, int);
} Node;

int max(int a, int b) {
    return a > b ? a : b;
}
Node* create_node(Node* parent, int l, int r, int (*op)(int, int)) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = parent;
    node->l = l;
    node->r = r;
    node->lc = NULL;
    node->rc = NULL;
    node->val = r - l;
    node->op = op;
    return node;
}

void split(Node* node, int x) {
    // No balancing, but doesn't seem to give timeouts.
    if (!(node->l <= x && x <= node->r)) {
        return;
    }
    if (x == node->l || x == node->r) {
        // Split lies on borders.
        return;
    }
    if (node->lc) {
        if (x == node->lc->r) {
            // Split lies on mid split.
            return;
        }
        if (x < node->lc->r) {
            split(node->lc, x);
        } else {
            split(node->rc, x);
        }
        node->val = node->op(node->lc->val, node->rc->val);
    } else {
        node->lc = create_node(node, node->l, x, node->op);
        node->rc = create_node(node, x, node->r, node->op);
        node->val = node->op(x - node->l, node->r - x);
    }
}

long* getMaxArea(int w, int h, int isVertical_count, bool* isVertical, int distance_count, int* distance, int* result_count) {
    Node* w_root = create_node(NULL, 0, w, &max);
    Node* h_root = create_node(NULL, 0, h, &max);
    long* ans = (long*)malloc(distance_count * sizeof(long));
    for (int i = 0; i < distance_count; i++) {
        if (isVertical[i]) {
            split(w_root, distance[i]);
        } else {
            split(h_root, distance[i]);
        }
        ans[i] = (long)w_root->val * h_root->val;
    }
    *result_count = distance_count;
    return ans;
}

// long* getMaxArea(int w, int h, int isVertical_count, bool* isVertical, int distance_count, int* distance, int* result_count) {

// }

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int w = parse_int(ltrim(rtrim(readline())));

    int h = parse_int(ltrim(rtrim(readline())));

    int isVertical_count = parse_int(ltrim(rtrim(readline())));

    bool* isVertical = malloc(isVertical_count * sizeof(bool));

    for (int i = 0; i < isVertical_count; i++) {
        bool isVertical_item = parse_int(ltrim(rtrim(readline()))) != 0;

        *(isVertical + i) = isVertical_item;
    }

    int distance_count = parse_int(ltrim(rtrim(readline())));

    int* distance = malloc(distance_count * sizeof(int));

    for (int i = 0; i < distance_count; i++) {
        int distance_item = parse_int(ltrim(rtrim(readline())));

        *(distance + i) = distance_item;
    }

    int result_count;
    long* result = getMaxArea(w, h, isVertical_count, isVertical, distance_count, distance, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%ld", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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
