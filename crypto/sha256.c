#include "hblk_crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest
				[SHA256_DIGEST_LENGTH]) {

	if (digest == NULL)
	{
		return (NULL);
	}
	else
	{
		return ((uint8_t *)SHA256((unsigned char *)s, len, (unsigned char *)digest));
	}
}
