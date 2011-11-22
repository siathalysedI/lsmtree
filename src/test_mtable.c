#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mtable.h"
#define L (23)
int main()
{
	int i;
	char k[20]={0};
	struct mtable *tbl=mtable_new(L);

	for(i=1;i<L;i++)
	{
		snprintf(k,20,"key%d",i);
		if(mtable_notfull(tbl))
			mtable_add(tbl,k,i);
		else
			printf("you need a new mtable\n");
	}
	mtable_dump(tbl);

	snprintf(k,20,"key%d",3);
	mtable_remove(tbl,k);
	mtable_dump(tbl);

	mtable_free(tbl);

	return 1;
}
