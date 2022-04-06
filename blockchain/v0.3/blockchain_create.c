#include "blockchain.h"

/**
* genesis_block - creates genesis block
* Return: a genesis block or NULL if failed
*/

block_t *genesis_block(void)
{
	block_t *genesis;

	genesis = calloc(1, sizeof(*genesis));
	if (!genesis)
		return (NULL);

	memcpy(genesis->data.buffer, GENESIS_DATA, GENESIS_DATA_LEN);
	genesis->data.len = GENESIS_DATA_LEN;
	*(genesis->data.buffer + GENESIS_DATA_LEN) = '\0';

	memcpy(genesis->hash, GENESIS_HASH, SHA256_DIGEST_LENGTH);
	genesis->info.timestamp = GENESIS_TIMESTAMP;
	return (genesis);
}

/**
* blockchain_create - creates blockchain
* Return: a blockchain
*/

blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain;
	block_t *genesis;

	blockchain = malloc(sizeof(*blockchain));
	if (!blockchain)
		return (NULL);
	genesis = genesis_block();
	if (!genesis)
	{
		free(blockchain);
		return (NULL);
	}
	blockchain->chain = llist_create(MT_SUPPORT_TRUE);
	if (!blockchain->chain)
	{
		free(blockchain), free(genesis);
		return (NULL);
	}
	if (llist_add_node(blockchain->chain, genesis, ADD_NODE_FRONT) == -1)
	{
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain), free(genesis);
		return (NULL);
	}
	return (blockchain);
}
