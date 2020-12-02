#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mpi.h"

int main(int argc, char* argv[]);
int congruence(int a, int b, int c, int* error);
int i4_gcd(int i, int j);
int i4_max(int i1, int i2);
int i4_min(int i1, int i2);
int i4_sign(int i);
void lcrg_anbn(int a, int b, int c, int n, int* an, int* bn);
int lcrg_evaluate(int a, int b, int c, int x);
int power_mod(int a, int n, int m);

/******************************************************************************/
int main(int argc, char* argv[]) {
    int a;
    int an;
    int b;
    int bn;
    int c;
    int error;
    int id;
    int j;
    int k;
    int k_hi;
    int p;
    int u;
    int v;

    double t1, t2;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    a = 16807;
    b = 0;
    c = 2147483647;

    k_hi = 10000;

    if (id == 0) {
        t1 = MPI_Wtime();
        k = 0;
        v = 12345;

        for (k = 1; k <= k_hi; k++) {
            u = v;
            v = lcrg_evaluate(a, b, c, u); // 5 operations
        }
    }
    lcrg_anbn(a, b, c, p, &an, &bn);

    v = 12345;
    for (j = 1; j <= id; j++) {
        u = v;
        v = lcrg_evaluate(a, b, c, u); // 5 * process_id
    }
    k = id;

    for (k = id + p; k <= k_hi; k = k + p) {
        u = v;
        v = lcrg_evaluate(an, bn, c, u); //5 * 10*process_total/process_id
    }

    if (id == 0) {
        t2 = MPI_Wtime();
        // printf("Time: %9.6lf ms\n", (t2 - t1) * 1000);
        printf("%9.6lf\n", (t2 - t1) * 1000);
    }
    MPI_Finalize();
    return 0;
}
/******************************************************************************/

int congruence(int a, int b, int c, int* error) {
#define N_MAX 100

    int a_copy;
    int a_mag;
    int a_sign;
    int b_copy;
    int b_mag;
    int b_sign;
    int c_copy;
    int g;
    int k;
    int n;
    float norm_new;
    float norm_old;
    int q[N_MAX];
    int swap;
    int temp;
    int x;
    int xnew;
    int y;
    int ynew;
    int z;

    *error = 0;
    x = 0;
    y = 0;

    if (a == 0 && b == 0 && c == 0) {
        x = 0;
        return x;
    } else if (a == 0 && b == 0 && c != 0) {
        *error = 1;
        x = 0;
        return x;
    } else if (a == 0 && b != 0 && c == 0) {
        x = 0;
        return x;
    } else if (a == 0 && b != 0 && c != 0) {
        x = 0;
        if ((c % b) != 0) {
            *error = 2;
        }
        return x;
    } else if (a != 0 && b == 0 && c == 0) {
        x = 0;
        return x;
    } else if (a != 0 && b == 0 && c != 0) {
        x = c / a;
        if ((c % a) != 0) {
            *error = 3;
            return x;
        }
        return x;
    } else if (a != 0 && b != 0 && c == 0) {
        /*  g = i4_gcd ( a, b ); */
        /*  x = b / g; */
        x = 0;
        return x;
    }
    g = i4_gcd(a, b);

    if ((c % g) != 0) {
        *error = 4;
        return x;
    }

    a_copy = a / g;
    b_copy = b / g;
    c_copy = c / g;

    a_mag = abs(a_copy);
    a_sign = i4_sign(a_copy);
    b_mag = abs(b_copy);
    b_sign = i4_sign(b_copy);

    if (a_mag == 1) {
        x = a_sign * c_copy;
        return x;
    } else if (b_mag == 1) {
        x = 0;
        return x;
    }

    if (b_mag <= a_mag) {
        swap = 0;
        q[0] = a_mag;
        q[1] = b_mag;
    } else {
        swap = 1;
        q[0] = b_mag;
        q[1] = a_mag;
    }

    n = 3;

    for (;;) {
        q[n - 1] = (q[n - 3] % q[n - 2]);

        if (q[n - 1] == 1) {
            break;
        }

        n = n + 1;

        if (N_MAX < n) {
            *error = 1;
            printf("\n");
            printf("CONGRUENCE - Fatal error!\n");
            printf("  Exceeded number of iterations.\n");
            exit(1);
        }
    }

    y = 0;
    for (k = n; 2 <= k; k--) {
        x = y;
        y = (1 - x * q[k - 2]) / q[k - 1];
    }

    if (swap == 1) {
        z = x;
        x = y;
        y = z;
    }

    x = x * a_sign;

    x = x * c_copy;

    x = x % b;

    if (x < 0) {
        x = x + b;
    }

    return x;
#undef N_MAX
}
/******************************************************************************/

