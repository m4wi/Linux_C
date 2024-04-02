#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// other example fork

int main () {
  int value = 0;
  for (int i = 0 ; i < 4 ; i++) {
    int vpid = fork();
    if (vpid != 0) { //dad
      value++;
      break;
    }
    else {  // child
      value += 2;
    }
  }

  printf("Soy el proceso %i y mi padre es el proceso %i , el valor es: %i\n", getpid(), getppid(), value);
  return 0;
}