#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void print_seq(int *mas, const int N)
{
    for (int i = 0; i < N; ++i) {
        printf("%d ", mas[i]);
    }
    printf("\n");
}

void generate_seq(int *mas, int *N)
{
    *N = rand() % 25 + 1;
    printf("N = %d\n", *N);
    for (int i = 0; i < *N; ++i) {
        int x = rand() % 2;
        if (x == 0) {
            x = -1;
        }
        mas[i] = (-1 * x) * rand() % 100;
        printf("%d ", mas[i]);
    }
    printf("\n");
    return;
}

int *find_positive(int *mas, const int N, int *len)
{
    for (int i = N - 1; i >= 0; --i) {
        if (mas[i] > 0) {
            *len = N - i;
            return &mas[i];
            // return (mas + i)
        }
    }
    *len = N;
    return mas;
}

int count_negative(int *mas, const int N)
{
    int ans = 0;  // счётчик
    for (int i = 0; i < N; ++i) {
        if (mas[i] < 0) {
            ++ans;
        }
    }
    return ans;
}

int main()
{
    srand((unsigned int)time(NULL));

    int N1, N2;
    int A[25], B[25];

    generate_seq(A, &N1);
    generate_seq(B, &N2);

    int len1, len2;

    int *ptr1 = find_positive(A, N1, &len1);
    int *ptr2 = find_positive(B, N2, &len2);

    printf("\n");
    print_seq(ptr1, len1);
    printf("\n");
    print_seq(ptr2, len2);
    printf("\n");

    printf("Negative in A = %d | B = %d\n", count_negative(A, N1), count_negative(B, N2));
    printf("Negative in part A = %d | B = %d\n", count_negative(ptr1, len1), count_negative(ptr2, len2));

    return 0;
}
