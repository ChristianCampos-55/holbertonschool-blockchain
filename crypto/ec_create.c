#include<stdio.h>
#include<stdlib.h>
#include "hblk_crypto.h"

EC_KEY *ec_create(void){
	
	uint8_t generated_key;
	
	EC_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE);
	if(key == NULL){
		return NULL;
	}
	generated_key = EC_KEY_generate_key(key);
	if(generated_key != 1){
		fprintf(stderr, "error during the creation of the key");
		return NULL;
	}
	return key;
	
}
