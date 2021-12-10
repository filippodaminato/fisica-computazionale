#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int counter = 0;
int current_label = 1;

#define empty -1
#define unset 0

typedef struct Node Node;

struct Node
{
    int value;
    Node *child;
    Node *parent;
};

Node *getFather(Node *nd)
{
    if (nd->parent == nd)
        return nd;
    else
        return getFather(nd->parent);
}

int value(Node *nd)
{
    int res = unset;
    if (nd->value != unset)
    {
        Node *father = getFather(nd);
        res = father->value;
    }
    return res;
}

void printGrid(Node **grid, int L)
{
    int res = 0;
    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            if (grid[y][x].value != unset)
            {
                Node *father = getFather(&grid[y][x]);
                res = father->value;
            }
            else
                res = unset;

            fprintf(stdout, "%d\t", res);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

void saveGrid(Node **grid, int L, char *file_name, char *file_mode)
{

    FILE *fl;
    fl = fopen(file_name, file_mode);

    int res = 0;
    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            res = grid[y][x].value;
            counter += grid[y][x].value;
            fprintf(fl, "%d ", res);
        }
        fprintf(fl, "\n");
    }

    fprintf(fl, "\n");
    fclose(fl);
}

void initRand()
{
    FILE *fl;
    fl = fopen("/dev/random", "r");
    int seed;
    fread(&seed, 4, 1, fl);
    fclose(fl);

    fprintf(stdout, "Seed: %d \n", seed);
    srand48(seed);
}

Node **initGrid(int L, double p)
{

    // creating the grid structure
    Node **res = (Node **)malloc(L * sizeof(Node *));

    for (int i = 0; i < L; i++)
    {
        res[i] = (Node *)malloc(L * sizeof(Node));
        for (int z = 0; z < L; z++)
            res[i][z].value = unset;
    }

    // filling the grid with "len" holes

    int len, x, y, i;

    len = (int)(L * L * p + 0.5);
    i = 0;

    while (i < len)
    {
        x = (rand() % L);
        y = (rand() % L);

        if (res[y][x].value == unset)
        {
            res[y][x].value = empty;
            res[y][x].parent = &res[y][x];
            i++;
        }
    }

    return res;
}

void **initDynamicGrid(int L, double pi, double pf, double dp)
{
    // creating the grid structure
    Node **res = (Node **)malloc(L * sizeof(Node *));

    for (int i = 0; i < L; i++)
    {
        res[i] = (Node *)malloc(L * sizeof(Node));
        for (int z = 0; z < L; z++)
            res[i][z].value = unset;
    }

    // filling the grid with "len" holes

    int len, len_pre, x, y, i;
    len_pre = 0;

    len = (int)(L * L * pi + 0.5);

    fprintf(stdout, "to: %d\n", (int)(((pf - pi) / dp) + 0.5));

    for (int v = 0; v <= (int)(((pf - pi) / dp) + 0.5); v++)
    {
        i = 0;

        fprintf(stdout, "len = %d , p = %f\n", len, pi + dp * v);

        while (i < len)
        {
            x = (rand() % (L));
            y = (rand() % (L));

            if (res[y][x].value == unset)
            {
                res[y][x].value = empty;
                res[y][x].parent = NULL;
                i++;
            }
        }

        len = (int)(L * L * dp + 0.5);

        printGrid(res, L);

        // saveGrid(res, L, "saving.txt", "a");
    }

    return 0;
}

void setLabel(Node **grid, int L)
{
    int changed = 1;
    int label_count = 1;

    if (grid[0][0].value != unset)
    {
        grid[0][0].value = label_count++;
        grid[0][0].parent = &grid[0][0];
    }

    while (changed)
    {
        changed = 0;
        for (int y = 0; y < L; y++)
        {
            for (int x = 0; x < L; x++)
            {
                counter++;

                if (value(&grid[y][x]) != unset)
                {

                    if (y > 0 && value(&grid[y - 1][x]) > unset && value(&grid[y - 1][x]) != value(&grid[y][x]))
                    {
                        if (value(&grid[y - 1][x]) < value(&grid[y][x]) || value(&grid[y][x]) == empty)
                        {
                            grid[y][x].parent = &grid[y - 1][x];
                            grid[y - 1][x].child = &grid[y][x];
                        }
                        else
                        {
                            grid[y - 1][x].parent = &grid[y][x];
                            grid[y][x].child = &grid[y - 1][x];
                        }

                        changed = 1;
                    }
                    else if (x > 0 && value(&grid[y][x - 1]) > unset && value(&grid[y][x - 1]) != value(&grid[y][x]))
                    {
                        if (value(&grid[y][x - 1]) < value(&grid[y][x]) || value(&grid[y][x]) == empty)
                        {
                            grid[y][x].parent = &grid[y][x - 1];
                            grid[y][x - 1].child = &grid[y][x];
                        }
                        else
                        {
                            grid[y][x - 1].parent = &grid[y][x];
                            grid[y][x].child = &grid[y][x - 1];
                        }

                        changed = 1;
                    }
                    else if (value(&grid[y][x]) == empty)
                    {
                        grid[y][x].value = label_count++;
                        grid[y][x].parent = &grid[y][x];
                    }
                }
            }
        }
    }
}

int numberOfCluster(Node **grid, int L)
{
    int count = 1;
    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            if (grid[y][x].parent == &grid[y][x])
                count++;
        }
    }

    return count;
}

int meansize(Node **grid, int L, int n_fath)
{
}

void analyzeGrid(Node **grid, int L)
{

    int n_clst = numberOfCluster(grid, L);
    int sizes[n_clst];

    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            int val = value(&grid[x][y]);
            if (val > empty)
                sizes[val - 1]++;
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 6)
    {
        fprintf(stdout, "Usage: %s | L | p_start | p_end | dp | #sample \n", argv[0]);
        exit(1);
    }

    initRand();

    int L = atoi(argv[1]);
    double p_start = atof(argv[2]);
    double p_end = atof(argv[3]);
    double dp = atof(argv[4]);
    int sample = atoi(argv[5]);

    fprintf(stdout, "Config:  L = %d | pi = %f | pf = %f | dp = %f | #sample = %d \n", L, p_start, p_end, dp, sample);

    double p = p_start;

    Node **grid = initGrid(L, p);
    printGrid(grid, L);

    setLabel(grid, L);

    printGrid(grid, L);

    fprintf(stderr, "N cluster: %d\n", numberOfCluster(grid, L));
    // initDynamicGrid(L, p_start, p_end, dp);

    printf("%d \n", counter);

    return 0;
}

// L^2 * p = N