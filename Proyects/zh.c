/*
  Simple program launcher
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define LONG_PROMPT 15
#define LONG_INPUT 50

int main () {
  char prompt[LONG_PROMPT] = {'$', ' ', '\0'};
  char input[LONG_INPUT];
  while (1) {
    printf("%s", prompt);
    scanf("%s", input);

    int pid = fork();

    if (pid != 0) { // dad
      wait(NULL);
    } else { // child
      execlp(input, input, NULL);
      printf("HUbo un fallo\n");
    }
  }
  return 0;
}