#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "skiplist.h"
#include "debug.h"

#define MAXNUM (29)
int main()
{
	int k;
	char key[SKIP_KSIZE];
	char val[SKIP_VSIZE];
	struct skiplist *list=skiplist_new(MAXNUM-1);

	for(k=0;k<MAXNUM;k++){
		snprintf(key,SKIP_KSIZE,"key:%d",k);
		snprintf(val,SKIP_VSIZE,"value:%d",k);

		if(skiplist_notfull(list))
			skiplist_insert(list,key,val,ADD);
		else
			__DEBUG("%s","****you need more skiplist...");
	}

	if(MAXNUM<1000)
		skiplist_dump(list);

	skiplist_free(list);
	return 0;
}
