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
char** split_string(char*);

int parse_int(char*);


/*
 * Complete the 'numberOfWays' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY roads as parameter.
 */

int dfs(int x, int d, int *dist, int **adj) {
    dist[x] = d;
    for (int i = 0; i < adj[x][0]; i++) {
        int y = adj[x][i+1];
        if (dist[y] == -1) {
            dfs(y, d + 1, dist, adj);
        }
    }
    return 0;
}

int numberOfWays(int roads_rows, int roads_columns, int** roads) {
    int n = roads_rows + 1;
    int **adj = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        adj[i] = malloc(sizeof(int) * n);
        memset(adj[i], 0, sizeof(int) * n);
    }
    for (int i = 0; i < roads_rows; i++) {
        int u = roads[i][0] - 1, v = roads[i][1] - 1;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
    int ans = 0;

    int *dist = malloc(sizeof(int) * n);

    void dfs(int x, int d) {
        dist[x] = d;
        for (int y = 0; y < n; y++) {
            if (adj[x][y] && dist[y] == -1) {
                dfs(y, d + 1);
            }
        }
    }

    // Brute force.
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                memset(dist, -1, sizeof(int) * n);
                dfs(i, 0);
                if (dist[j] != dist[k]) {
                    continue;
                }
                memset(dist, -1, sizeof(int) * n);
                dfs(j, 0);
                if (dist[i] == dist[k]) {
                    ans++;
                }
            }
        }
    }
    return ans;
}


int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int roads_rows = parse_int(ltrim(rtrim(readline())));

    int roads_columns = parse_int(ltrim(rtrim(readline())));

    int** roads = malloc(roads_rows * sizeof(int*));

    for (int i = 0; i < roads_rows; i++) {
        *(roads + i) = malloc(roads_columns * (sizeof(int)));

        char** roads_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < roads_columns; j++) {
            int roads_item = parse_int(*(roads_item_temp + j));

            *(*(roads + i) + j) = roads_item;
        }
    }

    int result = numberOfWays(roads_rows, roads_columns, roads);

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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
