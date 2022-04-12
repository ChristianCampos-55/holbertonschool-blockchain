#include "transaction.h"


/**
 * empt - is buffer empty?
 * @buf: to check
 * @size: of buffer
 * Return: 0 if not empty
 */

int empt(uint8_t *buf, size_t size)
{
	return (!*buf && !memcmp(buf, buf + 1, size - 1));
}

/**
* coinbase_is_valid - validate trans
* @coinbase: to validate
* @block_index: where its stored
* Return: 1 if valid
*/

int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	uint8_t hash[SHA256_DIGEST_LENGTH];
	tx_in_t *txi;
	tx_out_t *txo;

	if (!coinbase)
		return (0);
	if (!transaction_hash(coinbase, hash) ||
		memcmp(coinbase->id, hash, SHA256_DIGEST_LENGTH))
		return (0);
	if (llist_size(coinbase->inputs) != 1 ||
		llist_size(coinbase->outputs) != 1)
		return (0);
	txi = llist_get_node_at(coinbase->inputs, 0);
	txo = llist_get_node_at(coinbase->outputs, 0);
	if (memcmp(txi->tx_out_hash, &block_index, 4))
		return (0);
	if (!empt(txi->block_hash, sizeof(txi->block_hash)) ||
		!empt(txi->tx_id, sizeof(txi->tx_id)) ||
		!empt((uint8_t *)&txi->sig, sizeof(txi->sig)))
		return (0);
	if (txo->amount != COINBASE_AMOUNT)
		return (0);
	return (1);
}
