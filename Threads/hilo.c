#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* dumb (void* argv) {
  int new_value = *(int*)argv;
  printf("El nuevo valor es : %i\n", new_value * 5);
  pthread_exit(0);
}


int main () {
  pthread_t thread;
  int old_value = 5;
  pthread_create(&thread, NULL, dumb, &old_value);
  pthread_join(thread, NULL);
  return 0;
}