#include "blockchain.h"

/**
* blockchain_destroy - deletes the block
* @blockchain: to delete
*/

void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;
	llist_destroy(blockchain->chain, 1, NULL);
	free(blockchain);
}
