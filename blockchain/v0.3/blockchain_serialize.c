#include "blockchain.h"

/**
* write_block - writes a single block
* @ptr: pointer
* @idx: index
* @arg: file
* Return: 0 if successful
*/

int write_block(llist_node_t ptr, unsigned int idx, void *arg)
{
	FILE *fp;
	block_t *block = ptr;

	UNUSED(idx);
	if (!arg || !ptr)
		return (-1);
	fp = (FILE *)arg;
	fwrite((void *)&block->info, sizeof(block->info), 1, fp);
	fwrite((void *)&block->data.len, sizeof(block->data.len), 1, fp);
	fwrite(block->data.buffer, block->data.len, 1, fp);
	fwrite(block->hash, sizeof(block->hash), 1, fp);
	return (0);
}

/**
* blockchain_serialize - writes a blockchain
* @blockchain: blockchain
* @path: file
* Return: 0 if successful
*/

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	hblk_file_t header;
	FILE *fp;

	if (!blockchain || !path)
		return (-1);

	memcpy(header.hblk_magic, "HBLK", 4);
	memcpy(header.hblk_version, "0.3", 3);
	header.hblk_endian = _get_endianness();
	header.hblk_blocks = llist_size(blockchain->chain);
	if (header.hblk_blocks == -1)
		return (-1);
	fp = fopen(path, "w");
	if (!fp)
		return (-1);
	fwrite(&header, sizeof(header), 1, fp);
	if (llist_for_each(blockchain->chain, write_block, fp) == -1)
	{
		fclose(fp);
		return (-1);
	}
	fclose(fp);
	return (0);
}
