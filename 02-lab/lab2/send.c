#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

/* We don't touch this */
#define HOST "127.0.0.1"
#define PORT 10000

#define DLE (char)0
#define STX (char)2
#define ETX (char)3

/* TODO 2: implement send_frame function */
void send_frame(void* packet, int size) {
	send_byte(DLE);
	send_byte(STX);

	for (int i = 0; i < size; i++) {
		char current_byte = (char) *((char *) packet + i);
		send_byte(current_byte);
		if (current_byte == DLE) {
			send_byte(DLE);
		}
	}

	send_byte(DLE);
	send_byte(ETX);
}

int main(int argc,char** argv){
	init(HOST,PORT);

	/* Send Hello */
	// send_byte(DLE);
	// send_byte(STX);
	// send_byte('H');
	// send_byte('e');
	// send_byte('l');
	// send_byte('l');
	// send_byte('o');
	// send_byte('!');

	/* TODO 2: call send_frame function with a given string input */
	Packet *packet = (Packet *) malloc(sizeof(Packet));
	packet->size = 12;
	strcpy(packet->payload, "Hello There!");
	packet->sum = 12;

	/* TODO 3: use send_frame to send a structure of type Packet */
	send_frame(packet, sizeof(Packet));

	/* TODO 4: send 100 bytes, send 300 bytes, append a timestamp to these frames */	
	struct timeval current;
	gettimeofday(&current, 0);
	SmallPacket *packet1 = (SmallPacket *) malloc(sizeof(SmallPacket));
	packet1->timestamp = current;
	strcpy(packet1->payload, "This is the first payload");
	send_frame(packet1, sizeof(SmallPacket));
	BigPacket *packet2 = (BigPacket *) malloc(sizeof(BigPacket));
	packet2->timestamp = current;
	strcpy(packet2->payload, "This is the second payload");
	send_frame(packet2, sizeof(BigPacket));
	
	return 0;
}
