#include <stdio.h>
#include <stdlib.h>
#include "hblk_crypto.h"


uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]){

	const EC_GROUP *group = NULL;
	const EC_POINT *p = NULL;
	size_t convert;
	if(!key || !pub){
		return NULL;
	}
	group = EC_KEY_get0_group (key);
	p = EC_KEY_get0_public_key (key);
	
	convert = EC_POINT_point2oct(group,p,POINT_CONVERSION_UNCOMPRESSED,pub,EC_PUB_LEN,NULL);
	if(!convert){
		return NULL;
	}
	return pub;
	
}
