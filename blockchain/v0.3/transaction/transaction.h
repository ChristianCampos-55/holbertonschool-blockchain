#ifndef __TRANSACTION_H_
#define __TRANSACTION_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <llist.h>
#include <openssl/sha.h>
#include <time.h>
#include <unistd.h>
#include "../blockchain.h"
#define ALIGN_SIZE(sizeToAlign, PowerOfTwo)       \
        (((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))
#define COINBASE_AMOUNT 50
#define TX_OUT_HASH_LEN (sizeof(uint32_t) + EC_PUB_LEN)
#define TX_IN_HASH_LEN SHA256_DIGEST_LENGTH
#define TX_OUT_HASH_VAL_LEN SHA256_DIGEST_LENGTH
#define TX_IN_HASH_VAL_LEN 3 * SHA256_DIGEST_LENGTH


/**
 * struct transaction_s - trans struct
 * @id:  hash of all the inputs and outputs.
 * @inputs: list of transaction inputs
 * @outputs: list of transaction outputs
 */

typedef struct transaction_s
{
	uint8_t     id[SHA256_DIGEST_LENGTH];
	llist_t     *inputs;
	llist_t     *outputs;
} transaction_t;

/**
 * struct tx_out_s - trans output
 * @amount: received
 * @pub: receiver's address
 * @hash: hash of @amount and @pub
 */

typedef struct tx_out_s
{
	uint32_t    amount;
	uint8_t     pub[EC_PUB_LEN];
	uint8_t     hash[SHA256_DIGEST_LENGTH];
} tx_out_t;

/**
 * struct tx_in_s - Transaction input
 *
 * Description: trans input 
 * @block_hash: block of @tx_id
 * @tx_id: ID of @tx_out_hash
 * @tx_out_hash: hash of output
 * @sig: signature
 */

typedef struct tx_in_s
{
	uint8_t     block_hash[SHA256_DIGEST_LENGTH];
	uint8_t     tx_id[SHA256_DIGEST_LENGTH];
	uint8_t     tx_out_hash[SHA256_DIGEST_LENGTH];
	sig_t       sig;
} tx_in_t;

/**
 * struct unspent_tx_out_s - unspect currency
 * @block_hash: block of @tx_id
 * @tx_id: ID of @tx_out_hash
 * @out: reference of trans
 */

typedef struct unspent_tx_out_s
{
	uint8_t     block_hash[SHA256_DIGEST_LENGTH];
	uint8_t     tx_id[SHA256_DIGEST_LENGTH];
	tx_out_t    out;
} unspent_tx_out_t;

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN]);
unspent_tx_out_t
*unspent_tx_out_create(uint8_t block_hash[SHA256_DIGEST_LENGTH],
										uint8_t tx_id[SHA256_DIGEST_LENGTH],
										tx_out_t const *out);
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent);
uint8_t *transaction_hash(transaction_t const *transaction,
						  uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
				  EC_KEY const *sender, llist_t *all_unspent);
transaction_t *transaction_create(EC_KEY const *sender, EC_KEY const *receiver,
								  uint32_t amount, llist_t *all_unspent);
int transaction_is_valid(transaction_t const *transaction,
						 llist_t *all_unspent);
transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index);
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index);
void transaction_destroy(transaction_t *transaction);
int filter_unspent(llist_node_t node, unsigned int idx, void *args);

#endif
