#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min_idx(float *m, int n)
{
    int idx = 0;
    float mn = m[0];
    for (int i = 1; i < n; ++i) {
        if (mn > m[i]) {
            mn = m[i];
            idx = i;
        }
    }
    return idx;
}

int main()
{
    srand((unsigned int)time(NULL));
    float A[25], B[25];

    int N1 = rand() % 25 + 1;
    printf("N1 = %d\n", N1);
    for (int i = 0; i < N1; ++i) {
        A[i] = (float)rand() / rand();
        printf("%.2f ", A[i]);
    }
    printf("\n");

    int N2 = rand() % 25 + 1;
    printf("N2 = %d\n", N2);
    for (int i = 0; i < N2; ++i) {
        B[i] = (float)rand() / rand();
        printf("%.2f ", B[i]);
    }
    printf("\n");

    int min1 = min_idx(A, N1);
    int min2 = min_idx(B, N2);

    printf("%d %d\n", min1, min2);
    if (N1 - 1 - min1 < N2 - 1 - min2) {
        printf("A: %d elements to the end", N1 - 1 - min1);
    }
    else {
        printf("B: %d elements to the end", N2 - 1 - min2);
    }

    return 0;
}
