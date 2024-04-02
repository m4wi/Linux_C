#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* dumb (void* argv) {
  int new_value = *(int*)argv;
  printf("El nuevo valor es : %i\n", new_value * 5);
  pthread_exit(0);
}


int main () {
  pthread_t thread, thread2;
  int old_value = 5, old_value2 = 10;
  pthread_create(&thread, NULL, dumb, &old_value);
  pthread_create(&thread2, NULL, dumb, &old_value2);
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);
  return 0;
}