#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  char *lineptr = NULL, *saveptr1, *token;
  size_t n = 0;
  const char delim = ' ';
  printf("Please enter some text: ");
  getline(&lineptr, &n, stdin);
  printf("Tokens: \n");
  token = strtok_r(lineptr, &delim, &saveptr1);
  while (token) {
    printf("%s\n", token);
    token = strtok_r(NULL, &delim, &saveptr1);
  }
  free(lineptr);

  return 0;
}
