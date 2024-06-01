#include <stdio.h>
#include <stdlib.h>
static int mark[20];
int i, j, np, nr;

int main()
{
    int **alloc, **request, *avail, *r, *f;

    np = 5; // Number of processes
    nr = 3; // Number of resources

    // Memory allocation for matrices and arrays
    alloc = (int **)malloc(np * sizeof(int *));
    request = (int **)malloc(np * sizeof(int *));
    avail = (int *)malloc(nr * sizeof(int));
    r = (int *)malloc(nr * sizeof(int));
    f = (int *)malloc(np * sizeof(int));

    // Initialize the finish array
    for(i = 0; i < np; i++)
        f[i] = 0;

    // Hardcoded total resources
    int total_resources[3] = {10, 5, 7};
    for (i = 0; i < nr; i++)
    {
        r[i] = total_resources[i];
    }

    // Hardcoded request matrix
    int request_matrix[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    for (i = 0; i < np; i++)
    {
        request[i] = (int *)malloc(nr * sizeof(int));
        for (j = 0; j < nr; j++)
        {
            request[i][j] = request_matrix[i][j];
        }
    }

    // Hardcoded allocation matrix
    int allocation_matrix[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    for (i = 0; i < np; i++)
    {
        alloc[i] = (int *)malloc(nr * sizeof(int));
        for (j = 0; j < nr; j++)
        {
            alloc[i][j] = allocation_matrix[i][j];
        }
    }

    // Available Resource calculation
    for (j = 0; j < nr; j++)
    {
        avail[j] = r[j];
        for (i = 0; i < np; i++)
        {
            avail[j] -= alloc[i][j];
        }
    }

    // Display available resources
    for (i = 0; i < nr; i++)
    {
        printf("Resc %d :: %d\n", i, avail[i]);
    }

    while (1)
    {
        int deadlock = 1;
        for (i = 0; i < np; i++)
        {
            int canBeProc = 1;
            for (j = 0; j < nr; j++)
            {
                if (request[i][j] > avail[j])
                {
                    canBeProc = 0;
                }
            }
            if (canBeProc && f[i] == 0)
            {
                deadlock = 0;
                f[i] = 1;
                for (j = 0; j < nr; j++)
                {
                    avail[j] += alloc[i][j];
                }
            }
        }
        if (deadlock)
        {
            printf("\nDeadlock detected\n");
            break;
        }
        int completed = 1;
        for (i = 0; i < np; i++)
        {
            if (f[i] == 0)
            {
                completed = 0;
            }
        }
        if (completed)
        {
            printf("\nDeadlock not detected\n");
            break;
        }
    }

    // Free allocated memory
    for (i = 0; i < np; i++)
    {
        free(alloc[i]);
        free(request[i]);
    }
    free(alloc);
    free(request);
    free(avail);
    free(r);
    free(f);

    return 0;
}
