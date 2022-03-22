#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "common.h"
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


size_t hamming_decode(uint8_t *enc, size_t len, uint8_t *buf) {
	for (size_t idx = 0; idx < (len / 2); idx++) {
		/* In the encoded message we have to concatenate 4 bits from two different bytes. */
		buf[idx] = hamming_7to4(enc[idx * 2]) << 4;
		buf[idx] |= hamming_7to4(enc[idx * 2 + 1]);
	}

	return len / 2;
}

int main(int argc,char** argv) {
	struct l3_msg t;
	init(HOST,PORT);

	uint8_t enc_ph[sizeof(struct l3_msg) * 2];

	/* Receive the encoded message */
	int len = link_recv(&enc_ph, sizeof(enc_ph));
	if (len < 0){
		perror("Receive message");
		return -1;
	}

	hamming_decode(enc_ph, len, (void *) &t);

	int sum_ok = inet_csum((void *) t.payload, t.hdr.len) == t.hdr.sum;

	printf("len=%d; sum(%s)=0x%04hx; payload=\"%s\";\n", t.hdr.len, sum_ok ? "GOOD" : "BAD", t.hdr.sum, t.payload);

	return 0;
}
