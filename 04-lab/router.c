#include "skel.h"

/* Array of router interfaces (e.g. 0,1,2,3) */
int interfaces[ROUTER_NUM_INTERFACES];

/* Routing table */
struct rtable_entry *rtable;
int rtable_len;

/* Mac table */
struct nei_entry *nei_table;
int nei_table_len;

/*
 Returns a pointer (eg. &rtable[i]) to the best matching route
 for the given protocol and destination address. Or NULL if there is no matching route.
*/
struct rtable_entry *get_best_route(uint16_t proto, struct in_addr dest_ip, struct in6_addr dest_ip6) {
	/* TODO 1: Implement the function. We don't use dest_ip6 at this exercise */
	return NULL;
}

/*
 Returns a pointer (eg. &nei_table[i]) to the best matching neighbor table entry.
 for the given protocol and destination address. Or NULL if there is no matching route.
*/
struct nei_entry *get_nei_entry(uint16_t proto, struct in_addr dest_ip, struct in6_addr dest_ip6) {
    /* TODO 2: Implement the function. We don't use dest_ip6 at this exercise. */
    return NULL;
}

int main(int argc, char *argv[])
{
	msg m;
	int rc;

	init();

	rtable = malloc(sizeof(struct rtable_entry) * 100);
	DIE(rtable == NULL, "memory");

	nei_table = malloc(sizeof(struct  nei_entry) * 100);
	DIE(nei_table == NULL, "memory");
	
	/* Read the static routing table and the MAC table */
	rtable_len = read_rtable(rtable);
	nei_table_len = read_nei_table(nei_table);

	while (1) {
		/* Receives a packet from an interface */
		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
		
		/* Extract the Ethernet header from the packet. Since protocols are stacked, the first header is the ethernet header,
		 * the next header is at m.payload + sizeof(struct ether_header) */
		struct ether_header *eth_hdr = (struct ether_header *) m.payload;

		/* We check if the packet is IPV4. Watch out for the usage of ntohs, why do we need it? Hint: Network Order */
		if (ntohs(eth_hdr->ether_type) == ETHERTYPE_IP) {
			
		}

		/* TODO 3: Check if this is an IPv4 or IPv6 packet and route accordingly. For now we will drop IPv6 packets and forward only IPv4.*/

		/* TODO 4: Check the checksum as required by IPv4  */

		/* TODO 5: Check TTL >= 1 */

		/* TODO 6: Find best matching route (using the function you wrote at TODO 1) */

		/* TODO 7: Find matching neighbour table entry (using the function you wrote at TODO 2)*/

		/* TODO 8: Update TTL and recalculate the checksum */

		/* TODO 9: Update the Ethernet addresses */

		/* TODO 10: Forward the pachet to best_route->interface */
	}
}
