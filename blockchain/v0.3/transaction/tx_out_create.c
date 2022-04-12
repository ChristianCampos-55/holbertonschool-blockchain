#include "transaction.h"

/**
* tx_out_create - create transaction output
* @amount: amount of transaction
* @pub: public key of transaction receiver
* Return: transaction output
*/

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *t = calloc(1, sizeof(*t));

	if (!t)
		return (NULL);

	t->amount = amount;
	memcpy(t->pub, pub, sizeof(t->pub));
	if (!sha256((int8_t const *)t, sizeof(t->amount) + sizeof(t->pub), t->hash))
		return (free(t), NULL);

	return (t);
}
