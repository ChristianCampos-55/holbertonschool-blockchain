#include "transaction.h"

/**
* tx_out_create - create transaction output
* @amount: amount of transaction
* @pub: public key of transaction receiver
* Return: transaction output
*/

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *trans;

	if (!pub)
		return (NULL);
	trans = calloc(1, sizeof(*trans));
	if (!trans)
		return (NULL);
	trans->amount = amount;
	memcpy(trans->pub, pub, EC_PUB_LEN);
	if (!sha256((const int8_t *)trans, TX_OUT_HASH_LEN, trans->hash))
	{
		free(trans);
		return (NULL);
	}
	return (trans);
}
