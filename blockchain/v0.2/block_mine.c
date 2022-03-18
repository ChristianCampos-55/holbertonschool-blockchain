#include "blockchain.h"

/**
* block_mine - mines
* @block: block to mine
*/

void block_mine(block_t *block)
{
	block->info.nonce = 0;
	do {
		++block->info.nonce;
		if (!block_hash(block, block->hash))
			return;
	} while (hash_matches_difficulty(block->hash, block->info.difficulty) == 0);
}
