#include <stdlib.h>
#include <stdio.h>
#include "index.h"
#include "debug.h"

#define KSIZE (16)
#define VSIZE (20)

#define MAX_MTBL (10)
#define MAX_MTBL_SIZE (10)

int main()
{
	int i,ret;
	char key[KSIZE];
	char val[VSIZE];

	struct index *idx=index_new("test_idx",MAX_MTBL,MAX_MTBL_SIZE);
	for(i=0;i<102;i++){
		snprintf(key,KSIZE,"key:%d",i);
		snprintf(val,VSIZE,"val:%d",i);
		ret=index_add(idx,key,KSIZE,val,VSIZE);
		if(ret)
		 	__DEBUG("<%s> Write...key:<%s>,value:<%s>",__FILE__,key,val);
		else
			__DEBUG("%s","Write failed....");
	}

	return 0;

}
