#ifndef __BLOCKCHAIN_H_
#define __BLOCKCHAIN_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <llist.h>
#include <openssl/sha.h>
#include <time.h>
#include <unistd.h>
#include "../../crypto/hblk_crypto.h"
#include "transaction.h"
#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
#define GENESIS_DATA "Holberton School"
#define GENESIS_TIMESTAMP 1537578000
#define GENESIS_DATA_LEN 16
#define UNUSED(x) (void)(x)
#define BLOCK_GENERATION_INTERVAL 1
#define DIFFICULTY_ADJUSTMENT_INTERVAL 5


/**
 * struct blockchain_s - Block struct
 * @chain: pointers to block_t
 */

typedef struct blockchain_s
{
	llist_t     *chain;
} blockchain_t;

#define BLOCKCHAIN_DATA_MAX 1024

/**
 * struct block_data_s - data
 * @buffer: buffer
 * @len: size
 */

typedef struct block_data_s
{
	int8_t      buffer[BLOCKCHAIN_DATA_MAX];
	uint32_t    len;
} block_data_t;

/**
 * struct block_info_s - structure
 * @index: block in the chain
 * @difficulty: proof of work
 * @timestamp: time of creation
 * @nonce: alter block
 * @prev_hash: prev block in chain
 */ 

typedef struct block_info_s
{
	uint32_t    index;
	uint32_t    difficulty;
	uint64_t    timestamp;
	uint64_t    nonce;
	uint8_t     prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

/**
 * struct block_s - structure
 * @info: info
 * @data: data
 * @hash: 256-bit digest
 */

typedef struct block_s
{
	block_info_t    info;
	block_data_t    data;
	llist_t     *transactions;
	uint8_t     hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
 * struct hblk_file_s - format
 *
 * @hblk_magic: magic bytes
 * @hblk_version: version
 * @hblk_endian: endianness
 * @hblk_blocks: number of blocks
 */

typedef struct hblk_file_s
{
	uint8_t hblk_magic[4];
	uint8_t hblk_version[3];
	uint8_t hblk_endian;
	int32_t hblk_blocks;
} hblk_file_t;

blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev,
					  int8_t const *data, uint32_t data_len);
void block_destroy(block_t *block);
void blockchain_destroy(blockchain_t *blockchain);
uint8_t *block_hash(block_t const *block,
					uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);
blockchain_t *blockchain_deserialize(char const *path);
int block_is_valid(block_t const *block, block_t const *prev_block);
uint8_t _get_endianness(void);
void _swap_endian(void *p, size_t size);
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
							uint32_t difficulty);
int block_is_valid(block_t const *block, block_t const *prev_block);
void block_mine(block_t *block);
uint32_t blockchain_difficulty(blockchain_t const *blockchain);

#endif
