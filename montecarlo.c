#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define a 0
#define b 10

double function(double x) {
    return exp(-x * x);
}

void approximate_integral(long N, double *I, double *E_fx, double *E_fx2) {
    double sum_fx = 0.0;
    double sum_fx2 = 0.0;
    
    #pragma omp parallel reduction(+:sum_fx, sum_fx2)
    {
        unsigned int seed = (unsigned int) time(NULL) + omp_get_thread_num();
        
        #pragma omp for
        for (long i = 0; i < N; i++) {
            double rand_val = (double)rand_r(&seed) / RAND_MAX;
            double x = a + rand_val * (b - a);
            double fx = function(x);
            sum_fx += fx;
            sum_fx2 += fx * fx;
        }
    }

    *E_fx = sum_fx / N;
    *E_fx2 = sum_fx2 / N;
    *I = (b - a) * (*E_fx);
}

double std_dev(long N, double E_fx, double E_fx2) {
    double variance = E_fx2 - E_fx * E_fx;
    double sigma = sqrt((b - a) * variance);
    return sigma;
}

double calculate_error(long N, double E_fx, double E_fx2) {
    double sigma = std_dev(N, E_fx, E_fx2);
    return sigma / sqrt(N);
}

int main(int argc, char **argv) {
    
    double start = omp_get_wtime();
    
    long N = atoi(argv[1]);
    char *env = getenv("OMP_NUM_THREADS");
    int number_of_threads = atoi(env);
    omp_set_num_threads(number_of_threads);


    double I, E_fx, E_fx2;
    approximate_integral(N, &I, &E_fx, &E_fx2);

    double error = calculate_error(N, E_fx, E_fx2);

    double end = omp_get_wtime();
    double run_time = end - start;

    printf("%.6f\n", I);
    printf("%.6f\n", error);
    printf("%.6f\n", run_time);

    return 0;
}