#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main (int argc, char** argv) {
  if (argc != 2) {
    printf("Write one only argument\n");
    exit(-1);
  }

  struct stat data;
  char file_type[32];
  if (stat(argv[1], &data) != 0) {
    printf("Fail read file\n");
    exit(-1);
  } // obtener los datos del archivo

  switch (data.st_mode & __S_IFMT) {
  case __S_IFREG:
    strcpy(file_type, "regular");
    break;
  case __S_IFDIR:
    strcpy(file_type, "directorio");
    break;
  case __S_IFLNK:
    strcpy(file_type, "symbolic link");
    break;
  default:
    printf("This file not recognized\n");
    exit(-1);
    break;
  }
  printf("File name:      %s\n", argv[1]);
  printf("type:           %s\n", file_type);
  printf("permissions:    %o\n", data.st_mode & 0777);
  printf("symbolic links: %lu\n", data.st_nlink);
  printf("size:           %lu\n", data.st_size);
  printf("inode:          %lu\n", data.st_ino);
  printf("last accesed:   %s\n", ctime(&data.st_mtime));
  return 0;
}