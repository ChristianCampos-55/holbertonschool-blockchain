#include "hblk_crypto.h"

/**
* sha256 - find hash value (digest) of a sequence of bytes
* @s: byte sequence
* @len: lenght of @s
* @digest: buffer to store the digest
* Return: digest or NULL if failed
*/
uint8_t *sha256(int8_t const *s,
				size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!s || !digest)
		return (NULL);
	return (SHA256((void *)s, len, digest));
}
