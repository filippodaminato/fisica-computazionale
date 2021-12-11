#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int counter = 0;
int current_label = 1;

#define empty -1
#define unset 0

typedef unsigned long long int big;
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

Node **voidGird(int L)
{
    // creating the grid structure
    Node **res = (Node **)malloc(L * sizeof(Node *));

    for (int i = 0; i < L; i++)
    {
        res[i] = (Node *)malloc(L * sizeof(Node));
        for (int z = 0; z < L; z++)
            res[i][z].value = unset;
    }

    return res;
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

int numberOfCluster(Node **grid, int L)
{
    int count = 0;
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

    // Rinomino tutti i father in modo tale che non ci siano buchi nella numerazione (tipo: 1,3,7 => 1,2,3)
    int cnt = 1;
    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            if (grid[y][x].parent == &grid[y][x])
                grid[y][x].value = cnt++;
        }
    }
}

int percolating(Node **grid, int L)
{
    for (int i = 0; i < L; i++)
    {
        if (value(&grid[0][i]) != unset)
        {
            for (int z = 0; z < L; z++)
            {
                int val = value(&grid[0][i]);
                if (val == value(&grid[L - 1][z]))
                    return val;
            }
        }
    }

    return 0;
}

big *analyzeGrid(Node **grid, int L)
{
    big *res = (big *)malloc(5 * sizeof(big));
    int n_clst = numberOfCluster(grid, L);

    int *clst_sizes = (int *)malloc(sizeof(int) * n_clst);

    int holes_count = 0;
    int s_tot = 0;

    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            int val = value(&grid[x][y]);
            if (val > unset)
                clst_sizes[val - 1]++;

            if (val == unset)
                holes_count++;
        }
    }

    for (int i = 0; i < n_clst; i++)
        s_tot += clst_sizes[i] * clst_sizes[i];

    int percol = percolating(grid, L);
    int s_percol = 0;

    if (percol != unset)
        s_percol = clst_sizes[percol - 1];

    res[0] = (big)holes_count;
    res[1] = (big)(percol != unset) ? 1 : 0;
    res[2] = (big)s_percol;
    res[3] = (big)s_tot;
    res[4] = (big)n_clst;

    // fprintf(stderr, "Holes\tPercol\tSPercol\tStot\tNcltr\n");
    // fprintf(stderr, "%d\t%d\t%d\t%d\t%d\t\n\n", res[0], res[1], res[2], res[3], res[4]);
    free(clst_sizes);

    return res;
}

void **initDynamicGrid(int L, double pi, double pf, double dp, int samples)
{
    int len, x, y, i;

    int run = (int)(((pf - pi) / dp) + 0.5) + 1;

    fprintf(stderr, "Run: %d\n", run);
    big **res = (big **)malloc(run * sizeof(big *));

    for (int i = 0; i < run; i++)
        res[i] = (big *)malloc(5 * sizeof(big));

    for (int s = 0; s < samples; s++)
    {

        Node **grd = voidGird(L);      // creating void grid structure
        len = (int)(L * L * pi + 0.5); //quantità di buchi da fare

        // per ogni probabilità
        for (int v = 0; v < run; v++)
        {
            i = 0;

            // cerco delle posizioni random, se queste sono "unset" ci faccio un buco "empty"
            while (i < len)
            {
                x = (rand() % (L));
                y = (rand() % (L));

                if (grd[y][x].value == unset)
                {
                    grd[y][x].value = empty;
                    grd[y][x].parent = &grd[y][x];
                    i++;
                }
            }

            len = (int)(L * L * dp + 0.5);

            setLabel(grd, L);

            big *datas = analyzeGrid(grd, L);
            res[v][0] += datas[0];
            res[v][1] += datas[1];
            res[v][2] += datas[2];
            res[v][3] += datas[3];
            res[v][4] += datas[4];
        }
    }

    fprintf(stderr, "L\tP\t\tHoles\tPercol\tSPercol\tStot\tNcltr\n");
    for (int i = 0; i < run; i++)
        fprintf(stderr, "%d\t%f\t%lld\t%lld\t%lld\t%lld\t%lld\t\n\n", L, pi + (dp * i), res[i][0], res[i][1], res[i][2], res[i][3], res[i][4]);

    return 0;
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

    initDynamicGrid(L, p_start, p_end, dp, sample);

    printf("Tot. Labeling iterations %d \n", counter);

    return 0;
}