int i4_gcd(int i, int j) {
    int ip;
    int iq;
    int ir;
    if (i == 0) {
        return i4_max(1, abs(j));
    } else if (j == 0) {
        return i4_max(1, abs(i));
    }
    ip = i4_max(abs(i), abs(j));
    iq = i4_min(abs(i), abs(j));
    for (;;) {
        ir = ip % iq;
        if (ir == 0) break;
        ip = iq;
        iq = ir;
    }
    return iq;
}
/******************************************************************************/

int i4_max(int i1, int i2) { return i2 < i1 ? i1 : i2; }
/******************************************************************************/

int i4_min(int i1, int i2) { return i1 < i2 ? i1 : i2; }

/******************************************************************************/

int i4_sign(int i) { return i < 0 ? -1 : 1; }

/******************************************************************************/

void lcrg_anbn(int a, int b, int c, int n, int* an, int* bn) {
    int am1;
    int anm1tb;
    int ierror;

    if (n < 0) {
        printf("\n");
        printf("LCRG_ANBN - Fatal error!\n");
        printf("  Illegal input value of N = %d\n", n);
        exit(1);
    }

    if (c <= 0) {
        printf("\n");
        printf("LCRG_ANBN - Fatal error!\n");
        printf("  Illegal input value of C = %d\n", c);
        exit(1);
    }

    if (n == 0) {
        *an = 1;
        *bn = 0;
    } else if (n == 1) {
        *an = a;
        *bn = b;
    } else {
        *an = power_mod(a, n, c);
        am1 = a - 1;
        anm1tb = (*an - 1) * b;

        *bn = congruence(am1, c, anm1tb, &ierror);

        if (ierror) {
            printf("\n");
            printf("LCRG_ANBN - Fatal error!\n");
            printf("  An error occurred in the CONGRUENCE routine.\n");
            exit(1);
        }
    }

    return;
}
/******************************************************************************/

int lcrg_evaluate(int a, int b, int c, int x) {
    long long int a8;
    long long int b8;
    long long int c8;
    long long int x8;
    int y;
    long long int y8;

    a8 = (long long int)a;
    b8 = (long long int)b;
    c8 = (long long int)c;
    x8 = (long long int)x;

    y8 = (a8 * x8 + b8) % c8;

    y = (int)(y8);

    if (y < 0) {
        y = y + c;
    }

    return y;
}
/******************************************************************************/

int power_mod(int a, int n, int m) {
    long long int a_square2;
    int d;
    long long int m2;
    int x;
    long long int x2;

    if (a < 0) {
        return -1;
    }

    if (m <= 0) {
        return -1;
    }

    if (n < 0) {
        return -1;
    }

    a_square2 = (long long int)a;
    m2 = (long long int)m;
    x2 = (long long int)1;

    while (0 < n) {
        d = n % 2;

        if (d == 1) {
            x2 = (x2 * a_square2) % m2;
        }

        a_square2 = (a_square2 * a_square2) % m2;
        n = (n - d) / 2;
    }

    while (x2 < 0) {
        x2 = x2 + m2;
    }

    x = (int)x2;

    return x;
}
/******************************************************************************/
