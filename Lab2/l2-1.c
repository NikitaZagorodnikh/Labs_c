#include <stdio.h>


int main()
{
    const int N = 4;
    int M[N][N];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &M[i][j]);
        }
        // X[i] <=> *(x + i), * - оператор разыменования
    }

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

    return 0;
}