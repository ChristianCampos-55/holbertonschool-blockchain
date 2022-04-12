#include "blockchain.h"

/**
 * get_harshness - bits in hash
 * @hash: buffer
 * Return: harshness
 */
uint32_t get_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH])
{
	uint8_t *ptr = (uint8_t *)hash;
	uint32_t harshness = 0;
	int i;

	for (; ptr < hash + SHA256_DIGEST_LENGTH; ptr++)
	{
		for (i = 7; i >= 0; i--)
		{
			if ((*ptr >> i) & 1)
				return (harshness);
			harshness++;
		}
	}
	return (harshness);
}

/**
* hash_matches_difficulty - checks for hash match
* @hash: hash
* @difficulty: block stifness
* Return: 1 if hash matches difficulty
*/

int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
	uint32_t difficulty)
{
	if (!hash)
		return (0);
	return (get_harshness(hash) >= difficulty);
}
