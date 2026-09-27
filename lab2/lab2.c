#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  size_t size = 0;
  char *line = NULL;

  while (1) {
    printf("Enter Program to Run: ");
    printf("\n");

    ssize_t lineLength = getline(&line, &size, stdin);
    if (lineLength == -1) {
      free(line);
      return 1;
    }

    if (line[lineLength - 1] == '\n') {
      line[lineLength - 1] = '\0';
    }
    pid_t pid = fork();

    if (pid == -1) {
      free(line);
      return 1;
    }
    if (pid == 0) {
      execlp(line, line, NULL);
      printf("Exec failure: \n");
      free(line);
      exit(1);
    }
    if (waitpid(pid, NULL, 0) == -1) {
      free(line);
      return 1;
    }
  }
}
