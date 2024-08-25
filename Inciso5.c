#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072
#define THRESHOLD 1024 // Umbral para cambiar a ejecución secuencial

long count_key_parallel(long start, long end, long *a, long key) {
    if (end - start <= THRESHOLD) {
        // Caso base: contar secuencialmente
        long count = 0;
        for (long i = start; i < end; i++) {
            if (a[i] == key) count++;
        }
        return count;
    } else {
        //dividir el trabajo
        long mid = (start + end) / 2;
        long left_count, right_count;
        
        #pragma omp task shared(left_count)
        left_count = count_key_parallel(start, mid, a, key);
        
        #pragma omp task shared(right_count)
        right_count = count_key_parallel(mid, end, a, key);
        
        #pragma omp taskwait
        return left_count + right_count;
    }
}

int main() {
    long a[N], key = 42, nkey = 0;
    
    // Inicialización del arreglo 
    for (long i = 0; i < N; i++) a[i] = rand() % N;
    a[N % 43] = key;
    a[N % 73] = key;
    a[N % 3] = key;
    
    // Conteo paralelo
    #pragma omp parallel
    {
        #pragma omp single
        nkey = count_key_parallel(0, N, a, key);
    }
    
    printf("Numero de veces que 'key' aparece en paralelo: %ld\n", nkey);
    return 0;
}