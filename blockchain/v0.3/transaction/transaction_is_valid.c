#include "transaction.h"

/**
* matcher - finds unmatches
* @node: curr node
* @args: args vector
* Return: 0 on success
 */
int matcher(llist_node_t node, void *arg)
{
	unspent_tx_out_t *utxo = node;
	tx_in_t *txi = arg;

	if (!memcmp(txi->tx_out_hash, utxo->out.hash, SHA256_DIGEST_LENGTH))
		return (1);
	return (0);
}

/**
* check_inputs - vals input
* @node: curr node
* @idx: @node
* @args: args vector
* Return: 0 on success
*/

int check_inputs(llist_node_t node, unsigned int idx, void *arg)
{
	tx_in_t *txi = node;
	validation_vistor_t *visitor = arg;
	unspent_tx_out_t *utxo =
		llist_find_node(visitor->all_unspent, matcher, txi);
	EC_KEY *key;

	if (!utxo)
	{
		dprintf(2, "check_inputs: utxo NULL\n");
		visitor->valid = 0;
		return (1);
	}
	key = ec_from_pub(utxo->out.pub);
	if (!key ||
		!ec_verify(key, visitor->tx->id, SHA256_DIGEST_LENGTH, &txi->sig))
	{
		dprintf(2, "check_inputs: key error\n");
		visitor->valid = 0;
		return (EC_KEY_free(key), 1);
	}
	EC_KEY_free(key);
	visitor->in_amount += utxo->out.amount;
	return (0);
	(void)idx;
}

/**
* checl_amounts - validates each input
* @node: curr node
* @idx: @node
* @arg: args vector
* Return: 0 on success
*/

int checl_amounts(llist_node_t node, unsigned int idx, void *arg)
{
	tx_out_t *txo = node;
	validation_vistor_t *visitor = arg;

	visitor->out_amount += txo->amount;
	return (0);
	(void)idx;
}

/**
* transaction_is_valid - validate trans
* @transaction: to check
* @all_unspent: unspent check
* Return: 1 if valid
*/

int transaction_is_valid(transaction_t const *transaction,
	llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	validation_vistor_t visitor = {0};

	if (!transaction || !all_unspent)
		return (0);
	visitor.tx = transaction;
	visitor.all_unspent = all_unspent;
	visitor.valid = 1;
	if (!transaction_hash(transaction, hash_buf))
		return (0);
	if (memcmp(transaction->id, hash_buf, SHA256_DIGEST_LENGTH))
		return (0);
	if (llist_for_each(transaction->inputs, check_inputs, &visitor) ||
		!visitor.valid)
		return (0);
	if (llist_for_each(transaction->outputs, checl_amounts, &visitor) ||
		visitor.in_amount != visitor.out_amount || !visitor.in_amount)
	{
		return (0);
	}
	return (1);
}
