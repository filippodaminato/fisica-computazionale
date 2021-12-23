#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef long long int Long;

typedef struct
{
    int len;
    Long *x;

} Trajectory;

Trajectory *initTrajectory(int len)
{
    Trajectory *res = (Trajectory *)malloc(sizeof(Trajectory));

    res->len = len;
    res->x = (Long *)calloc(len, sizeof(Long));

    return res;
}

void saveTrajectory(Trajectory tj, char *file_name, char *file_mode)
{
    FILE *fl;
    fl = fopen(file_name, file_mode);
    fprintf(fl, "#t \t x\n");
    for (int i = 0; i < tj.len; i++)
    {
        fprintf(fl, "%d \t %lld\n", (i + 1), tj.x[i]);
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

    fprintf(stderr, "Seed: %d \n", seed);
    srand48(seed);
}

void easy_RW(int tmax)
{
    Trajectory *tj = initTrajectory(tmax);
    Long pos = 0;

    for (int i = 0; i < tj->len; i++)
    {
        pos += (drand48() < 0.5) ? 1 : -1;
        tj->x[i] = pos;
    }

    saveTrajectory(*tj, "tj.out", "a");

    free(tj);
}

void RW(int tmax, int n_tj, int b)
{
    Trajectory *tjs[3];

    for (int i = 0; i < 3; i++)
    {
        tjs[i] = initTrajectory(tmax);
    }

    int len = 0;
    int m = b;

    while (m < tmax)
    {
        m *= b;
        len++;
    }

    m = b;

    // initi matrix for histo
    int **histo = (int **)calloc(len, sizeof(int *));
    for (int i = 0; i < len; i++)
    {
        histo[i] = (int *)calloc(2 * m + 1, sizeof(int));
        m *= b;
    }

    // RW + histo
    Long pos = 0;
    for (int z = 1; z < n_tj + 1; z++)
    {
        m = b;
        int f = 0;
        for (int i = 1; i < tmax; i++)
        {
            pos += (drand48() < 0.5) ? 1 : -1;

            // fprintf(stderr, "asd ok %d %d %lld \n", z, i, pos);

            tjs[0]->x[i] += pos;
            tjs[1]->x[i] += pos * pos;
            tjs[2]->x[i] += pos * pos * pos * pos;

            if (m == i)
            {
                histo[f][i + pos] += 1;
                m *= b;
                f++;
            }
        }
    }

    double div = 1. / n_tj;

    FILE *fl;
    fl = fopen("m_vs_t.out", "w");
    fprintf(fl, "#t \t x \t sx \t x^2 \t sx^2\n");

    for (int k = 0; k < tmax; k++)
    {
        double m1 = tjs[0]->x[k] * div;
        double sm1 = sqrt(1. / (n_tj - 1) * div * (tjs[1]->x[k] - div * tjs[0]->x[k] * tjs[0]->x[k]));
        double m2 = tjs[1]->x[k] * div;
        double sm2 = sqrt(1. / (n_tj - 1) * div * (tjs[2]->x[k] - div * tjs[1]->x[k] * tjs[1]->x[k]));

        fprintf(fl, "%d \t %.10lf \t %.10lf \t %.10lf \t %.10lf \n", k, m1, sm1, m2, sm2);
    }

    fclose(fl);

    fl = fopen("histo.out", "w");
    m = b;

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 2 * m + 1; j++)
        {
            fprintf(fl, " %3d\t %d \n", j - m, histo[i][j]);
        }

        m *= b;
        fprintf(fl, "\n\n");
    }

    fclose(fl);
}

int main(int argc, char const *argv[])
{

    if (argc != 4)
    {
        fprintf(stderr, "usage : %s | t_max | n_trajectory | b \n", argv[0]);
        exit(1);
    }

    initRand();

    int tmax = atof(argv[1]);
    int n_tj = atof(argv[2]);
    int b = atoi(argv[3]);

    fprintf(stderr, "Config:\n\tTmax: %d, N_traj: %d, B: %d\n", tmax, n_tj, b);

    // for (int i = 0; i < 10; i++)
    // {
    //     easy_RW(tmax);
    // }

    RW(tmax, n_tj, b);

    return 0;
}
