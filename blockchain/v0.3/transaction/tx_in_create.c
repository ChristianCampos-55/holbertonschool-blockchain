#include "transaction.h"

/**
* tx_in_create - creates an input
* @unspent: unspent trnas pointer
* Return: trans input
*/

tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *txi;

	if (!unspent)
		return (NULL);

	txi = calloc(1, sizeof(*txi));
	if (!txi)
		return (NULL);

	memcpy(txi->block_hash, unspent->block_hash, sizeof(txi->block_hash));
	memcpy(txi->tx_id, unspent->tx_id, sizeof(txi->tx_id));
	memcpy(txi->tx_out_hash, unspent->out.hash, sizeof(txi->tx_out_hash));

	return (txi);
}
