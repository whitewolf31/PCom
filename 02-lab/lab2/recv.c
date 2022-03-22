#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"
#include <sys/time.h>

#define HOST "127.0.0.1"
#define PORT 10001
#define MAX_LEN 1000

#define DLE (char)0
#define STX (char)2
#define ETX (char)3

/* TODO 2: write recv_frame function */
void* recv_frame() {
  char c1,c2;
  do {
    c1 = recv_byte();
    c2 = recv_byte();
  } while(c1 != DLE || c2 != STX);

  char *buffer = (char *) malloc(MAX_LEN);

  c2 = recv_byte();
  int i = 0;

  while (1) {
    c1 = c2;
    c2 = recv_byte();
    if (c1 == DLE && c2 == ETX) break;
    if (c1 == DLE && c2 == DLE) {
      c2 = recv_byte();
    }
    buffer[i++] = c1;
  }
  void *received_frame = (void *) malloc(i - 1);
  memcpy(received_frame, buffer, i - 1);
  return received_frame;
}


int main(int argc,char** argv){
  init(HOST,PORT);
  

  char c;

  /* Wait for the start of a frame */
  // char c1,c2;
  // do {
	// c1 = recv_byte();
	// c2 = recv_byte();
  // } while(c1 != DLE || c2 != STX);
  
  // printf("%d ## %d\n",c1, c2);
  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  /* TODO 2: Run the receiver until you receive the frame DONE */

  /* TODO 3: receive a frame with a structure of type Packet */
  Packet* packet = (Packet *) recv_frame();
  printf("Receive Packet of length %d\n", packet->size);
  printf("Packet payload: %s\n", packet->payload);
  printf("Packet sum: %d\n", packet->sum);
  struct timeval current;
  gettimeofday(&current, 0);
  SmallPacket* packet1 = (SmallPacket *) recv_frame();
  printf("Received Packet: %s\n", packet1->payload);
  double elapsed = (current.tv_sec - packet1->timestamp.tv_sec) + (current.tv_usec - packet1->timestamp.tv_usec)*1e-6;
  printf("Elapsed %f seconds\n", elapsed); 
  gettimeofday(&current, 0);
  BigPacket* packet2 = (BigPacket *) recv_frame();
  printf("Received Packet: %s\n", packet2->payload);
  elapsed = (current.tv_sec - packet2->timestamp.tv_sec) + (current.tv_usec - packet2->timestamp.tv_usec)*1e-6;
  printf("Elapsed %f seconds\n", elapsed); 
  /* TODO 4: Measure latency in a while loop for any frame that contains a timestamp we receive, print frame_size and latency */

  printf("[RECEIVER] Finished transmission\n");
  return 0;
}
