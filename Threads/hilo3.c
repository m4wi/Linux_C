// suma de numeros de un array

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARR_SIZE 100

// variables globales
int num_threads;
int* arr;
int* thread_rsp;

void* sum (void* argv) {
  int id = *(int*)argv;
  int num_to_sum = ARR_SIZE / num_threads;
  int start = num_to_sum * id;
  int end = num_to_sum + start;

  int sum = 0;

  for (int i = start ; i < end ; i++)
    sum += arr[i];

  thread_rsp[id] = sum;
  printf("El hilo %i ha terminado con el resultado: %i\n", id, sum);
  pthread_exit(0);
}


int main (int argc, char** argv) {
  if (argc != 2) {
    printf("Write only one argument");
    exit(-1);
  }

  num_threads = atoi(argv[1]);
  arr = malloc(sizeof(int) * ARR_SIZE);
  thread_rsp = malloc(sizeof(int) * num_threads);

  for (int i = 1 ; i <= ARR_SIZE ; i++)
    arr[i - 1] = i;
  
  // Threads
  pthread_t threadz[num_threads];
  int id_threadz[num_threads];
  int total = 0;

  for (int i = 0 ; i < num_threads ; i++) {
    id_threadz[i] = i;
    pthread_create(&threadz[i], NULL, sum, (void*)&id_threadz[i]);
  }

  for (int j = 0 ; j < num_threads ; j++) {
    pthread_join(threadz[j], NULL);
    total += thread_rsp[j];
  }

  printf("Resultado de la suma: %i\n", total);
  free(arr);
  free(thread_rsp);
  return 0;
}