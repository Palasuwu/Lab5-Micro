#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    long long shared_var = 0;
    long long private_var = 0;
    int i;

    #pragma omp parallel for shared(shared_var) private(private_var)
    for (i = 0; i < N; i++) {
        shared_var += i;
        private_var += i;
    }

    printf("Valor final de shared_var: %lld\n", shared_var);
    printf("Valor final de private_var: %lld\n", private_var);

    return 0;
}