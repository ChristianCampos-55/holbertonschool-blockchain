#include "transaction.h"

/**
* unspent_tx_out_create - creates unspent trans
* @block_hash: hash of @tx_id
* @tx_id: ID of @out
* @out: copy of trans
* Return: unspent trans
*/
unspent_tx_out_t *unspent_tx_out_create(uint8_t
										block_hash[SHA256_DIGEST_LENGTH],
										uint8_t tx_id[SHA256_DIGEST_LENGTH],
										tx_out_t const *out)
{
	unspent_tx_out_t *utx = calloc(1, sizeof(*utx));

	if (!utx)
		return (NULL);
	memcpy(utx->block_hash, block_hash, sizeof(utx->block_hash));
	memcpy(utx->tx_id, tx_id, sizeof(utx->tx_id));
	memcpy(&utx->out, out, sizeof(utx->out));

	return (utx);
}
