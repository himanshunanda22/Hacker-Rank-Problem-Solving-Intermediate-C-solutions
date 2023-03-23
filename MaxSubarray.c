#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long maxSubarrayValue(int arr_count, int* arr) {
    int i, j, k;
    long ans = 0, a, b;
    long* even = (long*)malloc((arr_count+1)*sizeof(long));
    long* odd = (long*)malloc((arr_count+1)*sizeof(long));

    even[0] = 0;
    odd[0] = 0;

    for (i = 0; i < arr_count; i++) {
        if (i % 2 == 0) {
            even[i+1] = even[i] + arr[i];
            odd[i+1] = odd[i];
        } else {
            even[i+1] = even[i];
            odd[i+1] = odd[i] + arr[i];
        }
    }

    for (i = 0; i < arr_count; i++) {
        for (j = i + 1; j <= arr_count; j++) {
            a = even[j] - even[i];
            b = odd[j] - odd[i];
            ans = (a - b)*(a - b) > ans ? (a - b)*(a - b) : ans;
        }
    }

    free(even);
    free(odd);
    
    return ans;
}

int main() {
    int arr_count, i;
    scanf("%d", &arr_count);
    int* arr = (int*)malloc(arr_count*sizeof(int));
    for (i = 0; i < arr_count; i++) {
        scanf("%d", &arr[i]);
    }
    long result = maxSubarrayValue(arr_count, arr);
    printf("%ld\n", result);
    free(arr);
    return 0;
