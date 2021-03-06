#include <stdio.h>
#include <string.h>
#include "aes.h"
#include "sha1.h"

#define SDAT_FLAG 0x01000000
#define SDAT_COMPRESSED_FLAG 0x00000001
#define SDAT_FLAG_0x02 0x00000002
#define SDAT_ENCRYPTED_KEY_FLAG 0x00000008
#define SDAT_FLAG_0x10 0x00000010
#define SDAT_FLAG_0x20 0x00000020
#define SDAT_DEBUG_DATA_FLAG 0x80000000

unsigned char SDAT_KEY[] = {0x0D, 0x65, 0x5E, 0xF8, 0xE6, 0x74, 0xA9, 0x8A, 0xB8, 0x50, 0x5C, 0xFA, 0x7D, 0x01, 0x29, 0x33};
unsigned char EDAT_KEY_0[] = {0xBE, 0x95, 0x9C, 0xA8, 0x30, 0x8D, 0xEF, 0xA2, 0xE5, 0xE1, 0x80, 0xC6, 0x37, 0x12, 0xA9, 0xAE};
unsigned char EDAT_HASH_0[] = {0xEF, 0xFE, 0x5B, 0xD1, 0x65, 0x2E, 0xEB, 0xC1, 0x19, 0x18, 0xCF, 0x7C, 0x04, 0xD4, 0xF0, 0x11};
unsigned char EDAT_KEY_1[] = {0x4C, 0xA9, 0xC1, 0x4B, 0x01, 0xC9, 0x53, 0x09, 0x96, 0x9B, 0xEC, 0x68, 0xAA, 0x0B, 0xC0, 0x81};
unsigned char EDAT_HASH_1[] = {0x3D, 0x92, 0x69, 0x9B, 0x70, 0x5B, 0x07, 0x38, 0x54, 0xD8, 0xFC, 0xC6, 0xC7, 0x67, 0x27, 0x47};
unsigned char EDAT_IV[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

typedef struct 
{
	unsigned char magic[4];
    int version;
    int license;
    int type;
    unsigned char content_id[0x30];
    unsigned char digest[0x10];
    unsigned char title_hash[0x10];
    unsigned char dev_hash[0x10];
    unsigned long long unk1;
    unsigned long long unk2;
} NPD_HEADER;

typedef struct 
{
	int flags;
	int block_size;
	unsigned long long file_size;
} SDAT_HEADER;