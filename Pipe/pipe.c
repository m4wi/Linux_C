#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


/*
  File Descriptors
  0 -> stdin
  1 -> stdout
  2 -> stderr
  3 -> pipe[0] - read
  4 -> pipe[1] - write
*/

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Write one argument\n");
    exit(-1);
  }
  // define pipe
  int pipe1[2];
  pipe(pipe1);
  int vpid = fork();
  char buffer[64];

  if (vpid != 0) // dad - read
  {
    close(pipe1[1]);
    read(pipe1[0], buffer, 64);
    close(pipe1[0]);
    close(1);
    open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0755);
    printf("El padre acaba de Leer: %s\n", buffer);
  }
  else // child - write
  {
    strcpy(buffer, "Sistemas Operativos");
    close(pipe1[0]);
    write(pipe1[1], buffer, strlen(buffer));
    close(pipe1[1]);
    printf("El Hijo Escribio: %s\n", buffer);
  }

  return 0;
}