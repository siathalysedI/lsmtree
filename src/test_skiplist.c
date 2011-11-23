#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "skiplist.h"

#define MAXNUM (10)

int main()
{
	int i,k;
	for(i=0;i<MAXNUM;i++){
		struct skiplist *list=skiplist_new(256);
		for(k=0;k<10;k++)
		{
		char key[KEYSIZE];
		snprintf(key,KEYSIZE,"key:%d",k);
		skiplist_insert(list,key,k,ADD);
		}
		skiplist_dump(list);
		skiplist_free(list);
	}

	return 0;
}
