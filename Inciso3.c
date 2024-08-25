#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Visual en Mac tira error de declaracion implicita , pero lo deja correr asi que mejor ya no lo toque :p 
//Jorge Palacios 
#define N 20

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int fibonacci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int num = 10;
    int fib_num = 30;
    int arr[N];
    unsigned long long fact_result;
    int fib_result, max_result;

    // Inicializar el arreglo con números aleatorios
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            fact_result = factorial(num);
            printf("Factorial de %d: %llu (calculado por el hilo %d)\n", num, fact_result, omp_get_thread_num());
        }

        #pragma omp section
        {
            fib_result = fibonacci(fib_num);
            printf("Fibonacci número %d: %d (calculado por el hilo %d)\n", fib_num, fib_result, omp_get_thread_num());
        }

        #pragma omp section
        {
            max_result = find_max(arr, N);
            printf("Máximo en el arreglo: %d (encontrado por el hilo %d)\n", max_result, omp_get_thread_num());
        }
    }

    return 0;
}