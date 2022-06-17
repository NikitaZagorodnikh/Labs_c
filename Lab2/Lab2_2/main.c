#include <stdio.h>
#include <stdlib.h>

int ubuvanie(const void *l, const void *r)  // вернуть 1, если нужно поменять
{
    int x = *((int *)l);
    int y = *((int *)r);
    return x < y;
}


int main()
{
    const int N = 8;
    int M[N];

    for (int i = 0; i < N; ++i) {
        scanf("%d", M + i);
    }

    int mn = M[0], mn_idx = 0;
    int mx = M[0], mx_idx = 0;
    for (int i = 1; i < N; ++i) {
        if (mn > M[i]) {
            mn = M[i];
            mn_idx = i;
        }
        if (mx < M[i]) {
            mx = M[i];
            mx_idx = i;
        }
        // TODO что делать с повторяющимися?
    }

    int l, r;
    if (mn_idx < mx_idx) {
        l = mn_idx;
        r = mx_idx;
    }
    else {
        l = mx_idx;
        r = mn_idx;
    }

    printf("%d %d\n", l, r);

    qsort(M + l, r - l + 1, sizeof(int), ubuvanie);

    // for (int i = l; i <= r; ++i) {
    //     for (int j = l; j <= r - 1; ++j) {
    //         if (M[j] < M[j + 1]) {
    //             int tmp = M[j];
    //             M[j] = M[j + 1];
    //             M[j + 1] = tmp;
    //         }
    //     }
    // }


    for (int i = 0; i < N; ++i) {
        printf("%d ", M[i]);
    }
    printf("\n");

    return 0;
}
