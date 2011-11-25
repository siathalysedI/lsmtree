#include <stdlib.h>
#include <stdio.h>
#include "index.h"
#include "debug.h"
#include "util.h"

#define KSIZE (16)
#define VSIZE (20)

#define LOOP (5000000)
#define MAX_MTBL (7)
#define MAX_MTBL_SIZE (300000)

int main()
{
	int i,ret;
	char key[KSIZE];
	char val[VSIZE];

	struct slice sk,sv;

	struct index *idx=index_new("test_idx",MAX_MTBL,MAX_MTBL_SIZE);
	for(i=0;i < LOOP;i++){
		snprintf(key,KSIZE,"key:%d",i);
		snprintf(val,VSIZE,"val:%d",i);

		sk.len=KSIZE;
		sk.data=key;
		sv.len=VSIZE;
		sv.data=val;

		ret=index_add(idx,&sk,&sv);
		if(!ret)
			__DEBUG("%s","Write failed....");
	}

	return 0;

}
