#ifndef LIB
#define LIB

#define MAX_LEN 1400

#include <sys/time.h>

typedef struct {
  // int type;
  int len;
  char payload[MAX_LEN];
} msg;

typedef struct {
  int size;
  char payload[30];
  int sum;
} Packet;

typedef struct {
  struct timeval timestamp;
  char payload[100];
} SmallPacket;

typedef struct {
  struct timeval timestamp;
  char payload[300];
} BigPacket;


void init(char* remote,int remote_port);
void set_local_port(int port);
void set_remote(char* ip, int port);
int send_message(const msg* m);
int recv_message(msg* r);
int send_byte(char c);
char recv_byte();

//msg* receive_message_timeout(int timeout);

#endif

