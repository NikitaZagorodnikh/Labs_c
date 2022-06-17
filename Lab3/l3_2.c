#include <stdio.h>

const int N = 4;

int sum_column(int M[N][N], int N, int column_idx)
{
    int ans = 0;
    for (int i = column_idx; i < N; ++i) {
        ans += M[i][column_idx];
    }

    return ans;
}

int main()
{
    int M[N][N];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &M[i][j]);
        }
    }

    for (int i = )
    printf("%d\n", sum_column(M, N, i));
    // M = int **
    // M[i] = int *

    return 0;
}