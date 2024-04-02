#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
  int pipe1[2];
  pipe(pipe1);
  int vfork = fork();
  if (vfork != 0) { // proccess sort
    close(pipe1[1]); // close pipe-read
    close(0); // close stdin
    dup(pipe1[0]);
    close(pipe1[0]);
    close(1);
    open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0755);
    execlp("sort", "sort", "-u", NULL);
    
  } else {

    int pipe2[2];
    pipe(pipe2);

    int vfork2 = fork();
    if (vfork2 != 0) { //proccess cut
      close(pipe2[1]); // close pipe-write
      close(pipe1[0]); // close pipe-read
      close(0); // close stdin
      dup(pipe2[0]); // redirection stdin - pipe[0]
      close(pipe2[0]); // close pipe-write
      close(1);
      dup(pipe1[1]);
      close(pipe1[1]);
      execlp("cut", "cut", "-c5-12", NULL);

    } else { // procces ps
      close(pipe2[0]); // close pipe-read
      close(1); // close stdout
      dup(pipe2[1]);
      close(pipe2[1]);
      execlp("ps", "ps", "-efl", NULL);
    }
  }
  return 0;
}