#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displace(char *arr[5], char *line) {
  free(arr[0]);
  arr[0] = arr[1];
  arr[1] = arr[2];
  arr[2] = arr[3];
  arr[3] = arr[4];
  arr[4] = strdup(line);
}

int main() {

  char *arr[5] = {0};
  int count = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  while (1) {
    printf("Enter input: ");

    nread = getline(&line, &len, stdin);

    if (nread == -1)
      break;
    if (nread > 0 && line[nread - 1] == '\n')
      line[nread - 1] = '\0';

    displace(arr, line);

    if (count < 5)
      count++;

    if (strcmp(line, "print") == 0) {
      for (int i = 5 - count; i < 5; i++) {
        printf("%s\n", arr[i]);
      }
    }
  }

  for (int i = 0; i < 5; i++)
    free(arr[i]);
  free(line);

  return 0;
}
// 1. Read user input from the keyboard line by line
//
// 2. Store 5 last lines inputted from the user
//
// 3. When user enters command print, then print the 5 lines
