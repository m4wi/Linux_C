#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int main (int argc, char** argv) {
  if (argc != 2) {
    printf("Write only one argument\n");
    exit(-1);
  }
  struct stat data;
  DIR *dir;
  struct dirent *dp;
  char *file;
  int p1[2], p2[2];

  if (stat(argv[1], &data)) {
    printf("stat failed!\n");
    exit(-1);
  }
  if (!S_ISDIR(data.st_mode)) {
    printf("It isn't a directory\n");
    exit(-1);
  }
  dir = opendir(argv[1]);
  dp = readdir(dir);
  return 0;
}