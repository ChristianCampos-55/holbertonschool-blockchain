#include "hblk_crypto.h"

/**
* ec_to_pub - get public key from EC_KEY struct
* @key: EC key
* @pub: buffer
* Return: pointer
*/

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *pkey;
	const EC_GROUP *group;

	if (!key || !pub)
		return (NULL);
	pkey = EC_KEY_get0_public_key(key);
	if (!pkey)
		return (NULL);
	group = EC_KEY_get0_group(key);
	if (!group)
		return (NULL);
	if (!EC_POINT_point2oct(group, pkey,
							POINT_CONVERSION_UNCOMPRESSED, pub, EC_PUB_LEN, NULL))
		return (NULL);
	return (pub);
}
