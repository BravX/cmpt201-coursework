#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  while (1) {
    printf("Please enter some text: ");
    nread = getline(&line, &len, stdin);

    char *saveptr;
    char *token = strtok_r(line, " ", &saveptr);
    printf("Tokens: \n");
    while (token != NULL) {
      printf("\t%s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }

  free(line);

  return 0;
}
