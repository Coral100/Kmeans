#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int  d, n;

double **readInput();
double calcDis(double *v1, double *v2);
void addVectors(double *v1, double *v2);
void calcCentroids(double *vector, double m);
double **kmeans(int k, int MAXITER);

void print(int k, double **centroids);

int main(int argc, char *argv[]) {
    double **res;
    int MAXITER;
    int i;
    int k = atoi(argv[1]);
    if (argc == 2) {
        MAXITER = 200;
    } else {
        MAXITER = atoi(argv[2]);
    }

    res = kmeans(k, MAXITER);

    if (k >= n || MAXITER < 1) {
        printf("invalid inputs");
        exit(-1);
    }

    print(k, res);

    for (i = 0; i<k; i++) {
        free(res[i]);
    }
    free(res);
    return 0;
}
double **readInput() {
    double coordinate;
    char c;
    int i, j;
    double **vectors;
    double *vec;

    while (scanf("%lf%c", &coordinate, &c) == 2) {
        d++;
        if (c == '\n') {
            n++;
        }
    }
    rewind(stdin);

    d /= n;

    vec = (double *)calloc(d, sizeof(double));
    vectors = (double **)calloc(n, sizeof(double *));

    i = 0 ;
    j = 0;

    while (scanf("%lf%c", &coordinate, &c) == 2) {
        vec[i] = coordinate;
        if (c != '\n') {
            i += 1;
        }
        else {
            vectors[j] = vec;
            j += 1;
            vec = (double *) calloc(d, sizeof(double));
            assert(vec != NULL);
            i = 0;
        }
    }

    free(vec);
    return vectors;
}

double sqr(double x) {
    return x * x;
}

double calcDis(double *v1, double *v2) {
    double res = 0;
    int i;
    for (i = 0; i < d; i++) {
        res += sqr(v1[i] - v2[i]);
    }
    return res;
}

void addVectors(double *v1, double *v2) {
    int i;
    for (i = 0; i < d; i++) {
        v1[i] += v2[i];
    }
}

void calcCentroids(double *vector, double m) {
    int i;
    for (i = 0; i < d; i++) {
        vector[i] = vector[i] / m;
    }
}

double **kmeans(int k, int MAXITER) {
    int iters = 0 ;
    int i, j,t, s, a, b, c, r, g, l, h, e, cnt;
    int cng = 0;
    double **vectors = readInput();
    double **centroids;
    double **new_centroids;
    int *groups;
    double curr_dis, new_dis = 0;
    int index;
    double *sum;
    groups = (int *) calloc(n, sizeof(int));
    assert(groups != NULL);


    centroids = (double **) malloc(k * sizeof(double *));
    assert(centroids != NULL);
    for (i = 0; i < k; i++) {
        centroids[i] = (double *) calloc(d, sizeof(double));
    }
    for (t = 0; t < k; t++) {
        for (j = 0; j < d; j++) {
            centroids[t][j] = vectors[t][j];
        }
    }


    while (iters < MAXITER && cng == 0) {
        iters++;
        for (s = 0; s < n; s++) {
            index = 0;
            curr_dis = calcDis(vectors[s], centroids[0]);
            for (a = 1; a < k; a++) {
                new_dis = calcDis(vectors[s], centroids[a]);
                if (new_dis < curr_dis) {
                    curr_dis = new_dis;
                    index = a;
                }
            }
            groups[s] = index;
        }

        new_centroids = (double **) malloc(k * sizeof(double *));
        assert(new_centroids != NULL);

        for (b = 0; b < k; b++) {
            new_centroids[b] = (double *) calloc(d, sizeof(double));
        }

        for (c = 0; c < k; c++) {
            sum = (double *) calloc(d , sizeof(double));
            assert(sum != NULL);
            cnt = 0;
            for (r = 0; r < n; r++) {
                if (groups[r] == c) {
                    addVectors(sum, vectors[r]);
                    cnt++;
                }
            }
            calcCentroids(sum, cnt);
            new_centroids[c] = sum;
        }

        cng = 1;
        for (g = 0; g < k; g++) {
            for (l = 0; l < d; l++) {
                if (centroids[g][l] != new_centroids[g][l]) {
                    cng = 0;
                }
                centroids[g][l] = new_centroids[g][l];
            }
        }
    }

    free(groups);
    for (h=0; h<n; h++) {
        free(vectors[h]);
    }
    free(vectors);
    for (e=0; e<k; e++) {
        free(new_centroids[e]);
    }
    free(new_centroids);
    return centroids;
}

void print(int k, double **centroids) {
    int i, j;
    for (i = 0; i < k; i++) {
        for (j = 0; j < d; j++) {
            printf("%.4f", centroids[i][j]);
            if (j < d - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
}