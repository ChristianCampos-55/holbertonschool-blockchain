#include "transaction.h"

/**
 * in_h - hash ins
 * @node: struct
 * @idx: inode
 * @arg: arg vector
 * Return: 0
 */

int in_h(llist_node_t node, unsigned int idx, void *arg)
{
	memcpy(*(uint8_t **)arg, node, SHA256_DIGEST_LENGTH * 3);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH * 3;
	return (0);
	(void)idx;
}

/**
 * out_h - hash outs
 * @node: struct
 * @idx: inode
 * @arg: arg vector
 * Return: 0
 */

int out_h(llist_node_t node, unsigned int idx, void *arg)
{
	memcpy(*(uint8_t **)arg, ((tx_out_t *)node)->hash, SHA256_DIGEST_LENGTH);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH;
	return (0);
	(void)idx;
}

/**
* transaction_hash - creates trans
* @transaction: unspent trans
* @hash_buf: buffer to store trans
* Return: NULL on failure
*/

uint8_t *transaction_hash(transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	ssize_t len;
	uint8_t *_buf, *buf;

	if (!transaction)
		return (NULL);
	len = SHA256_DIGEST_LENGTH * 3 * llist_size(transaction->inputs)
		+ SHA256_DIGEST_LENGTH * llist_size(transaction->outputs);
	_buf = buf = calloc(1, len);
	if (!_buf)
		return (NULL);
	llist_for_each(transaction->inputs, in_h, &buf);
	llist_for_each(transaction->outputs, out_h, &buf);
	if (!sha256((const int8_t *)_buf, len, hash_buf))
		hash_buf = NULL;
	free(_buf);
	return (hash_buf);
}
