#include "hblk_crypto.h"

/**
* ec_sign - msg with EC_KEY pair
* @key: key pair
* @msg: sign
* @msglen: message length
* @sig: sign
* Return: buffer
*/

int ec_verify(EC_KEY const *key, uint8_t const *msg,
				 size_t msglen, sig_t const *sig)
{
	if (!key || !msg || !sig)
		return (0);
	if (ECDSA_verify(0, msg, (int)msglen,
					  sig->sig, sig->len, (EC_KEY *)key) < 1)
		return (0);
	return (1);
}
