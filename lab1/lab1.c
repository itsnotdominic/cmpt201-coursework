#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *lineptr = NULL;
  size_t len = 0;
  printf("Enter a line: \n");
  ssize_t nread = getline(&lineptr, &len, stdin);
  if (nread == -1) {
    free(lineptr);
    perror("getline failed");
    exit(EXIT_FAILURE);
  }
  // printf("%s", lineptr);

  char *saveptr = NULL;
  char *ret = strtok_r(lineptr, " ", &saveptr);

  while (ret != NULL) {
    printf("%s\n", ret);
    ret = strtok_r(NULL, " ", &saveptr);
  }

  free(lineptr);
  return 0;
}
