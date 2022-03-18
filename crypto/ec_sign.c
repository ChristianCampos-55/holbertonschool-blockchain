#include "hblk_crypto.h"

/**
* ec_sign - msg with EC_KEY pair
* @key: key pair
* @msg: sign
* @msglen: message length
* @sig: sign
* Return: buffer
*/

uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
				 size_t msglen, sig_t *sig)
{
	uint32_t len = 0;

	if (!key || !msg || !msglen)
		return (NULL);

	memset(sig->sig, 0, sizeof(sig->sig));
	if (!ECDSA_sign(0, msg, (int)msglen, sig->sig, &len, (EC_KEY *)key))
	{
		sig->len = 0;
		return (NULL);
	}
	sig->len = (uint8_t)len;
	return (sig->sig);
}
