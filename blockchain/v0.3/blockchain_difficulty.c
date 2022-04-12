#include "blockchain.h"

/**
* blockchain_difficulty - get new difficulty
* @blockchain: blockchain to get dif from
* Return: difficulty
*/

uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *l_b, *ad_c;
	uint64_t et, at;

	if (!blockchain)
		return (0);

	l_b = llist_get_tail(blockchain->chain);
	if (!l_b)
		return (0);

	if (l_b->info.index == 0 ||
		l_b->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL)
		return (l_b->info.difficulty);

	ad_c = llist_get_node_at(blockchain->chain,
		l_b->info.index + 1 - DIFFICULTY_ADJUSTMENT_INTERVAL);
	et = DIFFICULTY_ADJUSTMENT_INTERVAL * BLOCK_GENERATION_INTERVAL;
	at = l_b->info.timestamp - ad_c->info.timestamp;
	if (at * 2 < et)
		return (l_b->info.difficulty + 1);

	else if (at > 2 * et)
		return (l_b->info.difficulty > 0 ?
			l_b->info.difficulty - 1 : 0);

	return (l_b->info.difficulty);
}
