#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Declaração do vetor para armazenar o valor da subárea calculada por cada
// thread
double *threadsResults;

double a, b, h;            // Function limits with b>a
int nThreads, nTrapezoids; // Number of threads and trapezoids

// Calculates the trapezoid area
void *calcAreaTrap(void *tid);

// function 1
double f1(double x);

// function 2
double f2(double x);

int main(int argc, char *argv[]) {

  double result = 0.0; // Result
  int status, i;       // thread creation status and iterator
  void *thread_return; // thread return

  printf("Número de threads:\n");
  scanf("%d", &nThreads);

  printf("Número de trapézios:\n");
  scanf("%d", &nTrapezoids);

  // Atribuindo Valor para a
  a = 0.0;

  // Atribuindo Valor para b
  // b = 2.0 * M_PI;
  b = 10.0;

  // Trapezoid height
  h = (b - a) / nTrapezoids;

  if (nThreads < 1 || nTrapezoids < 1) {
    printf("Entrada inválida!\n");
    return 0;
  }

  // Vetor que armazena o id de cada thread criada
  pthread_t *threads = malloc(nThreads * sizeof(pthread_t));

  // Alocação do vetor para armazenar o valor da subárea calculada por cada
  // thread
  threadsResults = malloc(nThreads * sizeof(double));

  // Criar threads
  for (i = 0; i < nThreads; i++) {
    status = pthread_create(&threads[i], NULL, calcAreaTrap, (void *)(size_t)i);
  }

  // Esperando todas as threads terminarem e somando o resultado de cada uma
  for (i = 0; i < nThreads; i++) {
    pthread_join(threads[i], &thread_return);
    result += threadsResults[i];
    printf("Resultado da Thread %d = %.2e\n", i, threadsResults[i]);
  }

  //Se o zero for negativo a notacao cientifica não é exibida corretamente
  if ((int) result == -0) result = 0.00;

  printf("Com %d trapézios, %d threads, limite a: %.2e, limite b: %.2e o resultado "
         "final é: %.2e\n",
         nTrapezoids, nThreads, a, b, result);

  free(threads);
  free(threadsResults);
  return 0;
}

// Calculates the trapezoid area
void *calcAreaTrap(void *tid) {
  double result;
  double local_a, local_b;
  int i, local_n;

  if ((int)(size_t)tid == nThreads - 1) {
    // trapezoid number for that thread
    local_n = nTrapezoids / nThreads + nTrapezoids % nThreads;

    local_a = a + nTrapezoids / nThreads * h * (int)(size_t)tid;
    local_b = b;
  } else {
    // trapezoid number for that thread
    local_n = nTrapezoids / nThreads;

    local_a = a + local_n * h * (int)(size_t)tid;
    local_b = local_a + local_n * h;
  }

  printf("Thread %d: local_n = %d; local_a = %.2e ; local_b = %.2e\n",
         (int)(size_t)tid, local_n, local_a, local_b);

  // Cálculo da área do subconjunto de trapézios da Thread
  result = (f1(local_a) + f1(local_b)) / 2.0;

  for (i = 1; i < local_n; i++) {
    double x_i = local_a + i * h;
    result += f1(x_i);
  }

  result = h * result;

  // Escrevendo o resultado no vetor em memória compartilhada
  threadsResults[(int)(size_t)tid] = result;

  sleep(1);
  pthread_exit(NULL);
}

// function 1
double f1(double x) { return 5.0; }

// function 2
double f2(double x) { return (sin(2.0 * x) + cos(5.0 * x)); }