#include "blockchain.h"

/**
* tx_to_buffer - copies to buffer
* @tr: trans node
* @idx:  @tr
* @buffer: buffer to copy
* Return: 0
*/

int tx_to_buffer(llist_node_t tr, unsigned int idx, void *buffer)
{
	memcpy((int8_t *)buffer + idx * SHA256_DIGEST_LENGTH,
		   tr, SHA256_DIGEST_LENGTH);
	return (0);
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
	size_t len;
	int list_size;
	int8_t *buffer;

	if (!block)
		return (NULL);
	len = sizeof(block->info) + block->data.len;
	list_size = llist_size(block->transactions);
	if (list_size == -1)
		list_size = 0;
	len += (size_t)(SHA256_DIGEST_LENGTH * list_size);
	buffer = calloc(1, len);
	if (!buffer)
		return (NULL);
	memcpy(buffer, block, sizeof(block->info) + block->data.len);
	llist_for_each(block->transactions, tx_to_buffer,
				   buffer + sizeof(block->info) + block->data.len);
	sha256(buffer, len, hash_buf);
	free(buffer);
	return (hash_buf);
}
