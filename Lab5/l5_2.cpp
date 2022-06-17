#include <cstdio>
#include <cstdlib>

float **makeMatrix(float **matrix, int N, int M)  // создает пустую матрицу
{
    matrix = (float **)malloc(N * sizeof(float *));
    for (int i = 0; i < N; ++i) {
        matrix[i] = (float *)malloc(M * sizeof(float));
    }
    return matrix;
}

void clearMatrix(float **matrix, int N)
{
    for (int i = 0; i < N; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void inputMatrix(float **matrix, int N, int M)
{
    printf("Введите %d элементов на %d строках\n", M, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%f", &matrix[i][j]);
        }
    }
}

void printMatrix(float **matrix, int N, int M)
{
    printf("Введите %d элементов на %d строках", M, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%f", matrix[i][j]);
        }
        printf("\n");
    }
}

float **solve(float **matrix, int N, int M, int *len)
{
    float **res = NULL;
    for (int i = 0; i < N; ++i) {
        if (i < N / 2) {
            for (int j = M / 2; j < M; ++j) {
                if (matrix[i][j] < 0) {
                    res = (float **)realloc(res, (*len + 1) * sizeof(float *));
                    res[*len] = &matrix[i][j];
                    *len = *len + 1;
                }
            }
        }
        else {
            for (int j = 0; j < M / 2; ++j) {
                if (matrix[i][j] < 0) {
                    res = (float **)realloc(res, (*len + 1) * sizeof(float *));
                    res[*len] = &matrix[i][j];
                    *len = *len + 1;
                }
            }
        }
    }
    return res;
}

int main()
{
    float **matrix = NULL;

    int n, m;
    printf("Введите N и M через пробел: ");
    scanf("%d %d", &n, &m);

    matrix = makeMatrix(matrix, n, m);
    inputMatrix(matrix, n, m);

    int len = 0;
    float **res = solve(matrix, n, m, &len);

    for (int i = 0; i < len && res; ++i) {
        printf("%p %f\n", res[i], *res[i]);
    }

    if (res) {
        free(res);
    }

    clearMatrix(matrix, n);

    return 0;
}