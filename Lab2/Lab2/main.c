#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

const int N = 5;


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
    //     // X[i] <=> *(x + i), * - �������� �������������
    // }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = N - 1 - i; j < N; ++j) {
            if (M[i][j] % 2 == 0 && M[i][j] > 0) {
                ans++;
            }
            // printf("%d ", M[i][j]);
        }
        // printf("\n");
    }

    printf("%d\n", ans);

    const int N2 = N / 2;
    int M2[N2];

    for (int i = 0; i < N2; ++i) {
        M2[i] = INT_MIN;
    }

    for (int i = 1; i < N; i += 2) {
        for (int j = 0; j < N; ++j) {
            if (M2[i / 2] < M[i][j]) {
                M2[i / 2] = M[i][j];
            }
        }
    }
    for (int i = 0; i < N2; ++i) {
        printf("%d ", M2[i]);
    }
    printf("\n");

    return 0;
}
