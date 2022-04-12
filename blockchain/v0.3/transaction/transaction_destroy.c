#include "transaction.h"

/**
* transaction_destroy - del trans
* @transaction: trans to del
*/

void transaction_destroy(transaction_t *transaction)
{
	if (!transaction)
		return;
	llist_destroy(transaction->inputs, 1, NULL);
	llist_destroy(transaction->outputs, 1, NULL);
	free(transaction);
}
