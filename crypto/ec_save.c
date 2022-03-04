#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "hblk_crypto.h"

int ec_save(EC_KEY *key, char const *folder){
	char pub_path[PATH_MAX];
	char pv_path[PATH_MAX];
	FILE *fpub;
	FILE *fpriv;
	char separ ='/';

	if(!key){
		return 0;
	}
	if(opendir(folder))
	{
		fprintf(stderr,"%s","folder EXISTS\n");	
	}
	else if(ENOENT == errno)
	{
		if(mkdir(folder,0777)==-1)
		{
			fprintf(stderr,"%s","ERROR creating directory\n");
			return 0;
		}
		else
		{	
			fprintf(stderr,"%s","Directory successfully created\n");
		}
	}
	else
	{
		fprintf(stderr,"%s","opendir failed\n");
	}	
	snprintf(pub_path, PATH_MAX + 1, "%s%c%s", folder,separ,PUB_FILENAME);
	snprintf(pv_path,PATH_MAX + 1,"%s%c%s",folder,separ,PRI_FILENAME);

	fpub = fopen(pub_path,"w+");
        fpriv = fopen(pv_path, "w+");
	
	if(PEM_write_EC_PUBKEY(fpub, key) == 0)
	{
		fclose(fpub);
		fclose(fpriv);
		return 0;
	}
	if(PEM_write_ECPrivateKey(fpriv, key, NULL, NULL, 0, NULL, NULL) == 0)
	{
		fclose(fpub);
		fclose(fpriv);
		return 0;

	}

	fclose(fpub);
	fclose(fpriv);
	return 1;
}
