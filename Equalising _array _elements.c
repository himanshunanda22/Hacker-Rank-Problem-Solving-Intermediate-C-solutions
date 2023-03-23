#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100005

int minOperations(int arr_count, int* arr, int threshold, int d) {
    // dp[i] := [count of i values, number of steps]
    int dp[MAX_N][2] = {0};
    int i, x, steps, ans = INT_MAX;

    // Sort the array in non-decreasing order
    qsort(arr, arr_count, sizeof(int), cmp);

    for (i = 0; i < arr_count; i++) {
        x = arr[i];
        steps = 0;

        while (1) {
            dp[x][0]++;
            dp[x][1] += steps;

            if (dp[x][0] >= threshold) {
                ans = (ans < dp[x][1]) ? ans : dp[x][1];
            }

            if (x == 0) {
                break;
            }

            x /= d;
            steps++;
        }
    }

    return ans;
}

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


