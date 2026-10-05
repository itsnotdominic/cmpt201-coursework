
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_history(char *history[], char *line) {
  free(history[0]);
  for (int i = 0; i < 4; i++) {
    history[i] = history[i + 1];
  }
  history[4] = line;
}

void print_history(char *history[]) {
  for (int i = 0; i < 5; i++) {
    if (history[i] != NULL) {
      printf("%s\n", history[i]);
    }
  }
}

int main(void) {
  char *history[5] = {NULL};
  char *line = NULL;
  size_t size = 0;

  while (getline(&line, &size, stdin) != -1) {
    line[strcspn(line, "\n")] = '\0';
    add_history(history, line);

    if (strcmp(line, "print") == 0) {
      print_history(history);
    }
    line = NULL;
    size = 0;
  }
  free(line);
  for (int i = 0; i < 5; i++) {
    free(history[i]);
  }
  return 0;
}
