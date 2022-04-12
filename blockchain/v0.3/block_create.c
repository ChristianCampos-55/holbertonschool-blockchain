#include "blockchain.h"

/**
* block_create - creates a block
* @prev: previous
* @data: new data
* @data_len: length
* Return: a new block
*/

block_t *block_create(block_t const *prev, int8_t const *data,
					  uint32_t data_len)
{
	block_t *block = calloc(1, sizeof(*block));
	llist_t *transactions = llist_create(MT_SUPPORT_FALSE);

	if (!block || !transactions)
		return (free(block), llist_destroy(transactions, 0, NULL), NULL);

	memcpy(&(block->data.buffer), data, MIN(data_len, BLOCKCHAIN_DATA_MAX));
	block->data.len = MIN(data_len, BLOCKCHAIN_DATA_MAX);
	block->info.index = prev->info.index + 1;
	block->info.timestamp = time(NULL);
	block->transactions = transactions;
	memcpy(&(block->info.prev_hash), prev->hash, SHA256_DIGEST_LENGTH);

	return (block);
}
