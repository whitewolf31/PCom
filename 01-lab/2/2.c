#include <stdio.h>
#include <stdlib.h>

typedef struct Packet {
  char  payload[100];
  int   sum;
  int   size;
} Packet;

int main() {
  FILE *file;
  file = fopen("ex3", "rb");
  fseek(file, 0, SEEK_END);
  long filelen = ftell(file);
  rewind(file);
  long arrLen = filelen / sizeof(Packet);
  Packet* packets = (Packet *) malloc(arrLen * sizeof(Packet));
  fread(packets, arrLen, sizeof(Packet), file);
  fclose(file);
  for (int i = 0; i < arrLen; i++) {
    printf("%s\n", packets[i].payload);
  }
  free(packets);

  return 0;
}