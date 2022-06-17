#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 8;

int sum_column(int M[N][N], int N, int column_idx)
{
    int ans = 0;
    for (int i = column_idx; i < N; ++i) {
        ans += M[i][column_idx];
    }

    return ans;
}

void generate(int matrix[N][N], int N, int M)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int tmp = -1 * (rand() % 2);
            matrix[i][j] = (tmp != 0) ? tmp * (rand() % 30) : rand() % 30;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    int M[N][N];

    generate(M, N, N);
    // for (int i = 0; i < N; ++i) {
    //     for (int j = 0; j < N; ++j) {
    //         scanf("%d", &M[i][j]);
    //     }
    // }

    for (int i = 0; i < N; ++i) {
        printf("%d\n", sum_column(M, N, i));
    }
    // M = int **
    // M[i] = int *

    return 0;
}
