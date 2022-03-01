#include <stdio.h>
#include <stdlib.h>

int main(int argv, char **argc) {
  char *filename = argc[1];
  FILE *file = fopen(filename, "r");
  int maxline = 100;
  char *buffer = (char *) malloc(maxline * sizeof(char));
  while (fgets(buffer, maxline, file)) {
    printf("%s", buffer);
  }
  free(buffer);
  return 0;
}