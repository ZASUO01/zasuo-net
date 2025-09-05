#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#define SYNC_BYTES 0x5A415355 // ZASU
#define MAX_DATA_BYTES 1024
#define PACKET_HEADER_BYTES 10

#define PING_FLAG 0x01
#define ACK_FLAG 0x02
#define DATA_FLAG 0x03
#define END_FLAG 0x04

typedef struct {
    uint32_t sync;
    uint8_t flags;
    uint16_t length;
    uint8_t id;
    uint16_t checksum;
    char data[MAX_DATA_BYTES];
} Packet;

int make_packet(Packet *p);
int is_valid_packet(Packet *p);

#endif