#include <stdlib.h>
#include <stdio.h>
#include "hblk_crypto.h"


uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t *sig){

	uint8_t *len = &sig->len;
	if(key == NULL || msg == NULL){
		return NULL;
	}
	*len = ECDSA_size(key);
	if(ECDSA_sign(0,(const unsigned char *)msg,msglen,(unsigned char *)sig,(unsigned int *)len,(EC_KEY*)key)==0){
		return NULL;
	}
	return sig->sig;

}
