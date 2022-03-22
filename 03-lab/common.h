#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "link_emulator/lib.h"

static inline uint8_t hamming_4to7(uint8_t c) {
	uint8_t d1 = (c & 0x8) >> 3;
	uint8_t d2 = (c & 0x4) >> 2;
	uint8_t d3 = (c & 0x2) >> 1;
	uint8_t d4 = c & 0x1;

	uint8_t p1 = d1 ^ d2 ^ d4;
	uint8_t p2 = d1 ^ d3 ^ d4;
	uint8_t p3 = d2 ^ d3 ^ d4;

	uint8_t enc = (p1 << 6) | (p2 << 5) | (d1 << 4) | (p3 << 3) | (d2 << 2) | (d3 << 1) | d1;

	return enc;
}

static inline uint8_t hamming_7to4(uint8_t c) {
	uint8_t d4 = c & 0x1;
	uint8_t d3 = (c & 0x4) >> 1;
	uint8_t d2 = (c & 0x2) >> 2;
	uint8_t d1 = (c & 0x10) >> 4;
	uint8_t r[7];
	for (int i = 0; i < 7; i++) {
		r[i] = (c & (0x1 << i)) >> i;
	}

	uint8_t dec = (d1 << 3) | (d2 << 2) | (d3 << 1) | d4;

	uint8_t z1 = r[0] ^ r[2] ^ r[4] ^ r[6];
	uint8_t z2 = r[1] ^ r[2] ^ r[5] ^ r[6];
	uint8_t z3 = r[3] ^ r[4] ^ r[5] ^ r[6];
	uint8_t z = (z3 << 2) | (z2 << 1) | (z1 << 0);
	if (z > 0) {
		dec ^= (0x1 << (z - 1));
		d4 = dec & 0x1;
	  d3 = (dec & 0x4) >> 1;
	  d2 = (dec & 0x2) >> 2;
	  d1 = (dec & 0x10) >> 4;

		dec = (d1 << 3) | (d2 << 2) | (d3 << 1) | d4;
	}

	return dec;
}

uint16_t inet_csum(uint8_t *buf, size_t len);

/* Layer 3 header */
struct l3_msg_hdr {
	uint16_t len;
	uint16_t sum;
};

/* Layer 3 frame */
struct l3_msg {
	struct l3_msg_hdr hdr;
	/* Data */
	char payload[sizeof(((msg *) NULL)->payload) / 2 - sizeof(struct l3_msg_hdr)];
};
