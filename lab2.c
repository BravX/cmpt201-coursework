#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int wstatus;

  while (1) {
    printf("Enter programs to run.\n");
    nread = getline(&line, &len, stdin);
    line[nread - 1] = '\0';

    // Fork will create a copy of the running process
    // So that means they want us to run the fork while being able to return to the memory of
    // execution of the parent fork

    pid_t pid = fork();
    // On success the PID of the child process is returned in the parent, and 0 is returned in the
    // child.
    // So I
    if (pid == 0) { // so the child
      execl(line, line, (char *)NULL);
      printf("Exec failure\n");
    }

    else {
      waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
    }
  }

  free(line);

  return 0;
}
