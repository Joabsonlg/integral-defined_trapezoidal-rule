#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Por enquanto o vetor está sendo alocado estaticamente para fins de teste
// Tem que modificar para alocar dinamicamente de acordo com o número de Threads
// passado pelo usuário
#define NTHREADS 6
double threadsResults[NTHREADS];

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

  nThreads = NTHREADS;

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

  pthread_t threads[nThreads];

  // Criar threads
  for (i = 0; i < nThreads; i++) {
    status = pthread_create(&threads[i], NULL, calcAreaTrap, (void *)(size_t)i);
  }

  // esperando todas as threads terminarem e somando o resultado de cada uma
  for (i = 0; i < nThreads; i++) {
    pthread_join(threads[i], &thread_return);
    result += threadsResults[i];
    printf("Partial result = %lf\n", result);
  }

  printf("Com %d trapézios, %d threads, limite a: %f, limite b: %f o resultado "
         "final é: %f\n",
         nTrapezoids, nThreads, a, b, result);
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

    // local_a = a + nTrapezoids / nThreads * h * (int)(size_t)tid;
    local_a = a + local_n * h * (int)(size_t)tid;
    local_b = b;
  } else {
    // trapezoid number for that thread
    local_n = nTrapezoids / nThreads;

    local_a = a + local_n * h * (int)(size_t)tid;
    local_b = local_a + local_n * h;
  }

  printf("Thread %d: local_n = %d; local_a = %lf ; local_b = %lf\n",
         (int)(size_t)tid, local_n, local_a, local_b);

  // cálculo da área do subconjunto de trapézios da Thread usando a Solução 2 do
  // video
  result = (f1(local_a) + f1(local_b)) / 2.0;

  for (i = 1; i < local_n; i++) {
    int x_i = local_a + i * h;
    result += f1(x_i);
  }

  result = h * result;

  // escrevendo o resultado no vetor
  threadsResults[(int)(size_t)tid] = result;

  sleep(1);
  pthread_exit(NULL);
}

// function 1
double f1(double x) { return 5.0; }

// function 2
double f2(double x) { return (sin(2.0 * x) + cos(5.0 * x)); }