#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, r, i, j, f, fl, k = -1, *re, **p, **mx, **ne, *s, *jk;
    printf("(19BIT0292)Enter the number of processes: ");
    scanf("%d", &n);
    p = (int **)malloc(sizeof(int *) * n);
    mx = (int **)malloc(sizeof(int *) * n);
    ne = (int **)malloc(sizeof(int *) * n);
    jk = (int *)malloc(sizeof(int) * n);
    printf("(19BIT0292)Number of types of resources: ");
    scanf("%d", &r);
    re = (int *)malloc(sizeof(int) * r);
    s = (int *)calloc(r, sizeof(int));
    printf("\n(19BIT0292)Enter the process allocation matrix\n");
    for (i = 0; i < n; i++)
    {
        p[i] = (int *)malloc(sizeof(int) * r);
        printf("\nP%d: ", i + 1);
        for (j = 0; j < r; j++)
            scanf("%d", &p[i][j]);
    }
    printf("\n(19BIT0292)Enter the process maximum matrix\n");
    for (i = 0; i < n; i++)
    {
        mx[i] = (int *)malloc(sizeof(int) * r);
        ne[i] = (int *)malloc(sizeof(int) * r);
        printf("\nP%d: ", i + 1);
        for (j = 0; j < r; j++)
        {
            scanf("%d", &mx[i][j]);
            ne[i][j] = mx[i][j] - p[i][j];
        }
    }
    printf("\n(19BIT0292)Need Matrix\n");
    for (i = 0; i < n; i++)
    {
        printf("\nP%d: ", i + 1);
        for (j = 0; j < r; j++)
        {
            printf("%d ", ne[i][j]);
            s[j] += ne[i][j];
        }
    }
    printf("\n(19BIT0292)Total number of resources used uptil now(in sequece): ");
    for (i = 0; i < r; i++)
    {
        printf("%d ", s[i]);
    }

    for (i = 0; i < r; i++)
    {
        printf("\n(19BIT0292)Enter the remaing instance of resouces number %d: ", i + 1);
        scanf("%d", re + i);
    }
    printf("(19BIT0292)Sequence: \n");
    while (1)
    {
        fl = 0;
        for (i = 0; i < n; i++)
        {
            if (p[i] == NULL)
                continue;
            else
            {
                f = 0;
                for (j = 0; j < r; j++)
                    if (ne[i][j] > re[j])
                    {
                        f = 1;
                        break;
                    }
                if (f == 0)
                {
                    printf("P%d(", i + 1);
                    for (j = 0; j < r - 1; j++)
                    {
                        re[j] += p[i][j];
                        printf("%d,", re[j]);
                    }
                    re[r - 1] += p[i][r - 1];
                    printf("%d)\n", re[r - 1]);
                    p[i] = NULL;
                    fl = 1;
                    jk[++k] = i + 1;
                    continue;
                }
            }
        }
        if (fl == 0)
            break;
    }
    if (k == -1)
        printf("\n\n(19BIT0292)Unsafe State");
    else
    {
        printf("\n(19BIT0292)Safe State sequence <P%d", jk[0]);
        for (i = 1; i < k + 1; i++)
            printf(",P%d", jk[i]);
        printf(">");
    }
}