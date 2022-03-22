#include "common.h"
#include <stdio.h>

uint16_t inet_csum(uint8_t *buf, size_t len) {
	register long sum = 0;
	 while( len > 1 )  {
     /*  This is the inner loop */
         sum += *((unsigned short *) buf);
				 (unsigned short *) buf++;
         len -= 2;
	}
	
			/*  Add left-over byte, if any */
	if( len > 0 )
					sum += * (unsigned char *) buf;
	
			/*  Fold 32-bit sum to 16 bits */
	while (sum>>16)
			sum = (sum & 0xffff) + (sum >> 16);
	
	return ~sum;
}
