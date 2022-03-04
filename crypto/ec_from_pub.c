#include <stdio.h>
#include <stdlib.h>
#include"hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]){

	EC_KEY *key;
	const EC_GROUP *group;
	EC_POINT *point=NULL;
	uint8_t convert;
	uint8_t setkey;
	if(!pub){
		return NULL;
	}
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	group = EC_KEY_get0_group(key);
	point = EC_POINT_new(group);
	convert = EC_POINT_oct2point(group,point,pub,EC_PUB_LEN,NULL);
	if(!convert){
		return NULL;
	}
	setkey = EC_KEY_set_public_key(key,point);
	if(!setkey){
		return NULL;
	}
	return key;
}
