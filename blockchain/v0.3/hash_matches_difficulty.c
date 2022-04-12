#include "blockchain.h"

/**
* hash_matches_difficulty - checks for hash match
* @hash: hash
* @difficulty: block stifness
* Return: 1 if hash matches difficulty
*/

int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
							uint32_t difficulty)
{
	uint32_t i, mod;

	mod = difficulty & 7;
	difficulty -= mod;
	difficulty /= 8;
	for (i = 0; i < difficulty; ++i)
	{
		if (hash[i] != 0)
			return (0);
	}
	if (hash[difficulty] >> (8 - mod))
		return (0);
	return (1);
}
