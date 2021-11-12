#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int N;
double a, b, c;

typedef struct
{
    int len, i;
    double dt;
    double *x, *y, *z;

} Trajectory;

typedef struct
{
    double x, y, z;

} Vector;

Trajectory *initTrajectory(double dt)
{
    Trajectory *res = (Trajectory *)malloc(sizeof(Trajectory));

    res->len = N;
    res->i = 0;
    res->x = (double *)calloc(N, sizeof(double));
    res->y = (double *)calloc(N, sizeof(double));
    res->z = (double *)calloc(N, sizeof(double));
    res->dt = dt;

    return res;
}

void saveTrajectory(Trajectory *t, Vector v)
{
    int pos = t->i;
    t->x[pos] = v.x;
    t->y[pos] = v.y;
    t->z[pos] = v.z;

    t->i++;
}

void printTrajectory(Trajectory t)
{
    fprintf(stdout, "\n#Trajectory\n#T\t,x\t,y\t,z\n");
    for (int i = 0; i < t.len; i++)
    {
        fprintf(stdout, "%.10lf,%.10lf,%.10lf,%.10lf\n", t.dt * i, t.x[i], t.y[i], t.z[i]);
    }
}

Vector *initVector(x0, y0, z0)
{
    Vector *v = (Vector *)malloc(sizeof(Vector));

    v->x = x0;
    v->y = y0;
    v->z = z0;

    return v;
}

Vector sum(Vector a, Vector b)
{
    Vector res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;

    return res;
}

Vector dt_step(Vector v, double dt)
{
    Vector res;
    res.x = (-v.y - v.z) * dt;
    res.y = (v.x + a * v.y) * dt;
    res.z = (b + v.z * (v.x - c)) * dt;

    return res;
}

Trajectory *RK2(Vector v, double T, double dt)
{

    Vector k1, k2;
    Trajectory *tj = initTrajectory(dt);

    for (int i = 0; i < tj->len; i++)
    {
        saveTrajectory(tj, v);

        k1 = dt_step(v, dt * 0.5);
        k2 = dt_step(sum(v, k1), dt);
        v = sum(v, k2);
    }

    saveTrajectory(tj, v);

    return tj;
}

/* 
    tj = traiettoria
    axis = asse da analizzare
    t_error = errore relativo massimo (serve per calcolare il transiente)

    return: [ t1_medio, t2_medio, transiente ]
*/
int *analyzePeriod(Trajectory tj, char axis, double t_error)
{
    int counter = 0;                                                // numero di mezzi periodi
    double *traj;                                                   // salvo la traiettoria in base all'asse scelto in input (axis)
    double *inversion_t = (double *)calloc(tj.len, sizeof(double)); // array di tempi nei quali avviene il cambio di segno

    switch (axis)
    {
    case 'x':
        traj = tj.x;
        break;
    case 'y':
        traj = tj.y;
        break;
    case 'z':
        traj = tj.z;
        break;

    default:
        fprintf(stderr, "ERROR: Asse non valido");
        return NULL;
        break;
    }

    // scorro l'array della traiettoria e mi salvo il tempo nel quale avviene il cambio di segno
    for (int i = 1; i < tj.len; i++)
    {
        if (traj[i] * traj[i - 1] <= 0)
            inversion_t[counter++] = tj.dt * (2 * i - 1) / 2; // mi salvo il tempo = (t2 - t1) / 2
    }

    if (counter % 2 != 0)
        counter--;

    // Tempo medio ( include il transiente )
    double t1_mean = 2 * (inversion_t[counter - 1] - inversion_t[0]) / counter;

    // Calcolo Transiente basanto sul Tempo medio precedente
    int i = 3;
    int end = 0;
    double current_t;

    while (i < counter && !end)
    {
        current_t = (inversion_t[i] - inversion_t[i - 2]);

        if (fabs(current_t - t1_mean) / t1_mean <= t_error) // se errore relativo minore del errore limite
            end = !end;
        else
            i++;
    }

    //tempo transiente
    double t_transient = inversion_t[i - 2];

    // Ricalcolo tempo medio partendo dalla parte stazionaria
    double t2_mean = 2 * (inversion_t[counter - 1] - inversion_t[i - 2]) / (counter - i + 2);

    fprintf(stderr, "Period on axis: %c \n T1: %.10lf \t Ttran: %.10lf \t T2: %.10lf \n", axis, t1_mean, t_transient, t2_mean);

    int *res = (int *)calloc(3, sizeof(int));
    res[0] = t1_mean;
    res[1] = t2_mean;
    res[2] = t_transient;

    return res;
}

void analyzeByC(Vector v, double T, double dt, int c1, int c2)
{
    int len = abs(c2 - c1);

    FILE *fptr;
    Trajectory *tj[len];

    fptr = fopen("analyze_by_c.out", "wo");
    fprintf(fptr, "\n#Trajectory by c without transient time\n#T\t,x\t,y\t,z\n");

    for (int i = 0; i < len; i++)
    {
        c = c1 + i;
        tj[i] = RK2(v, T, dt);
        // int *res = analyzePeriod(*tj[i], 'x', 0.01);

        for (int x = 150 / dt; x < tj[i]->len; x++)
        {
            fprintf(fptr, "%.10lf,%.10lf,%.10lf,%.10lf\n", tj[i]->dt * x, tj[i]->x[x], tj[i]->y[x], tj[i]->z[x]);
        }

        fprintf(fptr, "\n\n");
    }

    fclose(fptr);
}

int main(int argc, char const *argv[])
{
    if (argc != 8 + 1)
    {
        fprintf(stderr, "usage: %s | a,b,c | x0,y0,z0 | dt | T \n", argv[0]);
        return EXIT_FAILURE;
    }

    a = atof(argv[1]);
    b = atof(argv[2]);
    c = atof(argv[3]);

    Vector *o = initVector(atof(argv[4]), atof(argv[5]), atof(argv[6]));

    double dt = atof(argv[7]);
    double T = atof(argv[8]);

    N = (int)(T / dt + 0.5) + 1;

    Trajectory *tj = RK2(*o, T, dt);

    printTrajectory(*tj);

    analyzePeriod(*tj, 'x', 0.01);
    analyzePeriod(*tj, 'y', 0.01);
    analyzePeriod(*tj, 'z', 0.01);

    // usare per studiare regime staizonario
    //analyzeByC(*o, T, dt, 2, 11);

    return 0;
}
