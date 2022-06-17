#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 8;

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

void counter(int M[N][N], const int N, int *p, int *n)
{
    for (int i = 0; i < N; ++i) {
        for (int j = N - 1 - i; j < N; ++j) {
            if (M[i][j] > 0) {
                *p += 1;
            }
            else if (M[i][j] < 0) {
                *n += 1;
            }
        }
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

    int positive = 0, negative = 0;

    counter(M, N, &positive, &negative);

    printf("Positive = %d, negative = %d\n", positive, negative);

    return 0;
}
