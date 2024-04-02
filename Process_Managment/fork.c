#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// example fork process

int main () {
  int value = fork();
  if (value != 0) 
    printf("Soy el proceso Padre, mi pid es : %i \n", getpid());
  else
    printf("Soy el proceso Hijo, mi pid es: %i \n", getpid());
  return 0;
}