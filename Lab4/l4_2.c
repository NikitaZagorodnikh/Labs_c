#include <cstdio>

const int N = 4;

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
    int M[N][N];

    int positive = 0, negative = 0;

    counter(M, N, &positive, &negative);

    return 0;
}