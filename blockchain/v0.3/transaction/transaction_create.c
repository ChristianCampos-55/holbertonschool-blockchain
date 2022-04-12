#include "transaction.h"

/**
 * cool_unspent - unspent tx
 * @node: curr
 * @idx: node
 * @arg: vector
 * Return: 1 if failed
 */

int cool_unspent(llist_node_t node, unsigned int idx, void *arg)
{
	visitor_t *visitor = arg;
	unspent_tx_out_t *utx = node;

	if (!memcmp(utx->out.pub, visitor->sender_pub, EC_PUB_LEN))
	{
		if (llist_add_node(visitor->sender_unspent, node, ADD_NODE_REAR))
			exit(1);
		visitor->total_amount += utx->out.amount;
		if (visitor->total_amount >= visitor->amount)
			return (0);
	}
	return (0);
	(void)idx;
}

/**
 * mapper - maps output to input txs
 * @node: curr
 * @idx: node
 * @arg: vector
 * Return: 1 if failed
 */

int mapper(llist_node_t node, unsigned int idx, void *arg)
{
	llist_t *inputs = arg;
	unspent_tx_out_t *utx = node;
	tx_in_t *txi = tx_in_create(utx);

	if (!txi)
		exit(1);
	if (llist_add_node(inputs, txi, ADD_NODE_REAR))
		exit(1);
	return (0);
	(void)idx;
}

/**
 * popper - fills struct
 * @sender: key
 * @visitor: struct
 * @all_unspent: tx
 * @sender_pub: key
 * @receiver_pub: key
 * @tx: to fill
 * Return: filled struct
 */

transaction_t *popper(EC_KEY const *sender, visitor_t *visitor,
	llist_t *all_unspent, uint8_t *sender_pub, uint8_t *receiver_pub,
	transaction_t *tx)
{
	ssize_t i;
	tx_out_t *to_receiver, *to_sender;

	tx->inputs = llist_create(MT_SUPPORT_FALSE);
	tx->outputs = llist_create(MT_SUPPORT_FALSE);
	to_receiver = tx_out_create(visitor->amount, receiver_pub);
	to_sender = visitor->total_amount > visitor->amount ?
		tx_out_create(visitor->total_amount - visitor->amount, sender_pub) : 0;

	if (!tx->inputs || !tx->outputs || !to_receiver ||
		(visitor->total_amount > visitor->amount && !to_sender))
		return (llist_destroy(tx->inputs, 1, free),
			llist_destroy(tx->outputs, 1, free), free(tx), NULL);
	llist_for_each(visitor->sender_unspent, mapper, tx->inputs);

	if (llist_add_node(tx->outputs, to_receiver, ADD_NODE_REAR) ||
		(to_sender && llist_add_node(tx->outputs, to_sender, ADD_NODE_REAR)))
		exit(1);
	if (!transaction_hash(tx, tx->id))
		exit(1);

	for (i = 0; i < llist_size(tx->inputs); i++)
	{
		tx_in_t *in = llist_get_node_at(tx->inputs, i);

		if (!tx_in_sign(in, tx->id, sender, all_unspent))
			exit(1);
	}
	/* delete unspent? */
	llist_destroy(visitor->sender_unspent, 0, NULL);
	return (tx);
}

/**
* transaction_create - create trans
* @sender: sender key
* @receiver: receiver key
* @amount: amount to send
* @all_unspent: unspent trans
* Return: a new trans
*/

transaction_t *transaction_create(EC_KEY const *sender, EC_KEY const *receiver,
									uint32_t amount, llist_t *all_unspent)
{
	uint8_t sender_pub[EC_PUB_LEN], receiver_pub[EC_PUB_LEN];
	visitor_t visitor = {0};
	transaction_t *tx;

	if (!sender || !receiver || !amount || !all_unspent)
		return (NULL);

	if (!ec_to_pub(sender, sender_pub) || !ec_to_pub(receiver, receiver_pub))
		return (NULL);

	visitor.sender_unspent = llist_create(MT_SUPPORT_FALSE);
	if (!visitor.sender_unspent)
		return (NULL);

	visitor.amount = amount;
	visitor.sender_pub = sender_pub;
	llist_for_each(all_unspent, cool_unspent, &visitor);
	dprintf(2, "amount: %ld\n", visitor.total_amount);
	if (visitor.total_amount < amount)
		return (llist_destroy(visitor.sender_unspent, 0, NULL), NULL);

	tx = calloc(1, sizeof(*tx));
	if (!tx)
		return (NULL);

	return (popper(sender, &visitor, all_unspent, sender_pub,
		receiver_pub, tx));
}
