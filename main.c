#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Calculates the trapezoid area
void calcAreaTrap(double a, double b, int n, int t);

int main(int argc, char *argv[]) {

  double result = 0.0;       // Result
  double a, b;               // Function limits with b>a
  int nThreads, nTrapezoids; // Number of threads and trapezoids
  int status, i;             // thread creation status and iterator

  scanf("Número de threads: %d", &nThreads);
  scanf("Número de trapézios: %d", &nTrapezoids);
  scanf("Limete a: %lf", &a);
  scanf("Limite b: %lf", &b);
  if (b <= a || nThreads < 1 || nTrapezoids < 1) {
    printf("Entrada inválida!");
    return 0;
  }

  pthread_t threads[nThreads];

  // Criar threads
  //   for (i = 0; i < nThreads; i++) {
  //       status = pthread_create(&threads[i], NULL, calcAreaTrap, ...);
  //   }

  for (i = 0; i < nThreads; i++) {
    result += threads[i];
  }

  printf("Com %d trapézios e %d threads, a integral de %f em %f = %f",
         nTrapezoids, nThreads, a, b, result);
  return 0;
}

// Calculates the trapezoid area
void calcAreaTrap(double a, double b, int nThreads, int nTrapezoids) {
  double h, result;
  double local_a, local_b;
  int i, local_n;

  // Trapezoid height - for entire rooms only
  h = (b - a) / nTrapezoids;

  // trapezoid number for that thread
  local_n = nTrapezoids / nThreads;

  //   precisa terminar
  //   local_a = a + (local_n * h);
  //   local_b = local_a + local_n * h;

  //   result = (f(local_a) + f(local_b)) / 2.0;

  sleep(1);
  pthread_exit(NULL);
}