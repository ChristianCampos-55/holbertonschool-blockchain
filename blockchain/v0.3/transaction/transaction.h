#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <llist.h>
#include <openssl/sha.h>
#include <time.h>
#include <unistd.h>
#include "blockchain.h"

/**
 * struct transaction_s - trans struct
 * @id:  hash of all the inputs and outputs.
 * @inputs: list of transaction inputs
 * @outputs: list of transaction outputs
 */

typedef struct transaction_s
{
	uint8_t		id[SHA256_DIGEST_LENGTH];
	llist_t		*inputs;
	llist_t		*outputs;
} transaction_t;

/**
 * struct tx_out_s - trans output
 * @amount: received
 * @pub: receiver's address
 * @hash: hash of @amount and @pub
 */

typedef struct tx_out_s
{
	uint32_t	amount;
	uint8_t		pub[EC_PUB_LEN];
	uint8_t		hash[SHA256_DIGEST_LENGTH];
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

/**
 * struct Visitor - collect unspent
 * @sender_unspent: list to collect
 * @sender_pub: pub key
 * @total_amount: unspent curr
 * @amount:to send
 */

typedef struct Visitor
{
	llist_t		*sender_unspent;
	uint8_t		*sender_pub;
	uint64_t	total_amount;
	uint64_t	amount;

} visitor_t;

/**
 * struct Validation_Visitor - validator
 * @in_amount: txi am
 * @out_amount: txo am
 * @valid: 0 if unvalid
 * @all_unspent: unspent tx
 * @tx: to val
 * @block_index: index of tx
 */

typedef struct Validation_Visitor
{
	long	in_amount;
	long	out_amount;
	int		valid;
	llist_t		*all_unspent;
	transaction_t const		*tx;
	uint32_t	block_index;
} validation_vistor_t;

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN]);
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out);
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
llist_t *update_unspent(llist_t *transactions,
	uint8_t block_hash[SHA256_DIGEST_LENGTH], llist_t *all_unspent);

#endif
