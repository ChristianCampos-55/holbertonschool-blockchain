#include "blockchain.h"

/**
* tx_to_buffer - copies to buffer
* @tr: trans node
* @idx:  @tr
* @arg: argument vector
* Return: 0
*/

int hash_tx_ids(llist_node_t node, unsigned int idx, void *arg)
{
	memcpy(*(uint8_t **)arg, ((transaction_t *)node)->id,
	SHA256_DIGEST_LENGTH);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH;

	return (0);
	(void)idx;
}


/**
* block_hash - hash of a block
* @block: block to hash
* @hash_buf: digest
* Return: hash digest
*/

uint8_t *block_hash(block_t const *block,
					uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t len0 = sizeof(block->info) + block->data.len, len;
	int8_t *_buf, *buf;

	len = len0;
	if (llist_size(block->transactions) > 0)
		len += llist_size(block->transactions) * SHA256_DIGEST_LENGTH;
	buf = _buf = calloc(1, len);
	if (!buf)
		return (NULL);

	memcpy(buf, &block->info, len0);
	buf += len0;
	llist_for_each(block->transactions, hash_tx_ids, &buf);
	sha256(_buf, len, hash_buf);
	free(_buf);

	return (hash_buf);
}
