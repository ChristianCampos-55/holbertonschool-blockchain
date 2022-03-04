#include <stdio.h>
#include <stdlib.h>
#include "hblk_crypto.h"

int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t const *sig){
	
	if(key==NULL || msg ==NULL || sig == NULL){
		return 0;
	}
	if(ECDSA_verify(0,(const unsigned char*)msg,msglen,(unsigned char*)sig,(int)SIG_MAX_LEN,(EC_KEY *)key)==0)
	{
		return 0;
	}
	return 1;
}
